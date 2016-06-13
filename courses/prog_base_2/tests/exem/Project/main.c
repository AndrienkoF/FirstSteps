#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "func.h"

// unit-test function
static void new_int_notnullStr(void **state){
    char str [30]= "";
	assert_non_null(str);
}

static void new_int_normalStr(void **state){
    char str [30]= "1, 245,4,5,6";
    assert_int_equal(checkStr(str), 1);
}

static void new_int_sumStr(void **state){
    char str [30]= "1, 245,4,5,6";
    assert_int_equal(numString(str), 261);
}

static void new_char_sumStr(void **state){
    char str [30]= "asfsafdgdf";
    assert_int_equal(numString(str), 0);
}

static void new_int_sumStr2(void **state){
    char str [30]= "1, , , , 2";
    assert_int_equal(numString(str), 3);
}

int main(){
    const struct CMUnitTest tests[] = {
		cmocka_unit_test(new_int_nullStr),
		cmocka_unit_test(new_int_normalStr),
		cmocka_unit_test(new_int_sumStr),
		cmocka_unit_test(new_char_sumStr),
		cmocka_unit_test(new_int_sumStr2),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}

/*
int main(){
    char str [30]= "1, , 4,5,6";
    checkStr(str);
    return 0;
}*/
