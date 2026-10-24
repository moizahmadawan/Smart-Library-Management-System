# Smart Library Management System (C++ | DSA)

A console-based library management system written in C++17 that uses **custom-built data structures** (no STL containers for the core logic) to manage books, issuing, waiting lists and undo.

## Features

- Add and remove books
- Search a book by **ID** (Hash Table) or by **title** (BST)
- List books alphabetically (BST in-order traversal)
- Sort books by **year, author or ID** (Merge Sort)
- Issue a book; if it is already issued, the student joins a **waiting queue**
- On return, the next student in the queue gets the book automatically
- **Undo** the last action (add / issue / return)

## Data Structures Used

| Data Structure | Where it is used | Complexity |
|---|---|---|
| Hash Table (separate chaining) | Fast search by book ID | O(1) average |
| Binary Search Tree | Search and sorted listing by title | O(log n) average |
| Queue (linked list) | Waiting list for issued books | O(1) enqueue/dequeue |
| Stack (linked list) | Undo history | O(1) push/pop |
| Merge Sort | Sort by year / author / ID | O(n log n) |

## Project Structure

```
smart-library-cpp/
├── include/
│   ├── Book.h         # Book structure and print helper
│   ├── BST.h          # Binary Search Tree (by title)
│   ├── HashTable.h    # Hash Table with chaining (by ID)
│   ├── Library.h      # Library class (ties everything together)
│   ├── MergeSort.h    # Merge Sort for books
│   ├── Queue.h        # Linked-list queue (waiting list)
│   ├── Stack.h        # Linked-list stack (undo)
│   └── Utils.h        # Input helpers and toLower
├── src/
│   ├── Library.cpp    # Library logic
│   └── main.cpp       # Menu and program entry point
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

## Build and Run

**Requirements:** a C++17 compiler (g++ / MinGW / clang).

Using Make:

```bash
make
./library        # Windows: library.exe
```

Without Make:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/Library.cpp -o library
./library
```

## Sample Run

```
Choice: 7
Book ID: 101
Student name: Ali
  Issued "Data Structures in C++" to Ali.

Choice: 7
Book ID: 101
Student name: Sara
  Already issued to Ali. Sara added to waiting list (position 1).

Choice: 8
Book ID: 101
  Ali returned "Data Structures in C++".
  Auto-issued to next in queue: Sara.
```

## How It Works

1. **Add book:** the book is inserted into the Hash Table (ID) and the BST (title).
2. **Issue:** if the book is free it is issued, otherwise the student is enqueued.
3. **Return:** the next student is dequeued and issued automatically.
4. **Undo:** the last action is popped from the stack and reversed.

## Possible Improvements

- Save and load books from a file
- Member accounts and due dates
- Graph-based campus navigator module
- GUI (Qt) version

## Author

**Malik Moiz Ahmad Awan**
BS Computer Science, University of Gujrat

Licensed under the MIT License.
