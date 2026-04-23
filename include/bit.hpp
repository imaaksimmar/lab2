#pragma once
#include <concepts>
#include <cstddef>
#include "exceptions.hpp"

template <std::integral T>
struct BitProxy {
    T& ref;
    size_t idx;

    BitProxy(T& value, size_t index) : ref(value), idx(index) {}

    BitProxy& operator=(bool val) {
        if(val) {
            ref = ref | (static_cast<T>(1) << idx);
        }
        
        else {
            ref = ref & ~(static_cast<T>(1) << idx);
        }
        return *this;
    }

    operator bool() const {
        return (ref >> idx) & 1;
    }
};



template <std::integral T>
class Bit {
private:
    static constexpr size_t BIT_COUNT = sizeof(T)*8;
    T value;
    using Proxy = BitProxy<T>;

public:
    Bit() : value(0) {}
    Bit(T val) : value(val) {}
    Bit(const Bit& other) : value(other.value) {}

    Bit& operator=(const Bit& other) {
    if(this == &other) {
        return *this; 
    }
    value = other.value; 
    return *this;        
    }
    
    static constexpr size_t BitCount() { 
        return BIT_COUNT; 
    }

    bool operator[](size_t idx) const {
        if(idx >= BIT_COUNT) {
            throw IndexOutOfRange();
        }
        return (value >> idx) & static_cast<T>(1);
    }

    Proxy operator[](size_t idx) {
        if(idx >= BIT_COUNT) {
            throw IndexOutOfRange();
        }
        return Proxy(value, idx);
    }

    Bit operator&(const Bit& other) const { 
        return Bit(value & other.value); 
    }
    Bit operator|(const Bit& other) const { 
        return Bit(value | other.value); 
    }
    Bit operator^(const Bit& other) const { 
        return Bit(value ^ other.value);
    }
    Bit operator~() const { 
        return Bit(~value);
    }

    T GetValue() const { return value; }
    operator bool() const { return value != 0; }
};












