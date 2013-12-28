/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Mateusz Kolodziejski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file moccpp/System/cstdio.cpp
 *
 * @desc vsnprintf C standard library function compatible with all supported operating systems.
 */

#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdint>

#include <moccpp/System/cstdio.hpp>

namespace moccpp
{

namespace System
{

#if defined _MSC_VER

void blank_invalid_parameter_hdl(const wchar_t * /*expression*/, const wchar_t * /*function*/, const wchar_t * /*file*/, unsigned int /*line*/, uintptr_t /*pReserved*/)
{
    // do nothing
}

#endif

int32_t vsnprintf(char * s, size_t size_of_buffer, size_t n, const char * format, va_list arg)
{
#if defined _MSC_VER || defined __CYGWIN__
  #ifdef __GNU__C
    n = size_of_buffer;
    return ::vsnprintf(s, n, format, arg);
  #else
    _invalid_parameter_handler oldHandler, newHandler;
    newHandler = blank_invalid_parameter_hdl;
    oldHandler = _set_invalid_parameter_handler(newHandler);

    int32_t ret = vsnprintf_s(s, size_of_buffer, n, format, arg);

    if (ret < 0) {
        _set_invalid_parameter_handler(oldHandler);
        return _vscprintf(format, arg); // required size
    }

    _set_invalid_parameter_handler(oldHandler);
    return ret;
  #endif
#else
    n = size_of_buffer;
    return ::vsnprintf(s, n, format, arg);
#endif
}

}

}
