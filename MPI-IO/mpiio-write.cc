#include <algorithm>
#include <cassert>
#include <iostream>
#include <mpi.h>
#include <numeric>
#include <vector>

using std::vector;

/* We will create a 2D array with 4 columns and 6 rows with a layout like so:

 0  1  2  3
 4  5  6  7
 8  9 10 11
12 13 14 15
16 17 18 19
20 21 22 23

The number of columns and rows is untentionally uneven so it is clear when we
are referring to a given dimension
*/
int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // I'll use an eror handler here to focus on the operations
  MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_ARE_FATAL);

  int comm_size, comm_rank;

  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  const int global_rows = 6;
  const int global_columns = 4;

  // We'll use row-based partitioning because it is the simplest.

  // To keep things simple we will ensure that the number of rows is evenly
  // divisible by the number of processes. To accomplish this we'll have some
  // processes return early and we'll make a new communicator.

  // First, if we have more processes than rows we'll have those exit.
  int procs = std::min(comm_size, global_rows);

  // Second, we'll check if it evenly divides
  if (global_rows % procs != 0) {
    // If it doesn't we need to round down to a number that does divide evenly.
    // There's probably a more elegant solution but this works and is simple
    int i = procs;
    while (i > 1) {
      if (global_rows % i == 0) {
        break;
      }
      --i;
    }
    procs = i;
  }

  // We'll split the communicator to only hold the ones we need
  int color = comm_rank < procs ? 0 : MPI_UNDEFINED;
  MPI_Comm comm;
  MPI_Comm_split(MPI_COMM_WORLD, color, comm_rank, &comm);
  if (comm_rank >= procs) {
    std::cerr << comm_rank << ", signing out" << std::endl;
    MPI_Finalize();
    return 0;
  }

  MPI_Comm_size(comm, &comm_size);
  MPI_Comm_rank(comm, &comm_rank);

  assert(comm_size == procs);

  // use "comm" instead of MPI_COMM_WORLD from here on out

  // Determine which rows we own.
  int block = global_rows / comm_size;
  int start = block * comm_rank;
  int stop = start + block;

#ifndef NDEBUG
  // Print out block ranges if NDEBUG is not
  // defined
  std::cerr << comm_rank << " owns [" << start << "," << stop << ")"
            << std::endl;
#endif

  // Create a buffer for the data
  vector<int> data(block * global_columns);

  // fill it with the correct numbers
  // (iota is from <numeric>)
  std::iota(data.begin(), data.end(), start * global_columns);

  // To avoid parameter parsing we'll save this to a file "data.out"
  MPI_File fh;

  // todo: open file

  // todo: save the dimensions in rows, columns order

  // todo: describe global array

  // todo: use collective write operation

  // todo: close file

  MPI_Finalize();
  return 0;
}
