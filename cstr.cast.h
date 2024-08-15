//
// Created by mario on 2024/8/16.
//

#ifndef CSTR_CAST_H
#define CSTR_CAST_H

#include "cstr.def.h"
#include "cstr.err.h"

extern CStrStatusCode cstr_cast_to_size(CString* cstr, size_t* size, int scale);

extern CStrStatusCode cstr_ref_cast_to_size(CStringRef* cstr_ref, size_t* size, int scale);

#endif //CSTR_CAST_H
