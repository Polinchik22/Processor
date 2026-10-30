#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>



#include "structures.h"
#include "ReadingAndSpliting.h"
#include "Stack_t.h"


#define StackCtor(stack_name, stack, capacity) StackCtor (__FILE__,      \
                                                        __FUNCTION__,  \
                                                        __LINE__,      \
                                                        stack_name, \
                                                        stack, \
                                                        capacity)

typedef unsigned int data;

void outing         (struct Stack_t* program_stack, double argument, double* regs);
void poping         (struct Stack_t* program_stack, double argument, double* regs);
void poping_r       (struct Stack_t* program_stack, double argument, double* regs);
void push           (struct Stack_t* program_stack, double argument, double* regs);
void push_r         (struct Stack_t* program_stack, double argument, double* regs);
void addition       (struct Stack_t* program_stack, double argument, double* regs);
void substraction   (struct Stack_t* program_stack, double argument, double* regs);
void multiplication (struct Stack_t* program_stack, double argument, double* regs);
void division       (struct Stack_t* program_stack, double argument, double* regs);
void multiplying    (struct Stack_t* program_stack, double argument, double* regs);


const int MEMORY_FOR_LINE_ENDING = 1;

struct Comand Comands_list[COMANDS_AMOUNT] = {
    {HTL,    0, nullptr},
    {OUT,    1, outing},
    {POP,    1, poping}, //что делает просто pop
    {POP_R,  2, poping_r},
    {PUSH,   2, push},
    {PUSH_R, 2, push_r},
    {ADD,    1, addition},
    {SUB,    1, substraction},
    {DIV,    1, division},
    {MUL,    1, multiplying},
    {CALL,   1, nullptr}
};

struct Registers_t {double ax; double bx; double cx; double dx;};


int main(int argc, char** argv) {
    srand(time(NULL));

    char* byte_code_file = argv[1];
    struct stat byte_code_file_info = {};
    stat(byte_code_file, &byte_code_file_info);

    off_t file_size = byte_code_file_info.st_size;
    char* bin_byte_code = (char*) calloc(file_size + MEMORY_FOR_LINE_ENDING, sizeof(char));
    assert(bin_byte_code);

    int file_descriptor = open(byte_code_file, O_RDONLY);
    checking_opening_file(file_descriptor);

    reading_file(file_descriptor, bin_byte_code, file_size);
    close(file_descriptor);


    int byte_code_len = file_size/sizeof(data);
    data* byte_code = (data*) bin_byte_code;


    printf("array size: %d \n", byte_code_len);
    for (int i = 0; i < byte_code_len; i++) {
        printf("%d ", byte_code[i]);
    }

    Stack_t program_stack = {};
    StackCtor("program_stack", &program_stack, 5);
    StackPush(&program_stack, 5.5);
    Printing_stack(&program_stack);

    int pc = 0;
    // struct Registers_t Registers = {};
    double Registers[4] = {};
    struct Comand current_comand = Comands_list[byte_code[pc]]; //TODO проверку на то что нет сегфолта

    while (current_comand.comand_name != HTL) {
        current_comand.operation(&program_stack, byte_code[pc+1], Registers);
        pc += current_comand.comand_size_to_bait_code;

        current_comand = Comands_list[byte_code[pc]];
    }

    // StackDtor(&program_stack);
    free(bin_byte_code);
}



void outing(Stack_t* program_stack, double argument, double* regs) {
    double value = StackPop(program_stack);
    printf("%f ", value);

    StackPush(program_stack, value);
}


void poping(Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
}


void poping_r(Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
}


void push(Stack_t* program_stack, double argument, double* regs) {
    printf("push arg: %f \n", argument);
    Printing_stack(program_stack);
    StackPush(program_stack, argument);
}


void push_r(struct Stack_t* program_stack, double argument, double* regs) {
    StackPush(program_stack, regs[argument]);
}


void addition(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    StackPush(program_stack, value_1 + value_2);
}

void substraction(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    StackPush(program_stack, value_2 - value_1);
}

void multiplication(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    StackPush(program_stack, value_1 * value_2);
}

void division(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    if (value_2 != 0) {
        StackPush(program_stack, value_2 / value_1);
    }
}

void multiplying(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    if (value_2 != 0) {
        StackPush(program_stack, value_2 * value_1);
    }
}
