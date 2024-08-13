#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "cstr.def.h"
#include "cstr.err.h"

#define DEFAULT_CSTR_LEN 32

static CStrStatusCode cstr_expand(CString* cstr) {

#ifdef __MEM_SENSITIVE__
    char* str_buf = malloc(cstr->_cstr_len + DEFAULT_CSTR_LEN);

    if (str_buf == NULL) {
        return CStrMemError;
    }

    cstr->_cstr_len = cstr->_cstr_len + DEFAULT_CSTR_LEN;
#else
    cstr->_cstr_len = cstr->_cstr_len + DEFAULT_CSTR_LEN;

    char* str_buf = malloc(cstr->_cstr_len);
#endif

    strncpy(str_buf, cstr->_cstr, cstr->_cstr_sz);

    free(cstr->_cstr);

    cstr->_cstr = str_buf;

    return CStrSuccess;
}

CStrStatusCode cstr_new(size_t str_len, char str[], CString** cstr) {
    if (cstr == NULL || str == NULL) {
        return CStrFuncArgError;
    }

    CString* new_cstr = malloc(sizeof(*new_cstr));

    new_cstr->_cstr_len = str_len + DEFAULT_CSTR_LEN;
    new_cstr->_cstr = malloc(new_cstr->_cstr_len);

    strncpy(new_cstr->_cstr, str, str_len);

    new_cstr->_cstr_sz = str_len;

    *cstr = new_cstr;

    return CStrSuccess;
}

CStrStatusCode cstr_new_nocheck(size_t str_len, char str[], CString** cstr) {
    CString* new_cstr = malloc(sizeof(*new_cstr));

    new_cstr->_cstr_len = str_len + DEFAULT_CSTR_LEN;
    new_cstr->_cstr = malloc(new_cstr->_cstr_len);

    strncpy(new_cstr->_cstr, str, str_len);

    new_cstr->_cstr_sz = str_len;

    *cstr = new_cstr;

    return CStrSuccess;
}

CStrStatusCode cstr_expand_length(size_t cstr_len, CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (cstr_len <= cstr->_cstr_len) {
        return CStrFuncArgError;
    }

    char* str_buf = malloc(cstr_len);

#ifdef __MEM_SENSITIVE__
    if (str_buf == NULL) {
        return CStrMemError;
    }
#endif

    cstr->_cstr_len = cstr_len;

    strncpy(str_buf, cstr->_cstr, cstr->_cstr_sz);

    free(cstr->_cstr);

    cstr->_cstr = str_buf;

    return CStrSuccess;
}

CStrStatusCode cstr_expand_length_nocheck(size_t cstr_len, CString* cstr) {
    char* str_buf = malloc(cstr_len);

#ifdef __MEM_SENSITIVE__
    if (str_buf == NULL) {
        return CStrMemError;
    }
#endif

    cstr->_cstr_len = cstr_len;

    strncpy(str_buf, cstr->_cstr, cstr->_cstr_sz);

    free(cstr->_cstr);

    cstr->_cstr = str_buf;

    return CStrSuccess;
}

CStrStatusCode cstr_pushc(char c, CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz == cstr->_cstr_len) {
#ifdef __MEM_SENSITIVE__
        CStrStatusCode expand_status_code = cstr_expand(cstr);
        if (expand_status_code != CStrSuccess) {
            return expand_status_code;
        }
#else
        cstr_expand(cstr);
#endif
    }

    cstr->_cstr[cstr->_cstr_sz++] = c;

    return CStrSuccess;
}

CStrStatusCode cstr_pushc_nocheck(char c, CString* cstr) {
    if (cstr->_cstr_sz == cstr->_cstr_len) {
#ifdef __MEM_SENSITIVE__
        CStrStatusCode expand_status_code = cstr_expand(cstr);
        if (expand_status_code != CStrSuccess) {
            return expand_status_code;
        }
#else
        cstr_expand(cstr);
#endif
    }

    cstr->_cstr[cstr->_cstr_sz++] = c;

    return CStrSuccess;
}

CStrStatusCode cstr_pushs(size_t str_len, char str[], CString* cstr) {
    if (cstr == NULL || str == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz + str_len > cstr->_cstr_len) {
#ifdef __MEM_SENSITIVE__
        CStrStatusCode expand_length_code = cstr_expand_length(cstr->_cstr_sz + str_len + DEFAULT_CSTR_LEN, cstr);

        if (expand_length_code != CStrSuccess) {
            return expand_length_code;
        }
#else
        cstr_expand_length(cstr->_cstr_sz + str_len + DEFAULT_CSTR_LEN, cstr);
#endif
    }

    strncpy(&cstr->_cstr[cstr->_cstr_sz], str, str_len);

    cstr->_cstr_sz += str_len;

    return CStrSuccess;
}

