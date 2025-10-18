#include <stdio.h>

#define MAX_BOOKS 1000

struct Book {
    char title[100];
    char author[50];
    char year[10];
    float grade;
};

struct Book books[MAX_BOOKS];
int books_count = 0;

void saveBookToFile(const char *filename, struct Book b) {
    FILE *fout = fopen(filename, "a");
    if (!fout) {
        printf("Can't open file\n");
        return;
    }
    fprintf(fout, "%s %s %s %.2f\n", b.title, b.author, b.year, b.grade);
    fclose(fout);
}

void loadBooks(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("Can't open file\n");
        return;
    }
    while (fscanf(fin, "%99s %49s %9s %f",
                  books[books_count].title,
                  books[books_count].author,
                  books[books_count].year,
                  &books[books_count].grade) == 4)
    {
        books_count++;
        if (books_count >= MAX_BOOKS) break;
    }

    fclose(fin);
}

void addBook() {
    if (books_count >= MAX_BOOKS) {
        printf("Can't add book to books list\n");
        return;
    }

    struct Book newBook;
    printf("Enter book title: ");
    scanf("%99s", newBook.title);

    printf("Enter book author: ");
    scanf("%49s", newBook.author);

    printf("Enter the year you read the book: ");
    scanf("%9s", newBook.year);

    printf("Enter your book grade: ");
    scanf("%f", &newBook.grade);

    books[books_count++] = newBook;
    saveBookToFile("books.txt", newBook);

    printf("Book added to the list\n");
}

void showBooks() {
    if (books_count == 0) {
        printf("No books found\n");
        return;
    }

    printf("\n--- All Books ---\n");
    printf("%-12s %-15s %s\n", "Title", "Author", "Year");
    printf("---------------------------------------\n");

    for (int i = 0; i < books_count; i++) {
        printf("%-12s %-15s %s\n",
               books[i].title,
               books[i].author,
               books[i].year);
    }
}

void showStats() {
    if (books_count == 0) {
        printf("No data for analysis\n");
        return;
    }
    float sum = 0;
    float best = books[0].grade;

    for (int i = 0; i < books_count; i++) {
        sum += books[i].grade;
        if (books[i].grade > best) {
            best = books[i].grade;
        }
    }

    printf("\n--- Statistics ---\n");
    printf("Number of books read: %d\n", books_count);
    printf("Average grade: %.2f\n", sum / books_count);
    printf("Max grade: %.2f\n", best);
}

void showMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Add book\n");
    printf("2. Show books\n");
    printf("3. Show stats\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    loadBooks("books.txt");

    int choice;
    do {
        showMenu();
        if (scanf("%d   ", &choice) != 1) {
            printf("Invalid input\n");
            break;
        }

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
                printf("Exit the program\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    } while (choice != 4);

    return 0;
}
