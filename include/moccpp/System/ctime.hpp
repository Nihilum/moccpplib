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
 * @file moccpp/System/ctime.hpp
 *
 * @desc Thread-safe gmtime, asctime, ctime C standard library functions compatible
 *  with all operating systems.
 */

#ifndef MOCCPP_SYSTEM_CTIME_HPP
#define MOCCPP_SYSTEM_CTIME_HPP

#include <cstdint>

#include <moccpp/Config.hpp>

namespace moccpp
{

namespace System
{

MOCCPP_DLL_PUBLIC inline int32_t gmtime(const time_t* timer, struct tm* result);
MOCCPP_DLL_PUBLIC inline int32_t asctime(char* buffer, size_t buff_size, const struct tm *_tm);
MOCCPP_DLL_PUBLIC inline int32_t ctime(char* buffer, size_t buff_size, const time_t* timer);

}

}

#endif // MOCCPP_SYSTEM_CTIME_HPP
