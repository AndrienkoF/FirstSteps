#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "heap.h"
#include "memory.h"

//unit-test function

static void new_void_createdHeap(void **state){
    heap_t * newHeap = new_heap(1,0);
    assert_non_null(newHeap);
    heap_free(newHeap);
}

static void new_memory_normalSize(void **state){
    heap_t * newHeap = new_heap(50,30);
    memory_t * memory = heap_interactionMemory(newHeap, 20);
    assert_int_equal(heap_status(newHeap), H_OK);
    assert_int_equal(memory_status(memory), M_EMPTY);
    heap_free(newHeap);
}

static void new_memory_fullSize(void **state){
    heap_t * newHeap = new_heap(50,30);
    memory_t * memory = heap_interactionMemory(newHeap, 100);
    assert_int_equal(heap_status(newHeap), H_FULL);
    assert_int_equal(memory_status(memory), M_EMPTY);
    heap_free(newHeap);
}

static void memoryFree_countOneMemory(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_free(newMemory, newHeap);
    heap_free(newHeap);
}

static void memoryFree_countTwoMemory(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_free(newMemory, newHeap);
    heap_t * newSecondHeap = new_heap(100,31);
    memory_t * newSecondMemory = heap_interactionMemory(newSecondHeap, 60);
    memory_free(newSecondMemory, newSecondHeap);
    heap_free(newHeap);
    heap_free(newSecondHeap);
}

static void heapSize_oneCount(void **state){
    heap_t * newHeap = new_heap(228,30);
    assert_int_equal(heap_size(newHeap), 228);
    heap_free(newHeap);
}

static void heapSize_twoCount(void **state){
    heap_t * newHeap = new_heap(228,30);
    assert_int_equal(heap_size(newHeap), 228);
    heap_t * newSecondHeap = new_heap(300,30);
    assert_int_equal(heap_size(newSecondHeap), 300);
    heap_free(newHeap);
    heap_free(newSecondHeap);
}

static void checkMemory_empty(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "");
    assert_int_equal(memory_status(newMemory), M_EMPTY);
    heap_free(newHeap);
}

static void checkMemory_full(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 1);
    memory_check(newMemory, "I am full string!");
    assert_int_equal(memory_status(newMemory), M_FULL);
    heap_free(newHeap);
}

static void checkMemory_normal_ok(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "I am normal string!");
    assert_int_equal(memory_status(newMemory), M_OK);
    heap_free(newHeap);
}

static void viewMemory_oneData(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Hello World!"), 0);
    heap_free(newHeap);
}

static void viewMemory_twoData(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Hello World!"), 0);

    heap_t * newSecondHeap = new_heap(100,31);
    memory_t * newSecondMemory = heap_interactionMemory(newSecondHeap, 30);
    memory_check(newSecondMemory, "Hello C\C++!");
    assert_int_equal(strcmp(memory_view(newSecondMemory), "Hello C\C++!"), 0);
    heap_free(newHeap);
    heap_free(newSecondHeap);
}

static void viewMemory_invalidData(void **state){
    heap_t * newHeap = new_heap(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 20);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Zdrastvuyte"), -1);
    heap_free(newHeap);
}

static void sizeMemory_normal(void **state){
    heap_t * newHeap = new_heap(60,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 10);
    assert_int_equal(memory_size(newMemory), 10);
    heap_free(newHeap);
}

int main(){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(new_void_createdHeap),
        cmocka_unit_test(new_memory_normalSize),
        cmocka_unit_test(new_memory_fullSize),
        cmocka_unit_test(memoryFree_countOneMemory),
        cmocka_unit_test(memoryFree_countTwoMemory),
        cmocka_unit_test(heapSize_oneCount),
        cmocka_unit_test(heapSize_twoCount),
        cmocka_unit_test(checkMemory_empty),
        cmocka_unit_test(checkMemory_full),
        cmocka_unit_test(checkMemory_normal_ok),
        cmocka_unit_test(viewMemory_oneData),
        cmocka_unit_test(viewMemory_twoData),
        cmocka_unit_test(viewMemory_invalidData),
        cmocka_unit_test(sizeMemory_normal),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
