#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

void checking_opening_file(int file_descriptor) {
    if (file_descriptor < 0) {
            printf("Ошибка чтения фаила\n");
            exit(1);
        }
}


void reading_file(int poem_file_descriptor, char* all_poem, off_t poem_size) {
    assert(all_poem);
    assert(poem_file_descriptor >= 0);
    assert(poem_size > 0);

    ssize_t read_size = read(poem_file_descriptor, all_poem, poem_size);
    if (read_size < 0) {
        printf("Ошибка чтения фаила\n");
        exit(1);
    }

    if (read_size == SIZE_MAX) {
        ;//TODO читать дальше
    }
}


size_t Counting_action(char* all_poem, size_t poem_size) {
    assert(all_poem);

    size_t lines_amount = 0;
    char current = '\0';
    for (int i = 0; (current = all_poem[i]) != '\0'; i++) {
        if (current == '\n') {
            lines_amount += 1;
        }
    }

    return lines_amount;
}


int Spliting_for_action(char* all_poem, char* lines_address[], size_t lines_amount) {
    assert(all_poem);
    assert(lines_address);

    int found_lines = 1;
    char current;

    lines_address[0] = all_poem;

    for (int current_index = 0; (current = all_poem[current_index]) != '\0'; current_index++) {
        if (current == '\n') {
            lines_address[found_lines++] = all_poem + current_index + 1*sizeof(char);
        }
    }

    return found_lines;

}
