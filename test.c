//
// Created by mario on 2024/8/13.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

#include "cstr.h"

int main(int argc, char* argv[]) {

    CString* cstr;

    cstr_new(sizeof(" a '  ' loop pool") - 1, " a '  ' loop pool", &cstr);

    size_t split_len = 0;
    CStringRef* split_strs = NULL;

    cstr_split_nocheck(cstr, ' ', '\'', '\'', &split_len, &split_strs);

    cstr_ref_fprint_nocheck(stdout, split_strs, split_len);

    return 0;
}