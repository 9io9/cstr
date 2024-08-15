//
// Created by mario on 2024/8/16.
//

#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "cstr.strop.h"


CStrStatusCode cstr_cast_to_size(CString* cstr, size_t* size, int scale) {
    if (cstr == NULL || size == NULL || scale == 0) {
        return CStrFuncArgError;
    }

    int cmp_res;
    size_t cstr_id = 0;

    switch (scale) {
        case 16:
            cstr_cmp_str(cstr, "0x", 2, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            break;

        case 8:
            cstr_cmp_str(cstr, "0", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            break;

        case 2:
            cstr_cmp_str(cstr, "b", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            break;

        default:
            return CStrCastInvalidScaleFormatError;
    }

    if (scale == 16) {
        if (strncasecmp("0x", cstr->_cstr, 2) != 0) {
            return CStrCastInvalidScaleFormatError;
        }
    }

    for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (isdigit())
    }
}