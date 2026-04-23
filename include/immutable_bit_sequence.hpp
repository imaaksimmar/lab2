#pragma once
#include <concepts>
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

template <std::integral T_word = unsigned char>
class ImmutableBitSequence : public Sequence<Bit<T_word>> {
private:
    DynamicArray<Bit<T_word>>* bits;

public:

    ImmutableBitSequence() : bits(new DynamicArray<Bit<T_word>>(0)) {}

    ImmutableBitSequence(Bit<T_word>* items, int count) 
        : bits(new DynamicArray<Bit<T_word>>(items, count)) {}

    ImmutableBitSequence(const ImmutableBitSequence& other) 
        : bits(new DynamicArray<Bit<T_word>>(*other.bits)) {}

    ImmutableBitSequence(const LinkedList<Bit<T_word>>& list) 
        : bits(new DynamicArray<Bit<T_word>>(list.GetLength())) {
        for(int i=0; i<list.GetLength(); i++) {
            bits->Set(i, list.Get(i));
        }
    }

    ~ImmutableBitSequence() { delete bits; }

    ImmutableBitSequence& operator=(const ImmutableBitSequence& other) {
        if(this == &other) {
            return *this;
        }
        delete bits;
        bits = new DynamicArray<Bit<T_word>>(*other.bits);
        return *this;
    }

    Bit<T_word> GetFirst() const override {
        if(bits->GetSize() == 0) {
            throw EmptyCollection();
        }
        return bits->Get(0);
    }

    Bit<T_word> GetLast() const override {
        if(bits->GetSize()== 0) {
            throw EmptyCollection();
        }
        return bits->Get(bits->GetSize()-1);
    }

    Bit<T_word> Get(int index) const override {
        if(index<0 || index>=bits->GetSize()) {
            throw IndexOutOfRange();
        }
        return bits->Get(index);
    }

    int GetLength() const override {
        return bits->GetSize();
    }

    const Bit<T_word>& operator[](int index) const {
        if(index<0 || index>=bits->GetSize()) {
            throw IndexOutOfRange();
        }
        return (*bits)[index];
    }

    Sequence<Bit<T_word>>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=bits->GetSize() || startIndex>endIndex) {
            throw InvalidArgument();
        }
        int subSize = endIndex-startIndex+1;
        ImmutableBitSequence* result = new ImmutableBitSequence();
        result->bits->Resize(subSize);
        for(int i=0; i<subSize; i++) {
            result->bits->Set(i, bits->Get(startIndex+i));
        }
        return result;
    }

    Sequence<Bit<T_word>>* Append(Bit<T_word> item) override {
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        copy->bits->Resize(copy->bits->GetSize()+1);
        copy->bits->Set(copy->bits->GetSize()-1, item);
        return copy;
    }

    Sequence<Bit<T_word>>* Prepend(Bit<T_word> item) override {
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        copy->bits->Resize(oldSize+ 1);
        for(int i=oldSize; i>0; i--) {
            copy->bits->Set(i, copy->bits->Get(i-1));
        }
        copy->bits->Set(0, item);
        return copy;
    }

    Sequence<Bit<T_word>>* InsertAt(Bit<T_word> item, int index) override {
        if(index<0 || index>bits->GetSize()) {
            throw IndexOutOfRange();
        }
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        copy->bits->Resize(oldSize+1);
        for(int i=oldSize; i>index; i--) {
            copy->bits->Set(i, copy->bits->Get(i-1));
        }
        copy->bits->Set(index, item);
        return copy;
    }

    Sequence<Bit<T_word>>* Concat(Sequence<Bit<T_word>>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
        }
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        int otherSize = otherSequence->GetLength();
        copy->bits->Resize(oldSize + otherSize);
        for(int i= 0; i<otherSize; i++) {
            copy->bits->Set(oldSize+i, otherSequence->Get(i));
        }
        return copy;
    }

    template <typename U_bit>
    ImmutableBitSequence<U_bit>* Map(Bit<U_bit> (*func)(Bit<T_word>)) const {
        ImmutableBitSequence<U_bit>* res = new ImmutableBitSequence<U_bit>();
        res->bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res->bits->Set(i, func(bits->Get(i)));
        }
        return res;
    }

    ImmutableBitSequence<T_word>* Where(bool (*predicate)(Bit<T_word>)) const {
    int count = 0;
    for(int i=0; i<bits->GetSize(); i++) {
        if(predicate(bits->Get(i))) {
            count++;
        }
    }
    ImmutableBitSequence<T_word>* res = new ImmutableBitSequence<T_word>();
    res->bits->Resize(count);
    int idx = 0;
    for(int i=0; i<bits->GetSize(); i++) {
        if(predicate(bits->Get(i))) {
            res->bits->Set(idx++, bits->Get(i));
        }
    } 
    return res;
}

    template <typename U>
    U Reduce(U (*func)(U, Bit<T_word>), U initial) const {
        U res = initial;
        for(int i=0; i <bits->GetSize(); i++) {
            res = func(res, bits->Get(i));
        }
        return res;
    }

    ImmutableBitSequence operator&(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) & other.bits->Get(i));
        }
        return res;
    }

    ImmutableBitSequence operator|(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) | other.bits->Get(i));
        }
        return res;
    }

    ImmutableBitSequence operator^(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) ^ other.bits->Get(i));
        }
        return res;
    }

    ImmutableBitSequence operator~() const {
        ImmutableBitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, ~bits->Get(i));
        }
        return res;
    }
};







