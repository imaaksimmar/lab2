#include "assert.hpp"
#include <iostream>
#include "../include/dynamic_array.hpp"
#include "../include/linked_list.hpp"
#include "../include/array_sequence.hpp"
#include "../include/list_sequence.hpp"
#include "../include/immutable_array_sequence.hpp"
#include "../include/immutable_list_sequence.hpp"
#include "../include/bit.hpp"
#include "../include/bit_sequence.hpp"
#include "../include/immutable_bit_sequence.hpp"
#include "../include/exceptions.hpp"



void testDynamicArrayConstructors() {
    DynamicArray<int> a(0);
    assert(a.GetSize() == 0);

    DynamicArray<int> b(5);
    assert(b.GetSize() == 5);

    int items[] = {1, 2, 3};
    DynamicArray<int> c(items, 3);
    assert(c.GetSize() == 3);
    assert(c.Get(0) == 1);
    assert(c.Get(2) == 3);

    DynamicArray<int> d(c);
    assert(d.GetSize() == 3);
    assert(d.Get(1) == 2);
}

void testDynamicArrayGet() {
    int items[] = {10, 20, 30};
    DynamicArray<int> a(items, 3);
    assert(a.Get(0) == 10);
    assert(a.Get(1) == 20);
    assert(a.Get(2) == 30);
}

void testDynamicArraySet() {
    DynamicArray<int> a(3);
    a.Set(0, 7);
    a.Set(1, 8);
    a.Set(2, 9);
    assert(a.Get(0) == 7);
    assert(a.Get(1) == 8);
    assert(a.Get(2) == 9);
}

void testDynamicArrayResize() {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    a.Resize(5);
    assert(a.GetSize() == 5);
    assert(a.Get(0) == 1);
    assert(a.Get(2) == 3);
    a.Resize(2);
    assert(a.GetSize() == 2);
    assert(a.Get(1) == 2);
}

void testDynamicArrayExceptions() {
    DynamicArray<int> a(3);
    bool caught = false;
    
    try { a.Get(-1); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);

    caught = false;
    try { a.Get(3); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);

    caught = false;
    try { a.Set(5, 0); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);

    caught = false;
    try { DynamicArray<int> bad(-1); } 
    catch(const Exceptions&) { caught = true; } //
    assert(caught);
}




void testLinkedListConstructors() {
    LinkedList<int> empty;
    assert(empty.GetLength() == 0);

    int items[] = {1, 2, 3};
    LinkedList<int> a(items, 3);
    assert(a.GetLength() == 3);
    assert(a.Get(0) == 1);

    LinkedList<int> b(a);
    assert(b.GetLength() == 3);
    assert(b.Get(2) == 3);
}

void testLinkedListGetFirstLast() {
    int items[] = {5, 10, 15};
    LinkedList<int> a(items, 3);
    assert(a.GetFirst() == 5);
    assert(a.GetLast() == 15);
}

void testLinkedListGet() {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> a(items, 5);
    assert(a.Get(0) == 1);
    assert(a.Get(4) == 5);
    assert(a.Get(2) == 3);
}

void testLinkedListAppendPrepend() {
    LinkedList<int> a;
    a.Append(1);
    a.Append(2);
    a.Append(3);
    assert(a.GetLength() == 3);
    assert(a.GetLast() == 3);
    a.Prepend(0);
    assert(a.GetLength() == 4);
    assert(a.GetFirst() == 0);
}

void testLinkedListInsertAt() {
    int items[] = {1, 3, 4};
    LinkedList<int> a(items, 3);
    a.InsertAt(2, 1);
    assert(a.GetLength() == 4);
    assert(a.Get(1) == 2);
    assert(a.Get(2) == 3);
}

void testLinkedListGetSubList() {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> a(items, 5);
    LinkedList<int>* sub = a.GetSubList(1, 3);

    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 2);
    assert(sub->Get(2) == 4);
    delete sub;
}

