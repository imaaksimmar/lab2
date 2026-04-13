#pragma once
#include <stdexcept>
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"

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

    ~ImmutableBitSequence() {
        delete bits;  
    }

    Bit GetFirst() const override {
        if(bits->GetSize() == 0) 
            throw std::out_of_range("ImmutableBitSequence::GetFirst: empty");
        return bits->Get(0);
    }

    Bit GetLast() const override {
        if(bits->GetSize() == 0) 
            throw std::out_of_range("ImmutableBitSequence::GetLast: empty");
        return bits->Get(bits->GetSize()-1);
    }

    Bit Get(int index) const override {
        if(index<0 || index>=bits->GetSize()) {
            throw std::out_of_range("ImmutableBitSequence::Get: index out of range");
        }
        return bits->Get(index);
    }

    int GetLength() const override {
        return bits->GetSize();
    }

    Sequence<Bit>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=bits->GetSize() || startIndex>endIndex) {
            throw std::out_of_range("ImmutableBitSequence::GetSubsequence: invalid indices");
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
            throw std::out_of_range("ImmutableBitSequence::InsertAt: index out of range");
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
            throw std::invalid_argument("ImmutableBitSequence::Concat: otherSequence is nullptr");
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
            throw std::invalid_argument("ImmutableBitSequence::And: size mismatch");
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
            throw std::invalid_argument("ImmutableBitSequence::Or: size mismatch");
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
            throw std::invalid_argument("ImmutableBitSequence::Xor: size mismatch");
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

    //
    unsigned long long ToMask() const {
        if(bits->GetSize() > 64) {
            throw std::overflow_error("ImmutableBitSequence::ToMask: too many bits for 64-bit mask");
        }
        unsigned long long mask = 0;
        for(int i = 0; i < bits->GetSize(); ++i) {
            if(bits->Get(i).GetValue()) {
                mask |= (1ULL << i);
            }
        }
        return mask;
    }

    static ImmutableBitSequence* FromMask(unsigned long long mask, int bitCount = 64) {
        ImmutableBitSequence* result = new ImmutableBitSequence();
        result->bits->Resize(bitCount);
        for(int i = 0; i < bitCount; ++i) {
            bool bit = (mask >> i) & 1ULL;
            result->bits->Set(i, Bit(bit));
        }
        return result;
    }
    //

    bool IsSet(int index) const {
        if(index < 0 || index >= bits->GetSize()) {
            throw std::out_of_range("ImmutableBitSequence::IsSet: index out of range");
        }
        return bits->Get(index).GetValue();
    }


    void SetBit(int index, bool value) {
            if (index<0 || index>=bits->GetSize()) {
                throw std::out_of_range("BitSequence::SetBit: index out of range");
            }
            bits->Set(index, Bit(value));
        }
};