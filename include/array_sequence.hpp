#pragma once
#include "sequence.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

// бит, в тестах поправить, интерфейс, мап 
// uint_8 хранить на базе чаров 
// [108] = d[3][12]
// DynamicArray<Bit Pack<int>> d;  вложенность битов над чарами 


template <typename T>
class ArraySequence : public Sequence<T> {
private: 
    DynamicArray<T>* array;
public:
    ArraySequence() : array(new DynamicArray<T>(0)) {}
    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ArraySequence(const ArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}
    
    ArraySequence(const LinkedList<T>& list) 
    : array(new DynamicArray<T>(list.GetLength())) {
        for(int i=0; i<list.GetLength(); i++) {
            array->Set(i, list.Get(i));
        }
    }
    
    ~ArraySequence() { delete array; }

    ArraySequence<T>& operator=(const ArraySequence<T>& other) {
    if(this == &other) {
        return *this;
    }
    delete array;
    array = new DynamicArray<T>(*other.array);
    return *this;
    }

    T& operator[](int index) { 
        return (*array)[index]; 
     }


    T GetFirst() const override { 
        if(array->GetSize() == 0)
            throw EmptyCollection();
        return array->Get(0);
    }

    T GetLast() const override {
        if(array->GetSize() == 0)
            throw EmptyCollection();
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize())
            throw IndexOutOfRange();
        return array->Get(index);
    }

    int GetLength() const override {
        return array->GetSize();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=array->GetSize() || startIndex>endIndex)
            throw InvalidArgument();
        
        ArraySequence<T>* result = new ArraySequence<T>();
        for(int i=startIndex; i<=endIndex; i++) {
            result->Append(array->Get(i));
        }
        return result;
    }

    Sequence<T>* Append(T item) override {
        array->Resize(array->GetSize() + 1);
        array->Set(array->GetSize()- 1, item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for(int i=oldSize; i>0; i--) {
            array->Set(i, array->Get(i- 1));
        }
        array->Set(0, item);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if(index<0 || index>array->GetSize())
            throw IndexOutOfRange();
        
        int oldSize = array->GetSize();
        array->Resize(oldSize + 1);
        for(int i=oldSize; i>index; i--) {
            array->Set(i, array->Get(i-1));
        }
        array->Set(index, item);
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
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

