//
// Created by mario on 2024/8/13.
//

#include <string.h>

#include "cstr.h"

int main(int argc, char* argv[]) {

    CString* cstr;

    cstr_new(sizeof("print hello with smiling faces") - 1, "print hello with smiling faces", &cstr);

    CStringRef cstr_ref;

    if (cstr_find_str(cstr, " wih s", sizeof(" wih s") - 1, &cstr_ref) == CStrOpPatterNotMatchError) {
        fprintf(stdout, "no match pattern\n");
        return -1;
    }

    cstr_ref_fprint(stdout, &cstr_ref, 1);

    return 0;
}