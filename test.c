#include <stdio.h>
#include "cu_string.h"

int main()
{
    const char *cstring = "hello world";
    long long cstring_length = cu_cstring_length(cstring);
    cu_string string = cu_string_allocate(cstring, cstring_length);
    printf("%s\n", string.data);

    cu_string copy_string = cu_string_copy(string);
    printf("%s\n", copy_string.data);


    const char *new_data_string = "new data string";
    long long new_data_string_length = cu_cstring_length(new_data_string);
    cu_string_set_data(&copy_string, new_data_string, new_data_string_length);
    printf("%s\n", cu_string_get_data(copy_string));

    const char* data_copy = cu_string_copy_data(copy_string);
    printf("%s\n", data_copy);

    cu_string substring = cu_string_allocate(cstring, cstring_length);
    long long index = cu_string_index_of(string, substring);
    printf("%lld\n", index);

    substring = cu_string_substring(copy_string, 0, 16);
    // printf("%s\n", substring.data);

    printf("%d\n", cu_string_is_lowercase(string));
    cu_string_to_uppercase(&copy_string);
    cu_string copy_copy_string = cu_string_to_uppercase_copy(copy_string);
    printf("%d\n", cu_string_is_uppercase(copy_copy_string));

    cu_string_free(&string);
    cu_string_free(&copy_string);
    cu_string_free(&substring);
}