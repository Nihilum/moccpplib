# The MIT License (MIT)
#
# Copyright (c) 2013 Mateusz Kolodziejski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

set(TEST_NAME moccpp_test_system)
set(PERF_NAME moccpp_perf_system)

set(TEST_SRCS
  TestSystem.hpp
  TestSystem.cpp
  )

set(PERF_SRCS
  PerfSystem.cpp
  )

add_executable(${TEST_NAME} ${TEST_SRCS})
add_executable(${PERF_NAME} ${PERF_SRCS})

target_link_libraries(${TEST_NAME} ${MOCCPP_LIB} ${CPPUNIT_LIB})
target_link_libraries(${PERF_NAME} ${MOCCPP_LIB})

install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
install(TARGETS ${PERF_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
