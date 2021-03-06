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

function(MSource_GetDepsFile MSOURCE_DEPS_FILE MSOURCE_NUM_OF_DEPS)
  file(STRINGS deps.txt TMP_DEPS_FILE)
  list(LENGTH TMP_DEPS_FILE TMP_NUM_OF_DEPS)

  set(${MSOURCE_DEPS_FILE} ${TMP_DEPS_FILE} PARENT_SCOPE)
  set(${MSOURCE_NUM_OF_DEPS} ${TMP_NUM_OF_DEPS} PARENT_SCOPE)

  unset(TMP_DEPS_FILE)
  unset(TMP_NUM_OF_DEPS)
endfunction()