void testLinkedListConcat() {
    int a_items[] = {1, 2};
    int b_items[] = {3, 4};

    LinkedList<int> a(a_items, 2);
    LinkedList<int> b(b_items, 2);
    LinkedList<int>* c = a.Concat(&b);

    assert(c->GetLength() == 4);
    assert(c->Get(0) == 1);
    assert(c->Get(3) == 4);
    delete c;
}

void testLinkedListExceptions() {
    LinkedList<int> empty;
    bool caught = false;
    
    try { empty.GetFirst(); } 
    catch (const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { empty.GetLast(); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    int items[] = {1, 2};
    LinkedList<int> a(items, 2);
    
    caught = false;
    try { a.Get(-1); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { a.Get(5); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
}



void testArraySequenceConstructors() {
    ArraySequence<int> empty;
    assert(empty.GetLength() == 0);
    int items[] = {1, 2, 3};

    ArraySequence<int> a(items, 3);
    assert(a.GetLength() == 3);
    assert(a.Get(0) == 1);

    ArraySequence<int> b(a);
    assert(b.GetLength() == 3);
    assert(b.Get(2) == 3);
    LinkedList<int> ll(items, 3);
    ArraySequence<int> c(ll);

    assert(c.GetLength() == 3);
    assert(c.Get(1) == 2);
}

void testArraySequenceGetFirstLast() {
    int items[] = {10, 20, 30};
    ArraySequence<int> a(items, 3);
    assert(a.GetFirst() == 10);
    assert(a.GetLast() == 30);
}

void testArraySequenceGet() {
    int items[] = {5, 6, 7};
    ArraySequence<int> a(items, 3);

    assert(a.Get(0) == 5);
    assert(a.Get(1) == 6);
    assert(a.Get(2) == 7);
}

void testArraySequenceAppendPrepend() {
    ArraySequence<int> a;
    a.Append(1);
    a.Append(2);

    assert(a.GetLength() == 2);
    assert(a.GetLast() == 2);
    a.Prepend(0);
    assert(a.GetLength() == 3);
    assert(a.GetFirst() == 0);
}

void testArraySequenceInsertAt() {
    int items[] = {1, 3};
    ArraySequence<int> a(items, 2);
    a.InsertAt(2, 1);

    assert(a.GetLength() == 3);
    assert(a.Get(1) == 2);
    assert(a.Get(2) == 3);
}

void testArraySequenceGetSubsequence() {
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> a(items, 5);
    Sequence<int>* sub = a.GetSubsequence(1, 3);

    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 2);
    assert(sub->Get(2) == 4);
    delete sub;
}

void testArraySequenceConcat() {
    int a_items[] = {1, 2};
    int b_items[] = {3, 4};

    ArraySequence<int> a(a_items, 2);
    ArraySequence<int> b(b_items, 2);
    a.Concat(&b);
    assert(a.GetLength() == 4);
    assert(a.Get(3) == 4);
}

void testArraySequenceMap() {
    int items[] = {1, 2, 3};
    ArraySequence<int> a(items, 3);
    Sequence<int>* mapped = a.Map([](int x) { return x * 2; });

    assert(mapped->Get(0) == 2);
    assert(mapped->Get(1) == 4);
    assert(mapped->Get(2) == 6);
    delete mapped;
}

void testArraySequenceWhere() {
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> a(items, 5);
    Sequence<int>* filtered = a.Where([](int x) { return x % 2 == 0; });
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 2);
    assert(filtered->Get(1) == 4);
    delete filtered;
}

void testArraySequenceReduce() {
    int items[] = {1, 2, 3};
    ArraySequence<int> a(items, 3);
    int result = a.Reduce([](int acc, int x) { return acc + x; }, 0);
    assert(result == 6);
}

void testArraySequenceExceptions() {
    ArraySequence<int> empty;
    bool caught = false;
    
    try { empty.GetFirst(); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { empty.GetLast(); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    int items[] = {1, 2, 3};
    ArraySequence<int> a(items, 3);
    
    caught = false;
    try { a.Get(-1); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { a.GetSubsequence(2, 1); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { a.Concat(nullptr); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
}



void testListSequenceConstructors() {
    ListSequence<int> empty;
    assert(empty.GetLength() == 0);
    int items[] = {1, 2, 3};

    ListSequence<int> a(items, 3);
    assert(a.GetLength() == 3);
    assert(a.Get(0) == 1);
    ListSequence<int> b(a);

    assert(b.GetLength() == 3);
    LinkedList<int> ll(items, 3);
    ListSequence<int> c(ll);
    assert(c.GetLength() == 3);
    assert(c.Get(2) == 3);
}

void testListSequenceGetFirstLast() {
    int items[] = {7, 8, 9};
    ListSequence<int> a(items, 3);
    assert(a.GetFirst() == 7);
    assert(a.GetLast() == 9);
}

void testListSequenceGet() {
    int items[] = {4, 5, 6};
    ListSequence<int> a(items, 3);
    assert(a.Get(0) == 4);
    assert(a.Get(2) == 6);
}

void testListSequenceAppendPrepend() {
    ListSequence<int> a;
    a.Append(1);
    a.Append(2);
    assert(a.GetLast() == 2);
    a.Prepend(0);
    assert(a.GetFirst() == 0);
    assert(a.GetLength() == 3);
}

void testListSequenceInsertAt() {
    int items[] = {1, 3};
    ListSequence<int> a(items, 2);
    a.InsertAt(2, 1);

    assert(a.GetLength() == 3);
    assert(a.Get(1) == 2);
}

void testListSequenceGetSubsequence() {
    int items[] = {10, 20, 30, 40};
    ListSequence<int> a(items, 4);
    Sequence<int>* sub = a.GetSubsequence(0, 2);

    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 10);
    assert(sub->Get(2) == 30);
    delete sub;
}

void testListSequenceConcat() {
    int a_items[] = {1, 2};
    int b_items[] = {3, 4};

    ListSequence<int> a(a_items, 2);
    ListSequence<int> b(b_items, 2);

    a.Concat(&b);
    assert(a.GetLength() == 4);
    assert(a.GetLast() == 4);
}

void testListSequenceMap() {
    int items[] = {1, 2, 3};
    ListSequence<int> a(items, 3);
    Sequence<int>* mapped = a.Map([](int x) { return x * 2; });

    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);
    delete mapped;
}

void testListSequenceWhere() {
    int items[] = {1, 2, 3, 4};
    ListSequence<int> a(items, 4);
    Sequence<int>* filtered = a.Where([](int x) { return x % 2 == 0; });

    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 2);
    delete filtered;
}

void testListSequenceReduce() {
    int items[] = {1, 2, 3};
    ListSequence<int> a(items, 3);
    int result = a.Reduce([](int acc, int x) { return acc + x; }, 0);
    assert(result == 6);
}

void testListSequenceExceptions() {
    ListSequence<int> empty;
    bool caught = false;
    
    try { empty.GetFirst(); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { empty.GetLast(); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
    
    int items[] = {1, 2};
    ListSequence<int> a(items, 2);
    
    caught = false;
    try { a.Concat(nullptr); } 
    catch(const Exceptions&) { caught = true; }
    assert(caught);
}



void testImmutableArraySequenceConstructors() {
    ImmutableArraySequence<int> empty;
    assert(empty.GetLength() == 0);
    int items[] = {1, 2, 3};

    ImmutableArraySequence<int> a(items, 3);
    assert(a.GetLength() == 3);
    assert(a.Get(0) == 1);

    ImmutableArraySequence<int> b(a);
    assert(b.GetLength() == 3);
    LinkedList<int> ll(items, 3);
    ImmutableArraySequence<int> c(ll);
    assert(c.GetLength() == 3);
    assert(c.Get(1) == 2);
}

void testImmutableArraySequenceGetFirstLast() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> a(items, 3);
    assert(a.GetFirst() == 1);
    assert(a.GetLast() == 3);
}

void testImmutableArraySequenceGet() {
    int items[] = {4, 5, 6};
    ImmutableArraySequence<int> a(items, 3);
    assert(a.Get(1) == 5);
}

void testImmutableArraySequenceAppendPrepend() {
    int items[] = {2, 3};
    ImmutableArraySequence<int> a(items, 2);
    Sequence<int>* b = a.Append(4);
    assert(b->GetLength() == 3);
    assert(b->GetLast() == 4);
    delete b;
    Sequence<int>* c = a.Prepend(1);
    assert(c->GetLength() == 3);
    assert(c->GetFirst() == 1);
    delete c;
}

void testImmutableArraySequenceInsertAt() {
    int items[] = {1, 3};
    ImmutableArraySequence<int> a(items, 2);
    Sequence<int>* b = a.InsertAt(2, 1);

    assert(b->GetLength() == 3);
    assert(b->Get(1) == 2);
    delete b;
}

void testImmutableArraySequenceGetSubsequence() {
    int items[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> a(items, 5);
    Sequence<int>* sub = a.GetSubsequence(1, 3);

    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 2);
    delete sub;
}

void testImmutableArraySequenceConcat() {
    int a_items[] = {1, 2};
    int b_items[] = {3, 4};

    ImmutableArraySequence<int> a(a_items, 2);
    ImmutableArraySequence<int> b(b_items, 2);
    Sequence<int>* c = a.Concat(&b);

    assert(c->GetLength() == 4);
    assert(c->Get(3) == 4);
    delete c;
}

void testImmutableArraySequenceMap() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> a(items, 3);
    Sequence<int>* mapped = a.Map([](int x) { return x * 2; });
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);
    delete mapped;
}

void testImmutableArraySequenceWhere() {
    int items[] = {1, 2, 3, 4};
    ImmutableArraySequence<int> a(items, 4);
    Sequence<int>* filtered = a.Where([](int x) { return x % 2 == 0; });
    assert(filtered->GetLength() == 2);
    delete filtered;
}

void testImmutableArraySequenceReduce() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> a(items, 3);
    int result = a.Reduce([](int acc, int x) { return acc + x; }, 0);
    assert(result == 6);
}

void testImmutableArraySequenceImmutability() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> a(items, 3);
    int lenBefore = a.GetLength();
    Sequence<int>* b = a.Append(99);

    assert(a.GetLength() == lenBefore);
    assert(b->GetLength() == lenBefore + 1);
    delete b;

    Sequence<int>* c = a.Prepend(0);
    assert(a.GetLength() == lenBefore);
    delete c;
}



void testImmutableListSequenceConstructors() {
    ImmutableListSequence<int> empty;
    assert(empty.GetLength() == 0);
    int items[] = {1, 2, 3};

    ImmutableListSequence<int> a(items, 3);
    assert(a.GetLength() == 3);
    assert(a.Get(0) == 1);

    ImmutableListSequence<int> b(a);
    assert(b.GetLength() == 3);
}

void testImmutableListSequenceGetFirstLast() {
    int items[] = {5, 10, 15};
    ImmutableListSequence<int> a(items, 3);
    assert(a.GetFirst() == 5);
    assert(a.GetLast() == 15);
}

void testImmutableListSequenceGet() {
    int items[] = {7, 8, 9};
    ImmutableListSequence<int> a(items, 3);
    assert(a.Get(1) == 8);
}

void testImmutableListSequenceAppendPrepend() {
    int items[] = {2, 3};
    ImmutableListSequence<int> a(items, 2);
    Sequence<int>* b = a.Append(4);
    assert(b->GetLength() == 3);
    assert(b->GetLast() == 4);
    delete b;

    Sequence<int>* c = a.Prepend(1);
    assert(c->GetFirst() == 1);
    delete c;
}

void testImmutableListSequenceInsertAt() {
    int items[] = {1, 3};
    ImmutableListSequence<int> a(items, 2);
    Sequence<int>* b = a.InsertAt(2, 1);
    assert(b->Get(1) == 2);
    delete b;
}

void testImmutableListSequenceGetSubsequence() {
    int items[] = {1, 2, 3, 4};
    ImmutableListSequence<int> a(items, 4);
    Sequence<int>* sub = a.GetSubsequence(0, 2);
    assert(sub->GetLength() == 3);
    assert(sub->Get(2) == 3);
    delete sub;
}

void testImmutableListSequenceConcat() {
    int a_items[] = {1, 2};
    int b_items[] = {3, 4};

    ImmutableListSequence<int> a(a_items, 2);
    ImmutableListSequence<int> b(b_items, 2);
    Sequence<int>* c = a.Concat(&b);

    assert(c->GetLength() == 4);
    assert(c->Get(2) == 3);
    delete c;
}

void testImmutableListSequenceMap() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> a(items, 3);
    Sequence<int>* mapped = a.Map([](int x) { return x * 2; });
    assert(mapped->Get(1) == 4);
    delete mapped;
}

