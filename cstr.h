#ifndef CSTR_LIBRARY_H
#define CSTR_LIBRARY_H

#include <stdio.h>
#include "cstr.def.h"
#include "cstr.err.h"
#include "cstr.strop.h"
#include "cstr.cast.h"

extern CStrStatusCode cstr_new(size_t str_len, char str[], CString** cstr);

extern CStrStatusCode cstr_expand_length(size_t cstr_len, CString* cstr);

extern CStrStatusCode cstr_pushc(char c, CString* cstr);

extern CStrStatusCode cstr_pushs(size_t str_len, char str[], CString* cstr);

extern CStrStatusCode cstr_popc(char* c, CString* cstr);

extern CStrStatusCode cstr_pops(size_t str_len, char str[], CString* cstr);

extern CStrStatusCode cstr_strcpy(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr);

extern CStrStatusCode cstr_fprint(FILE* f, CString* cstr);

extern CStrStatusCode cstr_ref_fprint(FILE* f, CStringRef* cstr_ref, size_t cstr_ref_len);

extern CStrStatusCode cstr_clean(CString* cstr);

extern CStrStatusCode cstr_free(CString** cstr);

extern CWStrStatusCode cwstr_new(size_t wstr_len, wchar_t wstr[], CWString** cwstr);

extern CWStrStatusCode cwstr_expand_length(size_t cwstr_len, CWString* cwstr);

extern CWStrStatusCode cwstr_pushc(wchar_t c, CWString* cwstr);

extern CWStrStatusCode cwstr_pushs(size_t wstr_len, wchar_t wstr[], CWString* cwstr);

extern CWStrStatusCode cwstr_popc(wchar_t* c, CWString* cwstr);

extern CWStrStatusCode cwstr_pops(size_t wstr_len, wchar_t wstr[], CWString* cwstr);

extern CWStrStatusCode cwstr_strcpy(size_t cwstr_start, size_t wstr_len, wchar_t wstr[], CWStrCopyFunc cwstr_cpy_func, CWString* cwstr);

extern CWStrStatusCode cwstr_free(CWString** cwstr);

// no argument check version

FUNC_ASSERT(CSTR != NULL, (STR_LEN == 0, STR == NULL) || (STR_LEN != 0, STR != NULL))
extern CStrStatusCode cstr_new_nocheck(size_t str_len, char str[], CString** cstr);

FUNC_ASSERT(CSTR != NULL, CSTR_LEN > CSTR->_cstr_len)
extern CStrStatusCode cstr_expand_length_nocheck(size_t cstr_len, CString* cstr);

FUNC_ASSERT(CSTR != NULL)
extern CStrStatusCode cstr_pushc_nocheck(char c, CString* cstr);

FUNC_ASSERT(CSTR != NULL, STR_LEN == 0 && STR == NULL || STR_LEN != 0 && STR != NULL)
extern CStrStatusCode cstr_pushs_nocheck(size_t str_len, char str[], CString* cstr);

FUNC_ASSERT(CSTR != NULL, C != NULL)
extern CStrStatusCode cstr_popc_nocheck(char* c, CString* cstr);

FUNC_ASSERT(CSTR != NULL, STR_LEN != 0, STR != NULL)
extern CStrStatusCode cstr_pops_nocheck(size_t str_len, char str[], CString* cstr);

FUNC_ASSERT(CSTR != NULL, STR_LEN != 0, STR != NULL)
extern CStrStatusCode cstr_strcpy_nocheck(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr);

FUNC_ASSERT(F != NULL, CSTR != NULL)
extern CStrStatusCode cstr_fprint_nocheck(FILE* f, CString* cstr);

FUNC_ASSERT(F != NULL, CSTR_REF != NULL)
extern CStrStatusCode cstr_ref_fprint_nocheck(FILE* f, CStringRef* cstr_ref, size_t cstr_ref_len);

FUNC_ASSERT(CSTR != NULL)
extern CStrStatusCode cstr_clean_nocheck(CString* cstr);

FUNC_ASSERT(CSTR != NULL, *CSTR != NULL)
extern CStrStatusCode cstr_free_nocheck(CString** cstr);

#undef FUNC_ASSERT
#endif //CSTR_LIBRARY_H
