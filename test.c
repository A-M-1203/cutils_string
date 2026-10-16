#include <stdio.h>
#include "cu_string.h"

int main()
{
    const char *cstrings[3] = {"ab", "abc", "abcd"};
    long long cstrings_lengths[3] = {2, 3, 4};
    const char *join_by_cstring = " ";
    long long join_result_length = 0;
    char *join_result = cu_cstring_join_copy(cstrings, cstrings_lengths, 3, join_by_cstring, 1, &join_result_length);
    printf("%s\n", join_result);
    printf("%lld\n", join_result_length);
}