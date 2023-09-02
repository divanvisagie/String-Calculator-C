#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "delim_parser.h"

DelimInfo find_delim_str(const char* input) {
    DelimInfo info = { .delim_count = 0, .remaining = NULL, .error = NULL };

    char* local_input = strdup(input);
    if (local_input == NULL) {
        info.error = "Error allocating memory";
        return info;
    }

    char* start_ptr = strstr(local_input, "//");
    if (start_ptr == NULL) {
        info.delim[0] = strdup(",");
        info.delim_count = 1;
        info.remaining = strdup(input);
        free(local_input);
        return info;
    }

    char* parse_ptr = start_ptr + 2;
    char* end_ptr = strstr(parse_ptr, "\n");
    if (end_ptr == NULL) {
        info.error = "String starting with // indicates a delimiter but no newline was found";
        free(local_input);
        return info;
    }
    *end_ptr = '\0';
    info.remaining = strdup(end_ptr + 1);
    
    start_ptr = strstr(parse_ptr, "[");
    if (start_ptr == NULL) {
        info.delim[0] = strdup(parse_ptr);
        info.delim_count = 1;
        free(local_input);
        return info;
    }

    //get string from start+1 until ]
    do {
        start_ptr++;
        end_ptr = strstr(start_ptr, "]");
        if (end_ptr == NULL) {
            info.error = "String starting with //[ indicates a delimiter but no ] was found";
            free(local_input);
            return info;
        }
        *end_ptr = '\0';
        info.delim[info.delim_count] = strdup(start_ptr);
        info.delim_count++;
        start_ptr = strstr(end_ptr + 1, "[");
    } while (start_ptr != NULL);
    
    
    free(local_input);
    return info;
}
