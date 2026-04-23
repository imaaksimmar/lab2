#include "assert.hpp"
#include "test.hpp"
#include <iostream>


int main() {
    testDynamicArrayConstructors(); std::cout << "testDynamicArrayConstructors\n";
    testDynamicArrayGet(); std::cout << "testDynamicArrayGet\n";
    testDynamicArraySet(); std::cout << "testDynamicArraySet\n";
    testDynamicArrayResize(); std::cout << "testDynamicArrayResize\n";
    testDynamicArrayExceptions(); std::cout << "testDynamicArrayExceptions\n";


    testLinkedListConstructors(); std::cout << "testLinkedListConstructors\n";
    testLinkedListGetFirstLast(); std::cout << "testLinkedListGetFirstLast\n";
    testLinkedListGet(); std::cout << "testLinkedListGet\n";
    testLinkedListAppendPrepend(); std::cout << "testLinkedListAppendPrepend\n";
    testLinkedListInsertAt(); std::cout << "testLinkedListInsertAt\n";
    testLinkedListGetSubList(); std::cout << "testLinkedListGetSubList\n";
    testLinkedListConcat(); std::cout << "testLinkedListConcat\n";
    testLinkedListExceptions(); std::cout << "testLinkedListExceptions\n";

   
    testArraySequenceConstructors(); std::cout << "testArraySequenceConstructors\n";
    testArraySequenceGetFirstLast(); std::cout << "testArraySequenceGetFirstLast\n";
    testArraySequenceGet(); std::cout << "testArraySequenceGet\n";
    testArraySequenceAppendPrepend(); std::cout << "testArraySequenceAppendPrepend\n";
    testArraySequenceInsertAt(); std::cout << "testArraySequenceInsertAt\n";
    testArraySequenceGetSubsequence(); std::cout << "testArraySequenceGetSubsequence\n";
    testArraySequenceConcat(); std::cout << "testArraySequenceConcat\n";
    testArraySequenceMap(); std::cout << "testArraySequenceMap\n";
    testArraySequenceWhere(); std::cout << "testArraySequenceWhere\n";
    testArraySequenceReduce(); std::cout << "testArraySequenceReduce\n";
    testArraySequenceExceptions(); std::cout << "testArraySequenceExceptions\n";


    testListSequenceConstructors(); std::cout << "testListSequenceConstructors\n";
    testListSequenceGetFirstLast(); std::cout << "testListSequenceGetFirstLast\n";
    testListSequenceGet(); std::cout << "testListSequenceGet\n";
    testListSequenceAppendPrepend(); std::cout << "testListSequenceAppendPrepend\n";
    testListSequenceInsertAt(); std::cout << "testListSequenceInsertAt\n";
    testListSequenceGetSubsequence(); std::cout << "testListSequenceGetSubsequence\n";
    testListSequenceConcat(); std::cout << "testListSequenceConcat\n";
    testListSequenceMap(); std::cout << "testListSequenceMap\n";
    testListSequenceWhere(); std::cout << "testListSequenceWhere\n";
    testListSequenceReduce(); std::cout << "testListSequenceReduce\n";
    testListSequenceExceptions(); std::cout << "testListSequenceExceptions\n";


    testImmutableArraySequenceConstructors(); std::cout << "testImmutableArraySequenceConstructors\n";
    testImmutableArraySequenceGetFirstLast(); std::cout << "testImmutableArraySequenceGetFirstLast\n";
    testImmutableArraySequenceGet(); std::cout << "testImmutableArraySequenceGet\n";
    testImmutableArraySequenceAppendPrepend(); std::cout << "testImmutableArraySequenceAppendPrepend\n";
    testImmutableArraySequenceInsertAt(); std::cout << "testImmutableArraySequenceInsertAt\n";
    testImmutableArraySequenceGetSubsequence(); std::cout << "testImmutableArraySequenceGetSubsequence\n";
    testImmutableArraySequenceConcat(); std::cout << "testImmutableArraySequenceConcat\n";
    testImmutableArraySequenceMap(); std::cout << "testImmutableArraySequenceMap\n";
    testImmutableArraySequenceWhere(); std::cout << "testImmutableArraySequenceWhere\n";
    testImmutableArraySequenceReduce(); std::cout << "testImmutableArraySequenceReduce\n";
    testImmutableArraySequenceImmutability(); std::cout << "testImmutableArraySequenceImmutability\n";

   
    testImmutableListSequenceConstructors(); std::cout << "testImmutableListSequenceConstructors\n";
    testImmutableListSequenceGetFirstLast(); std::cout << "testImmutableListSequenceGetFirstLast\n";
    testImmutableListSequenceGet(); std::cout << "testImmutableListSequenceGet\n";
    testImmutableListSequenceAppendPrepend(); std::cout << "testImmutableListSequenceAppendPrepend\n";
    testImmutableListSequenceInsertAt(); std::cout << "testImmutableListSequenceInsertAt\n";
    testImmutableListSequenceGetSubsequence(); std::cout << "testImmutableListSequenceGetSubsequence\n";
    testImmutableListSequenceConcat(); std::cout << "testImmutableListSequenceConcat\n";
    testImmutableListSequenceMap(); std::cout << "testImmutableListSequenceMap\n";
    testImmutableListSequenceWhere(); std::cout << "testImmutableListSequenceWhere\n";
    testImmutableListSequenceReduce(); std::cout << "testImmutableListSequenceReduce\n";
    testImmutableListSequenceImmutability(); std::cout << "testImmutableListSequenceImmutability\n";

    
    testBitSequenceConstructors(); std::cout << "testBitSequenceConstructors\n";
    testBitSequenceGetFirstLast(); std::cout << "testBitSequenceGetFirstLast\n";
    testBitSequenceGet(); std::cout << "testBitSequenceGet\n";
    testBitSequenceAppendPrepend(); std::cout << "testBitSequenceAppendPrepend\n";
    testBitSequenceInsertAt(); std::cout << "testBitSequenceInsertAt\n";
    testBitSequenceGetSubsequence(); std::cout << "testBitSequenceGetSubsequence\n";
    testBitSequenceConcat(); std::cout << "testBitSequenceConcat\n";
    testBitSequenceWhere(); std::cout << "testBitSequenceWhere\n";
    testBitSequenceReduce(); std::cout << "testBitSequenceReduce\n";
    testBitSequenceBitwiseOps(); std::cout << "testBitSequenceBitwiseOps\n";
    testBitSequenceExceptions(); std::cout << "testBitSequenceExceptions\n";
    testImmutableBitSequenceConstructors(); std::cout << "testImmutableBitSequenceConstructors\n";
    testImmutableBitSequenceBitwiseOps(); std::cout << "testImmutableBitSequenceBitwiseOps\n";
    testImmutableBitSequenceImmutability(); std::cout << "testImmutableBitSequenceImmutability\n";
    
   
    std::cout << "\nИТОГИ:\n";
    std::cout << "Успешно: " << getTrueTests() << "\n";
    std::cout << "Ошибок:  " << getFailedTests() << "\n";
    return getFailedTests() > 0 ? 1 : 0;
}