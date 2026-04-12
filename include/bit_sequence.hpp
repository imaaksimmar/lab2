#pragma once
#include <stdexcept>
#include "sequence.hpp"
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"

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

    ~BitSequence() {
        delete bits;
    }

    Bit GetFirst() const override {
        if(bits->GetSize() == 0) throw std::out_of_range("BitSequence::GetFirst: empty");
        return bits->Get(0);
    }

    Bit GetLast() const override {
        if(bits->GetSize() == 0) throw std::out_of_range("BitSequence::GetLast: empty");
        return bits->Get(bits->GetSize() - 1);
    }

    Bit Get(int index) const override {
        if(index<0 || index>=bits->GetSize()) {
            throw std::out_of_range("BitSequence::Get: index out of range");
        }
        return bits->Get(index);
    }

    int GetLength() const override {
        return bits->GetSize();
    }

    Sequence<Bit>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=bits->GetSize() || startIndex>endIndex) {
            throw std::out_of_range("BitSequence::GetSubsequence: invalid indices");
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
            throw std::out_of_range("BitSequence::InsertAt: index out of range");
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
            throw std::invalid_argument("BitSequence::Concat: otherSequence is nullptr");
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
            throw std::invalid_argument("BitSequence::And: size does not match");
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
            throw std::invalid_argument("BitSequence::Or: size does not match");
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
            throw std::invalid_argument("BitSequence::Xor: size does not match");
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
    
    //
    unsigned long long ToMask() const {
        if (bits->GetSize()>64) {
            throw std::overflow_error("BitSequence::ToMask: too many bits for 64-bit mask");
        }
        unsigned long long mask = 0;
        for (int i = 0; i < bits->GetSize(); ++i) {
            if (bits->Get(i).GetValue()) {
                mask |= (1ULL << i);
            }
        }
        return mask;
    }

    static BitSequence* FromMask(unsigned long long mask, int bitCount = 64) {
        BitSequence* result = new BitSequence();
        result->bits->Resize(bitCount);
        for (int i = 0; i < bitCount; ++i) {
            bool bit = (mask >> i) & 1ULL;
            result->bits->Set(i, Bit(bit));
        }
        return result;
    }

    bool IsSet(int index) const {
        if(index<0 || index >= bits->GetSize()) {
            throw std::out_of_range("BitSequence::IsSet: index out of range");
        }
        return bits->Get(index).GetValue();
    }
    //

};