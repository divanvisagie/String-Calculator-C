#ifndef DELIM_PARSER_H
#define DELIM_PARSER_H

typedef struct {
    char* delim;
    char* remaining;
    char* error;
} DelimInfo;

DelimInfo find_delim_str(const char* input);

#endif

