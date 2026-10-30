#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "structures.h"
#include "ReadingAndSpliting.h"

typedef unsigned int data;
unsigned int stupid_hash(const char* str);

int const MEMORY_FOR_LINE_ENDING = 1;
#define AMOUNT_USED_BYTES current_byte_index

int main(int argc, char** argv) {
    char* program_file = argv[1];
    struct stat program_file_info = {};
    stat(program_file, &program_file_info);

    off_t file_size = program_file_info.st_size;
    char* program = (char*) calloc(file_size + MEMORY_FOR_LINE_ENDING, sizeof(char));
    assert(program);

    int file_descriptor = open(program_file, O_RDONLY);

    checking_opening_file(file_descriptor);

    reading_file(file_descriptor, program, file_size);

    close(file_descriptor);

    size_t action_amount = Counting_action(program, file_size);

    // printf("action aomount %lu \n", action_amount);

    char** action_address = (char**) calloc(action_amount + MEMORY_FOR_LINE_ENDING, sizeof(char**));
    Spliting_for_action(program, action_address, action_amount);

    data* byte_code = (data*) calloc(action_amount * 2, sizeof(int));
    int current_byte_index = 0;

    for (int action_index = 0; action_index < action_amount; action_index++) {
        char* current_action;
        char regis = '\0';
        int  number = 0;

        if (sscanf(action_address[action_index], "%m[A-Za-z] %d", &current_action, &number) == 1) {
            free(current_action);
            sscanf(action_address[action_index], "%m[A-Za-z] %cx", &current_action, &regis);
        }

        unsigned int code_current_action = stupid_hash(current_action);

        // printf("read numd: %d \n", number);
        // printf("read: %d pop: %d \n", code_current_action, POP);

        switch (code_current_action) {

            case (CODE_HTL):
                byte_code[current_byte_index++] = HTL;

                break;

            case (CODE_OUT):
                byte_code[current_byte_index++] = OUT;

                break;

            case (CODE_POP):
                if (regis >= 'a') {
                    byte_code[current_byte_index++] = POP_R; //Так?
                    byte_code[current_byte_index++] = regis- 'a' + 1;


                } else {
                    byte_code[current_byte_index++] = POP; //Так?

                }

                break;

            case (CODE_PUSH):
                if (regis >= 'a') {
                    byte_code[current_byte_index++] = PUSH_R;
                    byte_code[current_byte_index++] = regis - 'a' + 1;


                } else {
                    byte_code[current_byte_index++] = PUSH;
                    byte_code[current_byte_index++] = number;

                }

                break;

            case (CODE_ADD):
                byte_code[current_byte_index++] = ADD;

                break;

            case (CODE_SUB):
                byte_code[current_byte_index++] = SUB;

                break;

            case (CODE_DIV):
                byte_code[current_byte_index++] = DIV;

                break;

            case (CODE_MUL):
                byte_code[current_byte_index++] = MUL;

                break;
        }

        free(current_action);
    }


    printf("current index: %d \n", current_byte_index);
    for (int i = 0; i < AMOUNT_USED_BYTES; i++) {
        printf("%d ", byte_code[i]);
    }

    FILE* bite_code_file = fopen("byte_code_file.txt", "w");
    fwrite(byte_code, sizeof(byte_code[0]), AMOUNT_USED_BYTES, bite_code_file);

    free(action_address);
    free(program);
    free(byte_code);

}


unsigned int stupid_hash(const char* str) {
    unsigned int hash = 0;
    int cur_ind = 0, cur_symb = 0;
    while ((cur_symb = str[cur_ind]) != 0) {
        if (cur_symb >= 'A' && cur_symb <= 'Z') {
            hash *= 100;
            hash += (cur_symb - 'A');
        }
        cur_ind++;
    }

    return hash;
}
