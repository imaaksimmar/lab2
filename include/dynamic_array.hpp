#pragma once 
#include <stdexcept> 


template <typename T> 
class DynamicArray {
private:
    T* data;
    int size; 
    
public:
    DynamicArray() : data(nullptr), size(0) {}
    DynamicArray(T* items, int count) : data(nullptr), size(0)  { 
        if(count < 0) {
            throw std::invalid_argument("DynamicArray: size cannot be negative");
        }
        size = count;
        data = new T[size];
        for(int i=0; i<size; i++) {
            data[i] = items[i];
        }
    }
    
    DynamicArray(int count) : data(nullptr), size(0) {
        if(count < 0) {  
            throw std::invalid_argument("DynamicArray: count cannot be negative");
        }
        size = count;
        data = new T[size];
    }
    
    DynamicArray(const DynamicArray<T>& otherDynamicArray) : data(nullptr), size(0) {
        size = otherDynamicArray.size;          
        data = new T[size];         
        for(int i=0; i<size; i++) {
            data[i] = otherDynamicArray.data[i]; 
        }
    }
    
    ~DynamicArray() {
        delete[] data;
    }
    
    
    T Get(int index) const { 
        if(index < 0 || index >= size) { 
            throw std::out_of_range("DynamicArray::Get: index out of range");
        }
        return data[index];
    }
    
    int GetSize() const {  
        return size;
    }
    
    void Set(int index, T value) {
        if(index < 0 || index >= size) {  
            throw std::out_of_range("DynamicArray::Set: index out of range");
        }
        data[index] = value;
    }
    
    void Resize(int newSize) {
        if(newSize < 0) {  
            throw std::invalid_argument("DynamicArray::Resize: newSize cannot be negative");
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