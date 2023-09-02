#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* delim;
    char* remaining;
    char* error;
} DelimInfo;

DelimInfo find_delim_str(const char* input) {
    DelimInfo info = { .delim = NULL, .remaining = NULL, .error = NULL };

    char *local_input = strdup(input);
    
    char *indicator = strstr(local_input, "//");
    
    if (indicator == NULL) {
        info.delim = strdup(",");
        info.remaining = strdup(input);
        free(local_input);
        return info;
    }
    
    char *end = strstr(indicator + 2, "\n");
    
    if (end == NULL) {
        info.error = "String starting with // indicates a delimiter but no newline was found";
        free(local_input);
        return info;
    }
    
    *end = '\0';
    info.delim = strdup(indicator + 2);
    info.remaining = strdup(end + 1);
    
    free(local_input);
    return info;
}

void replace_string(char* str, const char* search, const char* replace) {
    char* pos;
    int search_len = strlen(search);
    int replace_len = strlen(replace);

    pos = strstr(str, search);

    while (pos != NULL) {
        memmove(pos + replace_len, pos + search_len, strlen(pos + search_len) + 1);
        memcpy(pos, replace, replace_len);
        pos = strstr(pos + replace_len, search);
    }
}

/**
 * Add function that takes a string of numbers and returns the sum of those numbers.
 * 
 * @param input_ptr - string of numbers to add
 * @return sum of numbers
 * @retval >= 0 - sum of numbers
 * @retval -1 - negative number found
 * @retval -2 - error finding delimiter
 */
int add(char* input_ptr) {
    if (input_ptr == NULL || strcmp(input_ptr, "") == 0) {
        return 0;
    }

    DelimInfo info = find_delim_str(input_ptr);
    char* delims[] = {NULL};
    delims[0] = info.delim;

    if (info.error != NULL) {
        printf("Error finding delim %s\n", info.error);
        return -2;
    }
     
    for (int i = 0; i < 1; i++) {
        if (delims[i] == NULL) {
            continue;
        }
        replace_string(info.remaining, delims[i], "\n");
    }

    int sum = 0;
    char *tofree, *string, *token;
    // replace all string delims with newline character
    string = strdup(info.remaining);
    tofree = string;
    while ((token = strsep(&string, "\n")) != NULL) {
        int num = atoi(token);
        if (num < 0) {
            return -1;
        }
        sum += num;
    }

    return sum;
}


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

