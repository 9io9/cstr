//
// Created by mario on 2024/8/16.
//

#ifndef CSTR_CAST_H
#define CSTR_CAST_H

#include <stdint.h>
#include "cstr.def.h"
#include "cstr.err.h"

extern CStrCastStatusCode cstr_cast_to_ssize(CString* cstr, ssize_t* ssize, int scale);

extern CStrCastStatusCode cstr_ref_cast_to_ssize(CStringRef* cstr_ref, ssize_t* ssize, int scale);

extern CStrCastStatusCode cstr_cast_to_size(CString* cstr, size_t* size, int scale);

extern CStrCastStatusCode cstr_ref_cast_to_size(CStringRef* cstr_ref, size_t* size, int scale);

#if __MACHINE_WORD_SIZE__ == 64
extern CStrCastStatusCode cstr_cast_to_u64(CString* cstr, uint64_t* u64, int scale);

extern CStrCastStatusCode cstr_cast_to_i64(CString* cstr, int64_t* i64, int scale);
#endif

// no function arg check version

FUNC_ASSERT(CSTR != NULL, SSIZE != NULL)
extern CStrCastStatusCode cstr_cast_to_ssize_nocheck(CString* cstr, ssize_t* ssize, int scale);

FUNC_ASSERT(CSTR_REF != NULL, SSIZE != NULL)
extern CStrCastStatusCode cstr_ref_cast_to_ssize_nocheck(CStringRef* cstr_ref, ssize_t* ssize, int scale);

FUNC_ASSERT(CSTR != NULL, SIZE != NULL)
extern CStrCastStatusCode cstr_cast_to_size_nocheck(CString* cstr, size_t* size, int scale);

FUNC_ASSERT(CSTR_REF != NULL, SIZE != NULL)
extern CStrCastStatusCode cstr_ref_cast_to_size_nocheck(CStringRef* cstr_ref, size_t* size, int scale);

#if __MACHINE_WORD_SIZE__ == 64
FUNC_ASSERT(CSTR != NULL, U64 != NULL)
extern CStrCastStatusCode cstr_cast_to_u64_nocheck(CString* cstr, uint64_t* u64, int scale);

FUNC_ASSERT(CSTR_REF != NULL, I64 != NULL)
extern CStrCastStatusCode cstr_cast_to_i64_nocheck(CString* cstr, int64_t* i64, int scale);
#endif

#endif //CSTR_CAST_H
