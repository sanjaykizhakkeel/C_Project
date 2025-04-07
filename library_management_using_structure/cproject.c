#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct library {
    char book[30];
};
typedef struct library lib;

void display(lib*, int);
void add(lib**, int*);
void borrow(lib*, int*);
void end(void);

int main() {
    int n, a = 0;
    lib* data = NULL;
    printf("====== Welcome to Library ======\n");

    while (1) {
        printf("\nWhat option do you want?\n");
        printf("1. Display Available Books\n");
        printf("2. Add New Book\n");
        printf("3. Borrow Book\n");
        printf("4. Exit The Library\n");
        scanf("%d", &n);
        getchar(); // Clear newline character from input buffer

        switch (n) {
        case 1:
            display(data, a);
            break;
        case 2:
            add(&data, &a);
            break;
        case 3:
            borrow(data, &a);
            break;
        case 4:
            end();
            free(data); // Free allocated memory
            return 0;
        default:
            printf("Invalid option! Please try again.\n");
            break;
        }
    }
}

void display(lib* data, int n) {
    if (n == 0) {
        printf("No available books.\n");
    } else {
        printf("Books Available:\n");
        for (int i = 0; i < n; i++) {
            printf("%d. %s\n", i + 1, data[i].book);
        }
    }
}

void add(lib** data, int* n) {
    int count;
    printf("How many books do you want to add? ");
    scanf("%d", &count);
    getchar(); // Clear newline character from input buffer

    // Resize memory to accommodate new books
    *data = (lib*)realloc(*data, (*n + count) * sizeof(lib));
    if (*data == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        printf("Enter name of book %d: ", *n + i + 1);
        fgets((*data)[*n + i].book, sizeof((*data)[*n + i].book), stdin);
        (*data)[*n + i].book[strcspn((*data)[*n + i].book, "\n")] = '\0'; // Remove newline character
    }
    *n += count; // Update the total number of books
}

void borrow(lib* data, int* n) {
    if (*n == 0) {
        printf("No books available to borrow.\n");
        return;
    }

    char s[30];
    int found = 0;

    printf("Type the name of the book you want to borrow: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0'; // Remove newline character

    for (int i = 0; i < *n; i++) {
        if (strcmp(s, data[i].book) == 0) {
            found = 1;
            printf("You have borrowed: %s\n", data[i].book);

            // Shift remaining books to fill the gap
            for (int j = i; j < *n - 1; j++) {
                strcpy(data[j].book, data[j + 1].book);
            }
            (*n)--; // Decrease book count
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void end() {
    printf("Exiting the library. Thank you for visiting!\n");
}