CStrStatusCode cstr_pushs_nocheck(size_t str_len, char str[], CString* cstr) {
    if (cstr->_cstr_sz + str_len > cstr->_cstr_len) {
#ifdef __MEM_SENSITIVE__
        CStrStatusCode expand_length_code = cstr_expand_length(cstr->_cstr_sz + str_len + DEFAULT_CSTR_LEN, cstr);

        if (expand_length_code != CStrSuccess) {
            return expand_length_code;
        }
#else
        cstr_expand_length(cstr->_cstr_sz + str_len + DEFAULT_CSTR_LEN, cstr);
#endif
    }

    strncpy(&cstr->_cstr[cstr->_cstr_sz], str, str_len);

    cstr->_cstr_sz += str_len;

    return CStrSuccess;
}

CStrStatusCode cstr_popc(char* c, CString* cstr) {
    if (c == NULL || cstr == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz == 0) {
        return CStrZeroSizeError;
    }

    *c = cstr->_cstr[--cstr->_cstr_sz];

    return CStrSuccess;
}

CStrStatusCode cstr_popc_nocheck(char* c, CString* cstr) {
    if (cstr->_cstr_sz == 0) {
        return CStrZeroSizeError;
    }

    *c = cstr->_cstr[--cstr->_cstr_sz];

    return CStrSuccess;
}

CStrStatusCode cstr_pops(size_t str_len, char str[], CString* cstr) {
    if (cstr == NULL || str == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz < str_len) {
        return CStrZeroSizeError;
    }

    cstr->_cstr_sz -= str_len;

    strncpy(str, &cstr->_cstr[cstr->_cstr_sz], str_len);

    return CStrSuccess;
}

CStrStatusCode cstr_pops_nocheck(size_t str_len, char str[], CString* cstr) {
    if (cstr->_cstr_sz < str_len) {
        return CStrZeroSizeError;
    }

    cstr->_cstr_sz -= str_len;

    strncpy(str, &cstr->_cstr[cstr->_cstr_sz], str_len);

    return CStrSuccess;
}

CStrStatusCode cstr_split(CString* cstr, char sep, size_t* strs_len, CStringRef** strs) {
    if (cstr == NULL || strs_len == NULL || strs == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz == 0) {
        return CStrZeroSizeError;
    }

    *strs_len = 0;
    *strs = NULL;

    size_t old_cstr_id = 0;

    for (size_t cstr_id = 0; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (cstr->_cstr[cstr_id] == sep) {
            if (cstr_id != old_cstr_id) {
                *strs_len += 1;
            }

            old_cstr_id = cstr_id + 1;
        }
    }

    if (*strs_len == 0) {
        return CStrNoSplitError;
    }

    if (cstr->_cstr_sz - 1 != old_cstr_id) {
        *strs_len += 1;
    }

    *strs = malloc(sizeof(CStringRef) * *strs_len);

#ifdef __MEM_SENSITIVE__
    if (*strs == NULL) {
        return CStrMemError;
    }
#endif

    old_cstr_id = 0;

    for (size_t cstr_id = 0, strs_id = 0; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (cstr->_cstr[cstr_id] == sep) {
            if (cstr_id != old_cstr_id) {
                strs[0][strs_id]._cstr_ref_len = cstr_id - old_cstr_id;
                strs[0][strs_id]._cstr_ref = &cstr->_cstr[old_cstr_id];
                strs_id += 1;
            }

            old_cstr_id = cstr_id + 1;
        }
    }

    if (cstr->_cstr_sz - 1 != old_cstr_id) {
        strs[0][*strs_len - 1]._cstr_ref_len = cstr->_cstr_sz - old_cstr_id;
        strs[0][*strs_len - 1]._cstr_ref = &cstr->_cstr[old_cstr_id];
    }

    return CStrSuccess;
}

