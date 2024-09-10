#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Для работы с директориями

void print_menu() {
    printf("Меню:\n");
    printf("1. Указать путь к текстовому файлу для его открытия и чтения\n");
    printf("2. Добавить строку в конец файла и вывести содержимое файла\n");
    printf("3. Шифрование .c файлов кодом Цезаря и очистка .h файлов в директории\n");
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

void append_to_file(const char *path) {
    FILE *file = fopen(path, "a");
    if (!file) {
        printf("n/a\n");
        return;
    }

    char buffer[256];
    printf("Введите строку для добавления: ");
    getchar(); // Очистка буфера
    fgets(buffer, sizeof(buffer), stdin);

    if (fputs(buffer, file) == EOF) {
        printf("n/a\n");
        fclose(file);
        return;
    }
    fclose(file);

    read_file(path);
}

void caesar_cipher(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') {
            text[i] = 'A' + (c - 'A' + shift) % 26;
        } else if (c >= 'a' && c <= 'z') {
            text[i] = 'a' + (c - 'a' + shift) % 26;
        }
    }
}

void process_directory_caesar(const char *directory, int shift) {
    DIR *dir = opendir(directory);
    if (!dir) {
        printf("n/a\n");
        return;
    }

    struct dirent *entry;
    char path[512];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
            char *ext = strrchr(entry->d_name, '.');

            if (ext && strcmp(ext, ".c") == 0) {
                FILE *file = fopen(path, "r+");
                if (file) {
                    fseek(file, 0, SEEK_END);
                    long file_size = ftell(file);
                    fseek(file, 0, SEEK_SET);

                    char *buffer = malloc(file_size + 1);
                    if (buffer) {
                        fread(buffer, 1, file_size, file);
                        buffer[file_size] = '\0';
                        caesar_cipher(buffer, shift);
                        fseek(file, 0, SEEK_SET);
                        fwrite(buffer, 1, file_size, file);
                        free(buffer);
                    }
                    fclose(file);
                }
            } else if (ext && strcmp(ext, ".h") == 0) {
                FILE *file = fopen(path, "w");
                if (file) {
                    fclose(file);
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    int choice;
    char path[256] = ""; // Хранит путь к файлу или директории

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
        } else if (choice == 2) {
            if (strlen(path) == 0) {
                printf("n/a\n");
            } else {
                append_to_file(path);
            }
        } else if (choice == 3) {
            printf("Введите путь к директории: ");
            scanf("%s", path);
            printf("Введите сдвиг для шифрования Цезаря: ");
            int shift;
            scanf("%d", &shift);
            process_directory_caesar(path, shift);
        } else {
            printf("n/a\n");
        }

        printf("\n");
    }

    return 0;
}
