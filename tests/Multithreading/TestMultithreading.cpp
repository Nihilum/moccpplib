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
 * @file tests/Multithreading/TestMultithreading.hpp
 *
 * @desc Tests for all multithreading related classes and functions.
 */

#include <chrono>
#include <mutex>
#include <thread>
#include <cstdint>

#include <moccpp/Multithreading/synchronized.hpp>

#include "TestMultithreading.hpp"

void TestMultithreading::setUp()
{
}

void TestMultithreading::tearDown()
{
}

struct TestStruct
{
    moccpp::Multithreading::synchronized<uint32_t, std::mutex, std::lock_guard<std::mutex>> number;
    moccpp::Multithreading::synchronized<bool, std::mutex, std::lock_guard<std::mutex>> run;

    uint32_t get_number()
    {
        return number;
    }

    void set_number(uint32_t num)
    {
        number = num;
    }

    bool isRunning()
    {
        return run;
    }

    void set_running(bool running)
    {
        run = running;
    }
};

void TestMultithreading::test_synchronized()
{
    const uint32_t expected = 5;

    TestStruct testStruct;
    testStruct.number = 5;
    uint32_t actual = testStruct.number;
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void run_thread(TestStruct& testStruct, uint32_t& count)
{
    while (testStruct.isRunning())
    {
        ++count;
    }
}

void TestMultithreading::test_synchronized_multithreading()
{
    TestStruct testStruct{};
    testStruct.set_running(true);

    uint32_t count = 0;

    std::thread t1(run_thread, std::ref(testStruct), std::ref(count));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    testStruct.set_running(false);

    t1.join();

    CPPUNIT_ASSERT(count > 0);
}
