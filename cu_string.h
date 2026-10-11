#ifndef CU_STRING_H_
#define CU_STRING_H_

#include <stdlib.h>

#define CU_INTERNAL static

typedef struct
{
    long long length;
    char* data;
} cu_string;

CU_INTERNAL long long cu_cstring_length           (const char      *cstring);
CU_INTERNAL char*     cu_cstring_copy             (const char      *cstring, long long        length);
CU_INTERNAL cu_string cu_string_allocate          (const char      *cstring, long long        length);
CU_INTERNAL void      cu_string_free              (      cu_string *string);
CU_INTERNAL long long cu_string_set_data          (      cu_string *string,  const char      *new_data,       long long new_data_length);
CU_INTERNAL char*     cu_string_get_data          (      cu_string  string);
CU_INTERNAL char*     cu_string_copy_data         (      cu_string  string);
CU_INTERNAL cu_string cu_string_copy              (const cu_string  string);
CU_INTERNAL long long cu_string_index_of          (const cu_string  string,  const cu_string  substring);
CU_INTERNAL cu_string cu_string_substring         (const cu_string  string,  long long        start_index,    long long   substring_length);
CU_INTERNAL char*     cu_cstring_substring        (const char      *cstring, long long        cstring_length, long long   start_index,      long long csubstring_length);
CU_INTERNAL long long cu_cstring_index_of         (const char      *string,  long long        string_length,  const char *substring,        long long substring_length);
CU_INTERNAL int       cu_cstring_is_lowercase     (const char      *cstring, long long        length);
CU_INTERNAL int       cu_cstring_is_uppercase     (const char      *cstring, long long        length);
CU_INTERNAL int       cu_cstring_to_lowercase     (      char     **cstring, long long        length);
CU_INTERNAL int       cu_cstring_to_uppercase     (      char     **cstring, long long        length);
CU_INTERNAL char*     cu_cstring_to_lowercase_copy(      char      *cstring, long long        length);
CU_INTERNAL char*     cu_cstring_to_uppercase_copy(      char      *cstring, long long        length);
CU_INTERNAL int       cu_string_to_lowercase      (      cu_string *string);
CU_INTERNAL int       cu_string_to_uppercase      (      cu_string *string);
CU_INTERNAL cu_string cu_string_to_lowercase_copy (      cu_string  string);
CU_INTERNAL cu_string cu_string_to_uppercase_copy (      cu_string  string);
CU_INTERNAL int       cu_string_is_lowercase      (      cu_string  string);
CU_INTERNAL int       cu_string_is_uppercase      (      cu_string  string);

#define CU_STRING_IMPLEMENTATION
#ifdef CU_STRING_IMPLEMENTATION

long long cu_cstring_length(const char* cstring)
{
    if (cstring == NULL) return -1;
    long long cstring_length = 0;
    while(*cstring++ != 0)
    {
        cstring_length++;
    }
    return cstring_length;
}

char* cu_cstring_copy(const char* cstring, long long length)
{
    if (cstring == NULL) return NULL;
    char* cstring_copy = (char*)malloc(length * sizeof(char) + 1);
    for (long long i = 0; i <= length; i++)
    {
        cstring_copy[i] = cstring[i];
    }
    return cstring_copy;
}

cu_string cu_string_allocate(const char* cstring, long long length)
{
    cu_string new_string;
    new_string.data = cu_cstring_copy(cstring, length);
    new_string.length = length;
    return new_string;
}

void cu_string_free(cu_string *string)
{
    free(string->data);
    string->data = NULL;
    string->length = 0;
}

cu_string cu_string_copy(const cu_string string)
{
    cu_string string_copy = cu_string_allocate(string.data, string.length);
    return string_copy;
}

long long cu_string_set_data(cu_string *string, const char *new_data, long long new_data_length)
{
    if (string == NULL || new_data == NULL) return 0;
    if (string->data != NULL) free(string->data);
    string->data = cu_cstring_copy(new_data, new_data_length);
    string->length = new_data_length;
    return new_data_length;
}

char* cu_string_get_data(cu_string string)
{
    return string.data;
}

char* cu_string_copy_data(cu_string string)
{
    char* data_copy = cu_cstring_copy(string.data, string.length);
    return data_copy;
}

long long cu_cstring_index_of(const char *string, long long string_length, const char *substring, long long substring_length)
{
    long long length_difference = string_length - substring_length;
    if (substring_length == 0 || length_difference < 0) return -1;

    long long j;
    for (long long i = 0; i <= length_difference; i++)
    {
        for (j = 0; j < substring_length; j++)
        {
            if (string[i + j] != substring[j]) break;
        }
        if (j == substring_length) return i;
    }
    return -1;
}

