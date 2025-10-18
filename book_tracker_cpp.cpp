//
// Created by user on 01.10.2025.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_BOOKS = 1000;

struct Book
{
    char title[100];
    char author[50];
    char year[10];
    float grade;
};
Book books[MAX_BOOKS];
int books_count = 0;
void saveBooksToFile(const char *filename, Book b) {
    ofstream fout(filename, ios::app);

    if (!fout) {
        cout << "Can't open file " << endl;
        return;
    }
    fout << b.title << " " << b.author << " " << b.year << " " << b.grade << endl;

    fout.close();
}
void loadBooks(const char *filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Can't open file " << endl;
        return;
    }
    while (fin >> books[books_count].title >> books[books_count].author >> books[books_count].year >> books[books_count].grade) {
        books_count++;
    }

    fin.close();
}
void addBook() {
    if (books_count >= MAX_BOOKS) {
        cout << "Can't add book to books list" << endl;
    }
    Book newBook;
    cout << "Enter book title: ";
    cin >> newBook.title;
    cout << "Enter book author: ";
    cin >> newBook.author;
    cout << "Enter the year you read the book: ";
    cin >> newBook.year;
    cout << "Enter your book grade: ";
    cin >> newBook.grade;
    books[books_count++] = newBook;
    saveBooksToFile("books.txt", newBook);

    cout << "Book added in the list" << endl;
}

void showBooks() {
    if (books_count == 0) {
        cout << "No books found" << endl;
    }
    // Заголовок таблицы
    cout << "\n--- all books ---\n";
    cout << left << setw(12) << "Title"
         << setw(15) << "Author"
         << "Year\n";
    cout << "------------------------------\n";

    for (int i = 0; i < books_count; i++) {
            cout << left << setw(12) << books[i].title
                 << setw(15) << books[i].author
                 << books[i].year << "\n";
        }
}
void showStats() {
    if (books_count == 0) {
        cout << "No data for analys\n";
        return;
    }

    float sum_average = 0;
    float best_grade = books[0].grade;
    for (int i = 0; i < books_count; i++) {
        sum_average += books[i].grade;
        if (books[i].grade > best_grade) {
            best_grade = books[i].grade;
        }
    }
    cout << "\n--- Statistic ---\n";
    cout << "Number of books read: " << books_count << endl;
    cout << "Average grade: " << sum_average / books_count << endl;
    cout << "Max grade: " << best_grade << endl;
}

void showMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Add book\n";
    cout << "2. Show books\n";
    cout << "3. Show stats\n";
    cout << "4. Exit\n";
}

int main() {
    loadBooks("books.txt");

    int choice;

    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                showBooks();
                break;
            case 3:
                showStats();
                break;
            case 4:
                cout << "Exit the programm\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}


