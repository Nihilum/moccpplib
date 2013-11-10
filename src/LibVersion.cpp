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
 * @file moccpp/LibVersion.cpp
 *
 * @desc MOCCPP_CONSTEXPR functions providing information about library version.
 */

#include <moccpp/LibVersion.hpp>

namespace moccpp
{

uint16_t get_library_version_major()
{
	return MOCCPP_LIBRARY_VERSION_MAJOR;
}

uint16_t get_library_version_minor()
{
	return MOCCPP_LIBRARY_VERSION_MINOR;
}

uint16_t get_library_version_patch()
{
	return MOCCPP_LIBRARY_VERSION_PATCH;
}

/**
 * "48" is a position of '0' digit in the ASCII table (see http://www.asciitable.com/).
 * Adding 48 to any number out there will provide char representation of an int value.
 */
static char version[6] = {
	static_cast<char>(MOCCPP_LIBRARY_VERSION_MAJOR + 48),
	'.',
	static_cast<char>(MOCCPP_LIBRARY_VERSION_MINOR + 48),
	'.',
	static_cast<char>(MOCCPP_LIBRARY_VERSION_PATCH + 48),
	'\0'
};

const char* get_library_version_string()
{
	return version;
}

}
