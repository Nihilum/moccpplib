# The MIT License (MIT)
#
# Copyright (c) 2013-2015 Mateusz Kolodziejski
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

set(TEST_NAME moccpplib_tests)

find_package(moctest REQUIRED)

# Prepare project

# Compile flags
if(WIN32 AND NOT MINGW)
  # Disable dll-external warnings for Visual Studio; [/GS-] disable buffer overflow security checks (optimization)
  set(PROGRAM_COMPILE_FLAGS ${PROGRAM_COMPILE_FLAGS} "/wd4251 /wd4275 /wd4351 /GS-")
else()
  # Activate C++11 mode for GNU/GCC
  set(PROGRAM_COMPILE_FLAGS ${PROGRAM_COMPILE_FLAGS} "-std=c++11")
endif()

# Source files and includes
file(GLOB_RECURSE TEST_SRCS ${CMAKE_SOURCE_DIR}/tests/ ${CMAKE_SOURCE_DIR}/tests/*.cpp ${CMAKE_SOURCE_DIR}/tests/*.hpp)

# Link directories
link_directories(${Boost_LIBRARY_DIR})

# Include dirs
include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  ${CPPUNIT_INCLUDE_DIR}/
  ${Boost_INCLUDE_DIR}
  ${MOCTEST_INCLUDE_DIR}
)

# Compilation definitions
add_definitions( ${Boost_LIB_DIAGNOSTIC_DEFINITIONS} ) # http://www.cmake.org/cmake/help/v3.2/module/FindBoost.html
add_definitions( -DBOOST_ALL_DYN_LINK ) # use boost dlls

if (MINGW)
  add_definitions(-std=c++11)
endif()

# Properly setup RPATH (Linux)
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Specify that this project will build a program
add_executable(${TEST_NAME} ${TEST_SRCS})

set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS
  "${PROGRAM_COMPILE_FLAGS}"
)

# Link libraries
target_link_libraries(${TEST_NAME}
  debug ${CPPUNIT_DEBUG_LIBRARY}
  optimized ${CPPUNIT_LIBRARY}
  debug ${Boost_SYSTEM_LIBRARY_DEBUG}
  optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
  debug ${MOCTEST_DEBUG_LIBRARY}
  optimized ${MOCTEST_LIBRARY}
  ${MOCCPP_LIB}
)

install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
install(FILES "${MOCTEST_LIBRARY}" DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  install(FILES "${MOCTEST_DEBUG_LIBRARY}" DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
endif()
