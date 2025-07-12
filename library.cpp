#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Book {
protected:
    int bookID;
    string title;
    string author;
    bool isIssued;

public:
    Book() : bookID(0), title(""), author(""), isIssued(false) {}

    void addBook() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();  // clear newline after int input

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        isIssued = false;
    }

    void displayBook() const {
        cout << setw(10) << bookID << setw(20) << title << setw(20) << author << setw(10) 
             << (isIssued ? "Issued" : "Available") << endl;
    }

    int getBookID() const {
        return bookID;
    }

    bool getIsIssued() const {
        return isIssued;
    }

    void issueBook() {
        if (!isIssued) {
            isIssued = true;
            cout << "Book issued successfully.\n";
        } else {
            cout << "Book is already issued.\n";
        }
    }

    void returnBook() {
        if (isIssued) {
            isIssued = false;
            cout << "Book returned successfully.\n";
        } else {
            cout << "Book is not issued.\n";
        }
    }

    void saveToFile(ofstream &outfile) const {
        outfile << bookID << endl;
        outfile << title << endl;
        outfile << author << endl;
        outfile << isIssued << endl;
    }

    void loadFromFile(ifstream &infile) {
        infile >> bookID;
        infile.ignore(); 
        getline(infile, title);
        getline(infile, author);
        infile >> isIssued;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void loadData() {
        ifstream infile("library.txt");
        if (infile.is_open()) {
            int count;
            infile >> count;
            infile.ignore();
            for (int i = 0; i < count; ++i) {
                Book b;
                b.loadFromFile(infile);
                books.push_back(b);
            }
            infile.close();
        }
    }

    void saveData() {
        ofstream outfile("library.txt");
        if (outfile.is_open()) {
            outfile << books.size() << endl;
            for (int i = 0; i < books.size(); ++i) {
                books[i].saveToFile(outfile);
            }
            outfile.close();
        }
    }

    void addBook() {
        Book b;
        b.addBook();
        books.push_back(b);
        cout << "Book added successfully.\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }

        cout << setw(10) << "Book ID" << setw(20) << "Title" << setw(20) << "Author" 
             << setw(10) << "Status" << endl;
        for (int i = 0; i < books.size(); ++i) {
            books[i].displayBook();
        }
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (int i = 0; i < books.size(); ++i) {
            if (books[i].getBookID() == id) {
                books[i].issueBook();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (int i = 0; i < books.size(); ++i) {
            if (books[i].getBookID() == id) {
                books[i].returnBook();
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library lib;
    lib.loadData();
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.displayBooks();
                break;
            case 3:
                lib.issueBook();
                break;
            case 4:
                lib.returnBook();
                break;
            case 5:
                lib.saveData();
                cout << "Exiting... Data saved.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

