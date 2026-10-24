#include <iostream>
#include "Library.h"
#include "Utils.h"
using namespace std;

void showMenu() {
    cout << "\n=========== SMART LIBRARY SYSTEM ===========\n"
         << " 1. Add book\n"
         << " 2. Remove book\n"
         << " 3. Search by ID           (Hash Table)\n"
         << " 4. Search by title        (BST)\n"
         << " 5. List by title          (BST in-order)\n"
         << " 6. List by year/author/ID (Merge Sort)\n"
         << " 7. Issue book             (Queue if already issued)\n"
         << " 8. Return book\n"
         << " 9. Show waiting list\n"
         << "10. Undo last action       (Stack)\n"
         << " 0. Exit\n";
}

int main() {
    Library lib;

    // Sample data (not recorded in the undo stack)
    lib.addBook(101, "Data Structures in C++", "Mark Allen Weiss", 2013, false);
    lib.addBook(102, "Introduction to Algorithms", "Thomas Cormen", 2009, false);
    lib.addBook(103, "Clean Code", "Robert Martin", 2008, false);
    lib.addBook(104, "Operating System Concepts", "Abraham Silberschatz", 2018, false);
    lib.addBook(105, "Database System Concepts", "Henry Korth", 2019, false);

    int choice;
    do {
        showMenu();
        choice = readInt("Choice: ");
        cout << "\n";

        switch (choice) {
        case 1: {
            int id = readInt("ID: ");
            string title = readLine("Title: ");
            string author = readLine("Author: ");
            int year = readInt("Year: ");
            cout << (lib.addBook(id, title, author, year)
                         ? "  Book added.\n" : "  ID already exists.\n");
            break;
        }
        case 2: {
            int id = readInt("ID: ");
            cout << (lib.removeBook(id) ? "  Book removed.\n" : "  Not found.\n");
            break;
        }
        case 3: lib.searchById(readInt("ID: ")); break;
        case 4: lib.searchByTitle(readLine("Exact title: ")); break;
        case 5: lib.listSortedByTitle(); break;
        case 6: {
            int m = readInt("Sort by (1=Year, 2=Author, 3=ID): ");
            if (m < 1 || m > 3) { cout << "  Invalid option.\n"; break; }
            lib.listSortedBy(m);
            break;
        }
        case 7: {
            int id = readInt("Book ID: ");
            string student = readLine("Student name: ");
            lib.issueBook(id, student);
            break;
        }
        case 8: lib.returnBook(readInt("Book ID: ")); break;
        case 9: lib.showWaiting(readInt("Book ID: ")); break;
        case 10: lib.undo(); break;
        case 0: cout << "  Goodbye!\n"; break;
        default: cout << "  Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
