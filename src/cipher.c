#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("Меню:\n");
    printf("1. Указать путь к текстовому файлу для его открытия и чтения\n");
    printf("-1. Выход из программы\n");
}

void read_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("n/a\n");
        return;
    }

    int ch;
    int is_empty = 1;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        is_empty = 0;
    }
    
    if (is_empty) {
        printf("n/a\n");
    }
    
    fclose(file);
}

int main() {
    int choice;
    char path[256];

    while (1) {
        print_menu();
        printf("Введите команду: ");
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            break;
        }

        if (choice == -1) {
            break;
        } else if (choice == 1) {
            printf("Введите путь к файлу: ");
            scanf("%s", path);
            read_file(path);
        } else {
            printf("n/a\n");
        }

        printf("\n");
    }

    return 0;
}
