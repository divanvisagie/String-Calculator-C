#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "delim_parser.h"

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

    if (info.error != NULL) {
        printf("Error finding delim %s\n", info.error);
        return -2;
    }
     
    for (int i = 0; i < info.delim_count; i++) {
        if (info.delim[i] == NULL) {
            continue;
        }
        replace_string(info.remaining, info.delim[i], "\n");
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

