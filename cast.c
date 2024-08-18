//
// Created by mario on 2024/8/16.
//

#include <limits.h>
#include <ctype.h>

#include "cstr.strop.h"

CStrCastStatusCode cstr_cast_to_size(CString* cstr, size_t* size, int scale) {
    if (cstr == NULL || size == NULL || scale == 0) {
        return CStrFuncArgError;
    }

    if (cstr->_cstr_sz == 0) {
        return CStrCastZeroStrError;
    }

    int cmp_res;
    size_t cstr_id = 0;
    size_t shift_len;

    switch (scale) {
        case 16:
            cstr_cmp_str(cstr, "0x", 2, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 2;

#define digit_value shift_len
            for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
                if (isdigit(cstr->_cstr[cstr_id])) {
                    digit_value = cstr->_cstr[cstr_id] - '0';
                } else if (cstr->_cstr[cstr_id] >= 'a' && cstr->_cstr[cstr_id] <= 'f') {
                    digit_value = cstr->_cstr[cstr_id] - 'a' + 10;
                } else if (cstr->_cstr[cstr_id] >= 'A' && cstr->_cstr[cstr_id] <= 'F') {
                    digit_value = cstr->_cstr[cstr_id] - 'A' + 10;
                } else {
                    return CStrCastInvalidScaleFormatError;
                }

                if (cstr_id == cstr->_cstr_sz - 1) {
                    if (*size <= SIZE_MAX - digit_value) {
                        *size +=  digit_value;
                    } else {
                        return CStrCastOverflowError;
                    }
                } else {
                    if (*size <= (SIZE_MAX >> 4) - digit_value) {
                        *size = (*size + digit_value) << 4;
                    } else {
                        return CStrCastOverflowError;
                    }
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 10:
            *size = 0;

#define digit_value shift_len
            for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
                if (isdigit(cstr->_cstr[cstr_id])) {
                    digit_value = cstr->_cstr[cstr_id] - '0';

                    if (cstr_id == cstr->_cstr_sz - 1) {
                        if (*size <= SIZE_MAX - digit_value) {
                            *size +=  digit_value;
                        } else {
                            return CStrCastOverflowError;
                        }
                    } else {
                        if (*size <= SIZE_MAX / 10 - digit_value) {
                            *size = (*size + digit_value) * 10;
                        } else {
                            return CStrCastOverflowError;
                        }
                    }
                } else {
                    return CStrCastInvalidScaleFormatError;
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 8:
            cstr_cmp_str(cstr, "0", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 3;
            break;

        case 2:
            cstr_cmp_str(cstr, "b", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 1;
            break;

        default:
            return CStrCastInvalidScaleFormatError;
    }

    *size = 0;

    for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (isdigit(cstr->_cstr[cstr_id])) {
            size_t digit_value = cstr->_cstr[cstr_id] - '0';

            if (cstr_id == cstr->_cstr_sz - 1) {
                if (*size <= SIZE_MAX - digit_value) {
                    *size +=  digit_value;
                } else {
                    return CStrCastOverflowError;
                }
            } else {
                if (*size <= (SIZE_MAX >> shift_len) - digit_value) {
                    *size = *size + digit_value << shift_len;
                } else {
                    return CStrCastOverflowError;
                }
            }
        } else {
            return CStrCastInvalidScaleFormatError;
        }
    }

    return CStrCastSuccess;
}

CStrCastStatusCode cstr_cast_to_size_nocheck(CString* cstr, size_t* size, int scale) {
    if (cstr->_cstr_sz == 0) {
        return CStrCastZeroStrError;
    }

    int cmp_res;
    size_t cstr_id = 0;
    size_t shift_len;

    switch (scale) {
        case 16:
            cstr_cmp_str(cstr, "0x", 2, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 2;

#define digit_value shift_len
            for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
                if (isdigit(cstr->_cstr[cstr_id])) {
                    digit_value = cstr->_cstr[cstr_id] - '0';
                } else if (cstr->_cstr[cstr_id] >= 'a' && cstr->_cstr[cstr_id] <= 'f') {
                    digit_value = cstr->_cstr[cstr_id] - 'a' + 10;
                } else if (cstr->_cstr[cstr_id] >= 'A' && cstr->_cstr[cstr_id] <= 'F') {
                    digit_value = cstr->_cstr[cstr_id] - 'A' + 10;
                } else {
                    return CStrCastInvalidScaleFormatError;
                }

                if (cstr_id == cstr->_cstr_sz - 1) {
                    if (*size <= SIZE_MAX - digit_value) {
                        *size +=  digit_value;
                    } else {
                        return CStrCastOverflowError;
                    }
                } else {
                    if (*size <= (SIZE_MAX >> 4) - digit_value) {
                        *size = (*size + digit_value) << 4;
                    } else {
                        return CStrCastOverflowError;
                    }
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 10:
            *size = 0;

#define digit_value shift_len
            for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
                if (isdigit(cstr->_cstr[cstr_id])) {
                    digit_value = cstr->_cstr[cstr_id] - '0';

                    if (cstr_id == cstr->_cstr_sz - 1) {
                        if (*size <= SIZE_MAX - digit_value) {
                            *size +=  digit_value;
                        } else {
                            return CStrCastOverflowError;
                        }
                    } else {
                        if (*size <= SIZE_MAX / 10 - digit_value) {
                            *size = (*size + digit_value) * 10;
                        } else {
                            return CStrCastOverflowError;
                        }
                    }
                } else {
                    return CStrCastInvalidScaleFormatError;
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 8:
            cstr_cmp_str(cstr, "0", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 3;
            break;

        case 2:
            cstr_cmp_str(cstr, "b", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 1;
            break;

        default:
            return CStrCastInvalidScaleFormatError;
    }

    *size = 0;

    for (; cstr_id < cstr->_cstr_sz; ++cstr_id) {
        if (isdigit(cstr->_cstr[cstr_id])) {
            size_t digit_value = cstr->_cstr[cstr_id] - '0';

            if (cstr_id == cstr->_cstr_sz - 1) {
                if (*size <= SIZE_MAX - digit_value) {
                    *size +=  digit_value;
                } else {
                    return CStrCastOverflowError;
                }
            } else {
                if (*size <= (SIZE_MAX >> shift_len) - digit_value) {
                    *size = *size + digit_value << shift_len;
                } else {
                    return CStrCastOverflowError;
                }
            }
        } else {
            return CStrCastInvalidScaleFormatError;
        }
    }

    return CStrCastSuccess;
}

CStrCastStatusCode cstr_ref_cast_to_size(CStringRef* cstr_ref, size_t* size, int scale) {
    if (cstr_ref == NULL || size == NULL || scale == 0) {
        return CStrFuncArgError;
    }

    if (cstr_ref->_cstr_ref_len == 0) {
        return CStrCastZeroStrError;
    }

    int cmp_res;
    size_t cstr_id = 0;
    size_t shift_len;

    switch (scale) {
        case 16:
            cstr_ref_cmp_str(cstr_ref, "0x", 2, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 2;

#define digit_value shift_len
            for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
                if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';
                } else if (cstr_ref->_cstr_ref[cstr_id] >= 'a' && cstr_ref->_cstr_ref[cstr_id] <= 'f') {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - 'a' + 10;
                } else if (cstr_ref->_cstr_ref[cstr_id] >= 'A' && cstr_ref->_cstr_ref[cstr_id] <= 'F') {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - 'A' + 10;
                } else {
                    return CStrCastInvalidScaleFormatError;
                }

                if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                    if (*size <= SIZE_MAX - digit_value) {
                        *size +=  digit_value;
                    } else {
                        return CStrCastOverflowError;
                    }
                } else {
                    if (*size <= (SIZE_MAX >> 4) - digit_value) {
                        *size = *size + digit_value << 4;
                    } else {
                        return CStrCastOverflowError;
                    }
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 10:
            *size = 0;

#define digit_value shift_len
            for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
                if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';

                    if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                        if (*size <= SIZE_MAX - digit_value) {
                            *size +=  digit_value;
                        } else {
                            return CStrCastOverflowError;
                        }
                    } else {
                        if (*size <= SIZE_MAX / 10 - digit_value) {
                            *size = (*size + digit_value) * 10;
                        } else {
                            return CStrCastOverflowError;
                        }
                    }
                } else {
                    return CStrCastInvalidScaleFormatError;
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 8:
            cstr_ref_cmp_str(cstr_ref, "0", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 3;
            break;

        case 2:
            cstr_ref_cmp_str(cstr_ref, "b", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 1;
            break;

        default:
            return CStrCastInvalidScaleFormatError;
    }

    *size = 0;

    for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
        if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
            size_t digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';

            if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                if (*size <= SIZE_MAX - digit_value) {
                    *size +=  digit_value;
                } else {
                    return CStrCastOverflowError;
                }
            } else {
                if (*size <= (SIZE_MAX >> shift_len) - digit_value) {
                    *size = *size + digit_value << shift_len;
                } else {
                    return CStrCastOverflowError;
                }
            }
        } else {
            return CStrCastInvalidScaleFormatError;
        }
    }

    return CStrCastSuccess;
}

CStrCastStatusCode cstr_ref_cast_to_size_nocheck(CStringRef* cstr_ref, size_t* size, int scale) {
    if (cstr_ref == NULL || size == NULL || scale == 0) {
        return CStrFuncArgError;
    }

    if (cstr_ref->_cstr_ref_len == 0) {
        return CStrCastZeroStrError;
    }

    int cmp_res;
    size_t cstr_id = 0;
    size_t shift_len;

    switch (scale) {
        case 16:
            cstr_ref_cmp_str(cstr_ref, "0x", 2, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 2;

#define digit_value shift_len
            for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
                if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';
                } else if (cstr_ref->_cstr_ref[cstr_id] >= 'a' && cstr_ref->_cstr_ref[cstr_id] <= 'f') {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - 'a' + 10;
                } else if (cstr_ref->_cstr_ref[cstr_id] >= 'A' && cstr_ref->_cstr_ref[cstr_id] <= 'F') {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - 'A' + 10;
                } else {
                    return CStrCastInvalidScaleFormatError;
                }

                if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                    if (*size <= SIZE_MAX - digit_value) {
                        *size +=  digit_value;
                    } else {
                        return CStrCastOverflowError;
                    }
                } else {
                    if (*size <= (SIZE_MAX >> 4) - digit_value) {
                        *size = *size + digit_value << 4;
                    } else {
                        return CStrCastOverflowError;
                    }
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 10:
            *size = 0;

#define digit_value shift_len
            for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
                if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
                    digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';

                    if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                        if (*size <= SIZE_MAX - digit_value) {
                            *size +=  digit_value;
                        } else {
                            return CStrCastOverflowError;
                        }
                    } else {
                        if (*size <= SIZE_MAX / 10 - digit_value) {
                            *size = (*size + digit_value) * 10;
                        } else {
                            return CStrCastOverflowError;
                        }
                    }
                } else {
                    return CStrCastInvalidScaleFormatError;
                }
            }
#undef digit_value

            return CStrCastSuccess;

        case 8:
            cstr_ref_cmp_str(cstr_ref, "0", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 3;
            break;

        case 2:
            cstr_ref_cmp_str(cstr_ref, "b", 1, &cmp_res);

            if (cmp_res != 0) {
                return CStrCastInvalidScaleFormatError;
            }

            cstr_id = 1;
            shift_len = 1;
            break;

        default:
            return CStrCastInvalidScaleFormatError;
    }

    *size = 0;

    for (; cstr_id < cstr_ref->_cstr_ref_len; ++cstr_id) {
        if (isdigit(cstr_ref->_cstr_ref[cstr_id])) {
            size_t digit_value = cstr_ref->_cstr_ref[cstr_id] - '0';

            if (cstr_id == cstr_ref->_cstr_ref_len - 1) {
                if (*size <= SIZE_MAX - digit_value) {
                    *size +=  digit_value;
                } else {
                    return CStrCastOverflowError;
                }
            } else {
                if (*size <= (SIZE_MAX >> shift_len) - digit_value) {
                    *size = *size + digit_value << shift_len;
                } else {
                    return CStrCastOverflowError;
                }
            }
        } else {
            return CStrCastInvalidScaleFormatError;
        }
    }

    return CStrCastSuccess;
}