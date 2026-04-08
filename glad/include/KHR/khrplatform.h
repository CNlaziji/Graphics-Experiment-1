// khrplatform.h
// Copyright (c) 2008-2016 The Khronos Group Inc.
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
// 
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

#ifndef __khrplatform_h_
#define __khrplatform_h_

/* 
 * This file contains platform-specific types and definitions for the
 * OpenGL, OpenGL ES, and Vulkan loading libraries.
 */

/* Platform-specific types */
#if defined(_WIN32) && !defined(_WIN32_WCE)
    /* Windows Desktop */
    #define KHRONOS_APICALL __declspec(dllimport)
    #if defined(_MSC_VER)
        typedef signed char         khronos_int8_t;
        typedef unsigned char       khronos_uint8_t;
        typedef signed short        khronos_int16_t;
        typedef unsigned short      khronos_uint16_t;
        typedef signed int          khronos_int32_t;
        typedef unsigned int        khronos_uint32_t;
        typedef signed __int64      khronos_int64_t;
        typedef unsigned __int64    khronos_uint64_t;
        typedef float               khronos_float_t;
        typedef double              khronos_double_t;
        #define khronos_nullptr    nullptr
    #else
        typedef signed char         khronos_int8_t;
        typedef unsigned char       khronos_uint8_t;
        typedef signed short        khronos_int16_t;
        typedef unsigned short      khronos_uint16_t;
        typedef signed int          khronos_int32_t;
        typedef unsigned int        khronos_uint32_t;
        typedef signed long long    khronos_int64_t;
        typedef unsigned long long  khronos_uint64_t;
        typedef float               khronos_float_t;
        typedef double              khronos_double_t;
        #define khronos_nullptr    NULL
    #endif
#elif defined(_WIN32_WCE)
    /* Windows CE */
    #define KHRONOS_APICALL __declspec(dllimport)
    typedef signed char         khronos_int8_t;
    typedef unsigned char       khronos_uint8_t;
    typedef signed short        khronos_int16_t;
    typedef unsigned short      khronos_uint16_t;
    typedef signed int          khronos_int32_t;
    typedef unsigned int        khronos_uint32_t;
    typedef signed __int64      khronos_int64_t;
    typedef unsigned __int64    khronos_uint64_t;
    typedef float               khronos_float_t;
    typedef double              khronos_double_t;
    #define khronos_nullptr    NULL
#elif defined(__ANDROID__)
    /* Android */
    #define KHRONOS_APICALL
    #include <stdint.h>
    typedef int8_t              khronos_int8_t;
    typedef uint8_t             khronos_uint8_t;
    typedef int16_t             khronos_int16_t;
    typedef uint16_t            khronos_uint16_t;
    typedef int32_t             khronos_int32_t;
    typedef uint32_t            khronos_uint32_t;
    typedef int64_t             khronos_int64_t;
    typedef uint64_t            khronos_uint64_t;
    typedef float               khronos_float_t;
    typedef double              khronos_double_t;
    #define khronos_nullptr    NULL
#elif defined(__APPLE__)
    /* Apple */
    #define KHRONOS_APICALL
    #include <stdint.h>
    typedef int8_t              khronos_int8_t;
    typedef uint8_t             khronos_uint8_t;
    typedef int16_t             khronos_int16_t;
    typedef uint16_t            khronos_uint16_t;
    typedef int32_t             khronos_int32_t;
    typedef uint32_t            khronos_uint32_t;
    typedef int64_t             khronos_int64_t;
    typedef uint64_t            khronos_uint64_t;
    typedef float               khronos_float_t;
    typedef double              khronos_double_t;
    #define khronos_nullptr    NULL
#elif defined(__unix__)
    /* Unix */
    #define KHRONOS_APICALL
    #include <stdint.h>
    typedef int8_t              khronos_int8_t;
    typedef uint8_t             khronos_uint8_t;
    typedef int16_t             khronos_int16_t;
    typedef uint16_t            khronos_uint16_t;
    typedef int32_t             khronos_int32_t;
    typedef uint32_t            khronos_uint32_t;
    typedef int64_t             khronos_int64_t;
    typedef uint64_t            khronos_uint64_t;
    typedef float               khronos_float_t;
    typedef double              khronos_double_t;
    #define khronos_nullptr    NULL
#else
    /* Default */
    #define KHRONOS_APICALL
    #include <stdint.h>
    typedef int8_t              khronos_int8_t;
    typedef uint8_t             khronos_uint8_t;
    typedef int16_t             khronos_int16_t;
    typedef uint16_t            khronos_uint16_t;
    typedef int32_t             khronos_int32_t;
    typedef uint32_t            khronos_uint32_t;
    typedef int64_t             khronos_int64_t;
    typedef uint64_t            khronos_uint64_t;
    typedef float               khronos_float_t;
    typedef double              khronos_double_t;
    #define khronos_nullptr    NULL
#endif

/* Define KHRONOS_APIENTRY if it's not already defined */
#ifndef KHRONOS_APIENTRY
    #define KHRONOS_APIENTRY
#endif

/* Define KHRONOS_APIATTRIBUTES if it's not already defined */
#ifndef KHRONOS_APIATTRIBUTES
    #define KHRONOS_APIATTRIBUTES
#endif

#endif // __khrplatform_h_
