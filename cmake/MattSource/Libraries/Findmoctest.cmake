# The MIT License (MIT)
#
# Copyright (c) 2014-2015 Mateusz Kolodziejski
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
#
# Find the moctest includes and library
#
# This module defines
# MOCTEST_INCLUDE_DIR, where to find FindTest.hpp, etc.
# MOCTEST_LIBRARIES, the libraries to link against to use moctest.
# MOCTEST_FOUND, If false, do not try to use moctest.

# also defined, but not for general use are
# MOCTEST_LIBRARY, where to find the moctest library.
# MOCTEST_DEBUG_LIBRARY, where to find the moctest library in debug mode.


file(GLOB DEPS_DIR ${MOCTEST_ROOT})

foreach(DEP ${DEPS_DIR})
  if(DEP MATCHES "moctest.*debug")
    set(MOCTEST_PATH_DEBUG ${DEP})
  endif()
  if(DEP MATCHES "moctest.*release")
    set(MOCTEST_PATH_RELEASE ${DEP})
  endif()
endforeach()

FIND_PATH(MOCTEST_INCLUDE_DIR moctest/FindTest.hpp
  ${MOCTEST_PATH_RELEASE}/include
  /usr/local/include
  /usr/include
)


FIND_LIBRARY(MOCTEST_LIBRARY moctest
             ${MOCTEST_PATH_RELEASE}/lib
             ${MOCTEST_INCLUDE_DIR}/../lib
             /usr/local/lib
             /usr/lib)
FIND_LIBRARY(MOCTEST_DEBUG_LIBRARY moctest
             ${MOCTEST_PATH_DEBUG}/lib
             ${MOCTEST_INCLUDE_DIR}/../lib
             /usr/local/lib
             /usr/lib)

IF(MOCTEST_INCLUDE_DIR)
  IF(MOCTEST_LIBRARY)
    SET(MOCTEST_FOUND "YES")
    SET(MOCTEST_LIBRARIES ${MOCTEST_LIBRARY} ${CMAKE_DL_LIBS})
    SET(MOCTEST_DEBUG_LIBRARIES ${MOCTEST_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
  ENDIF(MOCTEST_LIBRARY)
ENDIF(MOCTEST_INCLUDE_DIR)

if(moctest_FIND_REQUIRED AND NOT MOCTEST_FOUND)
  message(SEND_ERROR "Unable to find the requested moctest libraries. Make sure they are downloaded.")
endif()