void testImmutableListSequenceWhere() {
    int items[] = {1, 2, 3, 4};
    ImmutableListSequence<int> a(items, 4);
    Sequence<int>* filtered = a.Where([](int x) { return x % 2 == 0; });
    assert(filtered->GetLength() == 2);
    delete filtered;
}

void testImmutableListSequenceReduce() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> a(items, 3);
    int result = a.Reduce([](int acc, int x) { return acc + x; }, 0);
    assert(result == 6);
}

void testImmutableListSequenceImmutability() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> a(items, 3);
    int lenBefore = a.GetLength();
    Sequence<int>* b = a.Append(99);

    assert(a.GetLength() == lenBefore);
    assert(b->GetLength() == lenBefore + 1);
    delete b;
}



void testBitSequenceConstructors() {
    BitSequence empty;
    assert(empty.GetLength() == 0);
    Bit items[] = {Bit(1), Bit(0), Bit(1)};
    BitSequence a(items, 3);

    assert(a.GetLength() == 3);
    assert(a.Get(0).GetValue() == true);
    assert(a.Get(1).GetValue() == false);
    BitSequence b(a);
    assert(b.GetLength() == 3);
}

void testBitSequenceGetFirstLast() {
    Bit items[] = {Bit(1), Bit(0), Bit(1)};
    BitSequence a(items, 3);

    assert(a.GetFirst().GetValue() == true);
    assert(a.GetLast().GetValue() == true);
}

