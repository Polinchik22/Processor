#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

unsigned int stupid_hash(const char* str);


int main() {
    const char* comand_namess[COMANDS_AMOUNT]
       {"HTL   ",
        "OUT   ",
        "POP   ",
        "POP_R ",
        "PUSH  ",
        "PUSH_R",
        "ADD   ",
        "SUB   ",
        "DIV   ",
        "MUL   ",
        "CALL  "
    };

    for (int i = 0; i < COMANDS_AMOUNT; i++) {
        printf("%x \n", stupid_hash(comand_namess[i]));
    }
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
