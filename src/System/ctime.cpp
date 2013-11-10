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
 * @file moccpp/System/ctime.cpp
 *
 * @desc Thread-safe gmtime, asctime, ctime C standard library functions compatible
 *  with all operating systems.
 */

#include <ctime>
#include <cerrno>
#include <cstring>

#include <moccpp/System/ctime.hpp>

namespace moccpp
{

namespace System
{

int32_t gmtime(const time_t* timer, struct tm* result)
{
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    if (!gmtime_r(timer, result)) {
        return errno;
    }
  #else
    errno_t err_num = gmtime_s(result, timer);
    if (err_num != 0) {
        return err_num;
    }
  #endif
#else
  #ifdef __GNUC__
    if (!gmtime_r(timer, result)) {
        return errno;
    }
  #else
    struct tm* loc_result = gmtime(timer);
    if (loc_result == nullptr) {
        return errno;
    } else {
        memcpy(result, loc_result, sizeof(tm));
    }
  #endif
#endif
    return 0;
}

int32_t asctime(char* buffer, size_t buff_size, const struct tm *_tm)
{
    if (buff_size < 26) { // 26: see `man asctime_r`
        return EINVAL;
    }

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    if (!asctime_r(_tm, buffer)) {
        return errno;
    }
  #else
    errno_t err_num = asctime_s(buffer, buff_size, _tm);
    if (err_num != 0) {
        return err_num;
    }
  #endif
#else
  #ifdef __GNUC__
    if (!asctime_r(_tm, buffer)) {
        return errno;
    }
  #else
    char* loc_buffer = asctime(_tm);
    if (loc_buffer == nullptr) {
        return errno;
    } else {
        memcpy(buffer, loc_buffer, strlen(loc_buffer));
    }
  #endif
#endif
    return 0;
}

int32_t ctime(char* buffer, size_t buff_size, const time_t* timer)
{
  if (buff_size < 26) { // 26: see `man ctime_r`
    return EINVAL;
  }

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    if (!ctime_r(timer, buffer)) {
      return errno;
    }
  #else
    errno_t err_num = ctime_s(buffer, buff_size, timer);
    if (err_num != 0) {
      return err_num;
    }
  #endif
#else
  #ifdef __GNUC__
    if (!ctime_r(timer, buffer)) {
      return errno;
    }
  #else
    char* loc_buffer = ctime(timer);
    if (loc_buffer == nullptr) {
      return errno;
    } else {
      memcpy(buffer, loc_buffer, strlen(loc_buffer));
    }
  #endif
#endif
    return 0;
}

}

}
