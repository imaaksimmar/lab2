#pragma once
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

class BitSequence : public Sequence<Bit> {
private:
    DynamicArray<Bit>* bits;

public:
    BitSequence() : bits(new DynamicArray<Bit>(0)) {}
    BitSequence(Bit* items, int count) : bits(new DynamicArray<Bit>(items, count)) {}
    BitSequence(const BitSequence& other) : bits(new DynamicArray<Bit>(*other.bits)) {}

    BitSequence(const LinkedList<Bit>& srcList) 
    : bits(new DynamicArray<Bit>(srcList.GetLength())) {
        for (int i = 0; i < srcList.GetLength(); ++i) {
            bits->Set(i, srcList.Get(i));
        }
    }

    ~BitSequence() { delete bits; }

    BitSequence& operator=(const BitSequence& other) {
        if(this == &other) {
            return *this;
        }
        delete bits;
        bits = new DynamicArray<Bit>(*other.bits);
        return *this;
    }

    Bit& operator[](int index) {
        if(index<0 || index>=bits->GetSize()) {
            throw IndexOutOfRange();
        }
        return (*bits)[index]; 
    }

    const Bit& operator[](int index) const {
        if(index<0 || index>=bits->GetSize())
            throw IndexOutOfRange();
        return (*bits)[index];
    }

    Bit GetFirst() const override {
        if(bits->GetSize() == 0) {
            throw EmptyCollection();
        }
        return bits->Get(0);
    }

    Bit GetLast() const override {
        if(bits->GetSize() == 0) throw EmptyCollection();
        return bits->Get(bits->GetSize() - 1);
    }

    Bit Get(int index) const override {
        if(index<0 || index>=bits->GetSize()) {
            throw IndexOutOfRange();
        }
        return bits->Get(index);
    }

    int GetLength() const override {
        return bits->GetSize();
    }

    Sequence<Bit>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=bits->GetSize() || startIndex>endIndex) {
            throw InvalidArgument();
        }
        BitSequence* result = new BitSequence();
        int subSize = endIndex-startIndex+1;
        result->bits->Resize(subSize);
        for(int i=0; i<subSize; i++) {
            result->bits->Set(i, bits->Get(startIndex + i));
        }
        return result;
    }

    Sequence<Bit>* Append(Bit item) override {
        bits->Resize(bits->GetSize() + 1);
        bits->Set(bits->GetSize()-1, item);
        return this;
    }

    Sequence<Bit>* Prepend(Bit item) override {
        int oldSize = bits->GetSize();
        bits->Resize(oldSize+1);
        for(int i=oldSize; i>0; i--) {
            bits->Set(i, bits->Get(i-1));
        }
        bits->Set(0, item);
        return this;
    }

    Sequence<Bit>* InsertAt(Bit item, int index) override {
        if(index<0 || index>bits->GetSize()) {
            throw IndexOutOfRange();
        }
        int oldSize = bits->GetSize();
        bits->Resize(oldSize+1);
        for(int i=oldSize; i>index; i--) {
            bits->Set(i, bits->Get(i-1));
        }
        bits->Set(index, item);
        return this;
    }

    Sequence<Bit>* Concat(Sequence<Bit>* otherSequence) override {
        if (otherSequence == nullptr) {
            throw NullPointer();
        }
        int oldSize = bits->GetSize();
        int addSize = otherSequence->GetLength();
        bits->Resize(oldSize+addSize);
        for(int i=0; i<addSize; i++) {
            bits->Set(oldSize+i, otherSequence->Get(i));
        }
        return this;
    }

    Sequence<Bit>* Map(Bit (*func)(Bit)) const override {
        BitSequence* result = new BitSequence();
        result->bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result->bits->Set(i, func(bits->Get(i)));
        }
        return result;
    }

    Sequence<Bit>* Where(bool (*predicate)(Bit)) const override {
        BitSequence* result = new BitSequence();
        for(int i=0; i<bits->GetSize(); i++) {
            if(predicate(bits->Get(i))) {
                result->bits->Resize(result->bits->GetSize()+1);
                result->bits->Set(result->bits->GetSize()-1, bits->Get(i));
            }
        }
        return result;
    }

    Bit Reduce(Bit (*func)(Bit, Bit), Bit initial) const override {
        Bit result = initial;
        for(int i = bits->GetSize()-1; i>=0; i--) {
            result = func(bits->Get(i), result);
        }
        return result;
    }

    BitSequence And(const BitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        BitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) & other.bits->Get(i));
        }
        return result;
    }

    BitSequence Or(const BitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        BitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) | other.bits->Get(i));
        }
        return result;
    }

    BitSequence Xor(const BitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        BitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) ^ other.bits->Get(i));
        }
        return result;
    }

    BitSequence Not() const {
        BitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, ~bits->Get(i));
        }
        return result;
    }

    BitSequence operator&(const BitSequence& other) const {
        return this->And(other);
    }

    BitSequence operator|(const BitSequence& other) const {
        return this->Or(other);
    }

    BitSequence operator^(const BitSequence& other) const {
        return this->Xor(other);
    }      

    BitSequence operator~() const {
        return this->Not();
    }
    
};