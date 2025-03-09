#pragma once

#include "defines.hpp"
#include "collection/array.hpp"
#include "hash/hasher.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"

namespace pulsar {

template <typename KeyType, typename ValueType>
struct MapEntry {
    KeyType key;
    ValueType value;
};

template <typename KeyType, typename ValueType>
struct HashMapElement {
    MapEntry<KeyType, ValueType> entry;
    HashMapElement<KeyType, ValueType>* next;
};

template <typename KeyType,
          typename ValueType,
          typename AllocatorType = DefaultAllocator<HashMapElement<KeyType, ValueType>>,
          typename HasherType = Hasher>
class HashMap {
public:
    using ElementType = HashMapElement<KeyType, ValueType>;

private:
    
    uint32_t Hash(const KeyType& key) {
        return Hasher::hash<KeyType>(key) % capacity_;
    }
    
    void Insert(const KeyType& key, const ValueType& value) {
        uint32_t index = Hash(key);
        ElementType* new_element = allocator_.Allocate(1);
        new_element->entry.key = key;
        new_element->entry.value = value;
        elements_[index] = new_element;
    }

    void ResizeRehash(size_t new_capacity) {
        
        size_t old_capacity = capacity_;
        ElementType** old_elements = elements_;
        
        size_t allocation_size = new_capacity * sizeof(ElementType*);
        ElementType** new_elements = Memory::Allocate(allocation_size);
        Memory::Write(new_elements, 0, allocation_size);

        for (uint32_t i = 0; i < old_capacity; i++) {
            if (old_hashes[i] == EMPTY_HASH) {
                continue;
            }
            // insertion 
        }

    }

private:
    ElementType** elements_;
    AllocatorType allocator_;
    size_t size_;
    // TODO: Use prime number for capacity.
    size_t capacity_;
};

}  //namespace pulsar