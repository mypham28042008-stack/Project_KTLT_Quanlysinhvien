#ifndef HASHMAP_H
#define HASHMAP_H

#include "LinkedList.h"
#include <string>

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;

    HashEntry() : key(K()), value(V()) {}
    HashEntry(K k, V v) : key(k), value(v) {}

    // Overloaded == operator compares only the keys.
    bool operator==(const HashEntry& other) const {
        return this->key == other.key;
    }
};

template <typename K, typename V>
class HashMap {
private:
    LinkedList<HashEntry<K, V>>* buckets;
    size_t size;
    size_t capacity;

    // Hàm hỗ trợ tìm số nguyên tố tiếp theo để băm lại
    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    size_t getNextPrime(size_t n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Thuật toán băm DJB2 cho khóa std::string
    size_t hashFunction(const std::string& key, size_t cap) const {
        size_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % cap;
    }

    // Hàm băm quá tải cho dung lượng mặc định
    size_t hashFunction(const std::string& key) const {
        return hashFunction(key, capacity);
    }

    // Băm lại khi tải vượt quá 0.75
    void rehash() {
        size_t newCapacity = getNextPrime(capacity * 2);
        LinkedList<HashEntry<K, V>>* newBuckets = new LinkedList<HashEntry<K, V>>[newCapacity];
        
        for (size_t i = 0; i < capacity; ++i) {
            Node<HashEntry<K, V>>* current = buckets[i].getHead();
            while (current != nullptr) {
                size_t newIndex = hashFunction(current->data.key, newCapacity);
                newBuckets[newIndex].insertAtHead(current->data);
                current = current->next;
            }
        }
        delete[] buckets;
        buckets = newBuckets;
        capacity = newCapacity;
    }

public:
    HashMap(size_t initialCapacity = 10007) : size(0), capacity(initialCapacity) {
        buckets = new LinkedList<HashEntry<K, V>>[capacity];
    }

    ~HashMap() {
        clear();
        delete[] buckets;
    }

    // Disable copy constructor and assignment operator
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;

    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            buckets[i].clear();
        }
        size = 0;
    }

    // Insert or update key-value pair. Returns true if new element added.
    bool put(const K& key, V value) {
        // Auto rehash if load factor >= 0.75
        if ((float)size / capacity >= 0.75f) {
            rehash();
        }

        size_t index = hashFunction(key);
        Node<HashEntry<K, V>>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value; // Update existing
                return false;
            }
            current = current->next;
        }

        // Key does not exist, insert at head
        buckets[index].insertAtHead(HashEntry<K, V>(key, value));
        size++;
        return true;
    }

    // Retrieve value by key. Returns default V (e.g. nullptr) if not found.
    V get(const K& key) const {
        size_t index = hashFunction(key);
        Node<HashEntry<K, V>>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                return current->data.value;
            }
            current = current->next;
        }
        return V(); // default (nullptr for pointer)
    }

    // Remove entry by key
    bool remove(const K& key) {
        size_t index = hashFunction(key);
        if (buckets[index].remove(HashEntry<K, V>(key, V()))) {
            size--;
            return true;
        }
        return false;
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }
    
    // Iterate through all values and return them in a newly constructed LinkedList
    // (Caller must manage the returned list memory)
    LinkedList<V>* values() const {
        LinkedList<V>* list = new LinkedList<V>();
        for (size_t i = 0; i < capacity; ++i) {
            Node<HashEntry<K, V>>* current = buckets[i].getHead();
            while (current != nullptr) {
                list->insertAtTail(current->data.value);
                current = current->next;
            }
        }
        return list;
    }

    size_t getCollisionCount() const {
        size_t collisions = 0;
        for (size_t i = 0; i < capacity; ++i) {
            size_t bucketSize = buckets[i].getSize();
            if (bucketSize > 1) {
                collisions += (bucketSize - 1);
            }
        }
        return collisions;
    }
};

#endif // HASHMAP_H
