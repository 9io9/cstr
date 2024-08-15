//
// Created by mario on 2024/8/16.
//

#ifndef CSTR_STROP_H
#define CSTR_STROP_H

#include "cstr.def.h"
#include "cstr.err.h"

extern CStrStatusCode cstr_split(CString* cstr, char sep, size_t* strs_len, CStringRef** strs);

extern CStrOpStatusCode cstr_find_str(CString* cstr, const char* str, size_t str_len, CStringRef* found_str);

extern CStrOpStatusCode cstr_find_str_ref(CString* cstr, CStringRef* str, CStringRef* found_str);

extern CStrOpStatusCode cstr_cmp_str(CString* cstr, const char* str, size_t str_len, int* cmp_res);

// nocheck version

FUNC_ASSERT(CSTR != NULL, STRS_LEN != NULL, STRS != NULL)
extern CStrStatusCode cstr_split_nocheck(CString* cstr, char sep, size_t* strs_len, CStringRef** strs);

FUNC_ASSERT(CSTR != NULL, STR != NULL, STR_LEN != 0, FOUND_STR != NULL)
extern CStrOpStatusCode cstr_find_str_nocheck(CString* cstr, const char* str, size_t str_len, CStringRef* found_str);

FUNC_ASSERT(CSTR != NULL, STR != NULL, FOUND_STR != NULL)
extern CStrOpStatusCode cstr_find_str_ref_nocheck(CString* cstr, CStringRef* str, CStringRef* found_str);

#endif //CSTR_STROP_H
