#include <malloc.h>
#include <string.h>

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
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (str_len != 0 && str == NULL) {
        return CStrFuncArgError;
    }

    if (str_len == 0 && str != NULL) {
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

CStrStatusCode cstr_pushs(size_t str_len, char str[], CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (str_len == 0 && str != NULL) {
        return CStrFuncArgError;
    }

    if (str_len != 0 && str == NULL) {
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

CStrStatusCode cstr_pops(size_t str_len, char str[], CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (str_len == 0 || str == NULL) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz < str_len) {
        return CStrZeroSizeError;
    }

    cstr->_cstr_sz -= str_len;

    strncpy(str, &cstr->_cstr[cstr->_cstr_sz], str_len);

    return CStrSuccess;
}

CStrStatusCode cstr_strcpy(size_t cstr_start, size_t str_len, char str[], CStrCopyFunc cstr_cpy_func, CString* cstr) {
    if (cstr == NULL) {
        return CStrFuncArgError;
    }

    if (str_len == 0 || str == NULL) {
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