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
 * @file tests/System/PerfSystem.cpp
 *
 * @desc Performance tests of operating system related functions.
 */

#include <ctime>
#include <chrono>
#include <cmath>
#include <limits>
#include <thread>
#include <cstdint>
#include <iostream>

#include <boost/timer/timer.hpp>

#include <moccpp/System/ctime.hpp>

using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;

void display_stats(const cpu_timer& timer, const nanosecond_type& expected_time)
{
    cpu_times const elapsed_times(timer.elapsed());
    nanosecond_type const elapsed(elapsed_times.wall);

    if (elapsed > expected_time) {
        std::cout << "WARN  PERFORMANCE DECREASE, expected_time: " << expected_time << "(ns) vs elapsed_time: " << elapsed << " (ns)\n";
    }

    std::cout << timer.format();
}

void perf_test_gmtime()
{    
    nanosecond_type const expected_time(1000000); // 1 millisecond
    std::cout << "START perf_test_gmtime()\n";

    time_t rawtime;
    struct tm time_res;
    struct tm* timeinfo = &time_res;
    time(&rawtime);

    cpu_timer timer;
    
    uint16_t sum = 0;
    moccpp::System::gmtime(&rawtime, timeinfo);
    sum += timeinfo->tm_sec;

    timer.stop();
    display_stats(timer, expected_time);
    std::cout << "END   perf_test_gmtime()\n" << std::endl;
}

void perf_test_asctime()
{
    nanosecond_type const expected_time(1000000); // 1 millisecond
    std::cout << "START perf_test_asctime()\n";

    const size_t buff_size = 26;
    char buffer[buff_size];
    buffer[0] = '\0';

    time_t rawtime;
    struct tm time_res;
    struct tm* timeinfo = &time_res;
    time(&rawtime);

    moccpp::System::gmtime(&rawtime, timeinfo);

    cpu_timer timer;

    volatile bool test = false;
    moccpp::System::asctime(buffer, buff_size, timeinfo);
    test = (buffer[0] == '\0') ? false : true;

    timer.stop();
    display_stats(timer, expected_time);
    std::cout << "END   perf_test_asctime()\n" << std::endl;
}

void perf_test_ctime()
{
    nanosecond_type const expected_time(3000000); // 3 milliseconds
    std::cout << "START perf_test_ctime()\n";

    const size_t buff_size = 26;
    char buffer[buff_size];
    buffer[0] = '\0';

    time_t rawtime;
    time(&rawtime);

    cpu_timer timer;

    volatile bool test = false;
    moccpp::System::ctime(buffer, buff_size, &rawtime);
    test = (buffer[0] == '\0') ? false : true;

    timer.stop();
    display_stats(timer, expected_time);
    std::cout << "END   perf_test_ctime()\n" << std::endl;
}

int main(int argc, char* argv[])
{
    perf_test_gmtime();
    perf_test_asctime();
    perf_test_ctime();
}
