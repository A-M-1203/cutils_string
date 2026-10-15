#ifndef CU_STRING_H_
#define CU_STRING_H_

#include <stdlib.h>

#define CU_INTERNAL static

typedef struct
{
    long long length;
    char* data;
} cu_string, string, CU_String, String;

CU_INTERNAL long long  cu_cstring_length           (const char      *cstring);
CU_INTERNAL char*      cu_cstring_copy             (const char      *cstring,   long long       length);
CU_INTERNAL cu_string  cu_string_allocate          (const char      *cstring,   long long       length);
CU_INTERNAL void       cu_string_free              (      cu_string *string);
CU_INTERNAL long long  cu_string_set_data          (      cu_string *string,    const char     *new_data,        long long   new_data_length);
CU_INTERNAL long long  cu_string_set_data_copy     (      cu_string *string,    const char     *new_data,        long long   new_data_length);
CU_INTERNAL char*      cu_string_get_data          (const cu_string  string); 
CU_INTERNAL char*      cu_string_get_data_copy     (const cu_string  string); 
CU_INTERNAL cu_string  cu_string_copy              (const cu_string  string); 
CU_INTERNAL long long  cu_string_index_of          (const cu_string  string,    const cu_string substring); 
CU_INTERNAL cu_string  cu_string_substring         (const cu_string  string,    long long       start_index,     long long   substring_length);
CU_INTERNAL char*      cu_cstring_substring        (const char      *cstring,   long long       cstring_length,  long long   start_index,         long long  csubstring_length);
CU_INTERNAL long long  cu_cstring_index_of         (const char      *string,    long long       string_length,   const char *substring,           long long  substring_length);
CU_INTERNAL int        cu_cstring_compare          (const char      *cstring_1, const char     *cstring_2,       long long   length);   
CU_INTERNAL long long  cu_cstring_is_lowercase     (const char      *cstring,   long long       length);    
CU_INTERNAL long long  cu_cstring_is_uppercase     (const char      *cstring,   long long       length);    
CU_INTERNAL long long  cu_cstring_to_lowercase     (      char     **cstring,   long long       length);    
CU_INTERNAL long long  cu_cstring_to_uppercase     (      char     **cstring,   long long       length);    
CU_INTERNAL char*      cu_cstring_to_lowercase_copy(      char      *cstring,   long long       length);    
CU_INTERNAL char*      cu_cstring_to_uppercase_copy(      char      *cstring,   long long       length);    
CU_INTERNAL int        cu_string_compare           (const cu_string  string_1,  const cu_string string_2,        long long   length);   
CU_INTERNAL long long  cu_string_is_lowercase      (      cu_string  string);    
CU_INTERNAL long long  cu_string_is_uppercase      (      cu_string  string);    
CU_INTERNAL long long  cu_string_to_lowercase      (      cu_string *string);    
CU_INTERNAL long long  cu_string_to_uppercase      (      cu_string *string);    
CU_INTERNAL cu_string  cu_string_to_lowercase_copy (      cu_string  string);    
CU_INTERNAL cu_string  cu_string_to_uppercase_copy (      cu_string  string);    
CU_INTERNAL long long  cu_cstring_trim_start       (      char      *cstring,   long long       length,          char        trim_character);   
CU_INTERNAL long long  cu_cstring_trim_end         (      char      *cstring,   long long       length,          char        trim_character);   
CU_INTERNAL long long  cu_cstring_trim             (      char      *cstring,   long long       length,          char        trim_character);   
CU_INTERNAL char*      cu_cstring_trim_start_copy  (const char      *cstring,   long long       length,          char        trim_character,      long long *trimed_cstring_length);
CU_INTERNAL char*      cu_cstring_trim_end_copy    (const char      *cstring,   long long       length,          char        trim_character,      long long *trimed_cstring_length);
CU_INTERNAL char*      cu_cstring_trim_copy        (const char      *cstring,   long long       length,          char        trim_character,      long long *trimed_cstring_length);
CU_INTERNAL long long  cu_string_trim_start        (cu_string       *string,    char            trim_character);    
CU_INTERNAL long long  cu_string_trim_end          (cu_string       *string,    char            trim_character);    
CU_INTERNAL long long  cu_string_trim              (cu_string       *string,    char            trim_character);    
CU_INTERNAL cu_string  cu_string_trim_start_copy   (cu_string        string,    char            trim_character);    
CU_INTERNAL cu_string  cu_string_trim_end_copy     (cu_string        string,    char            trim_character);    
CU_INTERNAL cu_string  cu_string_trim_copy         (cu_string        string,    char            trim_character);    
CU_INTERNAL char**     cu_cstring_split            (const char      *cstring,   long long       length,          const char *split_by_cstring,    long long  split_by_cstring_length, long long *split_result_length);
CU_INTERNAL cu_string* cu_string_split             (cu_string        string,    cu_string       split_by_string, long long  *split_result_length);

