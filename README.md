# OS Lab 1 - Process Management

Name: Jordan Austin
Course: Operating Systems
Semester: Fall 2026

## Overview
This lab contains implementations for process creation, execution, pipes, and process synchronization using POSIX system calls in C on Linux.

## Folder Contents
- src/: demo programs from the lab instructions (fork, exec, pipe, pipeline, zombie).
- challenges/: challenge exercises 1 through 10 plus helper worker.
- lab_report/: written answers and notes for the lab questions.
- Makefile: builds all programs into the bin directory.

## How To Compile
To build all demo and challenge binaries, run:
make

To remove all compiled files:
make clean

## How To Run
All output binaries are saved in ./bin/.

Examples:
./bin/fork_demo
./bin/ch1_single_fork
./bin/ch2_multi_child 5
./bin/ch6_pipe_sum
./bin/ch7_pipeline "\.c"
./bin/ch10_pool 8 3

## Notes
- Built and tested on Ubuntu Linux with gcc and GNU Make.
- Make sure to pass a search term argument when running challenge 7.
