#include <stdio.h>
#include <fcntl.h>

const int MEMORY_FOR_LINE_ENDING = 1;

struct Comand* Comands_list {
    {HTL,    0},
    {OUT,    1, outing},
    {POP,    1, poping}, //что делает просто pop
    {POP_R,  2, poping_r},
    {PUSH,   2, push},
    {PUSH_R, 2, push_r},
    {ADD,    1, addition},
    {SUB,    1, substraction},
    {DIV,    1, division},
    {MUL,    1, multiplying},
    {CALL}
}

struct Registers = {double ax, double bx, double cx, double dx};


int main(int argc, double* bait_code) {
    double registers  = [NaN, NaN, Nan, Nan];

    struct Stack_t program_stack = {};
    StackCtor("program_stack", &program_stack, 5);

    int pc = 0;
    struct comand current_comand = Comand_list[bait_code[pc]]; //TODO проверку на то что нет сегфолта

    while (current_comand.comand_name != HTL) {
        current_comand.operation(&program_stack, bait_code[pc+1], &registers);
        pc += current_comand.comand_size_to_bait_code;

        current_comand = Comand_list[pc];
    }
}





void outing(struct Stack_t* program_stack, double argument, double* regs) {
    double value = StackPop(program_stack);
    printf("%f ", value);

    StackPush(program_stack, value);
}


void poping(struct Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
}


void poping_r(struct Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
}


void push(struct Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
}


void push_r(struct Stack_t* program_stack, double argument, double* regs) {
    StackPop(program_stack);
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

    StackPush(Code, value_1 * value_2);
}

void division(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    if (value_2 != 0) {
        StackPush(Code, value_2 / value_1);
    }
}

void multiplying(struct Stack_t* program_stack, double argument, double* regs){
    double value_1 = StackPop(program_stack);
    double value_2 = StackPop(program_stack);

    if (value_2 != 0) {
        StackPush(program_stack, value_2 * value_1);
    }
}
