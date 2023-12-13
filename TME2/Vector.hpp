#pragma once

#include <ostream>
#include <cstddef>

namespace pr {

    template <typename T>

    class Vector {
        size_t alloc_sz;
        T *tab;
        size_t sz;

        void ensure_capacity(size_t n) {
            if (n >= alloc_sz) {
                alloc_sz = std::max(alloc_sz * 2,n);
                T *new_tab = new T[alloc_sz];
                for (size_t i = 0; i < sz; ++i) {
                    new_tab[i] = tab[i];
                }
                delete[] tab;
                tab = new_tab;
            }
        }
    }


}