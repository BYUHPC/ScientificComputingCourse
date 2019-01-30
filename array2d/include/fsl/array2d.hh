#ifndef FSL_ARRAY2D_HH
#define FSL_ARRAY2D_HH

#include <cassert>
#include <cstddef>
#include <utility>
#include <valarray>

namespace fsl {

template <class T> class array2d {
public:
  using size_type = std::size_t;

  array2d(size_type rows, size_type columns)
      : columns_{columns}, storage_(rows * columns) {
    // in debug builds these checks will happen
    // in release builds these checks will not happen
    assert(rows > 0);
    assert(columns > 0);
  }

  array2d(array2d const &b) = default;
  array2d(array2d &&b) noexcept = default;
  ~array2d() = default;

  size_type rows() const {
    // How do we calculate the number of rows since we did not store it?
    return 0;
  }

  size_type columns() const { return columns_; }

  /* Return row `n` from the storage, which should support operator[].
   * Changes made to the return value should be reflected in this object.
   *
   * Example:
   *   array2d<float> a{1,2};
   *   auto first = a[0];
   *   first[0] = 0;
   *   first[1] = 1;
   *   assert(a[0][0] == 1);
   *   assert(a[0][1] == 1);
   */
  void operator[](size_type n) {
    /* How do we return a single row? How big is a single row?
     * What should the return type of this member function be?
     */
  }

  /* Return the element at row and column.
   *
   * Example:
   *   array2d<float> a{2,2};
   *   a(0, 0) = 0;
   *   a(0, 1) = 1;
   *   a(1, 0) = 2;
   *   a(1, 1) = 3;
   *
   * These should be equivalent:
   *     (*this)(row, column) == (*this)[row][column]
   * but operator() should generally be more efficient.
   */
  T &operator()(size_type row, size_type column) {
    // How do we translate row and column (2d) into offset (1d)?
    size_type offset;
    return storage_[offset];
  }

  /* Swap all the contents of `other` with `this`, and vice versa. */
  void swap(array2d &other) {
    using std::swap;
    // How do we swap these?
  }

private:
  /* The number of columns per row. */
  size_type columns_;
  std::valarray<T> storage_;
};

template <class T> void swap(array2d<T> &a, array2d<T> &b) { a.swap(b); }
} // namespace fsl

#endif
