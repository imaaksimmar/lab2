#pragma once
#include <stdexcept>
#include "sequence.hpp"
#include "dynamic_array.hpp"


template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* array;
public:
    ArraySequence() : array(new DynamicArray<T>(0)) {}
    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ArraySequence(const ArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}
    
    ~ArraySequence() {
        delete array;
    }
    
    T GetFirst() const override { 
        if(array->GetSize() == 0)
            throw std::out_of_range("ArraySequence::GetFirst: sequence is empty");
        return array->Get(0);
    }

    T GetLast() const override {
        if(array->GetSize() == 0)
            throw std::out_of_range("ArraySequence::GetLast: sequence is empty");
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize())
            throw std::out_of_range("ArraySequence::Get: index out of range");
        return array->Get(index);
    }

    int GetLength() const override {
        return array->GetSize();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=array->GetSize() || startIndex>endIndex)
            throw std::out_of_range("ArraySequence::GetSubsequence: invalid indices");
        
        ArraySequence<T>* result = new ArraySequence<T>();
        for(int i=startIndex; i<=endIndex; i++) {
            result->Append(array->Get(i));
        }
        return result;
    }

    Sequence<T>* Append(T item) override {
        array->Resize(array->GetSize() + 1);
        array->Set(array->GetSize() - 1, item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for(int i=oldSize; i>0; i--) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(0, item);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if(index<0 || index>array->GetSize())
            throw std::out_of_range("ArraySequence::InsertAt: index out of range");
        
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for(int i=oldSize; i>index; i--) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(index, item);
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw std::invalid_argument("ArraySequence::Concat: otherSequence is nullptr");
        }
        for(int i=0; i<otherSequence->GetLength(); i++) {
            this->Append(otherSequence->Get(i));
        }
        return this;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        ArraySequence<T>* result = new ArraySequence<T>();
        for(int i=0; i<array->GetSize(); i++) {
            result->Append(func(array->Get(i)));
        }
        return result; 
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        ArraySequence<T>* result = new ArraySequence<T>();
        for(int i=0; i<array->GetSize(); i++) {
            T item = array->Get(i);
            if(predicate(item)) {
                result->Append(item);
            }
        }
        return result;
    }

    T Reduce(T (*func)(T, T), T initial) const override {
        T result = initial;
        for(int i=0; i<array->GetSize(); i++) {
            result = func(result, array->Get(i));      
        }
        return result;
    }
};

