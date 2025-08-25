# ADT Compilation

This repository contains implementations of fundamental **Abstract Data Types (ADTs)** and classic algorithms in **C**.  
Each module is implemented with separate source (`.c`) and header (`.h`) files where appropriate, and many include interactive or automated testers.  

The goal is to provide clean, educational examples of data structure and algorithm implementations.

---

## Contents

### 1. Linked List (Movie Review Database)
- **Files**:  
  - `A1 linked_list.c`  
  - `A1_driver.c` (automated tester)  
  - `A1_interactive.c` (interactive tester)  
- **Features**:  
  - Insert, search, update, delete movie reviews  
  - Maintain movie metadata (studio, year, BO, score)  
  - Query by studio or by score  
  - Insert cast members and calculate actor statistics  
  - Find the most profitable star  
- **Doc**: `CSCA48_Assignment_1.pdf`

---

### 2. Binary Search Tree (BST Sequencer)
- **Files**:  
  - `BSTs.c`  
  - `A2_test_driver.c`  
  - `A2_interactive_driver.c`  
  - Example songs: `bmc.txt`, `dusty.txt`, `minuet.txt`, `BST_driver_input.txt`  
  - `note_frequencies.txt`  
- **Features**:  
  - Store musical notes in a BST  
  - Insert, delete, search by unique key  
  - Traverse tree to create playlists  
  - Reverse songs, harmonize songs  
- **Doc**: `A2_handout.pdf`

---

### 3. AVL Tree
- **Files**:  
  - `AVL_tree.c`  
  - `AVL_tree.h`  
  - `AVL_tree_tester.c`  
- **Features**:  
  - Self-balancing BST using rotations (LL, RR, LR, RL)  
  - Insert, delete, search  
  - Maintain tree height for O(log n) operations  

---

### 4. Weight Balanced Tree (WBT)
- **Files**:  
  - `WBT.c`  
  - `WBT.h`  
  - `WBT_tester.c`  
  - (legacy) `Weight_Balance_Tree.c`  
- **Features**:  
  - Balanced BST using weight conditions  
  - Insert, delete, search  
  - Rank queries (`get_rank`, `findRank`)  
  - Split, join, union of trees  

---

### 5. Graph (Ingredient Graph - Adjacency Matrix)
- **Files**:  
  - `ingredient_graph.c`  
  - Data: `AdjMat_small.dat`, `AdjMat_full.dat`, `Ingredient_names_small.txt`, `Ingredient_names_full.txt`  
  - Drivers: `A3_driver.c`, `A3testdriver.c`  
- **Features**:  
  - Load graph from adjacency matrix  
  - Related ingredients query (direct / k-distance / with restrictions)  
  - Substitute ingredients in recipes  
- **Doc**: `A3_handout.pdf`

---

### 6. Graph Algorithms (Prim’s, Dijkstra, MinHeap)
- **Files**:  
  - `graph.c`, `graph.h`  
  - `graph_algos.c`, `graph_algos.h`  
  - `minheap.c`, `minheap.h`  
  - `graph_tester.c`  
  - Data: `sample_input.txt`, `sample_output.txt`  
- **Features**:  
  - Graph with adjacency list representation  
  - **Prim’s algorithm** for Minimum Spanning Tree  
  - **Dijkstra’s algorithm** for shortest paths  
  - Custom MinHeap for priority queue  

---

### 7. Heap
- **Files**:  
  - `heap.c`  
- **Features**:  
  - Array-based heap implementation  
  - Core operations: insert, delete, heapify  

---

### 8. Quick Sort
- **Files**:  
  - `quicksort.c`  
- **Features**:  
  - Classic QuickSort implementation for integer arrays  
  - Recursive partition-based sorting  

---

### 9. Sudoku Solver
- **Files**:  
  - `sudoku.c`  
- **Features**:  
  - Backtracking Sudoku solver  
  - Reads 9×9 grid and fills missing values  

---

## Compilation & Run

Each ADT can be compiled and tested separately with `gcc`.  
Examples:

```bash
# Compile AVL tree tester
gcc -o AVL_tester AVL_tree.c AVL_tree_tester.c
./AVL_tester

# Compile WBT tester
gcc -o WBT_tester WBT.c WBT_tester.c
./WBT_tester

# Compile BST interactive driver
gcc -o BST_driver BSTs.c A2_interactive_driver.c
./BST_driver

# Compile Graph tester
gcc -o graph_tester graph.c graph_algos.c minheap.c graph_tester.c
./graph_tester