CStrStatusCode cstr_split_nocheck(CString* cstr, char sep, size_t* strs_len, CStringRef** strs) {
    if (cstr->_cstr_sz == 0) {
        return CStrZeroSizeError;
    }

    *strs_len = 0;
    *strs = NULL;

    size_t old_cstr_id = 0;

    for (size_t cstr_id = 0; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (cstr->_cstr[cstr_id] == sep) {
            if (cstr_id != old_cstr_id) {
                *strs_len += 1;
            }

            old_cstr_id = cstr_id + 1;
        }
    }

    if (*strs_len == 0) {
        return CStrNoSplitError;
    }

    if (cstr->_cstr_sz - 1 != old_cstr_id) {
        *strs_len += 1;
    }

    *strs = malloc(sizeof(CStringRef) * *strs_len);

#ifdef __MEM_SENSITIVE__
    if (*strs == NULL) {
        return CStrMemError;
    }
#endif

    old_cstr_id = 0;

    for (size_t cstr_id = 0, strs_id = 0; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (cstr->_cstr[cstr_id] == sep) {
            if (cstr_id != old_cstr_id) {
                strs[0][strs_id]._cstr_ref_len = cstr_id - old_cstr_id;
                strs[0][strs_id]._cstr_ref = &cstr->_cstr[old_cstr_id];
                strs_id += 1;
            }

            old_cstr_id = strs_id + 1;
        }
    }

    if (cstr->_cstr_sz - 1 != old_cstr_id) {
        strs[0][*strs_len - 1]._cstr_ref_len = cstr->_cstr_sz - old_cstr_id;
        strs[0][*strs_len - 1]._cstr_ref = &cstr->_cstr[old_cstr_id];
    }

    return CStrSuccess;
}

CStrStatusCode cstr_strcpy(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr) {
    if (cstr == NULL || str_len == 0 || str == NULL) {
        return CStrFuncArgError;
    }

    if (cstr_start + str_len - 1 >= cstr->_cstr_sz) {
        return CStrOutOfBoundError;
    }

    if (cstr_cpy_func == CSTR_DEFAULT_CPYFUNC) {
        strncpy(str, &cstr->_cstr[cstr_start], str_len);
    } else {
        cstr_cpy_func(str, &cstr->_cstr[cstr_start], str_len);
    }

    return CStrSuccess;
}

CStrStatusCode cstr_strcpy_nocheck(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr) {
    if (cstr_start + str_len - 1 >= cstr->_cstr_sz) {
        return CStrOutOfBoundError;
    }

    if (cstr_cpy_func == CSTR_DEFAULT_CPYFUNC) {
        strncpy(str, &cstr->_cstr[cstr_start], str_len);
    } else {
        cstr_cpy_func(str, &cstr->_cstr[cstr_start], str_len);
    }

    return CStrSuccess;
}

CStrStatusCode cstr_fprint(FILE* f, CString* cstr) {
    if (f == NULL || cstr == NULL) {
        return CStrFuncArgError;
    }

    fwrite(cstr->_cstr, sizeof(char), cstr->_cstr_sz, f);

    return CStrSuccess;
}

CStrStatusCode cstr_ref_fprint(FILE* f, CStringRef* cstr_ref, size_t cstr_ref_len) {
    if (f == NULL || cstr_ref == NULL) {
        return CStrFuncArgError;
    }

    for (size_t ref_id = 0; ref_id < cstr_ref_len; ++ref_id) {
        fwrite(cstr_ref[ref_id]._cstr_ref, sizeof(char), cstr_ref[ref_id]._cstr_ref_len, f);
        fwrite("\n", sizeof(char), 1, f);
    }

    return CStrSuccess;
}

CStrStatusCode cstr_fprint_nocheck(FILE* f, CString* cstr) {
    fwrite(cstr->_cstr, sizeof(char), cstr->_cstr_sz, f);

    return CStrSuccess;
}

CStrStatusCode cstr_ref_fprint_nocheck(FILE* f, CStringRef* cstr_ref, size_t cstr_ref_len) {
    for (size_t ref_id = 0; ref_id < cstr_ref_len; ++ref_id) {
        fwrite(cstr_ref[ref_id]._cstr_ref, sizeof(char), cstr_ref[ref_id]._cstr_ref_len, f);
        fwrite("\n", sizeof(char), 1, f);
    }

    return CStrSuccess;
}

CStrStatusCode cstr_clean(CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    cstr->_cstr_sz = 0;

    return CStrSuccess;
}

CStrStatusCode cstr_clean_nocheck(CString* cstr) {
    cstr->_cstr_sz = 0;

    return CStrSuccess;
}

CStrStatusCode cstr_free(CString** cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (*cstr == NULL) {
        return CStrFuncArgError;
    }

    if ((*cstr)->_cstr == NULL) {
        return CStrNullStrError;
    }

    free((*cstr)->_cstr);
    free(*cstr);

    *cstr = NULL;

    return CStrSuccess;
}

CStrStatusCode cstr_free_nocheck(CString** cstr) {
    if ((*cstr)->_cstr == NULL) {
        return CStrNullStrError;
    }

    free((*cstr)->_cstr);
    free(*cstr);

    *cstr = NULL;

    return CStrSuccess;
}