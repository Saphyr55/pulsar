#pragma once

#include <functional>

#include "core_exports.hpp"
#include "defines.hpp"

namespace pulsar {

class PULSAR_CORE_API Hasher {
public:
    static unsigned long long fnv_hash_1a_64(void* key, int len) {
        uint8_t* p = static_cast<uint8_t*>(key);
        uint64_t h = 0xcbf29ce484222325ULL;
    
        for (int32_t i = 0; i < len; i++) {
            h = (h ^ p[i]) * 0x100000001b3ULL;
        }
    
        return h;
    }
    
    template <typename T>
    static uint32_t hash(const T& value) {
        return std::hash<T>{}(value);
    }

};

}  //namespace pulsar