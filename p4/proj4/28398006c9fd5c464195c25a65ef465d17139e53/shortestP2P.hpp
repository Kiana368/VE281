#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P {
  public:
      ShortestP2P() = default;

      ~ShortestP2P(){
          for (auto &n : nodes) {
            delete n;
          }
          for (int i = 0; i <node_num ; ++i) {
            delete [] dist[i];
          }
          delete [] dist;
      }

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph(){
          // initialize the number of nodes and edges
          cin>>node_num>>edge_num;
          // create new nodes
          nodes.resize(node_num);
          for (int i = 0; i <node_num ; ++i) {
              nodes[i]=new Node(i);
          }
          // create new edges
          int start_node_ind, end_node_ind, cur_weight;
          for (int j = 0; j <edge_num ; ++j) {
              cin>>start_node_ind>>end_node_ind>>cur_weight;
              Edge * edge= new Edge(cur_weight,start_node_ind,end_node_ind);
              nodes[start_node_ind]->next_edges.emplace_back(edge);
              edges.emplace_back(edge);
          }
          // proper or not (check whether exist a loop which has a total negative weight)
          check_valid();
          // use the idea of dp to obtain the distance map for all the nodes
          floyd();
      }

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(unsigned int A, unsigned int B){
          // use Dijkstra algorithm is not proper for the condition of multiple pairs of source and destination
//          list<dist_node> node_list;
//          vector<int> dist(node_num,INF);
//          node_list.emplace_back(make_pair(0,A));
//          dist[A]=0;

//          while (!node_list.empty()){
//              while (!node_list.empty() && node_list.front().first>dist[node_list.front().second]){
//                  node_list.pop_front();
//              }
//              if(node_list.empty()) break;
//              unsigned int top_node_index=node_list.front().second;
//              node_list.pop_front();
//              for (auto &e : nodes[top_node_index]->next_edges) {
//                  int temp_weight=e->weight;
//                  unsigned int next_node_index=e->end_index;
//                  if (dist[next_node_index]>dist[top_node_index]+temp_weight){
//                      dist[next_node_index]=dist[top_node_index]+temp_weight;
//                      node_list.emplace_back(make_pair(dist[next_node_index],next_node_index));
//                  }
//              }
//          }
          if (dist[A][B]==INF){
              cout<<"INF"<<endl;
          }else {
              cout << dist[A][B] << endl;
          }
      }

  private:
    // internal data and functions.
//    typedef pair<int,unsigned int> dist_node;

    class Edge{
    public:
        int weight;
        int start_index;
        int end_index;

        Edge(int weight, int start, int end): weight(weight), start_index(start), end_index(end) {}
    };

    class Node{
    public:
        vector<Edge*> next_edges;
        int index;
        explicit Node(int ind): index(ind) {}
        ~Node(){
            for (auto &e : next_edges) {
                delete e;
            }
        }
    };

    int node_num;
    int edge_num;
    vector<Node*> nodes;
    vector<Edge*> edges;
    vector<bool> marked;
    vector<bool> on_stack;
    vector<Edge*> edgeTo;
    int ** dist;

    void dfs(int cur_index){
        // mark as visited and pushed into stack
        marked[cur_index]=true;
        on_stack[cur_index]=true;

        for (auto &e : nodes[cur_index]->next_edges) {
            int next_index=e->end_index;
            // if the next node is not visited, record the current edge to it and dfs it
            if (marked[next_index]==0){
                edgeTo[next_index]=e;
                dfs(next_index);
            }
            // if the next node is already in the stack, there exist a loop
            else if(on_stack[next_index]==1){
                Edge *temp_e=e;
                int sum=0;
                while (temp_e->start_index!=next_index){
                    sum+=temp_e->weight;
//                    if(edgeTo[temp_e->start_index]== nullptr){
//                        cout<<"!!"<<endl;
//                        exit(0);
//                    }
                    temp_e=edgeTo[temp_e->start_index];
                }
                sum+=temp_e->weight;
                // if the loop is a negative loop, then the shortest path between two nodes may be negative infinity
                if (sum<0) {
                    cout<<"Invalid graph. Exiting."<<endl;
                    exit(0);
                }
                // If exist such situation: 0<=>1<=>2, cannot directly return to the upper case
                if (nodes[temp_e->end_index]->next_edges.size()==1) return;
                else continue;
            }
        }
        // pop out the stack
        on_stack[cur_index]=false;
    }

    void check_valid(){
        // check whether there exists a loop which has a total negative length
        marked.resize(node_num);
        on_stack.resize(node_num);
        edgeTo.resize(node_num);

        for (auto & n : nodes) {
            if (marked[n->index]==0) dfs(n->index);
        }
    }

    void floyd(){
        // floyd algorithm
        // generate map
        dist=new int*[node_num];
        for (int k = 0; k <node_num ; ++k) {
            dist[k]=new int[node_num];
        }
        // initialize the map with infinity
        for (int i = 0; i <node_num ; ++i) {
            for (int j = 0; j <node_num ; ++j) {
                if(i==j) dist[i][j]=0;
                else dist[i][j]=INF;
            }
        }
        // update the distance using the input edges
        for (auto &e : edges) {
            dist[e->start_index][e->end_index]=e->weight;
        }
        // calculate the distance map
        for (int k = 0; k <node_num ; ++k) {
            for (int i = 0; i < node_num; ++i) {
                // the "if" condition is used to reduce time
                if (dist[i][k]<INF && i!=k){
                    for (int j = 0; j < node_num; ++j) {
                        if (j==i || j==k || dist[k][j]==INF) continue;

                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
    }
};
