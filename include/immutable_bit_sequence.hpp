#pragma once
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

class ImmutableBitSequence : public Sequence<Bit> {
private:
    DynamicArray<Bit>* bits;

public:
    ImmutableBitSequence() : bits(new DynamicArray<Bit>(0)) {}
    ImmutableBitSequence(Bit* items, int count) : bits(new DynamicArray<Bit>(items, count)) {}
    ImmutableBitSequence(const ImmutableBitSequence& other)  : bits(new DynamicArray<Bit>(*other.bits)) {}
    
    ImmutableBitSequence(const LinkedList<Bit>& srcList) 
        : bits(new DynamicArray<Bit>(srcList.GetLength())) {
        for (int i=0; i<srcList.GetLength(); i++) {
            bits->Set(i, srcList.Get(i));
        }
    }

    ~ImmutableBitSequence() { delete bits; }

    ImmutableBitSequence& operator=(const ImmutableBitSequence& other) {
        if(this == &other) {
            return *this;
        }
        delete bits;
        bits = new DynamicArray<Bit>(*other.bits);
        return *this;
    }

    const Bit& operator[](int index) const {
        if(index<0 || index>=bits->GetSize())
            throw IndexOutOfRange();
        return (*bits)[index];
    }

    Bit GetFirst() const override {
        if(bits->GetSize() == 0) 
            throw EmptyCollection();
        return bits->Get(0);
    }

    Bit GetLast() const override {
        if(bits->GetSize() == 0) 
            throw EmptyCollection();
        return bits->Get(bits->GetSize()-1);
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
        ImmutableBitSequence* result = new ImmutableBitSequence();
        int subSize = endIndex-startIndex+1;
        result->bits->Resize(subSize);
        for(int i=0; i<subSize; i++) {
            result->bits->Set(i, bits->Get(startIndex+i));
        }
        return result;
    }


    Sequence<Bit>* Append(Bit item) override {
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        copy->bits->Resize(oldSize+1);
        copy->bits->Set(oldSize, item);  
        return copy;
    }

    Sequence<Bit>* Prepend(Bit item) override {
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        copy->bits->Resize(oldSize+1);
        for(int i=oldSize; i>0; i--) {
            copy->bits->Set(i, copy->bits->Get(i-1));  
        }
        copy->bits->Set(0, item);
        return copy;
    }

    Sequence<Bit>* InsertAt(Bit item, int index) override {
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

    Sequence<Bit>* Concat(Sequence<Bit>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
        }
        ImmutableBitSequence* copy = new ImmutableBitSequence(*this);
        int oldSize = copy->bits->GetSize();
        int addSize = otherSequence->GetLength();
        copy->bits->Resize(oldSize + addSize);
        for(int i=0; i<addSize; i++) {
            copy->bits->Set(oldSize+i, otherSequence->Get(i));
        }
        return copy;
    }

    Sequence<Bit>* Map(Bit (*func)(Bit)) const override {
        ImmutableBitSequence* result = new ImmutableBitSequence();
        result->bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result->bits->Set(i, func(bits->Get(i)));
        }
        return result;
    }

    Sequence<Bit>* Where(bool (*predicate)(Bit)) const override {
        ImmutableBitSequence* result = new ImmutableBitSequence();
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
        for(int i=0; i<bits->GetSize(); i++) {
            result = func(bits->Get(i), result);
        }
        return result;
    }

    ImmutableBitSequence And(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) & other.bits->Get(i));
        }
        return result;
    }

    ImmutableBitSequence Or(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) | other.bits->Get(i));
        }
        return result;
    }

    ImmutableBitSequence Xor(const ImmutableBitSequence& other) const {
        if(bits->GetSize() != other.bits->GetSize()) {
            throw SizeMismatch();
        }
        ImmutableBitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, bits->Get(i) ^ other.bits->Get(i));
        }
        return result;
    }

    ImmutableBitSequence Not() const {
        ImmutableBitSequence result;
        result.bits->Resize(bits->GetSize());
        for(int i=0; i<bits->GetSize(); i++) {
            result.bits->Set(i, ~bits->Get(i));
        }
        return result;
    }

    ImmutableBitSequence operator&(const ImmutableBitSequence& other) const {
        return this->And(other);
    }

    ImmutableBitSequence operator|(const ImmutableBitSequence& other) const {
        return this->Or(other);
    }   

    ImmutableBitSequence operator^(const ImmutableBitSequence& other) const {
        return this->Xor(other);
    }

    ImmutableBitSequence operator~() const {
        return this->Not();
    }

};