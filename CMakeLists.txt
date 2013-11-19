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

cmake_minimum_required(VERSION 2.8)
project(moccpplib)
set(LIBRARY_NAME moccpp)

add_definitions(
  -DMOCCPP_LIBRARY_VERSION_MAJOR=0
  -DMOCCPP_LIBRARY_VERSION_MINOR=1
  -DMOCCPP_LIBRARY_VERSION_PATCH=5
)

if(WIN32)
  # Disable dll-external warnings for Visual Studio; [/GS-] disable buffer overflow security checks (optimization)
  set(LIBRARY_COMPILE_FLAGS ${LIBRARY_COMPILE_FLAGS} "-DMOCCPP_DLL=1 /wd4251 /wd4275 /GS-")
else()
  # Activate C++11 mode for GNU/GCC
  set(LIBRARY_COMPILE_FLAGS ${LIBRARY_COMPILE_FLAGS} "-std=c++11 -DMOCCPP_DLL=1")
endif()

file(GLOB_RECURSE LIBRARY_SRCS ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/include/*.hpp)

link_directories(${BOOST_LIBS})

include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  ${CPPUNIT_INCLUDES}
  ${BOOST_INCLUDES}
)

add_definitions( ${Boost_LIB_DIAGNOSTIC_DEFINITIONS} )
add_definitions( -DBOOST_ALL_DYN_LINK )
add_definitions( -DBOOST_FILESYSTEM_NO_DEPRECATED )

add_library(${LIBRARY_NAME} SHARED
  ${LIBRARY_SRCS}
)

set(MOCCPP_LIB ${LIBRARY_NAME})

add_subdirectory(tests)

install(TARGETS ${LIBRARY_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(TARGETS ${LIBRARY_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/tests
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# Install Boost libraries and moccpp library if on Windows
if (DEFINED WIN32)
  add_definitions( -D_WIN32_WINNT=0x0501 )

  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_chrono-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_date_time-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_filesystem-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_log_setup-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_log-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_program_options-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_regex-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_system-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_thread-.*")
  set(MOCCPP_BOOST_LIBS_INUSE ${MOCCPP_BOOST_LIBS_INUSE} "boost_timer-.*")


  file(TO_CMAKE_PATH ${BOOST_LIBS} MOCCPP_BOOST_LIBS)
  file(GLOB_RECURSE MOCCPP_BOOST_LIBS_INSTALL ${MOCCPP_BOOST_LIBS}/ ${MOCCPP_BOOST_LIBS}/*.dll)

  foreach(fName ${MOCCPP_BOOST_LIBS_INSTALL})
    foreach(libName ${MOCCPP_BOOST_LIBS_INUSE})
      if(${fName} MATCHES ${libName})
        install(FILES "${fName}" DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
      endif()
    endforeach()
  endforeach()
endif()


set_target_properties(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS
  "${LIBRARY_COMPILE_FLAGS}"
)
