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

/** @file matrix/uniform_matrix.h
 *  @author Brandon Pacewic
 *  This file contains the complete code for uniform_matrix.
 *  Code snippets can be moved into the basic_uniform_matrix class as needed.
 */

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class uniform_matrix_row {
   public:
    typedef Ty* pointer;
    typedef const Ty* const_pointer;
    typedef Ty& reference;
    typedef const Ty& const_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    /**
     *  @brief Constructs an empty uniform_matrix_row.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row() {}

    /**
     *  @brief Constructs an uniform_matrix_row with a given size.
     *  @param t_n Number of elements in the row.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row(size_type& t_n)
        : elements{std::make_unique<value_type[]>(t_n)}, length{t_n} {}

    /**
     *  @brief Constructs an uniform_matrix_row with a given size and value.
     *  @param t_n Number of elements in the row.
     *  @param t_value Value to initialize each element with.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row(size_type& t_n, const value_type& t_value)
        : elements{std::make_unique<value_type[]>(t_n)}, length{t_n} {
        std::fill(elements.get(), elements.get() + length, t_value);
    }

    /**
     *  @brief Returns the number of elements in the row.
     *  @return Number of elements in the row.
     */
    const size_type size() const { return length; }

    /**
     *  @brief Returns a pointer to the first element in the row.
     *  @return Pointer to the first element in the row.
     */
    pointer begin() noexcept { return &elements[0]; }

    /**
     *  @brief Returns a constant pointer to the first element in the row.
     *  @return Constant pointer to the first element in the row.
     */
    const const_pointer begin() const noexcept { return &elements[0]; }

    /**
     *  @brief Returns a pointer to the element one past the last element in
     *         the row.
     *  @return Pointer to the element one past the last element in the row.
     */
    pointer end() noexcept { return &elements[length]; }

    /**
     *  @brief Returns a constant pointer to the element one past the last
     *         element in the row.
     *  @return Constant pointer to the element one past the last element in
     *          the row.
     */
    const const_pointer end() const noexcept { return &elements[length]; }

    /**
     * @brief Returns a reference to the first element in the row.
     * @return reference to the first element in the row.
     */
    reference front() noexcept { return *begin(); }

    /**
     * @brief Returns a constant reference to the first element in the row.
     * @return constant reference to the first element in the row.
     */
    const_reference front() const noexcept { return *begin(); }

    /**
     * @brief Returns a reference to the last element in the row.
     * @return reference to the last element in the row.
     */
    reference back() noexcept { return *(end() - 1); }

    /**
     * @brief Returns a constant reference to the last element in the row.
     * @return constant reference to the last element in the row.
     */
    const_reference back() const noexcept { return *(end() - 1); }

    /**
     * @brief Returns a reference to the element at the given index.
     * @param index Index of the element to return.
     * @return reference to the element at the given index.
     */
    reference operator[](const size_type& index) { return elements[index]; }

    /**
     * @brief Returns a constant reference to the element at the given index.
     * @param index Index of the element to return.
     * @return constant reference to the element at the given index.
     */
    const_reference operator[](const size_type& index) const {
        return elements[index];
    }

   private:
    std::unique_ptr<value_type[]> elements;
    size_type length;
};

