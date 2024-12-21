#!/bin/bash

# Constants
NUM_RUNS_FROM=81920
NUM_RUNS_TO=100000
JUMP=2
DENSITY="sparse"
INPUT_FILE="input_file.edgelist"
TIME_OUTPUT_FILE="testes/sparse/time_sparse_range.csv"
SEQUENTIAL_DIR="sequential"
OMP_DIR="openmp"
OMP_THREADS=4

# Create or overwrite the time output file
rm -f "$TIME_OUTPUT_FILE"
touch "$TIME_OUTPUT_FILE"
printf "Nodes;Edges;Sequential Time;OMP 2 THREADS;OMP 3 THREADS;OMP 4 THREADS;" >> "$TIME_OUTPUT_FILE"


# Check if the generate_edgelist program exists
if ! [[ -x "./generate_edgelist" ]]; then
    echo "Error: 'generate_edgelist' program not found or not executable."
    exit 1
fi

# Main loop
for (( i=$NUM_RUNS_FROM; i<=$NUM_RUNS_TO; i = i * $JUMP )); do
    echo "Run $i: Generating input file..."
    ./generate_edgelist "$i" "$DENSITY" "$INPUT_FILE"
    
    if [[ $? -ne 0 ]]; then
        echo "Error: Failed to generate input file for run $i."
        exit 1
    fi

    # Count the number of edges in the generated file
    if [[ -f "$INPUT_FILE" ]]; then
        EDGES=$(wc -l < "$INPUT_FILE")
    else
        echo "Error: Input file '$INPUT_FILE' not found for run $i."
        exit 1
    fi

    # Append the number of nodes and edges to the time output file
    printf "\n%d;%d;" "$i" "$EDGES" >> "$TIME_OUTPUT_FILE"

    # Test sequential program
    echo "Run $i: Testing sequential program..."
    if [[ -d "$SEQUENTIAL_DIR" ]]; then
        pushd "$SEQUENTIAL_DIR" > /dev/null
        make run FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: Sequential program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        popd > /dev/null
    else
        echo "Error: Sequential directory '$SEQUENTIAL_DIR' not found."
        exit 1
    fi

    # Test OMP program
    echo "Run $i: Testing OMP program..."
    if [[ -d "$OMP_DIR" ]]; then
        pushd "$OMP_DIR" > /dev/null
        make run THREADS=2 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: OMP program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        make run THREADS=3 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: OMP program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        make run THREADS=4 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: OMP program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        popd > /dev/null
    else
        echo "Error: OMP directory '$OMP_DIR' not found."
        exit 1
    fi

    echo "Run $i: Completed."
done

echo "All runs completed successfully. Results saved in '$TIME_OUTPUT_FILE'."