void testBitSequenceGet() {
    Bit items[] = {Bit(0), Bit(1), Bit(0)};
    BitSequence a(items, 3);
    assert(a.Get(1).GetValue() == true);
}

void testBitSequenceAppendPrepend() {
    BitSequence a;
    a.Append(Bit(1));
    a.Append(Bit(0));

    assert(a.GetLength() == 2);
    assert(a.GetFirst().GetValue() == true);
    a.Prepend(Bit(0));
    assert(a.GetFirst().GetValue() == false);
    assert(a.GetLength() == 3);
}

void testBitSequenceInsertAt() {
    Bit items[] = {Bit(1), Bit(1)};
    BitSequence a(items, 2);
    a.InsertAt(Bit(0), 1);
    assert(a.GetLength() == 3);
    assert(a.Get(1).GetValue() == false);
}

void testBitSequenceGetSubsequence() {
    Bit items[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
    BitSequence a(items, 4);
    Sequence<Bit>* sub = a.GetSubsequence(1, 2);
    assert(sub->GetLength() == 2);
    assert(sub->Get(0).GetValue() == false);
    delete sub;
}

void testBitSequenceConcat() {
    Bit a_items[] = {Bit(1), Bit(0)};
    Bit b_items[] = {Bit(0), Bit(1)};
    BitSequence a(a_items, 2);
    BitSequence b(b_items, 2);
    a.Concat(&b);
    assert(a.GetLength() == 4);
    assert(a.GetLast().GetValue() == true);
}

void testBitSequenceMap() {
    Bit items[] = {Bit(1), Bit(0), Bit(1)};
    BitSequence a(items, 3);

    Sequence<Bit>* mapped = a.Map([](Bit b) { return ~b; });
    assert(mapped->Get(0).GetValue() == false);
    assert(mapped->Get(1).GetValue() == true);
    delete mapped;
}

void testBitSequenceWhere() {
    Bit items[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
    BitSequence a(items, 4);

    Sequence<Bit>* ones = a.Where([](Bit b) { return b.GetValue(); });
    assert(ones->GetLength() == 2);
    delete ones;
}

void testBitSequenceReduce() {
    Bit items[] = {Bit(1), Bit(0), Bit(1)};
    BitSequence a(items, 3);

    Bit result = a.Reduce([](Bit x, Bit acc) { return x | acc; }, Bit(0));
    assert(result.GetValue() == true);
}

void testBitSequenceBitwiseOps() {
    Bit a_items[] = {Bit(1), Bit(0), Bit(1), Bit(0)};
    Bit b_items[] = {Bit(1), Bit(1), Bit(0), Bit(0)};

    BitSequence a(a_items, 4);
    BitSequence b(b_items, 4);

    BitSequence andRes = a & b;
    assert(andRes.Get(0).GetValue() == true);
    assert(andRes.Get(1).GetValue() == false);
    assert(andRes.Get(2).GetValue() == false);

    BitSequence orRes = a | b;
    assert(orRes.Get(0).GetValue() == true);
    assert(orRes.Get(1).GetValue() == true);
    assert(orRes.Get(3).GetValue() == false);

    BitSequence xorRes = a ^ b;
    assert(xorRes.Get(0).GetValue() == false);
    assert(xorRes.Get(1).GetValue() == true);

    BitSequence notRes = ~a;
    assert(notRes.Get(0).GetValue() == false);
    assert(notRes.Get(1).GetValue() == true);
}


void testBitSequenceExceptions() {
    BitSequence empty;
    bool caught = false;
    
    try { empty.GetFirst(); } catch (const Exceptions&) { caught = true; }
    assert(caught);

    Bit items[] = {Bit(1), Bit(0)};
    BitSequence a(items, 2);
    
    caught = false;
    try { a.Get(-1); } catch (const Exceptions&) { caught = true; }
    assert(caught);

    caught = false;
    try { a.Concat(nullptr); } catch (const Exceptions&) { caught = true; }
    assert(caught);

    Bit c_items[] = {Bit(1)};
    BitSequence c(c_items, 1);
    caught = false;
    try { a & c; } catch (const Exceptions&) { caught = true; }
    assert(caught);
}



void testImmutableBitSequenceConstructors() {
    ImmutableBitSequence empty;
    assert(empty.GetLength() == 0);
    Bit items[] = {Bit(1), Bit(0), Bit(1)};
    ImmutableBitSequence a(items, 3);
    
    assert(a.GetLength() == 3);
    assert(a.Get(0).GetValue() == true);
    ImmutableBitSequence b(a);
    assert(b.GetLength() == 3);
}

void testImmutableBitSequenceBitwiseOps() {
    Bit a_items[] = {Bit(1), Bit(0)};
    Bit b_items[] = {Bit(0), Bit(1)};
    ImmutableBitSequence a(a_items, 2);
    ImmutableBitSequence b(b_items, 2);

    ImmutableBitSequence andRes = a & b;
    assert(andRes.Get(0).GetValue() == false);
    assert(andRes.Get(1).GetValue() == false);

    ImmutableBitSequence orRes = a | b;
    assert(orRes.Get(0).GetValue() == true);
    assert(orRes.Get(1).GetValue() == true);

    ImmutableBitSequence xorRes = a ^ b;
    assert(xorRes.Get(0).GetValue() == true);
    assert(xorRes.Get(1).GetValue() == true);

    ImmutableBitSequence notRes = ~a;
    assert(notRes.Get(0).GetValue() == false);
    assert(notRes.Get(1).GetValue() == true);
}

void testImmutableBitSequenceImmutability() {
    Bit items[] = {Bit(1), Bit(0)};
    ImmutableBitSequence a(items, 2);
    int lenBefore = a.GetLength();
    Sequence<Bit>* b = a.Append(Bit(1));
    assert(a.GetLength() == lenBefore);
    assert(b->GetLength() == lenBefore + 1);
    delete b;
}
