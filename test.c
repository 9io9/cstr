//
// Created by mario on 2024/8/13.
//

#include <string.h>

#include "cstr.h"

int main(int argc, char* argv[]) {

    CString* cstr;

    if (cstr_new(sizeof("he llo") - 1, "hello", &cstr) != CStrSuccess) {
        return -1;
    }

    if (cstr_pushs(sizeof("cat more") - 1, "catmore", cstr) != CStrSuccess) {
        return -1;
    }

    char str_buf[32] = { 0 };

    memset(str_buf, 'l', 31);

    if (cstr_strcpy(4, 3, str_buf, CSTR_DEFAULT_CPYFUNC, cstr) != CStrSuccess) {
        return -1;
    }

    fprintf(stdout, "%s\n", str_buf);

    if (cstr_pops(5, str_buf, cstr) != CStrSuccess) {
        return -1;
    }

    fprintf(stdout, "%s\n", str_buf);

    if (cstr_fprint(stdout, cstr) != CStrSuccess) {
        return -1;
    }

    size_t split_len;
    CStringRef* split_strs;

    if (cstr_split(cstr, ' ', &split_len, &split_strs) != CStrSuccess) {
        return -1;
    }

    return 0;
}