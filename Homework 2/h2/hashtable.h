#ifndef HASHTABLE_H
#define HASHTABLE_H


// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Keyey&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!

#include <iostream>

// A bucket's type tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class BucketType {
    Empty,
    Occupied,
    Deleted
};

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
class HashTable {

public:
    // A bucket has a type, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        BucketType type = BucketType::Empty;
        Key key;
        Value val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).
        // Suppose the initial size of buckets are 23.
        buckets.resize(23);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    Value &operator[](const Key &key) {
        // TODO
        Hasher hash;
        int hi, len= static_cast<int>(buckets.size());
        int h0 = static_cast<int>(hash(key) % len);
        for (int i = 0; i <=len/2 ; ++i) {
            int i1=i*i,i2=-i*i;
            // probing right part
            hi=(h0+i1)%len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                return buckets[hi].val;
            }else if(buckets[hi].type==BucketType::Empty || buckets[hi].type==BucketType::Deleted){
                buckets[hi].key=key;
                buckets[hi].val=Value{};
                buckets[hi].type=BucketType::Occupied;
                num_elements++;
                return buckets[hi].val;
            }
            // probing left part
            hi=(h0+i2)%len;
            if(hi<0) hi+=len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                return buckets[hi].val;
            }else if(buckets[hi].type==BucketType::Empty || buckets[hi].type==BucketType::Deleted){
                buckets[hi].key=key;
                buckets[hi].val=Value{};
                buckets[hi].type=BucketType::Occupied;
                num_elements++;
                return buckets[hi].val;
            }
        }
        return buckets[hi].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const Key &key, const Value &val) {
        // TODO
        Hasher hash;
        int hi, len= static_cast<int>(buckets.size());
        int h0 = static_cast<int>(hash(key) % len);
        for (int i = 0; i <=len/2 ; ++i) {
            int i1=i*i,i2=-i*i;
            // probing right part
            hi=(h0+i1)%len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                return false;
            }else if(buckets[hi].type==BucketType::Empty || buckets[hi].type==BucketType::Deleted){
                buckets[hi].key=key;
                buckets[hi].type=BucketType::Occupied;
                buckets[hi].val=val;
                num_elements++;
                return true;
            }
            // probing left part
            hi=(h0+i2)%len;
            if(hi<0) hi+=len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                return false;
            }else if(buckets[hi].type==BucketType::Empty || buckets[hi].type==BucketType::Deleted){
                buckets[hi].key=key;
                buckets[hi].type=BucketType::Occupied;
                buckets[hi].val=val;
                num_elements++;
                return true;
            }
        }
        return false;
    }

    // takes a key, and removes it from the hash table.
    // If the key isn’t already in the hash table, then the operation has no effect.
    // erase returns the number of items remove (0 or 1)
    size_t erase(const Key &key) {
        // TODO
        Hasher hash;
        int hi, len= static_cast<int>(buckets.size());
        int h0 = static_cast<int>(hash(key) % len);
        for (int i = 0; i <=len/2 ; ++i) {
            int i1=i*i,i2=-i*i;
            // probing right part
            hi=(h0+i1)%len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                buckets[hi].type=BucketType::Deleted;
                num_elements--;
                return 1;
            }else if(buckets[hi].type==BucketType::Empty ){
                return 0;
            }
            // probing left part
            hi=(h0+i2)%len;
            if(hi<0) hi+=len;
            if(buckets[hi].key==key && buckets[hi].type==BucketType::Occupied){
                buckets[hi].type=BucketType::Deleted;
                num_elements--;
                return 1;
            }else if(buckets[hi].type==BucketType::Empty ){
                return 0;
            }
        }
        return 0;
    }

private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use this to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // TODO (optional)

    }

    // You can add methods here if you like.

};

#endif // HASHTABLE_H