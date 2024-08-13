#ifndef CSTR_LIBRARY_H
#define CSTR_LIBRARY_H

#include "cstr.def.h"
#include "cstr.err.h"

extern CStrStatusCode cstr_new(size_t str_len, char str[], CString** cstr);

extern CStrStatusCode cstr_expand_length(size_t cstr_len, CString* cstr);

extern CStrStatusCode cstr_pushc(char c, CString* cstr);

extern CStrStatusCode cstr_pushs(size_t str_len, char str[], CString* cstr);

extern CStrStatusCode cstr_popc(char* c, CString* cstr);

extern CStrStatusCode cstr_pops(size_t str_len, char str[], CString* cstr);

extern CStrStatusCode cstr_strcpy(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr);

extern CStrStatusCode cstr_free(CString** cstr);

#endif //CSTR_LIBRARY_H
