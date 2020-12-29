#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);
typedef struct list_node list_node;
struct list_node{
    char *val;
    list_node *next;
};

// Complete the checkMagazine function below.
/**
 * @brief this function makes a list from an array.
 * @param array an array of char pointers.
 * @param size the size of the array.
 * @return pointer to the first list node.
*/
list_node *create_list (int size, char** array){
    list_node *tmp = NULL;
    for (int i=0; i<size; i++){
        list_node *node = malloc(sizeof(list_node));
        node->val = array[i];
        node->next = tmp;
        tmp = node;
    }
    return tmp;
}
/**
 * @brief this function frees the memory of a list.
 * @param node pointer to the first node.
*/
void free_list (list_node *node){
    while (node){
        list_node *tmp = node;
        node = node->next;
        free (tmp);
    }
}

/**
 * @brief this function checks if you can make the note from the magazine.
 * @param magazine an array of char pointers.
 * @param note_count the size of the note array.
 * @param note an array of char pointers.
 * @param note_count the size of the magazine array.
*/
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {
    list_node *magazine_list = create_list (magazine_count, magazine);
    list_node *note_list = create_list (note_count, note);
    list_node *magazine_list_tmp = magazine_list;
    list_node *note_list_tmp = note_list;
    while (note_list){
        char *word = note_list->val;
        int match = 0;
        while (magazine_list){
            if (strcmp(magazine_list->val, word)==0){
                match = 1;
                magazine_list->val = "\0";
                break;
            }
            else {
                magazine_list = magazine_list->next;
            }
        }
        if (match == 0){
            printf ("No");
            free_list (magazine_list_tmp);
            free_list (note_list_tmp);
            return;
        }
        note_list = note_list->next;
        magazine_list = magazine_list_tmp;
    }
    printf("Yes");
    free_list (magazine_list_tmp);
    free_list (note_list_tmp);
    return;
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
