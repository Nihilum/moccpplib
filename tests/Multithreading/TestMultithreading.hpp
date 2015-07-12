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

#ifndef MOCCPP_TESTS_MULTITHREADING_TEST_MULTITHREADING_HPP
#define MOCCPP_TESTS_MULTITHREADING_TEST_MULTITHREADING_HPP

#include <moctest/moctest.hpp>

class TestMultithreading : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(TestMultithreading);
    CPPUNIT_TEST(test_synchronized);
    CPPUNIT_TEST(test_synchronized_multithreading);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void test_synchronized();
    void test_synchronized_multithreading();
};

#endif // MOCCPP_TESTS_MULTITHREADING_TEST_MULTITHREADING_HPP
