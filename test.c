#include <stdio.h>
#include "cu_string.h"

int main()
{
    const char *cstring_1 = "abgd";
    const char *cstring_2 = "abed";
    int result = cu_cstring_compare(cstring_1, cstring_2, 3);
    printf("%d\n", result);
}