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

#include <limits>
#include <vector>

template <class AccumulationType, class BaseValueType = int>
class segment {
   public:
    using value_type = BaseValueType;
    using accumulation_type = AccumulationType;

    segment(value_type maximum_ = std::numeric_limits<value_type>::lowest(),
            accumulation_type sum_ = 0, value_type first_ = 0,
            value_type last = 0)
        : maximum(maximum_), sum(sum_), first(first_), last(last) {}

    const bool empty() const { return first == last; }

    void join(const segment& other) {
        if (other.empty()) {
            return;
        }

        if (empty()) {
            *this = other;
        } else {
            maximum = std::max(maximum, other.maximum);
            sum += other.sum;
            last = other.last;
        }
    }

    void join(const segment& a, segment& b) {
        *this = a;
        join(b);
    }

   private:
    value_type maximum;
    accumulation_type sum;
    value_type first, last;
};

template <class AccumulationType, class BaseValueType = int>
class basic_seg_tree {
   public:
    using value_type = segment<AccumulationType, BaseValueType>;
    using size_type = std::size_t;

    basic_seg_tree(size_type n = -1) {
        if (n >= 0) {
            init(n);
        }
    }

    void init(size_type n) {
        if (n >= 0) {
            tree_size = 1;

            while (tree_size < n) {
                tree_size <<= 1;
            }
        }

        tree_segments.assign(tree_size * 2, value_type());
    }

    void build(const std::vector<value_type>& inital) {
        size_type n = inital.size();
        init(n);

        for (size_type i = 0; i < n; ++i) {
            tree_segments[tree_size + i] = inital[i];
        }

        for (size_type position = tree_size - 1; position > 0; --position) {
            tree_segments[position].join(tree_segments[2 * position],
                                         tree_segments[2 * position + 1]);
        }
    }

    value_type query(size_type left, size_type right) {
        size_type left_index = left + tree_size;
        size_type right_index = right + tree_size;

        value_type answer;

        for (; left_index < right_index; left_index >>= 1, right_index >>= 1) {
            if (left_index & 1) {
                answer.join(tree_segments[left_index++]);
            }

            if (right_index & 1) {
                --right_index;
                answer.join(tree_segments[right_index]);
            }
        }

        return answer;
    }

   private:
    size_type tree_size;
    size_type tree_height;
    std::vector<value_type> tree_segments;
};