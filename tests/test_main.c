#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// Function under test from your src/main.c or some other source file
int add(int a, int b) {
    return a + b;
}

// A test case for the 'add' function
static void test_addition(void **state) {
    (void) state;  // unused variable
    assert_int_equal(add(1, 1), 2);
    assert_int_equal(add(0, 0), 0);
    assert_int_equal(add(-1, -1), -2);
}

// Another test case example
static void test_subtraction(void **state) {
    (void) state;  // unused variable
    assert_int_equal(add(2, -1), 1);
}

// Group all test cases together
int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_addition),
        cmocka_unit_test(test_subtraction),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

