#include <stdio.h>
#include "cu_string.h"

int main()
{
    const char *cstring = ",a,b,c,";
    long long cstring_length = cu_cstring_length(cstring);

    long long result_length = 0;
    char **split_cstrings = cu_cstring_split_copy(cstring, cstring_length, ",", 1, &result_length);
    for (long long i = 0; i < result_length; i++)
    {
        printf("%s ", split_cstrings[i]);
    }
    printf("\n");
    printf("%s\n", cstring);
}