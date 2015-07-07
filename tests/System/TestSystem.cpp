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
 * @file tests/System/TestSystem.hpp
 *
 * @desc Tests checking whether operating system related functions provide proper
 *  results.
 */

#include <ctime>
#include <memory>
#include <cstdint>

#include <boost/lexical_cast.hpp>

#include <moccpp/Config.hpp>
#include <moccpp/System/ctime.hpp>
#include <moccpp/System/cstdio.hpp>

#include "TestSystem.hpp"

void TestSystem::setUp()
{
}

void TestSystem::tearDown()
{
}

void TestSystem::test_gmtime()
{
    time_t rawtime;
    struct tm time_res;
    struct tm* given_time = &time_res;
    struct tm* expected_time;

    time(&rawtime);

    moccpp::System::gmtime(&rawtime, given_time);

#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( disable : 4996 )
  #endif
#endif
    expected_time = gmtime(&rawtime);
#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( default : 4996 )
  #endif
#endif

    if ((given_time->tm_sec == -1) ||
          (given_time->tm_min == -1) ||
          (given_time->tm_hour == -1) ||
          (given_time->tm_mday == -1) ||
          (given_time->tm_mon == -1) ||
          (given_time->tm_year == -1) ||
          (given_time->tm_wday == -1) ||
          (given_time->tm_yday == -1)
          // tm_isdst does not have to be checked, since it can be equal -1
       ) {
        CPPUNIT_ASSERT_EQUAL(true, false);
    }

    CPPUNIT_ASSERT_EQUAL(expected_time->tm_sec, given_time->tm_sec);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_min, given_time->tm_min);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_hour, given_time->tm_hour);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_mday, given_time->tm_mday);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_mon, given_time->tm_mon);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_year, given_time->tm_year);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_wday, given_time->tm_wday);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_yday, given_time->tm_yday);
    CPPUNIT_ASSERT_EQUAL(expected_time->tm_isdst, given_time->tm_isdst);
}

void TestSystem::test_asctime()
{
    const size_t buff_size = 26;
    char buffer[buff_size];

    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);

#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( disable : 4996 )
  #endif
#endif
    timeinfo = gmtime(&rawtime);
#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( default : 4996 )
  #endif
#endif

    moccpp::System::asctime(buffer, buff_size, timeinfo);

#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( disable : 4996 )
  #endif
#endif
    char* expected_buffer = asctime(timeinfo);
#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( default : 4996 )
  #endif
#endif

    CPPUNIT_ASSERT_EQUAL(std::string(expected_buffer), std::string(buffer));
}

void TestSystem::test_ctime()
{
    const size_t buff_size = 26;
    char buffer[buff_size];

    time_t rawtime;
    time(&rawtime);

    moccpp::System::ctime(buffer, buff_size, &rawtime);

#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( disable : 4996 )
  #endif
#endif
    char* expected_buffer = ctime(&rawtime);
#if defined _WIN32
  #ifndef __GNUC__
    #pragma warning( default : 4996 )
  #endif
#endif

    CPPUNIT_ASSERT_EQUAL(std::string(expected_buffer), std::string(buffer));
}

void log_inputter(bool small_buffer, const char* format, va_list args)
{
    const uint16_t max_standard_length = 256;
    char buffer[max_standard_length];
    char* pBuffer = buffer;

    // try with a small buffer first (which should be very quick)
    int32_t ret = moccpp::System::vsnprintf(pBuffer, max_standard_length, max_standard_length - 1, format, args);

    CPPUNIT_ASSERT(ret >= 0);

    if (small_buffer) {
        CPPUNIT_ASSERT(ret < max_standard_length);
        return;
    }

    CPPUNIT_ASSERT(ret >= max_standard_length);

    // small buffer has failed, because the data is too large - alloc a new buffer with suggested size (ret)
    std::shared_ptr<char> buff_to_write(new char[ret + 1], std::default_delete<char[]>());
    pBuffer = &(*buff_to_write);
    pBuffer[ret] = '\0'; // NOTE: this is actually ok, we are not exceeding here, since we've done new char[ret + 1], so we have that 1 extra character

    int32_t final_ret = moccpp::System::vsnprintf(pBuffer, ret + 1, ret, format, args);

    CPPUNIT_ASSERT(final_ret >= 0);
    CPPUNIT_ASSERT(final_ret < (ret + 1));
}

void small_logger(bool small_buffer, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    log_inputter(small_buffer, format, args);
    va_end(args);
}

void TestSystem::test_vsnprintf()
{
    small_logger(true, "abc %d", 12);
    small_logger(true, "def %d", 24);

    std::string large_buffer;

    for (uint16_t i = 0; i < 256; ++i) {
        large_buffer += boost::lexical_cast<std::string>(i);
    }

    small_logger(false, "%s", large_buffer.c_str());
}
