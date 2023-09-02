#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "delim_parser.h"
#include "calculator.h"

static void test_find_delim_str_single(void **state) {
    char* input = "//;\n1;2";
    DelimInfo di = find_delim_str(input);
    assert_string_equal(di.delim, ";");
    assert_string_equal(di.remaining, "1;2");
    assert_null(di.error);
}

static void test_find_delim_str_no_delim(void **state) {
    char* input = "1,2";
    DelimInfo di = find_delim_str(input);
    assert_string_equal(di.delim, ",");
    assert_string_equal(di.remaining, "1,2");
    assert_null(di.error);
}

static void test_find_delim_str_empty(void **state) {
    char* input = "";
    DelimInfo di = find_delim_str(input);
    assert_string_equal(di.delim, ",");
    assert_string_equal(di.remaining, "");
    assert_null(di.error);
}

static void test_empty_input(void **state) {
    assert_int_equal(add(""), 0);
}

static void test_add_with_comma(void **state) {
    assert_int_equal(add("1,2"), 3);
}

static void test_add_with_comma_and_newline() {
    assert_int_equal(add("1,2\n3"), 6);
}

static void test_add_with_newline_custom_delimiter() {
    assert_int_equal(add("//;\n1;2"), 3);
}

static void test_add_negative_number_should_throw_exception() {
    assert_int_equal(add("-2"), -1);
}

static void test_multi_character_delimiter() {
    assert_int_equal(add("//***\n1***2***3"), 6);
}
    
int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_find_delim_str_single),
        cmocka_unit_test(test_find_delim_str_no_delim),
        cmocka_unit_test(test_find_delim_str_empty),
        cmocka_unit_test(test_empty_input),
        cmocka_unit_test(test_add_with_comma),
        cmocka_unit_test(test_add_with_comma_and_newline),
        cmocka_unit_test(test_add_with_newline_custom_delimiter),
        cmocka_unit_test(test_add_negative_number_should_throw_exception),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

