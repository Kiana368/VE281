#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>

/**
 * An abstract template base of the KDTree class
 */
template<typename...>
class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template<typename ValueType, typename... KeyTypes>
class KDTree<std::tuple<KeyTypes...>, ValueType> {
public:
    typedef std::tuple<KeyTypes...> Key;
    typedef ValueType Value;
    typedef std::pair<const Key, Value> Data;
    static inline constexpr size_t KeySize = std::tuple_size<Key>::value;
    static_assert(KeySize > 0, "Can not construct KDTree with zero dimension");
protected:
    struct Node {
        Data data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Key &key, const Value &value, Node *parent) : data(key, value), parent(parent) {}

        const Key &key() { return data.first; }

        Value &value() { return data.second; }
    };

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator {
    private:
        KDTree *tree;
        Node *node;

        Iterator(KDTree *tree, Node *node) : tree(tree), node(node) {}

        /**
         * Increment the iterator
         * Time complexity: O(log n)
         * When a increment occurs, if the current node has a right subtree,
         * the next node should be the left most leaf in the right subtree;
         * otherwise (if the current node doesn’t have a right subtree),
         * you should move up (by parent pointer) and find the first ancestor node so that the current node is in
         * the left subtree of the ancestor node.
         * When you increment the right most leaf node in the tree, you’ll find that the
         * node is not in any of its ancestors’ left subtree, so you should end the loop and set the next node as nullptr.
         */
        void increment() {
            // TODO: implement this function
            // undefined behavior: end()
            if (node== nullptr) return;
            // if current node has a right subtree
            if (node->right){
                node=node->right;
                while (node->left) node=node->left;
            }else{
                // if current node does not have a right subtree
                while (node->parent) {
                    if (node->parent->left==node) {
                        node=node->parent;
                        return;
                    }
                    node=node->parent;
                }
                // if current node is the right most leaf node in the tree
                node= nullptr;
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        void decrement() {
            // TODO: implement this function
            // if current node is end()
            if (node== nullptr) {
                node=tree->root;
                while (node->right) node=node->right;
                return;
            }
            // if current node has a left subtree
            if (node->left){
                node=node->left;
                while (node->right) node=node->right;
            }else{
                // if current node does not have a left subtree
                while (node->parent) {
                    if (node->parent->right==node) {
                        node=node->parent;
                        return;
                    }
                    node=node->parent;
                }
                // if current node is the left most leaf node in the tree
                node= nullptr;
            }
        }

    public:
        friend class KDTree;

        Iterator() = delete;

        Iterator(const Iterator &) = default;

        Iterator &operator=(const Iterator &) = default;

        Iterator &operator++() {
            increment();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            increment();
            return temp;
        }

        Iterator &operator--() {
            decrement();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            decrement();
            return temp;
        }

        bool operator==(const Iterator &that) const {
            return node == that.node;
        }

        bool operator!=(const Iterator &that) const {
            return node != that.node;
        }

        Data *operator->() {
            return &(node->data);
        }

        Data &operator*() {
            return node->data;
        }
    };

protected:                      // DO NOT USE private HERE!
    Node *root = nullptr;       // root of the tree
    size_t treeSize = 0;        // size of the tree

    /**
     * Find the node with key
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param node
     * @return the node with key, or nullptr if not found
     */
    template<size_t DIM>
    Node *find(const Key &key, Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node== nullptr) return nullptr;
        if (key==node->key()) return node;
        if (std::get<DIM>(key) < std::get<DIM>(node->key()))
            return find<DIM_NEXT>(key,node->left);
        else
            return find<DIM_NEXT>(key,node->right);
    }

    /**
     * Insert the key-value pair, if the key already exists, replace the value only
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param value
     * @param node
     * @param parent
     * @return whether insertion took place (return false if the key already exists)
     */
    template<size_t DIM>
    bool insert(const Key &key, const Value &value, Node *&node, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node== nullptr){
            // create a node
            node= new Node(key, value, parent);
            ++treeSize;
            return true;
        }
        if (key==node->key()) {
            // update the value of the node
            node->value()=value;
            return false;
        }
        if (std::get<DIM>(key) < std::get<DIM>(node->key())){
            insert<DIM_NEXT>(key, value, node->left, node);
        }
        else {
            insert<DIM_NEXT>(key, value, node->right, node);
        }
        return false;
    }

    /**
     * Compare two keys on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return relationship of two keys on a dimension with the compare function
     */
    template<size_t DIM, typename Compare>
    static bool compareKey(const Key &a, const Key &b, Compare compare = Compare()) {
        if (std::get<DIM>(a) != std::get<DIM>(b)){
            return compare(std::get<DIM>(a), std::get<DIM>(b));
        }
        return compare(a, b);
    }

    /**
     * Compare two nodes on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return the minimum / maximum of two nodes
     */
    template<size_t DIM, typename Compare>
    static Node *compareNode(Node *a, Node *b, Compare compare = Compare()) {
        if (!a) return b;
        if (!b) return a;
        return compareKey<DIM, Compare>(a->key(), b->key(), compare) ? a : b;
    }

    /**
     * Find the minimum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the minimum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMin(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node== nullptr) return nullptr;
        Node *min=findMin<DIM_CMP, DIM_NEXT>(node->left);
        if(DIM_CMP!=DIM){
            Node *rightMin=findMin<DIM_CMP, DIM_NEXT>(node->right);
            min=compareNode<DIM_CMP, std::less<>>(min, rightMin);
        }
        return compareNode<DIM_CMP, std::less<>>(min, node);
    }

    /**
     * Find the maximum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the maximum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMax(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node== nullptr) return nullptr;
        Node *max=findMax<DIM_CMP, DIM_NEXT>(node->right);
        if(DIM_CMP!=DIM){
            Node *leftMax=findMax<DIM_CMP, DIM_NEXT>(node->left);
            max=compareNode<DIM_CMP, std::greater<>>(leftMax, max);
        }
        return compareNode<DIM_CMP, std::greater<>>(max, node);
    }

    template<size_t DIM>
    Node *findMinDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMin<DIM, 0>(root);
        return findMinDynamic<DIM_NEXT>(dim);
    }

    template<size_t DIM>
    Node *findMaxDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMax<DIM, 0>(root);
        return findMaxDynamic<DIM_NEXT>(dim);
    }

    /**
     * Erase a node with key (check the pseudocode in project description)
     * Time Complexity: max{O(k log n), O(findMin)}
     * @tparam DIM current dimension of node
     * @param node
     * @param key
     * @return nullptr if node is erased, else the (probably) replaced node
     */
    template<size_t DIM>
    Node *erase(Node *node, const Key &key) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node== nullptr) return nullptr;
        if (key==node->key()){
            // if node is a leaf
            if (node->right== nullptr && node->left== nullptr){
                delete node;
                --treeSize;
                return nullptr;
            }else if(node->right!= nullptr){
                // if node has a right subtree
                Node *min=findMin<DIM,DIM_NEXT>(node->right);
                const_cast<Key&>(node->key())=min->key();
                node->value()=min->value();
                node->right=erase<DIM_NEXT>(node->right, min->key());
            }else if(node->left!= nullptr) {
                // if node has a left subtree
                Node *max = findMax<DIM,DIM_NEXT>(node->left);
                const_cast<Key&>(node->key()) = max->key();
                node->value() = max->value();
                node->left=erase<DIM_NEXT>(node->left, max->key());
            }
        }else{
            if (std::get<DIM>(key) < std::get<DIM>(node->key())){
                node->left=erase<DIM_NEXT>(node->left, key);
            }else{
                node->right=erase<DIM_NEXT>(node->right, key);
            }
        }
        return node;
    }

    template<size_t DIM>
    Node *eraseDynamic(Node *node, size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return erase<DIM>(node, node->key());
        return eraseDynamic<DIM_NEXT>(node, dim);
    }

    // TODO: define your helper functions here if necessary
    template<size_t DIM>
    Node *KDTree_helper(std::vector<std::pair<Key, Value>> sorted_v, int left, int right, Node *parent){
        if (left>=right) return nullptr;
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // find the median point of data
        int mid=(left+right)/2;
        // sort in new dimension
        std::nth_element(sorted_v.begin()+left, sorted_v.begin() + mid, sorted_v.begin()+right, [](const std::pair<Key, Value> &l, const std::pair<Key, Value> &r) {
            return compareKey<DIM, std::less<>>(l.first, r.first);
        });
        // begin creating
        Node *new_node= new Node(sorted_v[mid].first,sorted_v[mid].second, parent);
        ++treeSize;
        new_node->left=KDTree_helper<DIM_NEXT>(sorted_v, left, mid, new_node);
        new_node->right=KDTree_helper<DIM_NEXT>(sorted_v, mid+1, right, new_node);
        return new_node;
    }

    void delete_helper(Node *node){
        if(node== nullptr) return;
        if (node->left) delete_helper(node->left);
        if (node->right) delete_helper(node->right);
        delete node;
    }

    Node *copy_helper(Node *node, Node *parent){
        if (node== nullptr) return nullptr;
        Node *new_node= new Node(node->key(), node->value(), parent);
        if(node->left) new_node->left= copy_helper(node->left, new_node);
        if(node->right) new_node->right= copy_helper(node->right, new_node);
        return new_node;
    }


