#ifndef FSL_ARRAY2D_HH
#define FSL_ARRAY2D_HH

#include "array1d.hh"

namespace fsl {

template <class T> class array2d {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using size_type = typename array1d<T>::size_type;

  array2d() : columns_{}, storage_{} {}

  array2d(size_type rows, size_type columns)
      : columns_{columns}, storage_{rows * columns} {}

  array2d(array2d const &b) = default;
  array2d(array2d &&b) = default;
  ~array2d() = default;

  size_type rows() const {
    // How do we calculate the number of rows since we did not store it?
    return 0;
  }

  size_type columns() const { return 0; }

  /* Return row `n` from the storage. */
  void operator[](size_type n) {
    // How do we return a single row? How big is a single row?
    // What should the return type of this member function be?
  }

  void const operator[](size_type row) const {
    // How do we implement the const version?
  }

  /* Return the element at row and column. These should be equivalent:
   *     (*this)(row, column) == (*this)[row][column]
   * but operator() should generally be more efficient. */
  reference operator()(size_type row, size_type column) {
    // How do we translate row and column (2d) into offset (1d)?
    size_type offset;
    return storage_[offset];
  }

  void swap(array2d &other) {
    // How do we swap these?
  }

private:
  /* The number of columns per row. */
  size_type columns_;
  array1d<value_type> storage_;
};

template <class T> void swap(array2d<T> &a, array2d<T> &b) { a.swap(b); }
}

#endif
