#pragma once

#include "defines.hpp"
#include "memory/memory.hpp"

namespace pulsar {

template <typename T>
class Option {
public:
    constexpr static Option<T> Some(const T& value) { return Option<T>(value); }

    constexpr static Option<T> None() { return Option<T>(); }

    constexpr Option(const T& value)
        : is_some_(true) {
        ::new (&storage_) T(value);
    }

    constexpr Option()
        : is_some_(false) {}

    constexpr Option(const Option& other)
        : is_some_(other.is_some_) {
        if (is_some_) {
            ::new (&storage_) T(*other.get_ptr());
        }
    }

    constexpr Option& operator=(const Option& other) {
        if (this != &other) {
            if (is_some_) {
                GetDataPtr()->~T();
            }
            is_some_ = other.is_some_;
            if (is_some_) {
                ::new (&storage_) T(*other.get_ptr());
            }
        }
        return *this;
    }

    constexpr ~Option() {
        if (is_some_) {
            GetDataPtr()->~T();
        }
    }

    constexpr bool HasValue() const { return is_some_; }

    constexpr T Unwrap() const {
        PCHECK(HasValue())
        return *GetDataPtr();
    }

    constexpr T UnwrapOr(const T& default_value) const {
        return HasValue() ? *GetDataPtr() : default_value;
    }

    const T& operator*() const {
        PCHECK(HasValue())
        return *GetDataPtr();
    }

    T& operator*() {
        PCHECK(HasValue())
        return *GetDataPtr();
    }

private:
    const T* GetDataPtr() const { return reinterpret_cast<const T*>(&storage_); }

    T* GetDataPtr() { return reinterpret_cast<T*>(&storage_); }

private:
    alignas(T) char storage_[sizeof(T)];
    bool is_some_;
};

}  // namespace pulsar