public:
    KDTree() = default;

    /**
     * Time complexity: O(kn log n)
     * @param v we pass by value here because v need to be modified
     */
    explicit KDTree(std::vector<std::pair<Key, Value>> v) {
        // TODO: implement this function
        if (v.empty()) return;
        // sort the vector
        std::stable_sort(v.begin(),v.end());
        // remove duplicated elements with reverse iteration
        auto last = std::unique(v.rbegin(), v.rend(), [](const auto& l, const auto& r) {
            return (!compareKey<0, std::less<>>(l.first, r.first)) && (!compareKey<0, std::greater<>>(l.first, r.first)); });
        v.erase(v.begin(), last.base());
        // construct the KDTree
        root= KDTree_helper<0>(v, 0, static_cast<int>(v.size()), nullptr);
        this->treeSize=v.size();
    }

    /**
     * Time complexity: O(n)
     */
    KDTree(const KDTree &that) {
        // TODO: implement this function
        if(this==&that) return;
        // clean the current KDTree
        delete_helper(root);
        // copy the whole KDTree
        this->root= copy_helper(that.root, nullptr);
        // update the attributes
        this->treeSize= that.treeSize;
    }

    /**
     * Time complexity: O(n)
     */
    KDTree &operator=(const KDTree &that) {
        // TODO: implement this function
        if(this==&that) return *this;
        // clean the current KDTree
        delete_helper(root);
        // copy the whole KDTree
        this->root= copy_helper(that.root, nullptr);
        // update the attributes
        this->treeSize= that.treeSize;
        return *this;
    }

    /**
     * Time complexity: O(n)
     */
    ~KDTree() {
        // TODO: implement this function
        delete_helper(root);
    }

    Iterator begin() {
        if (!root) return end();
        auto node = root;
        while (node->left) node = node->left;
        return Iterator(this, node);
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }

    Iterator find(const Key &key) {
        return Iterator(this, find<0>(key, root));
    }

    void insert(const Key &key, const Value &value) {
        insert<0>(key, value, root, nullptr);
    }

    template<size_t DIM>
    Iterator findMin() {
        return Iterator(this, findMin<DIM, 0>(root));
    }

    Iterator findMin(size_t dim) {
        return Iterator(this, findMinDynamic<0>(dim));
    }

    template<size_t DIM>
    Iterator findMax() {
        return Iterator(this, findMax<DIM, 0>(root));
    }

    Iterator findMax(size_t dim) {
        return Iterator(this, findMaxDynamic<0>(dim));
    }

    bool erase(const Key &key) {
        auto prevSize = treeSize;
        erase<0>(root, key);
        return prevSize > treeSize;
    }

    Iterator erase(Iterator it) {
        if (it == end()) return it;
        auto node = it.node;
        if (!it.node->left && !it.node->right) {
            it.node = it.node->parent;
        }
        size_t depth = 0;
        auto temp = node->parent;
        while (temp) {
            temp = temp->parent;
            ++depth;
        }
        eraseDynamic<0>(node, depth % KeySize);
        return it;
    }

    size_t size() const { return treeSize; }
};
