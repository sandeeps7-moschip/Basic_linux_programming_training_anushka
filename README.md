# Basic Linux Programming Training
Linux system programming training for Softnautics. It covers Inter process communication(IPC), Multi-threading, Memory Management and Embedded Linux concepts.

# Training document
Go through [training](./docs/training.md) document.

# Directory structure
Follow below directory structure for all assignments.
```
assignments/
├── Topic-3-Processes-and-Threads
│   ├── as_3_1
│   │   ├── bin
│   │   │   └── as_3_1
│   │   ├── build
│   │   │   └── Makefile
│   │   ├── docs
│   │   ├── include
│   │   └── src
│   │       └── as_3_1.c
│   └── Makefile
│   ├── as_3_1
├── Topic-4-IPC
└── Makefile
```
# Important notes:
1. Include directory should only have external header files (common to cross directories). Header files related to src directory must be in src directory only.
2. Individual makefiles to build only specific exercise, all assignments of specific chapter, all assignments of all chapters.
3. Parent makefile should call child makefiles  to perform required operation.
4. Object files should be generated  in src directory only.
5. Output binary should be put in bin directory of respective exercise.
6. Any docs (if required like README) should be put in docs directory.

