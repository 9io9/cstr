//
// Created by mario on 2024/8/13.
//

#include <stdio.h>
#include <string.h>

#include "cstr.h"

int main(int argc, char* argv[]) {

    CString* cstr;

    cstr_new(sizeof("073") - 1, "073", &cstr);

    size_t cast_size = 0;

    cstr_cast_to_size(cstr, &cast_size, 8);

    fprintf(stdout, "cast value = %zu\n", cast_size);

    return 0;
}