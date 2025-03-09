#pragma once

namespace pulsar {

enum class Ordering {
    LESS,
    EQUAL,
    GREATER
};

template <typename T>
class Comparator {

    Ordering Compare(const T& lhs, const T& rhs) const {
        
        if (lhs < rhs) {
            return Ordering::LESS;
        }
        
        if (lhs > rhs) {
            return Ordering::GREATER;
        }

        return Ordering::EQUAL;
    }

};

}