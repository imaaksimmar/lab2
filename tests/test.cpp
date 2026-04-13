#include <stdexcept>
#include "assert.hpp"
#include "dynamic_array.hpp"
#include <cstdio>
#include <cassert>


void testDefaultConstructor() {
    printf("----- DynamicArray: default constructor -----\n");
    DynamicArray<int> arr;
    assert(arr.GetSize() == 0);
}


void testConstructorFromArray() {
    printf("----- DynamicArray: constructor from array -----\n");
    int data[] = {10, 20, 30};
    DynamicArray<int> arr(data, 3);
    
    assert(arr.GetSize() == 3);
    assert(arr.Get(0) == 10);
    assert(arr.Get(1) == 20);
    assert(arr.Get(2) == 30);
}


void testCopyConstructor() {
    printf("----- DynamicArray: copy constructor -----\n");
    int data[] = {1, 2, 3};
    DynamicArray<int> original(data, 3);
    DynamicArray<int> copy(original);
    
    assert(copy.GetSize() == 3);
    assert(copy.Get(1) == 2);
    
    original.Set(1, 999);
    assert(copy.Get(1) == 2);        
    assert(original.Get(1) == 999); 
}

// ===== Тест 4: Get() с неверным индексом =====
void testGetThrowsOnInvalidIndex() {
    printf("----- DynamicArray: Get throws on invalid index -----\n");
    DynamicArray<int> arr;
    
    bool caught = false;
    try { arr.Get(0); } catch (const std::out_of_range&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { arr.Get(-5); } catch (const std::out_of_range&) { caught = true; }
    assert(caught);
    
    int data[] = {1, 2};
    DynamicArray<int> arr2(data, 2);
    
    caught = false;
    try { arr2.Get(2); } catch (const std::out_of_range&) { caught = true; }
    assert(caught);
}

// ===== Тест 5: Set() меняет значение =====
void testSetChangesValue() {
    printf("----- DynamicArray: Set changes value -----\n");
    int data[] = {10, 20, 30};
    DynamicArray<int> arr(data, 3);
    
    arr.Set(1, 999);
    assert(arr.Get(1) == 999);
    assert(arr.Get(0) == 10);  // Остальные не тронулись
}
