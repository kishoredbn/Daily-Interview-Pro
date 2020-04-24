#include <iostream>
#include <queue>
#include <unordered_map>

struct Key {
    int32_t id; 
    uint64_t weightage;
    Key(int32_t id, uint64_t weightage=1) : id(id), weightage(weightage) {};
    bool operator<(const Key &other) const { return weightage > other.weightage;}
    size_t operator()(const Key& tr) const {
        return std::hash<int32_t>()(tr.id);
    }
};

struct THash { // forgive c++
    size_t operator()(const Key& tr) const {
        return std::hash<int32_t>()(tr.id);
    }
};

struct TEqual { // forgive c++ again
    bool operator()(const Key& tr1, const Key& tr2) const {
        if (tr1.id == tr2.id) return true;
        return false;
    }
};

class Cache {
private:
    uint64_t capacity;
    uint64_t time_ticker;
    std::unordered_map<Key, int32_t, THash, TEqual> map_keys;
    std::priority_queue<Key> lru_min_heap;

    void RehashPriorityQueue()
    {
        lru_min_heap = std::priority_queue<Key>(); // clear lru_min_heap
        for (auto &&iter : map_keys) lru_min_heap.emplace(iter.first); // rehash lru_min_heap
    }

public:
    Cache(const uint64_t cache_size=1) : capacity(cache_size), time_ticker(0) {}
    ~Cache(){}

    void Set(int32_t key, int32_t value) { // sets a new key-val of reset key-value
        time_ticker++; // increments time

        auto _key = Key(key, time_ticker); // create a new key 
        auto find_key = map_keys.find(_key); // check if it is already there or not

        if(capacity) capacity--; // only add if there is capacity in the cache to do so
        else if(find_key == map_keys.end()) // capacity full need to remove lru element - if it is not is map
        { // edge case check: if the element is not a new append but an update, then don't proceed 
            auto lru = lru_min_heap.top(); lru_min_heap.pop(); // find lru from heap and remove it

            auto find_key_lru = map_keys.find(lru); // find lru from map and remove it
            if(find_key_lru != map_keys.end()) map_keys.erase(find_key_lru);
        }

        if(find_key != map_keys.end()) // now if the new key already there remove it and update priority queue
        {
            map_keys.erase(find_key);
            RehashPriorityQueue();
        }

        map_keys.emplace(_key, value); // finally add the key in 2 DS
        lru_min_heap.emplace(_key);
    }

    int32_t Get(int32_t key) { // get a key-value
        time_ticker++; // increments time
        int ret = 0;

        auto _key = Key(key, time_ticker); // create key again, time_ticker need to be updated
        auto find_key = map_keys.find(_key); 
        if(find_key != map_keys.end()) { // check key is there or not
            ret = find_key->second; // get the existing value to return
            map_keys.erase(find_key); // remove it

            RehashPriorityQueue(); // rehash priority queue
            
            map_keys.emplace(_key, ret); // finally add the key in 2 DS
            lru_min_heap.emplace(_key);
        }
        else
        {
            std::cout<<"None "; // Keys not found
        }

        return ret;
    }
};

int main()
{
    // test case 1:
    Cache cache(2);
    cache.Set(3, 3);
    cache.Set(4, 4);
    std::cout<<cache.Get(3)<<"\n";
    std::cout<<cache.Get(2)<<"\n";
    cache.Set(2, 2);
    std::cout<<cache.Get(4)<<"\n";
    std::cout<<cache.Get(3)<<"\n";
    std::cout<<cache.Get(2)<<"\n";
    std::cout<<cache.Get(3)<<"\n";
    cache.Set(4, 4);
    std::cout<<cache.Get(2)<<"\n";
    std::cout<<cache.Get(4)<<"\n";

    // test case 2:
    Cache cache1(3);
    cache1.Set(3, 3);
    cache1.Set(4, 4);
    std::cout<<cache1.Get(3)<<"\n";
    std::cout<<cache1.Get(2)<<"\n";
    cache1.Set(2, 2);
    std::cout<<cache1.Get(4)<<"\n";
    std::cout<<cache1.Get(3)<<"\n";
    std::cout<<cache1.Get(2)<<"\n";
    std::cout<<cache1.Get(3)<<"\n";
    cache1.Set(4, 4);
    std::cout<<cache1.Get(2)<<"\n";
    std::cout<<cache1.Get(4)<<"\n";

    // test case 3:
    Cache cache2(3);
    cache2.Set(3, 3);
    cache2.Set(4, 4);
    std::cout<<cache2.Get(3)<<"\n";
    std::cout<<cache2.Get(2)<<"\n";
    cache2.Set(2, 2);
    std::cout<<cache2.Get(4)<<"\n";
    std::cout<<cache2.Get(3)<<"\n";
    std::cout<<cache2.Get(2)<<"\n";
    std::cout<<cache2.Get(3)<<"\n";
    cache2.Set(4, 5);
    std::cout<<cache2.Get(2)<<"\n";
    std::cout<<cache2.Get(4)<<"\n";

    return 0;
}