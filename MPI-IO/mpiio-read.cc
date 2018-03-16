#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // todo: open file "data.out"
  // todo: read in dimensions
  // todo: describe 2d grid
  // todo: collective read
  // todo: close file
  // todo: test that we got the correct data

  MPI_Finalize();
  return 0;
}
