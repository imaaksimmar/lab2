#pragma once
#include <concepts>
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

template <std::integral T_word = unsigned char>
class BitSequence : public Sequence<Bit<T_word>> {
private:
    DynamicArray<Bit<T_word>>* bits;

public:

    BitSequence() : bits(new DynamicArray<Bit<T_word>>(0)) {}

    BitSequence(Bit<T_word>* items, int count) 
        : bits(new DynamicArray<Bit<T_word>>(items, count)) {}

    BitSequence(const BitSequence& other) 
        : bits(new DynamicArray<Bit<T_word>>(*other.bits)) {}

    BitSequence(const LinkedList<Bit<T_word>>& list) 
        : bits(new DynamicArray<Bit<T_word>>(list.GetLength())) {
        for (int i=0; i<list.GetLength(); i++) {
            bits->Set(i, list.Get(i));
        }
    }

    ~BitSequence() { delete bits; }

    BitSequence& operator=(const BitSequence& other) {
        if(this == &other) {
            return *this;
        }
        delete bits;
        bits = new DynamicArray<Bit<T_word>>(*other.bits);
        return *this;
    }


    Bit<T_word> GetFirst() const override {
        if(bits->GetSize()==0) {
            throw EmptyCollection();
        }
        return bits->Get(0);
    }

    Bit<T_word> GetLast() const override {
        if(bits->GetSize() == 0) {
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

    Bit<T_word>& operator[](int index) {
        if(index<0 || index>=bits->GetSize()) {
            throw IndexOutOfRange();
        }
        return (*bits)[index];
    }

    const Bit<T_word>& operator[](int index) const {
        if (index < 0 || index >= bits->GetSize()) throw IndexOutOfRange();
        return (*bits)[index];
    }

    Sequence<Bit<T_word>>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=bits->GetSize() || startIndex>endIndex) {
            throw InvalidArgument();
        }
        BitSequence* result = new BitSequence();
        int subSize = endIndex-startIndex+ 1;
        result->bits->Resize(subSize);
        for(int i= 0; i<subSize; i++) {
            result->bits->Set(i, bits->Get(startIndex+i));
        }
        return result;
    }

    Sequence<Bit<T_word>>* Append(Bit<T_word> item) override {
        bits->Resize(bits->GetSize()+1);
        bits->Set(bits->GetSize()-1, item);
        return this;
    }

    Sequence<Bit<T_word>>* Prepend(Bit<T_word> item) override {
        int oldSize = bits->GetSize();
        bits->Resize(oldSize + 1);
        for(int i=oldSize; i>0; i--) {
            bits->Set(i, bits->Get(i - 1));
        }
        bits->Set(0, item);
        return this;
    }

    Sequence<Bit<T_word>>* InsertAt(Bit<T_word> item, int index) override {
        if(index<0 || index>bits->GetSize()) {
            throw IndexOutOfRange();
        }
        int oldSize = bits->GetSize();
        bits->Resize(oldSize+ 1);
        for (int i=oldSize; i>index; i--) {
            bits->Set(i, bits->Get(i-1));
        }
        bits->Set(index, item);
        return this;
    }

    Sequence<Bit<T_word>>* Concat(Sequence<Bit<T_word>>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
        }
        int oldSize = bits->GetSize();
        int otherSize = otherSequence->GetLength();
        bits->Resize(oldSize + otherSize);
        for (int i=0; i<otherSize; i++) {
            bits->Set(oldSize+i, otherSequence->Get(i));
        }
        return this;
    }

    template <typename U_bit>
    BitSequence<U_bit>* Map(Bit<U_bit> (*func)(Bit<T_word>)) const {
        BitSequence<U_bit>* res = new BitSequence<U_bit>();
        res->bits->Resize(bits->GetSize()); 
        for(int i= 0; i<bits->GetSize(); i++) {
            res->bits->Set(i, func(bits->Get(i)));
        }
        return res;
    }

    BitSequence<T_word>* Where(bool (*predicate)(Bit<T_word>)) const {
        BitSequence<T_word>* res = new BitSequence<T_word>();
        for (int i=0; i<bits->GetSize(); i++) {
            if(predicate(bits->Get(i))) {
                res->Append(bits->Get(i));
            }
        }
        return res;
    }

    template <typename U>
    U Reduce(U (*func)(U, Bit<T_word>), U initial) const {
        U res = initial;
        for (int i=0; i<bits->GetSize(); i++) {
            res = func(res, bits->Get(i));
        }
        return res;
    }


    BitSequence operator&(const BitSequence& other) const {
        if (bits->GetSize() != other.bits->GetSize()) {
             throw SizeMismatch();
        }
        BitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) & other.bits->Get(i));
        }
        return res;
    }

    BitSequence operator|(const BitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        BitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i = 0; i < bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) | other.bits->Get(i));
        }
        return res;
    }

    BitSequence operator^(const BitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        BitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, bits->Get(i) ^ other.bits->Get(i));
        }
        return res;
    }

    BitSequence operator~() const {
        BitSequence res;
        res.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            res.bits->Set(i, ~bits->Get(i));
        }
        return res;
    }
};







