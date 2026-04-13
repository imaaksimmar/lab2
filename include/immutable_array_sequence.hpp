#pragma once
#include <stdexcept>
#include "sequence.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp" 

template <typename T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* array;

public:
    ImmutableArraySequence() : array(new DynamicArray<T>(0)) {}
    ImmutableArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}  
    
    ImmutableArraySequence(const LinkedList<T>& list) 
    : array(new DynamicArray<T>(list.GetLength())) {
        for(int i=0; i<list.GetLength(); i++) {
            array->Set(i, list.Get(i));
        }
    }

    ~ImmutableArraySequence() {
        delete array;
    }

    T GetFirst() const override { 
        if(array->GetSize() == 0) throw std::out_of_range("ImmutableArraySequence::GetFirst: empty");
        return array->Get(0);
    }

    T GetLast() const override {
        if(array->GetSize() == 0) throw std::out_of_range("ImmutableArraySequence::GetLast: empty");
        return array->Get(array->GetSize()-1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize()) throw std::out_of_range("ImmutableArraySequence::Get: out of range");
        return array->Get(index);
    }

    int GetLength() const override { 
        return array->GetSize(); 
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=array->GetSize() || startIndex>endIndex)
            throw std::out_of_range("ImmutableArraySequence::GetSubsequence: invalid indices");
        
        int subSize = endIndex - startIndex + 1;
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        result->array->Resize(subSize); 
        for(int i=0; i<subSize; i++) {
            result->array->Set(i, array->Get(startIndex+i));
        }
        return result;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        result->array->Resize(array->GetSize());
        for(int i=0; i<array->GetSize(); i++) {
            result->array->Set(i, func(array->Get(i)));
        }
        return result; 
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        for(int i=0; i<array->GetSize(); i++) {
            if(predicate(array->Get(i))) {
                result->array->Resize(result->array->GetSize()+1);
                result->array->Set(result->array->GetSize()-1, array->Get(i));
            }
        }
        return result;
    }

    T Reduce(T (*func)(T, T), T initial) const override {
        T result = initial;
        for(int i=0; i<array->GetSize(); i++) {
            result = func(array->Get(i), result);
        }
        return result;
    }

    
    Sequence<T>* Append(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        copy->array->Resize(copy->array->GetSize() + 1);
        copy->array->Set(copy->array->GetSize() - 1, item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        copy->array->Resize(oldSize+1);
        for(int i=oldSize; i>0; i--) {
            copy->array->Set(i, copy->array->Get(i-1));
        }
        copy->array->Set(0, item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if(index < 0 || index > array->GetSize())
            throw std::out_of_range("ImmutableArraySequence::InsertAt: index out of range");
        
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        copy->array->Resize(oldSize+ 1);
        for(int i=oldSize; i>index; i--) {
            copy->array->Set(i, copy->array->Get(i-1));
        }
        copy->array->Set(index, item);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw std::invalid_argument("ImmutableArraySequence::Concat: nullptr");
        }
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        int otherSize = otherSequence->GetLength();
        copy->array->Resize(oldSize+otherSize);
        for(int i=0; i<otherSize; i++) {
            copy->array->Set(oldSize+i, otherSequence->Get(i));
        }
        return copy;
    }
};