#define CU_STRING_IMPLEMENTATION
#ifdef CU_STRING_IMPLEMENTATION

long long cu_cstring_length(const char* cstring)
{
    if (cstring == NULL) return 0;

    long long cstring_length = 0;
    while(*cstring++ != 0)
    {
        cstring_length++;
    }

    return cstring_length;
}

char* cu_cstring_copy(const char* cstring, long long length)
{
    if (cstring == NULL || length < 0) return NULL;
    
    char* cstring_copy = (char*)malloc(length * sizeof(char) + 1);
    if (cstring_copy == NULL) return NULL;

    for (long long i = 0; i < length; i++)
    {
        cstring_copy[i] = cstring[i];
    }
    cstring_copy[length] = 0;

    return cstring_copy;
}

cu_string cu_string_copy(const cu_string string)
{
    cu_string string_copy = cu_string_allocate(string.data, string.length);
    return string_copy;
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

long long cu_string_set_data(cu_string *string, const char *new_data, long long new_data_length)
{
    if (string == NULL) return 0;

    string->data = (char*)new_data;
    string->length = new_data_length;
    return new_data_length;
}

long long cu_string_set_data_copy(cu_string *string, const char *new_data, long long new_data_length)
{
    if (string == NULL) return 0;
    free(string->data);

    char *new_data_copy = cu_cstring_copy(new_data, new_data_length);
    if (new_data_copy == NULL)
    {
        new_data_length = 0;
    }

    string->data = new_data_copy;
    string->length = new_data_length;
    return new_data_length;
}

char* cu_string_get_data(const cu_string string)
{
    return string.data;
}

char* cu_string_get_data_copy(const cu_string string)
{
    char* data_copy = cu_cstring_copy(string.data, string.length);
    return data_copy;
}

long long cu_cstring_index_of(const char *string, long long string_length, const char *substring, long long substring_length)
{
    if (string == NULL || substring == NULL) return -1;
    long long length_difference = string_length - substring_length;
    if (string_length <= 0 || substring_length <= 0 || length_difference < 0) return -1;

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
    if (cstring == NULL || cstring_length <= 0 || start_index < 0 || csubstring_length <= 0) return NULL;
    if (start_index + csubstring_length > cstring_length) return NULL;

    char* csubstring = (char*)malloc(csubstring_length * sizeof(char) + 1);
    if (csubstring == NULL) return NULL;

    for (long long i = 0; i < csubstring_length; i++)
    {
        csubstring[i] = cstring[i + start_index];
    }
    csubstring[csubstring_length] = 0;

    return csubstring;
}

long long cu_cstring_to_lowercase(char **cstring, long long length)
{
    if (cstring == NULL) return 0;

    long long i;
    for (i = 0; i < length; i++)
    {
        if ((*cstring)[i] >= 'A' && (*cstring)[i] <= 'Z')
            (*cstring)[i] += 'a' - 'A';
    }

    return i;
}

char* cu_cstring_to_lowercase_copy(char *cstring, long long length)
{
    long long result = cu_cstring_to_lowercase(&cstring, length);
    if (result == 0) return NULL;

    char *cstring_copy = cu_cstring_copy(cstring, length);
    return cstring_copy;
}

long long cu_cstring_is_lowercase(const char *cstring, long long length)
{
    if (cstring == NULL) return 0;

    long long i;
    for (i = 0; i < length; i++)
    {
        if (cstring[i] >= 'A' && cstring[i] <= 'Z') break;
    }

    return i == length;
}

long long cu_cstring_to_uppercase(char **cstring, long long length)
{
    if (cstring == NULL) return 0;

    long long i;
    for (i = 0; i < length; i++)
    {
        if ((*cstring)[i] >= 'a' && (*cstring)[i] <= 'z')
            (*cstring)[i] -= 'a' - 'A';
    }

    return i;
}

char* cu_cstring_to_uppercase_copy(char *cstring, long long length)
{
    long long result = cu_cstring_to_uppercase(&cstring, length);
    if (result == 0) return NULL;
    char *cstring_copy = cu_cstring_copy(cstring, length);
    return cstring_copy;
}

long long cu_cstring_is_uppercase(const char *cstring, long long length)
{
    if (cstring == NULL) return 0;

    long long i;
    for (i = 0; i < length; i++)
    {
        if (cstring[i] >= 'a' && cstring[i] <= 'z') break;
    }

    return i == length;
}

int cu_cstring_compare(const char *cstring_1, const char *cstring_2, long long length)
{
    if (cstring_1 == NULL && cstring_2 == NULL) return 0;
    if (cstring_1 == NULL) return -1;
    if (cstring_2 == NULL) return 1;

    for (long long i = 0; i < length; i++)
    {
        unsigned char char_1 = (unsigned char)cstring_1[i];
        unsigned char char_2 = (unsigned char)cstring_2[i];
        if (char_1 != char_2) return char_1 - char_2;
        if (char_1 == 0) return 0;
    }

    return 0;
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

long long cu_string_to_lowercase(cu_string *string)
{
    if (string == NULL) return 0;

    long long result = cu_cstring_to_lowercase(&string->data, string->length);
    return result;
}

cu_string cu_string_to_lowercase_copy(cu_string string)
{
    cu_string string_copy;
    long long result = cu_string_to_lowercase(&string);
    if (result == 0)
    {
        string_copy.data = NULL;
        string_copy.length = -1;
    }
    else
    {
        string_copy.data = cu_cstring_copy(string.data, string.length);
        string_copy.length = string.length;
    }

    return string_copy;
}

long long cu_string_is_lowercase(cu_string string)
{
    long long result = cu_cstring_is_lowercase(string.data, string.length);
    return result;
}

long long cu_string_to_uppercase(cu_string *string)
{
    if (string == NULL) return 0;

    long long result = cu_cstring_to_uppercase(&string->data, string->length);
    return result;
}

cu_string cu_string_to_uppercase_copy(cu_string string)
{
    cu_string string_copy;
    long long result = cu_string_to_uppercase(&string);
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

long long cu_string_is_uppercase(cu_string string)
{
    long long result = cu_cstring_is_uppercase(string.data, string.length);
    return result;
}

int cu_string_compare(const cu_string string_1, const cu_string string_2, long long length)
{
    int result = cu_cstring_compare(string_1.data, string_2.data, length);
    return result;
}

long long cu_cstring_trim_start(char *cstring, long long length, char trim_character)
{
    if (cstring == NULL || length <= 0) return 0;

    long long trim_count = 0;
    while (trim_count < length && cstring[trim_count++] == trim_character);
    if (trim_count == 0) return length;

    long long new_length = length - trim_count;
    for (long long i = 0; i < new_length; i++)
    {
        cstring[i] = cstring[i + trim_count];
    }

    cstring[new_length] = 0;
    return new_length;
}

long long cu_cstring_trim_end(char *cstring, long long length, char trim_character)
{
    if (cstring == NULL || length <= 0) return 0;

    long long i = length - 1;
    long long trim_count = 0;
    while (i >= 0 && cstring[i] == trim_character)
    {
        i--;
        trim_count++;
    }

    long long new_length = length - trim_count;
    cstring[new_length] = 0;
    return new_length;
}

long long cu_cstring_trim(char *cstring, long long length, char trim_character)
{
    long long new_length_1 = cu_cstring_trim_start(cstring, length, trim_character);
    long long new_length_2 = cu_cstring_trim_end(cstring, new_length_1, trim_character);
    return new_length_2;
}

char* cu_cstring_trim_start_copy(const char *cstring, long long length, char trim_character, long long *trimed_cstring_length)
{
    char *cstring_copy = cu_cstring_copy(cstring, length);
    *trimed_cstring_length = cu_cstring_trim_start(cstring_copy, length, trim_character);
    return cstring_copy;
}

char* cu_cstring_trim_end_copy(const char *cstring, long long length, char trim_character, long long *trimed_cstring_length)
{
    char *cstring_copy = cu_cstring_copy(cstring, length);
    *trimed_cstring_length = cu_cstring_trim_end(cstring_copy, length, trim_character);
    return cstring_copy;
}

char* cu_cstring_trim_copy(const char *cstring, long long length, char trim_character, long long *trimed_cstring_length)
{
    char *cstring_copy = cu_cstring_trim_start_copy(cstring, length, trim_character, trimed_cstring_length);
    *trimed_cstring_length = cu_cstring_trim_end(cstring_copy, *trimed_cstring_length, trim_character);
    return cstring_copy;
}

long long cu_string_trim_start(cu_string *string, char trim_character)
{
    long long new_length = cu_cstring_trim_start(string->data, string->length, trim_character);
    string->length = new_length;
    return new_length;
}

long long cu_string_trim_end(cu_string *string, char trim_character)
{
    long long new_length = cu_cstring_trim_end(string->data, string->length, trim_character);
    string->length = new_length;
    return new_length;
}

long long cu_string_trim(cu_string *string, char trim_character)
{
    cu_string_trim_start(string, trim_character);
    long long new_length_2 = cu_string_trim_end(string, trim_character);
    return new_length_2;
}

cu_string cu_string_trim_start_copy(cu_string string, char trim_character)
{
    cu_string string_copy = cu_string_copy(string);
    cu_string_trim_start(&string_copy, trim_character);
    return string_copy;
}

cu_string cu_string_trim_end_copy(cu_string string, char trim_character)
{
    cu_string string_copy = cu_string_copy(string);
    cu_string_trim_end(&string_copy, trim_character);
    return string_copy;
}

cu_string cu_string_trim_copy(cu_string string, char trim_character)
{
    cu_string string_copy = cu_string_trim_start_copy(string, trim_character);
    cu_string_trim_end(&string_copy, trim_character);
    return string_copy;
}

char** cu_cstring_split(const char *cstring, long long length, const char *split_by_cstring, long long split_by_cstring_length, long long *split_result_length)
{
    if (split_result_length == NULL) return NULL;
    *split_result_length = 0;
    if (cstring == NULL || length <= 0 || split_by_cstring == NULL || split_by_cstring_length <= 0)
    {
        return NULL;
    }

    long long capacity = 10;
    long long size = 0;
    char **split_result = (char**)malloc(capacity * sizeof(char*));
    if (split_result == NULL) return NULL;

    for(;;)
    {
        long long split_index = cu_cstring_index_of(cstring, length, split_by_cstring, split_by_cstring_length);
        long long new_cstring_length = (split_index == -1) ? length : split_index;

        if (split_index == -1 && new_cstring_length == 0) break;
        if (size == capacity)
        {
            capacity *= 2;
            char **split_result_tmp = (char**)realloc(split_result, capacity * sizeof(char*));
            if (split_result_tmp == NULL) goto cu_allocation_failed;
            split_result = split_result_tmp;
        }

        char *new_cstring = cu_cstring_copy(cstring, new_cstring_length);
        if (new_cstring == NULL) goto cu_allocation_failed;
        split_result[size++] = new_cstring;

        if (split_index == -1) break;

        cstring += split_index + split_by_cstring_length;
        length -= split_index + split_by_cstring_length;
    }
    
    *split_result_length = size;
    return split_result;

cu_allocation_failed:
    for (long long i = 0; i < size; i++)
    {
        free(split_result[i]);
    }
    free(split_result);

    *split_result_length = 0;
    return NULL;
}

cu_string* cu_string_split(cu_string string, cu_string split_by_string, long long *split_result_length)
{
    char **cstring_split_result = cu_cstring_split(string.data, string.length, split_by_string.data, split_by_string.length, split_result_length);
    if (cstring_split_result == NULL) return NULL;

    long long count = *split_result_length;
    cu_string *split_result = (cu_string*)malloc(count * sizeof(cu_string));
    if (split_result == NULL)
    {
        for (long long i = 0; i < count; i++)
        {
            free(cstring_split_result[i]);
        }
        free(cstring_split_result);
        *split_result_length = 0;
        return NULL;
    }

    for (long long i = 0; i < count; i++)
    {
        split_result[i].data = cstring_split_result[i];
        split_result[i].length = cu_cstring_length(cstring_split_result[i]);
    }

    free(cstring_split_result);
    return split_result;
}

#endif // CU_STRING_IMPLEMENTATION

#endif // CU_STRING_H_