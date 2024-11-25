#!/bin/bash

# Constants
NUM_RUNS_FROM=1000
NUM_RUNS_TO=1000
JUMP=1
DENSITY="sparse"
INPUT_FILE="input_file.edgelist"
TIME_OUTPUT_FILE="test.csv"
SEQUENTIAL_DIR="sequential"
MPI_DIR="mpi"
MPI_PROCS=4

# Create or overwrite the time output file
rm -f "$TIME_OUTPUT_FILE"
touch "$TIME_OUTPUT_FILE"
printf "Nodes;Edges;Sequential Time;MPI 2 procs;MPI 3 procs;MPI 4 procs;" >> "$TIME_OUTPUT_FILE"


# Check if the generate_edgelist program exists
if ! [[ -x "./generate_edgelist" ]]; then
    echo "Error: 'generate_edgelist' program not found or not executable."
    exit 1
fi

# Main loop
for (( i=$NUM_RUNS_FROM; i<=$NUM_RUNS_TO; i = i + $JUMP )); do
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

    # Test MPI program
    echo "Run $i: Testing MPI program..."
    if [[ -d "$MPI_DIR" ]]; then
        pushd "$MPI_DIR" > /dev/null
        make run PROCS=2 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: MPI program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        make run PROCS=3 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: MPI program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        make run PROCS=4 FILE="../$INPUT_FILE" TIME="../$TIME_OUTPUT_FILE"
        if [[ $? -ne 0 ]]; then
            echo "Error: MPI program failed for run $i."
            popd > /dev/null
            exit 1
        fi
        popd > /dev/null
    else
        echo "Error: MPI directory '$MPI_DIR' not found."
        exit 1
    fi

    echo "Run $i: Completed."
done

echo "All runs completed successfully. Results saved in '$TIME_OUTPUT_FILE'."
