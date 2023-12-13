#pragma once

#include <string>

namespace pr {

    template <typename iterator>

    size_t count (iterator begin, iterator end) {
        size_t sz = 0;
        while (begin != end) {
            ++begin;
            ++sz;
        }
        return sz;
    }

    template <typename iterator, typename T>

    size_t countIfEqual (iterator begin, iterator end, const T &value) {
        size_t sz = 0;
        while (begin != end) {
            if (*begin == value) {
                ++sz;
            }
            ++begin;
        }
        return sz;
    }
}