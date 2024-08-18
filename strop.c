//
// Created by mario on 2024/8/16.
//

#include <malloc.h>
#include <string.h>

#include "cstr.def.h"
#include "cstr.err.h"

static size_t cstr_ref_rfind_ch(CStringRef* str, char ch) {
    size_t ch_id = 0;

    for (size_t str_id = 0; str_id < str->_cstr_ref_len; ++str_id) {
        if (str->_cstr_ref[str_id] == ch) {
            ch_id = str_id;
        }
    }

    return ch_id;
}

CStrOpStatusCode cstr_find_str(CString* cstr, const char* str, size_t str_len, CStringRef* found_str) {
    if (cstr == NULL || str == NULL || found_str == NULL) {
        return CStrOpFuncArgError;
    }

    if (str_len == 0 || str_len > cstr->_cstr_sz) {
        return CStrOpPatterNotMatchError;
    }

    if (str_len == cstr->_cstr_sz) {
        return strncmp(str, cstr->_cstr, str_len) == 0 ? CStrOpSuccess : CStrOpPatterNotMatchError;
    }

    size_t cstr_id = 0;
    CStringRef str_ref = { ._cstr_ref = (char*) str, ._cstr_ref_len = str_len };

    for (size_t str_id = 0; str_id < str_len;) {
        if (cstr->_cstr[cstr_id + str_id] != str[str_id]) {

            if (cstr_id + str_len >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            cstr_id += str_len - cstr_ref_rfind_ch(&str_ref, cstr->_cstr[cstr_id + str_len]);

            if (cstr_id >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            str_id = 0;
        } else {
            ++str_id;
        }
    }

    found_str->_cstr_ref = &cstr->_cstr[cstr_id];
    found_str->_cstr_ref_len = str_len;

    return CStrOpSuccess;
}

CStrOpStatusCode cstr_find_str_nocheck(CString* cstr, const char* str, size_t str_len, CStringRef* found_str) {
    if (str_len > cstr->_cstr_sz) {
        return CStrOpPatterNotMatchError;
    }

    if (str_len == cstr->_cstr_sz) {
        return strncmp(str, cstr->_cstr, str_len) == 0 ? CStrOpSuccess : CStrOpPatterNotMatchError;
    }

    size_t cstr_id = 0;
    CStringRef str_ref = { ._cstr_ref = (char*) str, ._cstr_ref_len = str_len };

    for (size_t str_id = 0; str_id < str_len;) {
        if (cstr->_cstr[cstr_id + str_id] != str[str_id]) {

            if (cstr_id + str_len >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            cstr_id += str_len - cstr_ref_rfind_ch(&str_ref, cstr->_cstr[cstr_id + str_len]);

            if (cstr_id >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            str_id = 0;
        } else {
            ++str_id;
        }
    }

    found_str->_cstr_ref = &cstr->_cstr[cstr_id];
    found_str->_cstr_ref_len = str_len;

    return CStrOpSuccess;
}


CStrOpStatusCode cstr_find_str_ref(CString* cstr, CStringRef* str, CStringRef* found_str) {
    if (cstr == NULL || str == NULL || found_str == NULL) {
        return CStrOpFuncArgError;
    }

    if (str->_cstr_ref_len == 0 || str->_cstr_ref_len > cstr->_cstr_sz) {
        return CStrOpPatterNotMatchError;
    }

    if (str->_cstr_ref_len == cstr->_cstr_sz) {
        return strncmp(str->_cstr_ref, cstr->_cstr, cstr->_cstr_sz) == 0 ? CStrOpSuccess : CStrOpPatterNotMatchError;
    }

    size_t cstr_id = 0;

    for (size_t str_id = 0; str_id < str->_cstr_ref_len;) {
        if (cstr->_cstr[cstr_id + str_id] != str->_cstr_ref[str_id]) {

            if (cstr_id + str->_cstr_ref_len >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            cstr_id += str->_cstr_ref_len - cstr_ref_rfind_ch(str, cstr->_cstr[cstr_id + str->_cstr_ref_len]);

            if (cstr_id >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            str_id = 0;
        } else {
            ++str_id;
        }
    }

    found_str->_cstr_ref = &cstr->_cstr[cstr_id];
    found_str->_cstr_ref_len = str->_cstr_ref_len;

    return CStrOpSuccess;
}

CStrOpStatusCode cstr_find_str_ref_nocheck(CString* cstr, CStringRef* str, CStringRef* found_str) {
    if (str->_cstr_ref_len == 0 || str->_cstr_ref_len > cstr->_cstr_sz) {
        return CStrOpPatterNotMatchError;
    }

    if (str->_cstr_ref_len == cstr->_cstr_sz) {
        return strncmp(str->_cstr_ref, cstr->_cstr, cstr->_cstr_sz) == 0 ? CStrOpSuccess : CStrOpPatterNotMatchError;
    }

    size_t cstr_id = 0;

    for (size_t str_id = 0; str_id < str->_cstr_ref_len;) {
        if (cstr->_cstr[cstr_id + str_id] != str->_cstr_ref[str_id]) {

            if (cstr_id + str->_cstr_ref_len >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            cstr_id += str->_cstr_ref_len - cstr_ref_rfind_ch(str, cstr->_cstr[cstr_id + str->_cstr_ref_len]);

            if (cstr_id >= cstr->_cstr_sz) {
                return CStrOpPatterNotMatchError;
            }

            str_id = 0;
        } else {
            ++str_id;
        }
    }

    found_str->_cstr_ref = &cstr->_cstr[cstr_id];
    found_str->_cstr_ref_len = str->_cstr_ref_len;

    return CStrOpSuccess;
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

CStrOpStatusCode cstr_cmp_str(CString* cstr, const char* str, size_t str_len, int* cmp_res) {
    if (cstr == NULL || str == NULL || str_len == 0 || cmp_res == NULL) {
        return CStrOpFuncArgError;
    }

    if (str_len > cstr->_cstr_sz) {
        *cmp_res = 1;
        return CStrOpCmpSizeError;
    }

    for (size_t cmp_id = 0; cmp_id < str_len; ++cmp_id) {
        if (cstr->_cstr[cmp_id] > str[cmp_id]) {
            *cmp_res = 1;
            return CStrOpSuccess;
        }

        if (cstr->_cstr[cmp_id] < str[cmp_id]) {
            *cmp_res = -1;
            return CStrOpSuccess;
        }
    }

    *cmp_res = 0;

    return CStrOpSuccess;
}

CStrOpStatusCode cstr_cmp_str_nocheck(CString* cstr, const char* str, size_t str_len, int* cmp_res) {
    if (str_len > cstr->_cstr_sz) {
        *cmp_res = 1;
        return CStrOpCmpSizeError;
    }

    for (size_t cmp_id = 0; cmp_id < str_len; ++cmp_id) {
        if (cstr->_cstr[cmp_id] > str[cmp_id]) {
            *cmp_res = 1;
            return CStrOpSuccess;
        }

        if (cstr->_cstr[cmp_id] < str[cmp_id]) {
            *cmp_res = -1;
            return CStrOpSuccess;
        }
    }

    *cmp_res = 0;

    return CStrOpSuccess;
}

CStrOpStatusCode cstr_ref_cmp_str(CStringRef* cstr_ref, const char* str, size_t str_len, int* cmp_res) {
    if (cstr_ref == NULL || str == NULL || str_len == 0 || cmp_res == NULL) {
        return CStrOpFuncArgError;
    }

    if (str_len > cstr_ref->_cstr_ref_len) {
        *cmp_res = 1;
        return CStrOpCmpSizeError;
    }

    for (size_t cmp_id = 0; cmp_id < str_len; ++cmp_id) {
        if (cstr_ref->_cstr_ref[cmp_id] > str[cmp_id]) {
            *cmp_res = 1;
            return CStrOpSuccess;
        }

        if (cstr_ref->_cstr_ref[cmp_id] < str[cmp_id]) {
            *cmp_res = -1;
            return CStrOpSuccess;
        }
    }

    *cmp_res = 0;

    return CStrOpSuccess;
}

CStrOpStatusCode cstr_ref_cmp_str_nocheck(CStringRef* cstr_ref, const char* str, size_t str_len, int* cmp_res) {
    if (str_len > cstr_ref->_cstr_ref_len) {
        *cmp_res = 1;
        return CStrOpCmpSizeError;
    }

    for (size_t cmp_id = 0; cmp_id < str_len; ++cmp_id) {
        if (cstr_ref->_cstr_ref[cmp_id] > str[cmp_id]) {
            *cmp_res = 1;
            return CStrOpSuccess;
        }

        if (cstr_ref->_cstr_ref[cmp_id] < str[cmp_id]) {
            *cmp_res = -1;
            return CStrOpSuccess;
        }
    }

    *cmp_res = 0;

    return CStrOpSuccess;
}