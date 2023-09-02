#ifndef DELIM_PARSER_H
#define DELIM_PARSER_H

#define MAX_DELIM 10

typedef struct {
    char* delim[MAX_DELIM];
    int delim_count;
    char* remaining;
    char* error;
} DelimInfo;

DelimInfo find_delim_str(const char* input);

#endif

