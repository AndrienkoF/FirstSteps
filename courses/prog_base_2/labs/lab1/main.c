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
    heap_t * newHeap = heap_new(1,0);
    assert_non_null(newHeap);
    heap_delete(newHeap);
}

static void new_memory_normalSize(void **state){
    heap_t * newHeap = heap_new(50,30);
    memory_t * memory = heap_interactionMemory(newHeap, 20);
    assert_int_equal(heap_status(newHeap), H_OK);
    assert_int_equal(memory_status(memory), M_EMPTY);
    heap_delete(newHeap);
}

static void new_memory_fullSize(void **state){
    heap_t * newHeap = heap_new(50,30);
    memory_t * memory = heap_interactionMemory(newHeap, 100);
    assert_int_equal(heap_status(newHeap), H_FULL);
    assert_int_equal(memory_status(memory), M_EMPTY);
    heap_delete(newHeap);
}

static void new_heapSize_oneCount(void **state){
    heap_t * newHeap = heap_new(228,30);
    assert_int_equal(heap_getSize(newHeap), 228);
    heap_delete(newHeap);
}

static void new_heapSize_twoCount(void **state){
    heap_t * newHeap = heap_new(228,30);
    assert_int_equal(heap_getSize(newHeap), 228);
    heap_t * newSecondHeap = heap_new(300,30);
    assert_int_equal(heap_getSize(newSecondHeap), 300);
    heap_delete(newHeap);
    heap_delete(newSecondHeap);
}

static void new_checkMemory_empty(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "");
    assert_int_equal(memory_status(newMemory), M_EMPTY);
    heap_delete(newHeap);
}

static void new_checkMemory_full(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 1);
    memory_check(newMemory, "I am full string!");
    assert_int_equal(memory_status(newMemory), M_FULL);
    heap_delete(newHeap);
}

static void new_checkMemory_normal(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "I am normal string!");
    assert_int_equal(memory_status(newMemory), M_OK);
    heap_delete(newHeap);
}

static void new_viewMemory_oneData(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Hello World!"), 0);
    heap_delete(newHeap);
}

static void new_viewMemory_twoData(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 50);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Hello World!"), 0);

    heap_t * newSecondHeap = heap_new(100,31);
    memory_t * newSecondMemory = heap_interactionMemory(newSecondHeap, 30);
    memory_check(newSecondMemory, "Hello C\C++!");
    assert_int_equal(strcmp(memory_view(newSecondMemory), "Hello C\C++!"), 0);
    heap_delete(newHeap);
    heap_delete(newSecondHeap);
}

static void new_viewMemory_invalidData(void **state){
    heap_t * newHeap = heap_new(100,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 20);
    memory_check(newMemory, "Hello World!");
    assert_int_equal(strcmp(memory_view(newMemory), "Zdrastvuyte"), -1);
    heap_delete(newHeap);
}

static void new_sizeMemory_normal(void **state){
    heap_t * newHeap = heap_new(60,30);
    memory_t * newMemory = heap_interactionMemory(newHeap, 10);
    assert_int_equal(memory_getSize(newMemory), 10);
    heap_delete(newHeap);
}

int main(){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(new_void_createdHeap),
        cmocka_unit_test(new_memory_normalSize),
        cmocka_unit_test(new_memory_fullSize),
        cmocka_unit_test(new_heapSize_oneCount),
        cmocka_unit_test(new_heapSize_twoCount),
        cmocka_unit_test(new_checkMemory_empty),
        cmocka_unit_test(new_checkMemory_full),
        cmocka_unit_test(new_checkMemory_normal),
        cmocka_unit_test(new_viewMemory_oneData),
        cmocka_unit_test(new_viewMemory_twoData),
        cmocka_unit_test(new_viewMemory_invalidData),
        cmocka_unit_test(new_sizeMemory_normal),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
