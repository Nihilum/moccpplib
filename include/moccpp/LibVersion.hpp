/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2015 Mateusz Kolodziejski
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

constexpr uint16_t get_library_version_major()
{
	return 0;
}

constexpr uint16_t get_library_version_minor()
{
	return 3;
}

constexpr uint16_t get_library_version_patch()
{
	return 2;
}

constexpr const char* get_library_version_string()
{
	return MOCCPP_MACRO_NUMBER_TO_STRING(0)
			"."
			MOCCPP_MACRO_NUMBER_TO_STRING(3)
			"."
			MOCCPP_MACRO_NUMBER_TO_STRING(2);
}

}

#endif // MOCCPP_LIB_VERSION_HPP
