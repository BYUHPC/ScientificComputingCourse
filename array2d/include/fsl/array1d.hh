#ifndef FSL_ARRAY1D_HH
#define FSL_ARRAY1D_HH 1

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace fsl {

template <class T> class array1d {
public:
  // value_type is the type of item stored in array1d
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using iterator = T *;
  using const_iterator = T const *;
  using difference_type = std::ptrdiff_t;
  using size_type = int;

  // A constructor which has no parameters is called the default constructor
  array1d() : size_{}, storage_{} {}

  /* The explicit keyword prevents the compiler from automatically converting a
   * size_t to an array1d; the constructor must be explicitly called instead.
   */
  explicit array1d(size_type size)
      : size_{size}, storage_{std::make_unique<T[]>(size)} {}

  /* A constructor which takes a reference to another object of the same type
   * is called a copy contructor. It needs to make a complete copy. */
  array1d(array1d const &b) : array1d{b.size_} {
    std::copy_n(b.cbegin(), b.size_, begin());
  }

  /* This a move constructor. Think of it as a more efficient copy constructor
   * for the case when `b` is an object that is done (it's going to be
   * destroyed) so instead of copying everything the compiler steals everything
   * instead. */
  array1d(array1d &&b) = default;

  /* This is a destructor. It runs when the object has outlived its scope or
   * has been manually destroyed. The compiler generated version is sufficient
   * in this case. */
  ~array1d() = default;

  /* This is a copy-assignment operator. This methods deletes its existing
   * contents and makes a copy of the contents of b. */
  array1d &operator=(array1d const &b) {
    if (&b != this) {
      array1d<T> tmp{b};
      swap(tmp);
    }
    return *this;
  }

  /* This is the move-assignment operator. Similar to the move constructor it
  steals the contents of b since b is at the end of its lifetime instead of
  doing a full copy. */
  array1d &operator=(array1d &&b) = default;

  /* Returns a reference to the element at position n in the storage. The
   * argument n is not checked to see if it is in-bounds (meaning, exists
   * within the storage). Use the at() member function if bounds should be
   * checked. */
  reference operator[](size_type n) { return storage_[n]; }

  /* This is the const version of operator[]. */
  const_reference operator[](size_type n) const { return storage_[n]; }

  /* Returns a reference to the element at position n in the storage. This
   * function checkes if n is in-bounds and will throw an out_of_range
   * exception if it is not. Use operator[] for a version that does not check
   * bounds. */
  reference at(size_t n) {
    if (n < 0 || n >= size_) {
      throw std::out_of_range("Argument to array1d::at() was out-of-bounds.");
    }
    return storage_[n];
  }

  /* This is the const version of at(). */
  const_reference at(size_t n) const {
    if (n < 0 || n >= size_) {
      throw std::out_of_range("Argument to array1d::at() was out-of-bounds.");
    }
    return storage_[n];
  }

  /* Return an iterator to the beginning of the storage. C++ pointers fulfill
   * the requirements for contiguous iterators so this method can return the
   * address of the first item. Contiguous means the memory is in a linear
   * chunk without any holes. */
  iterator begin() { return &storage_[0]; }

  /* These are just const versions of begin() so if an object is const it can
   * return the const_iterator instead of the mutable iterator. */
  const_iterator cbegin() const { return &storage_[0]; }
  const_iterator begin() const { return cbegin(); }

  /* Return an iterator to the past-the-end element, meaning the element
   * immediately after the last one. C++ iterators are exclusive on the ending
   * side (they are inclusive on the beginning side). */
  iterator end() { return &storage_[size_]; }

  /* These are just const versions of end(). */
  const_iterator cend() const { return &storage_[size_]; }
  const_iterator end() const { return cend(); }

  /* Returns the number of items in storage. Returns a copy rather than a
   * reference so that it cannot be modified by the caller. */
  size_type size() const { return size_; }

  /* Returns true if and only if there are no items in the storage. */
  bool empty() const { return storage_.get() == nullptr; }

  /* Swaps this object with b, and b with this object. After the call to this
   * member function, the elements in this container are those which were in b
   * before the call, and the elements of b are those which were in this. */
  void swap(array1d b) {
    using std::swap;
    swap(size_, b.size_);
    swap(storage_, b.storage_);
  }

private:
  /* Code outside of this class should not directly manipulate these variables
   * because it needs to keep the size_ variable and size of the storage in
   * sync. This is why they are private and not public. The private variables
   * have an underscore suffix; this leaves the regular, clean names for
   * methods which return a copy of the value. This is purely a convention. */
  size_type size_;

  // storage holds size_ items of type value_type (or T, same thing)
  std::unique_ptr<value_type[]> storage_;
};

/* This swap exists for the ADL swap pattern, which I do not require students
 * to know or understand. */
template <class T> void swap(array1d<T> &a, array1d<T> &b) { a.swap(b); }
}

#endif
