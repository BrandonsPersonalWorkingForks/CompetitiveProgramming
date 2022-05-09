/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>

template <typename _Tp>
class _uniform_matrix_row {
   public:
    typedef _Tp* iterator;
    typedef const _Tp* const_iterator;

    _uniform_matrix_row() {}

    _uniform_matrix_row(std::size_t _sz)
        : elements{std::make_unique<_Tp[]>(_sz)}, sz{_sz} {}

    _uniform_matrix_row(std::size_t _sz, const _Tp& _element)
        : elements{std::make_unique<_Tp[]>(_sz)}, sz{_sz} {
        std::fill(elements.get(), elements.get() + sz, _element);
    }

    const std::size_t size() const { return sz; }

    iterator begin() { return &elements[0]; }
    const const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[sz]; }
    const const_iterator end() const { return &elements[sz]; }

    _Tp& operator[](const int& i) { return elements[i]; }

   private:
    std::unique_ptr<_Tp[]> elements;
    std::size_t sz;
};

template <typename _Tp>
class uniform_matrix {
   public:
    typedef _uniform_matrix_row<_Tp> row_type;
    typedef row_type* iterator;
    typedef const row_type* const_iterator;

    uniform_matrix(std::size_t _sz)
        : rows{std::make_unique<row_type[]>(_sz)}, sz{_sz} {
        for (std::size_t i = 0; i < sz; ++i) {
            rows[i] = _uniform_matrix_row<_Tp>(sz);
        }
    }

    uniform_matrix(std::size_t _sz, const _Tp& _element)
        : rows{std::make_unique<row_type[]>(_sz)}, sz{_sz} {
        for (std::size_t i = 0; i < sz; ++i) {
            rows[i] = row_type(sz, _element);
        }
    }

    const std::size_t size() const { return sz; }

    iterator begin() { return &rows[0]; }
    const const_iterator begin() const { return &rows[0]; }

    iterator end() { return &rows[sz]; }
    const const_iterator end() const { return &rows[sz]; }

    row_type& operator[](const int& i) const { return rows[i]; }

    void for_each(std::function<void(_Tp&)> lambda) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                lambda(rows[row][cell]);
            }
        }
    }

    void for_each(
        std::function<void(_Tp&, std::size_t&, std::size_t&)> lambda) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                lambda(rows[row][cell], row, cell);
            }
        }
    }

    void iota(_Tp start,
              std::unordered_set<_Tp> avoid = {static_cast<_Tp>(0)}) {
        this->for_each([&](_Tp& element, std::size_t&, std::size_t&) {
            while (avoid.find(start) != avoid.end()) {
                ++start;
            }

            element = start++;
        });
    }

    void sort_rows(std::function<bool(_Tp&, _Tp&)> lambda = [](_Tp& a, _Tp& b) {
        return a < b;
    }) {
        for (std::size_t row = 0; row < sz; ++row) {
            std::sort(rows[row].begin(), rows[row].end(), lambda);
        }
    }

    const void output(const bool& space = false) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < sz - 1) {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    std::size_t sz;
};