long long cu_string_index_of(const cu_string string, const cu_string substring)
{
    long long result = cu_cstring_index_of(string.data, string.length, substring.data, substring.length);
    return result;
}

char* cu_cstring_substring(const char *cstring, long long cstring_length, long long start_index, long long csubstring_length)
{
    if (start_index + csubstring_length > cstring_length) return NULL;
    char* csubstring = (char*)malloc(csubstring_length * sizeof(char) + 1);
    for (long long i = 0; i < csubstring_length; i++)
    {
        csubstring[i] = cstring[i + start_index];
    }
    csubstring[csubstring_length] = 0;
    return csubstring;
}

cu_string cu_string_substring(const cu_string string, long long start_index, long long substring_length)
{
    cu_string substring;
    if (start_index + substring_length > string.length)
    {
        substring.data = NULL;
        substring.length = 0;
    }
    else
    {
        substring.data = cu_cstring_substring(string.data, string.length, start_index, substring_length);
        substring.length = substring_length;
    }
    return substring;
}

int cu_cstring_to_lowercase(char **cstring, long long length)
{
    if (cstring == NULL) return 0;
    for (long long i = 0; i < length; i++)
    {
        if ((*cstring)[i] >= 'A' && (*cstring)[i] <= 'Z')
            (*cstring)[i] += 'a' - 'A';
    }
    return 1;
}

int cu_string_to_lowercase(cu_string *string)
{
    if (string == NULL) return 0;
    int result = cu_cstring_to_lowercase(&string->data, string->length);
    return result;
}

char* cu_cstring_to_lowercase_copy(char *cstring, long long length)
{
    int result = cu_cstring_to_lowercase(&cstring, length);
    if (result == 0) return NULL;
    char *cstring_copy = cu_cstring_copy(cstring, length);
    return cstring_copy;
}

cu_string cu_string_to_lowercase_copy(cu_string string)
{
    cu_string string_copy;
    int result = cu_string_to_lowercase(&string);
    if (result == 0)
    {
        string_copy.data = NULL;
        string_copy.length = 0;
    }
    else
    {
        string_copy.data = cu_cstring_copy(string.data, string.length);
        string_copy.length = string.length;
    }
    return string_copy;
}

int cu_cstring_is_lowercase(const char *cstring, long long length)
{
    if (cstring == NULL) return 0;
    long long i;
    for (i = 0; i < length; i++)
    {
        if (cstring[i] >= 'A' && cstring[i] <= 'Z') break;
    }
    return i == length;
}

int cu_string_is_lowercase(cu_string string)
{
    return cu_cstring_is_lowercase(string.data, string.length);
}

int cu_cstring_to_uppercase(char **cstring, long long length)
{
    if (cstring == NULL) return 0;
    for (long long i = 0; i < length; i++)
    {
        if ((*cstring)[i] >= 'a' && (*cstring)[i] <= 'z')
            (*cstring)[i] -= 'a' - 'A';
    }
    return 1;
}

int cu_string_to_uppercase(cu_string *string)
{
    if (string == NULL) return 0;
    int result = cu_cstring_to_uppercase(&string->data, string->length);
    return result;
}

char* cu_cstring_to_uppercase_copy(char *cstring, long long length)
{
    int result = cu_cstring_to_uppercase(&cstring, length);
    if (result < 0) return NULL;
    char *cstring_copy = cu_cstring_copy(cstring, length);
    return cstring_copy;
}

cu_string cu_string_to_uppercase_copy(cu_string string)
{
    cu_string string_copy;
    int result = cu_string_to_uppercase(&string);
    if (result == 0)
    {
        string_copy.data = NULL;
        string_copy.length = 0;
    }
    else
    {
        string_copy.data = cu_cstring_copy(string.data, string.length);
        string_copy.length = string.length;
    }
    return string_copy;
}

int cu_cstring_is_uppercase(const char *cstring, long long length)
{
    if (cstring == NULL) return 0;
    long long i;
    for (i = 0; i < length; i++)
    {
        if (cstring[i] >= 'a' && cstring[i] <= 'z') break;
    }
    return i == length;
}

int cu_string_is_uppercase(cu_string string)
{
    int result = cu_cstring_is_uppercase(string.data, string.length);
    return result;
}

#endif // CU_STRING_IMPLEMENTATION

#endif // CU_STRING_H_