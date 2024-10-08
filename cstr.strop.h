//
// Created by mario on 2024/8/16.
//

#ifndef CSTR_STROP_H
#define CSTR_STROP_H

#include "cstr.def.h"
#include "cstr.err.h"

#define FUNC_ASSERT(...)

extern CStrStatusCode cstr_split(CString* cstr, char sep, char split_enable_ch, char split_disable_ch, size_t* strs_len, CStringRef** strs);

extern CStrOpStatusCode cstr_find_str(CString* cstr, const char* str, size_t str_len, CStringRef* found_str);

extern CStrOpStatusCode cstr_find_str_ref(CString* cstr, CStringRef* str, CStringRef* found_str);

extern CStrOpStatusCode cstr_cmp_str(CString* cstr, const char* str, size_t str_len, int* cmp_res);

extern CStrOpStatusCode cstr_ref_cmp_str(CStringRef* cstr_ref, const char* str, size_t str_len, int* cmp_res);

// nocheck version

FUNC_ASSERT(CSTR != NULL, STRS_LEN != NULL, STRS != NULL)
extern CStrStatusCode cstr_split_nocheck(CString* cstr, char sep, char split_enable_ch, char split_disable_ch, size_t* strs_len, CStringRef** strs);

FUNC_ASSERT(CSTR != NULL, STR != NULL, STR_LEN != 0, FOUND_STR != NULL)
extern CStrOpStatusCode cstr_find_str_nocheck(CString* cstr, const char* str, size_t str_len, CStringRef* found_str);

FUNC_ASSERT(CSTR != NULL, STR != NULL, FOUND_STR != NULL)
extern CStrOpStatusCode cstr_find_str_ref_nocheck(CString* cstr, CStringRef* str, CStringRef* found_str);

FUNC_ASSERT(CSTR != NULL, STR != NULL, STR_LEN != 0, CMP_RES != NULL)
extern CStrOpStatusCode cstr_cmp_str_nocheck(CString* cstr, const char* str, size_t str_len, int* cmp_res);

FUNC_ASSERT(CSTR_REF != NULL, STR != NULL, STR_LEN != 0, CMP_RES != NULL)
extern CStrOpStatusCode cstr_ref_cmp_str_nocheck(CStringRef* cstr_ref, const char* str, size_t str_len, int* cmp_res);

#undef FUNC_ASSERT
#endif //CSTR_STROP_H
