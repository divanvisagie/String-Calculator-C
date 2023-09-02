typedef struct {
    char* delim;
    char* remaining;
    char* error;
} DelimInfo;

DelimInfo find_delim_str(const char* input);
