# Phenomenological Renormalization Group by Evidence

This project includes an implementation of the phenomenological renormalization group (RG) algorithm introduced by [arxiv:1812.11904](https://arxiv.org/pdf/1812.11904.pdf). The algorithm begins with a dataset and iteratively pairs and coarse grains the data based on a measure of evidence.

This code runs the PRG algorithm and stores the pairs found and normalized activity of the clusters in separate files in the 'data' folder.

## Structure

The project includes the following main components:

- `main.cpp`: The main driver of the program.
- `coarse_grain.cpp`: Functions for performing the coarse graining.
- `file_io.cpp`: Functions for reading and writing data to files.
- `helper_functions.cpp`: Helper functions
- `pairwise_evidence.cpp`: Function to calculate the pairwise evidence.

## Usage

To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

To run the program (make sure you are in the build directory):

```bash
./RG_Pairing
```

## Data

The `data` directory includes the following:

- `pairs.txt`: The pairs of data points formed during the RG process.
- `data.txt`: The coarse-grained data at each stage of the RG process.


