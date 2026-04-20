#pragma once 
#include "exceptions.hpp"


template <typename T> 
class DynamicArray {
private:
    T* data;
    uint32_t size; // поменять 
    
public:
    DynamicArray() : data(nullptr), size(0) {}

    DynamicArray(uint32_t count) : data(nullptr), size(0) {
        if(count < 0) {  
            throw InvalidArgument();
        }
        size = count;
        data = new T[size];
    }

    DynamicArray(T* items, uint32_t count) : DynamicArray(count) {
        if(count>0 && items==nullptr) {
            throw InvalidArgument();
        }
        for(int i=0; i<size; i++) {
            data[i] = items[i];
        }
    }
    
    DynamicArray(const DynamicArray<T>& otherDynamicArray) 
    : DynamicArray(otherDynamicArray.data, otherDynamicArray.size) {}
    
    ~DynamicArray() { delete[] data; }
    
    DynamicArray<T>& operator=(const DynamicArray<T>& otherDynamicArray ) {
        if(this == &otherDynamicArray) { return *this; }
        
        delete[] data;
        size = otherDynamicArray.size;
        data = new T[size];
        for(int i=0; i<size; i++) {
            data[i] = otherDynamicArray.data[i];
        }
        return *this;
    }
    
    T& operator[](int index) {
        if(index<0 || index>=size) {
            throw IndexOutOfRange();
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if(index < 0 || index >= size) { 
            throw IndexOutOfRange();
         }
        return data[index];
    }   
    
    T Get(int index) const { 
        if(index < 0 || index >= size) { 
            throw IndexOutOfRange();
        }
        return data[index];
    }
    
    int GetSize() const {  
        return size;
    }
    
    void Set(int index, T value) {
        if(index < 0 || index >= size) {  
            throw IndexOutOfRange();
        }
        data[index] = value;
    }
    
    void Resize(int newSize) {
        if(newSize < 0) {  
            throw InvalidArgument();
        }
        T* newData = new T[newSize];
        int copyLen = (newSize<size) ? newSize : size;  
        
        for(int i=0; i<copyLen; i++) {
            newData[i] = data[i];
        }
        
        delete[] data;   
        data = newData; 
        size = newSize;  
    }
}; 