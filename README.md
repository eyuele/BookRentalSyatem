# Book Rental System (C++)

A console-based Library Management System developed using Object-Oriented Programming (OOP) principles and custom data structures.

## Group Members
* **Eyuel Esubalew** (RCD/1690/2017)
* **Kidus Anteneh** (RCD/0264/2017)
* **Akbari Girma** (RCD/0235/2017)
* **Birhanemedin Mulat** (RCD/0242/2017)

## Project Timeline
* **Total Development Time:** 20 hours

## Features
* **Inventory Management:** Track books by Title, ISBN, and stock count.
* **Rental Processing:** Handle check-outs and returns with real-time stock updates.
* **Transaction Logging:** Manage active rentals using a custom Singly Linked List.
* **Persistent Storage:** Save and load data across sessions using flat-file databases (`books.txt`, `Rental.txt`).

## Technical Implementation
* **Object-Oriented Programming:** Modular design using classes for Books, Users, and Transactions.
* **Data Structures:** Manual implementation of a **Singly Linked List** utilizing Pointers and Dynamic Memory management.
* **STL Integration:** Usage of `std::vector` for efficient dynamic inventory storage.
* **File Handling:** Stream-based I/O for database persistence.

## Repository Structure
* `BookRental.cpp`: Main application entry point.
* `main.h`: Header file containing class definitions and file handling logic.
* `work-process/`: Contains step-by-step development process, handwritten logic photos, and planning documents.
* `books.txt`: Inventory database.
* `Rental.txt`: Transaction log database.

## Setup and Usage

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/eyuele/BookRentalSyatem.git](https://github.com/eyuele/BookRentalSyatem.git)
2. **Compile using G++:**
   ```bash
   g++ BookRental.cpp -o BookRental.exe
3. **Run the application:**
   ```Bash
   ./BookRental.exe
