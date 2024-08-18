//
// Created by mario on 2024/8/13.
//

#ifndef CSTR_ERR_H
#define CSTR_ERR_H

typedef enum CStrStatusCode {
    CStrSuccess = 0,
    CStrFuncArgError,
    CStrMemError,
    CStrZeroSizeError,
    CStrOutOfBoundError,
    CStrNullStrError,
    CStrNoSplitError,
}CStrStatusCode;

typedef enum CStrOpStatusCode {
    CStrOpSuccess = 0,
    CStrOpFuncArgError,
    CStrOpPatterNotMatchError,
    CStrOpCmpSizeError,
}CStrOpStatusCode;

typedef enum CStrCastStatusCode {
    CStrCastSuccess = 0,
    CStrCastInvalidScaleFormatError,
    CStrCastOverflowError,
    CStrCastZeroStrError,
}CStrCastStatusCode;

typedef enum CWStrStatusCode {
    CWStrSuccess = 0,
    CWStrFuncArgError,
    CWStrMemError,
    CWStrZeroSizeError,
    CWStrOutOfBoundError,
    CWStrNullStrError,
}CWStrStatusCode;

#endif //CSTR_ERR_H