template <class Ty>
class uniform_matrix {
   public:
    typedef uniform_matrix_row<Ty> row_type;
    typedef row_type* row_pointer;
    typedef const row_type* const_row_pointer;
    typedef Ty* type_pointer;
    typedef const Ty* const_type_pointer;
    typedef row_type& row_reference;
    typedef const row_type& const_row_reference;
    typedef Ty& type_reference;
    typedef const Ty& const_type_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    /**
     *  @brief Constructs an uniform_matrix object with a given size
     *  @param t_n Number of rows and columns in the matrix.
     */
    uniform_matrix(size_type t_n)
        : rows{std::make_unique<row_type[]>(t_n)}, row_length{t_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length);
        }
    }

    /**
     *  @brief Constructs an uniform_matrix object with a given size and value
     *  @param t_n Number of rows and columns in the matrix.
     *  @param t_value Value to initialize each element with.
     */
    uniform_matrix(size_type t_n, const value_type& t_value)
        : rows{std::make_unique<row_type[]>(t_n)}, row_length{t_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length, t_value);
        }
    }

    /**
     *  @brief Constructs an uniform_matrix object from a linear
     *         initializer list.
     *  @param t_list Initializer list to construct the matrix from.
     */
    uniform_matrix(const std::initializer_list<value_type>& t_list)
        : rows{std::make_unique<row_type[]>(t_list.size())},
          row_length{t_list.size()} {
        size_type i = 0;

        for (row_reference row : rows) {
            for (type_reference cell : row) {
                cell = *(t_list.begin() + i), ++i;

                if (i >= t_list.size()) {
                    break;
                }
            }
        }
    }

   private:
    typedef std::initializer_list<std::initializer_list<value_type>>
        m_matrix_initializer_list;

   protected:
    /**
     *  @brief Tests if a two dimensional initializer list is a perfect square.
     *  @param list The two dimensional initializer list to test.
     *  @return true if the list is square, else false.
     */
    inline static const bool is_square(const m_matrix_initializer_list& list) {
        for (const std::initializer_list<value_type>& row : list) {
            if (row.size() != list.size()) {
                return false;
            }
        }

        return true;
    }

   public:
    /**
     *  @brief Constructs an uniform_matrix object from a two dimentional
     *         initializer list.
     *  @param list Initializer list to construct the matrix from.
     *  @throw std::invalid_argument if the initializer list is not a perfect
     *        square.
     */
    uniform_matrix(const m_matrix_initializer_list& list)
        : rows{std::make_unique<row_type[]>(list.size())},
          row_length{list.size()} {
        if (!is_square(list)) {
            throw std::invalid_argument(
                "Invalid uniform_matrix to be constructed from initializer "
                "list. Initializer list is not a perfect square.");
        }

        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                rows[row][cell] = list[row][cell];
            }
        }
    }

    /**
     *  @brief Constructs an uniform_matrix object from a range of values.
     *  @param t_n Number of rows and columns in the matrix.
     *  @param t_begin Iterator to the first element in the range.
     *  @param t_end Iterator to the element one past the last element in the
     *         range.
     *  @throw std::invalid_argument if the range is not a perfect square.
     */
    template <class InputIterator>
    uniform_matrix(size_type t_n, InputIterator t_first, InputIterator t_last)
        : rows{std::make_unique<row_type[]>(t_n)}, row_length{t_n} {
        for (row_reference row : rows) {
            for (type_reference cell : row) {
                cell = *t_first, ++t_last;

                if (t_first == t_last) {
                    break;
                }
            }
        }

        if (t_first != t_last) {
            throw std::invalid_argument(
                "Invalid uniform_matrix to be constructed from range. "
                "Range is not a perfect square.");
        }
    }

    /**
     *   @brief Returns the number of rows in the matrix.
     *   @return Number of rows in the matrix.
     *
     *  In @a uniform_matrix the number of rows will always be the same
     *  as the number of columns.
     */
    const size_type size() const { return row_length; }

    /**
     *  @brief Returns the total number of elements in the matrix.
     *  @tparam ReturnType Type of the return value.
     *  @return const ReturnType
     */
    template <typename ReturnType = size_type>
    const ReturnType total_size() const {
        return (ReturnType)row_length * row_length;
    }

    /**
     *  @brief Returns a pointer to the first element in the matrix.
     *  @return pointer to the first element in the matrix.
     */
    row_pointer begin() noexcept { return &rows[0]; }

    /**
     *  @brief Returns a constant pointer to the first element in the matrix.
     *  @return constant pointer to the first element in the matrix.
     */
    const const_row_pointer begin() const noexcept { return &rows[0]; }

    /**
     *  @brief Returns a pointer to the element one past the last element in
     *         the matrix.
     *  @return pointer to the element one past the last element in the matrix.
     */
    row_pointer end() noexcept { return &rows[row_length]; }

    /**
     *  @brief Returns a constant pointer to the element one past the last
     *         element in the matrix.
     *  @return constant pointer to the element one past the last element in
     *          the matrix.
     */
    const const_row_pointer end() const noexcept { return &rows[row_length]; }

    /**
     *  @brief Returns a reference to the first element in the matrix.
     *  @return reference to the first element in the matrix.
     */
    row_reference front() noexcept { return *begin(); }

    /**
     *  @brief Returns a constant reference to the first element in the matrix.
     *  @return constant reference to the first element in the matrix.
     */
    const_row_reference front() const noexcept { return *begin(); }

    /**
     *  @brief Returns a reference to the last element in the matrix.
     *  @return reference to the last element in the matrix.
     */
    row_reference back() noexcept { return *(end() - 1); }

    /**
     *  @brief Returns a constant reference to the last element in the matrix.
     *  @return constant reference to the last element in the matrix.
     */
    const_row_reference back() const noexcept { return *(end() - 1); }

    /**
     *  @brief Returns a reference to the element at the given index.
     *  @param index Index of the element to return.
     *  @return reference to the element at the given index.
     */
    row_reference operator[](const size_type& index) { return rows[index]; }

    /**
     *  @brief Returns a constant reference to the element at the given index.
     *  @param index Index of the element to return.
     *  @return constant reference to the element at the given index.
     */
    const_row_reference operator[](const size_type& index) const {
        return rows[index];
    }

    /**
     *  @brief Returns true of any element in the matrix satisfies the given
     *         predicate.
     *  @tparam UnaryPredicate The predicate to check for.
     *  @return true if any element in the matrix satisfies the given predicate
     *          else false.
     */
    template <class UnaryPredicate>
    bool any_of(UnaryPredicate predicate) const {
        for (const_row_reference& row : *this) {
            for (const_type_reference& cell : row) {
                if (predicate(cell)) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     *  @brief Returns true if all elements in the matrix satisfy the given
     *         predicate.
     *  @tparam UnaryPredicate The predicate to check for.
     *  @return true if all elements in the matrix satisfy the given predicate
     *          else false.
     */
    template <class UnaryPredicate>
    bool all_of(UnaryPredicate predicate) const {
        for (const_row_reference& row : *this) {
            for (const_type_reference& cell : row) {
                if (!predicate(cell)) {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     *  @brief Returns true if any element in the matrix does not satisfy the
     *         given predicate.
     *  @tparam UnaryPredicate The predicate to check for.
     *  @return true if all elements in the matrix do not satisfy the given
     *          predicate else false.
     */
    template <class UnaryPredicate>
    bool none_of(UnaryPredicate predicate) const {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (predicate(*jt)) {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     *  @brief Returns a count of the number of elements in the matrix that
     *         are equal to the given value.
     *  @tparam ReturnType The type of the return value
     *  @param value The value to count.
     *  @return const ReturnType
     */
    template <typename ReturnType = size_type>
    ReturnType count(const value_type& value) const {
        ReturnType count = 0;

        for (const_row_reference& row : *this) {
            for (const_type_reference& cell : row) {
                if (cell == value) {
                    ++count;
                }
            }
        }

        return count;
    }

    /**
     *  @brief Returns a count of the number of elements in the matrix that
     *         satisfy the given predicate.
     *  @tparam predicate The predicate to check for.
     *  @tparam ReturnType The type of the return value
     *  @return const ReturnType
     */
    template <class UnaryPredicate, typename ReturnType = size_type>
    ReturnType count(UnaryPredicate predicate) const {
        ReturnType count = 0;

        for (const_row_reference& row : *this) {
            for (const_type_reference& cell : row) {
                if (predicate(cell)) {
                    ++count;
                }
            }
        }

        return count;
    }

    /**
     *  @brief Fills the whole matrix with a given value.
     *  @param value The value to fill the matrix with.
     */
    void fill(const value_type& value) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                cell = value;
            }
        }
    }

    /**
     *  @brief Fills each element with a given value, only if the currently
     *         stored value satisfies the given predicate.
     *  @param value The value to fill the matrix with.
     *  @tparam UnaryPredicate The predicate to check for.
     */
    template <class UnaryPredicate>
    void fill(const value_type& value, UnaryPredicate predicate) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                if (predicate(cell)) {
                    cell = value;
                }
            }
        }
    }

    /**
     *  @brief Fills the whole matrix with a range of values.
     *  @tparam InputIterator The type of the input iterator.
     *  @param first The first element in the range.
     *  @param last The last element in the range.
     *  @throw std::invalid_argument if the range is not the same size as the
     *         matrix.
     */
    template <class InputIterator>
    void fill(InputIterator first, InputIterator last) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                cell = *(first), ++first;
            }
        }

        if (first != last) {
            throw std::invalid_argument(
                "InputIterator range is not of size "
                "uniform_matrix size.");
        }
    }

    /**
     *  @brief Fills the matrix with the given value, only if the position of
     *         the cell satisfies the given predicate.
     *  @param value The value to fill the matrix with.
     *  @tparam BinaryPredicate The predicate to check for.
     */
    template <class BinaryPredicate>
    void fill_if(const value_type& value, BinaryPredicate predicate) {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                if (predicate(row, cell)) {
                    rows[row][cell] = value;
                }
            }
        }
    }

    /**
     *  @brief Returns a pointer to the first element that is equal to the
     *         given target.
     *  @param target The target to search for.
     *  @return pointer to the first element that is equal to the given target,
     *          if no element exists return a pointer to an element one past the
     *          end of the pointer one past the last row of the matrix.
     */
    type_pointer find_if(const value_type& target) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = it->begin(); jt != it->end(); ++jt) {
                if (*jt == target) {
                    return jt;
                }
            }
        }

        return end()->end();
    }

    /**
     *  @brief Returns a pointer to the first element that satisfies the given
     *         predicate.
     *  @tparam UnaryPredicate The predicate to check for.
     *  @return pointer to the first element that satisfies the given predicate,
     *          if no element exists return a pointer to an element one past the
     *          end of the pointer one past the last row of the matrix.
     */
    template <class UnaryPredicate>
    type_pointer find_if(UnaryPredicate predicate) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (predicate(*jt)) {
                    return jt;
                }
            }
        }

        return end()->end();
    }

    /**
     *  @brief Applies the given function to each element in the matrix.
     *  @param function The function to apply.
     *
     *  There are two definitions of this function. One with a std::function
     *  of return type void and of one argument value_type reference, and
     *  one with a std::function of return type void and of three arguments
     *  value_type reference, size_type reference of the current row, and
     *  size_type reference of the current column.
     */
    void for_each(std::function<void(value_type&)> function) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                function(cell);
            }
        }
    }

    /**
     *  @brief Applies the given function to each element in the matrix.
     *  @param function The function to apply.
     *
     *  Second definition of the uniform_matrix::for_each function. Note that
     *  any other function that needs to be range restricted should use this
     *  template function as a starting point as it is the only way to loop
     *  through the matrix while retrieving the current cell index of the
     *  element.
     */
    void for_each(
        std::function<void(value_type&, size_type&, size_type&)> function) {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                function(rows[row][cell], row, cell);
            }
        }
    }

    /**
     *  @brief Assigns each element in the matrix a series of increasing values.
     *  @param start The value to start at.
     *
     *  The base increment is one, there is no way to change this. If this
     *  functionality is needed, use a modified version of the
     *  @a uniform_matrix::for_each function insted.
     */
    void iota(value_type start) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                cell = start, ++start;
            }
        }
    }

   protected:
    /**
     *  @brief Struct to convert the matrix into a basic linear container.
     *
     *  TODO: Need to account for an overflow of the size_type variable.
     *
     *  This container should not be used outside of this class. Once
     *  constructed the contents cannot be modified.
     */
    template <class MTy>
    struct m_list_matrix_elements {
        typedef const MTy* const_pointer;
        typedef const MTy& const_reference;
        typedef MTy value_type;
        typedef std::size_t size_type;

        /**
         *  @brief Constructor.
         *  @param t_matrix The matrix to convert.
         */
        m_list_matrix_elements(const uniform_matrix& t_matrix)
            : m_linear_size{t_matrix.total_size()},
              m_linear_data{std::make_unique<value_type[]>(m_linear_size)} {
            size_type linear_index = 0;

            for (const_row_reference& row : t_matrix) {
                for (const_reference& cell : row) {
                    m_linear_data[linear_index] = cell, ++linear_index;
                }
            }
        }

        /**
         *  @brief Returns a constant pointer to the first element in the
         *         container.
         *  @return constant pointer to the first element in the container.
         */
        const const_pointer begin() const { return m_linear_data.get(); }

        /**
         *  @brief Returns a constant pointer to the element one past the end
         *         of the container.
         *  @return constant pointer to the element one past the end of the
         *          container.
         */
        const const_pointer end() const {
            return m_linear_data.get() + m_linear_size;
        }

        /**
         *  @brief Returns a reference to the element at the given index.
         *  @param index The index of the element to return.
         *  @return reference to the element at the given index.
         */
        const_reference operator[](const size_type& index) const {
            return m_linear_data[index];
        }

        std::unique_ptr<value_type[]> m_linear_data;
        size_type m_linear_size;
    };

    typedef m_list_matrix_elements<value_type> list_matrix_elements;

   public:
    /**
     *  @brief Tests if the matrix is sorted or not.
     *  @return true if the matrix is sorted, false otherwise.
     *
     *  Constructs a temporary linear container of all the matrix elements and
     *  tests against that.
     *
     *  Time complexity is O(n^2).
     */
    template <class BinaryPredicate = std::less<value_type>>
    bool is_sorted(BinaryPredicate predicate) const {
        list_matrix_elements linear_matrix{*this};
        return std::is_sorted(linear_matrix.begin(), linear_matrix.end(),
                              predicate);
    }

    /**
     *  @brief Outputs the matrix to the std::cout stream.
     *  @param space Determines if there should be a space between each element.
     */
    const void output(const bool& space = true) const {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < row_length - 1) {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }

    /**
     *  @brief Outputs the matrix to the specified stream.
     *  @param os The stream to output to.
     */
    const void output(std::ostream& os) const {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                os << rows[row][cell];

                if (cell < row_length - 1) {
                    os << ' ';
                }
            }

            os << '\n';
        }
    }

    /**
     *  @brief Tests if each row in the matrix is sorted.
     *  @tparam BinaryPredicate The predicate to test against.
     *  @return true if each row is sorted, false otherwise.
     *
     *  This function only tests each row individually. It does not test the
     *  matrix as a whole.
     */
    template <class BinaryPredicate = std::less<value_type>>
    bool rows_sorted(BinaryPredicate predicate) const {
        for (const_row_reference& row : *this) {
            if (!std::is_sorted(row.begin(), row.end(), predicate)) {
                return false;
            }
        }

        return true;
    }

    /**
     *  @brief Sorts the whole matrix.
     *  @tparam BinaryPredicate The predicate to test against.
     *
     *  This function sorts the whole matrix. It must first create a linear
     *  container of all the matrix elements to sort them with the lowest
     *  complexity.
     */
    template <class BinaryPredicate = std::less<value_type>>
    void sort(BinaryPredicate predicate) {
        list_matrix_elements linear_matrix{*this};
        std::sort(linear_matrix.begin(), linear_matrix.end(), predicate);
        this->fill(linear_matrix.begin(), linear_matrix.end());
    }

    /**
     *  @brief Sorts each row of the matrix individually.
     *  @tparam BinaryPredicate The predicate to test against.
     *
     *  This function does not sort the whole matrix. Only each
     *  row individually.
     */
    template <class BinaryPredicate = std::less<value_type>>
    void sort_rows(BinaryPredicate predicate) {
        for (row_reference& row : *this) {
            std::sort(row.begin(), row.end(), predicate);
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    size_type row_length;
};