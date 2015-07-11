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
 * @file moccpp/Multithreading/synchronized.hpp
 *
 * @desc template class which allows to synchronize multithreaded access to the underlying data.
 */

#ifndef MOCCPP_MULTITHREADING_SYNCHRONIZED_HPP
#define MOCCPP_MULTITHREADING_SYNCHRONIZED_HPP

#include <moccpp/Config.hpp>

namespace moccpp
{

namespace Multithreading
{

template<typename T, class M, typename G>
class synchronized final
{
public:
    synchronized() : m_data{} {}
    synchronized(const T& data) : m_data(data) {}
    ~synchronized() {}

    synchronized(const synchronized&) = delete;
    synchronized(synchronized&&) = delete;

    synchronized& operator=(const synchronized&) = delete;

    synchronized& operator=(const T& rhs)
    {
        G lock(const_cast<M&>(m_mutex));
        m_data = rhs;
    }

    operator T() const
    {
        G lock(const_cast<M&>(m_mutex));
        return m_data;
    }

private:
    M m_mutex;
    T m_data;
};

}

}

#endif // MOCCPP_MULTITHREADING_SYNCHRONIZED_HPP
