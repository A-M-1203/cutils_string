#include <stdio.h>
#include "cu_string.h"

int main()
{
    const char *cstring = "abcdTTT";
    long long cstring_length = cu_cstring_length(cstring);
    cu_string string = cu_string_allocate(cstring, cstring_length);

    cu_string string_copy = cu_string_trim_copy(string, 'T');
    printf("%s\n", string_copy.data);
    printf("%lld\n", string_copy.length);
}