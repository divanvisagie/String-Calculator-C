#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "delim_parser.h"

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
