# CMP SCI 4760 - Project 1: Process Management

## Project Overview

This project implements a basic simulation of an operating system's process management. The program `oss` (Operating System Simulator) manages multiple instances of a child process named `user`.
The `oss` program dynamically creates and manages these child processes based on command-line inputs, simulating process creation, execution, and termination.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software:

- GCC compiler
- Linux Operating System

### Installing

A step-by-step series of examples that tell you how to get a development environment running:

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/masfm8/cs4760-project1


   ### Running the Tests

   The functionality of the oss and user programs has been tested under various configurations:

Testing the user program directly:
./user 5

Testing the oss program with different parameters:

./oss -n 5 -s 3 -t 7

This command configures the oss program to launch 5 user processes, allowing no more than 3 to run simultaneously, each performing 7 iterations.

./oss -n 3 -s 3 -t 5

This setup tests the oss program with 3 user processes, each doing 5 iterations, with up to 3 processes running simultaneously.

### Known Issues
Currently, there are issues with the Makefile which may affect the compilation process. Efforts are ongoing to resolve these issues to ensure smoother builds and deployments.
   
