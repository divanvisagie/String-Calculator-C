#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

char find_delim(char* input) {
    char * indicator = strstr(input, "//");
    if (indicator == NULL) {
        return ',';
    }
    input = indicator + 2;
    return indicator[2];
}

int add(char* input) {
    if (input == NULL || strcmp(input, "") == 0) {
        return 0;
    }
    char *tofree, *string, *token;
    int sum = 0;

    tofree = string = strdup(input);
    char delim = find_delim(input);
    char* delims = malloc(sizeof(char) * 2);
    delims[0] = delim;
    delims[1] = '\n';

    while ((token = strsep(&string, delims)) != NULL) {
        int num = atoi(token);
        if (num < 0) {
            return -1;
        }
        sum += num;
    }

    free(tofree);
    return sum;
}

static void test_find_delim_single(void **state) {
    char* input = "//;\n1;2";
    char delim = find_delim(input);
    assert_int_equal(delim, ';');
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
        cmocka_unit_test(test_find_delim_single),
        cmocka_unit_test(test_empty_input),
        cmocka_unit_test(test_add_with_comma),
        cmocka_unit_test(test_add_with_comma_and_newline),
        cmocka_unit_test(test_add_with_newline_custom_delimiter),
        cmocka_unit_test(test_add_negative_number_should_throw_exception),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

