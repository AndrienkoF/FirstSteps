#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "list.h"

// unit-test function

static void new_void_checkMemory(void **state){
	post_t * newPost = new_post(7);
	assert_non_null(newPost);
	memory_delete(newPost);
}

static void addOnePost_countOnePost(void **state){
    post_t * newPost = new_post(0);
    post_add(newPost,"JARED LETO", "and it begins.. -j ", 0, 502);
    assert_int_equal(post_getLength(newPost), 1);
    memory_delete(newPost);
}

static void addTwoPost_countTwoPost(void **state){
    post_t * newPost = new_post(0);
    post_add(newPost,"ROBERT DOWNEY JR", "Et tu, D-pool? Gimme a shout when Rogers boots you out for \"cussing\"! ", 0, 941);
    post_add(newPost,"FEDIA ANDRIENKO", "Hello World! ", 1, 324);
    assert_int_equal(post_getLength(newPost), 2);
    memory_delete(newPost);
}

static void addPost_invalidIndex_postPositionError(void **state){
    post_t * newPost = new_post(0);
    assert_int_equal(post_add(newPost,"CHRIS EVANS", "That new trailer just broke my brain.  ", -1, 873), -1);
    memory_delete(newPost);
}

static void addPost_removePost_invalidIndex_postPositionError(void **state){
    post_t * newPost = new_post(0);
    post_add(newPost,"CHRIS EVANS", "That new trailer just broke my brain.  ", -1, 873);
    assert_int_equal(post_remove(newPost, 9), -1);
    memory_delete(newPost);
}

static void addPosts_findLargestPostForRepost(void **state){
    post_t * newPost = new_post(0);
    post_add(newPost,"CHRIS EVANS", "That new trailer just broke my brain.  ", 0, 873);
    post_add(newPost,"ROBERT DOWNEY JR", "Et tu, D-pool? Gimme a shout when Rogers boots you out for \"cussing\"! ", 1, 941);
    post_add(newPost,"FEDIA ANDRIENKO", "Hello World! ", 2, 1324);
    post_add(newPost,"JARED LETO", "and it begins.. -j ", 3, 502);
    assert_int_equal(largestNumRepost(newPost), 1324);
    memory_delete(newPost);
}

static void addPosts_findPost_ForRepostMoreThanGivenNum_invalidIndex_givenNumLargest(void **state){
    post_t * newPost = new_post(0);
    post_add(newPost,"CHRIS EVANS", "That new trailer just broke my brain.  ", 0, 873);
    post_add(newPost,"ROBERT DOWNEY JR", "Et tu, D-pool? Gimme a shout when Rogers boots you out for \"cussing\"! ", 1, 941);
    post_add(newPost,"FEDIA ANDRIENKO", "Hello World! ", 2, 324);
    post_add(newPost,"JARED LETO", "and it begins.. -j ", 3, 502);
    assert_int_equal(reposMoreThanGivenNum(newPost, 1000), -1);
    memory_delete(newPost);
}

int main(){
    const struct CMUnitTest tests[] = {
		cmocka_unit_test(new_void_checkMemory),
		cmocka_unit_test(addOnePost_countOnePost),
		cmocka_unit_test(addTwoPost_countTwoPost),
		cmocka_unit_test(addPost_invalidIndex_postPositionError),
		cmocka_unit_test(addPost_removePost_invalidIndex_postPositionError),
		cmocka_unit_test(addPosts_findLargestPostForRepost),
		cmocka_unit_test(addPosts_findPost_ForRepostMoreThanGivenNum_invalidIndex_givenNumLargest),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
