//
// Created by mario on 2024/8/13.
//

#ifndef CSTR_DEF_H
#define CSTR_DEF_H

#include <stddef.h>

#define CSTR_DEFAULT_CPYFUNC NULL

typedef size_t(*CStrCopyFunc)(char*, char*, size_t);
typedef size_t(*CWStrCopyFunc)(wchar_t*, wchar_t*, size_t);

typedef struct CString {
    size_t _cstr_len;
    size_t _cstr_sz;
    char* _cstr;
}CString;

typedef struct CWString {
    size_t _cwstr_len;
    size_t _cwstr_sz;
    wchar_t* _cwstr;
}CWString;

#endif //CSTR_DEF_H
