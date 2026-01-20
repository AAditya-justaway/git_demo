-----

-----

  - Aaditya Abhijeet Shinde

-----

## 1\. Project Overview

This project is designed to parse, store, sort, and manage publication entries from `.bib` files. The primary design challenge was to develop this system without using any C++ Standard Template Library (STL). 
-----

## 2\. System Architecture and Design

The system is architecturally divided into three primary components:

**Syscalls Module:** This serves as a low-level abstraction layer that encapsulates direct Linux system calls (`open`, `read`, `write`).  This module effectively creates a minimal, project-specific standard library.

**Publication Class:** This class acts as the core data model (entity class). It is responsible for managing the memory for all its fields (e.g., author, title, year), which are stored as dynamically allocated C-style strings (`char*`). Its constructors, destructor, and assignment operator are implemented to ensure deep copying and prevent memory leaks, adhering to the "Rule of Three."

**PublicationList Class:** This is the primary manager/container class responsible for aggregating `Publication` objects. It orchestrates the file parsing logic, manages a dynamic array for storing the `Publication` instances, and exposes high-level functionalities such as sorting and list concatenation.

-----

## 3\. Build and Execution Technique

### 3.1. Prerequisites

The build environment requires the following standard Linux development tools:

  - A C++ compiler
  - GNU `make`

### 3.2. Compilation

The project is compiled using the provided `Makefile`. This `Makefile` is configured to build all C++ source files and link them into a single executable binary.

To compile the application, navigate to the project's root directory in a terminal and execute the `make` command:

```bash
make
```

Upon successful compilation, an executable file named `bibmanager` will be generated in the root directory.

### 3.3. Execution

The program is executed from the command line and accepts one or two `.bib` files as arguments.

  - **To parse and sort a single file:**

    ```bash
    ./bibmanager <filename.bib>
    ```

  - **To parse two files, merge their contents, and sort the result:**

    ```bash
    ./bibmanager <file1.bib> <file2.bib>
    ```

The program outputs the unsorted and sorted publication lists to standard output for verification.
