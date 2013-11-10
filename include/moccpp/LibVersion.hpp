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
 * @file moccpp/LibVersion.hpp
 *
 * @desc MOCCPP_CONSTEXPR functions providing information about library version.
 */

#ifndef MOCCPP_LIB_VERSION_HPP
#define MOCCPP_LIB_VERSION_HPP

#include <cstdint>

#include <moccpp/Config.hpp>

namespace moccpp
{

MOCCPP_DLL_PUBLIC MOCCPP_CONSTEXPR uint16_t get_library_version_major();
MOCCPP_DLL_PUBLIC MOCCPP_CONSTEXPR uint16_t get_library_version_minor();
MOCCPP_DLL_PUBLIC MOCCPP_CONSTEXPR uint16_t get_library_version_patch();
MOCCPP_DLL_PUBLIC MOCCPP_CONSTEXPR const char* get_library_version_string();

}

#endif // MOCCPP_LIB_VERSION_HPP
