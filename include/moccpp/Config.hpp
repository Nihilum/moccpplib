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
 * @file moccpp/Config.hpp
 *
 * @desc Macros used to control the library release environment.
 */

#ifndef MOCCPP_CONFIG_HPP
#define MOCCPP_CONFIG_HPP

/**
 * Dynamic-link library Import/Export accross different environments.
 */

#if defined _WIN32 || defined __CYGWIN__
  #ifdef MOCCPP_DLL
    #ifdef __GNUC__
      #define MOCCPP_DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define MOCCPP_DLL_PUBLIC __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define MOCCPP_DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define MOCCPP_DLL_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define MOCCPP_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define MOCCPP_DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define MOCCPP_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MOCCPP_DLL_PUBLIC
    #define MOCCPP_DLL_LOCAL
  #endif
#endif

/**
 * C++11 constexpr keyword support
 */

#ifdef __GNUC__
#  if __GNUC_PREREQ(4,7)
#    define MOCCPP_CONSTEXPR constexpr
#  else
#    define MOCCPP_CONSTEXPR
#  endif
#else
#    define MOCCPP_CONSTEXPR
#endif

#endif // MOCCPP_CONFIG_HPP