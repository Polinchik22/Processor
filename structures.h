#ifndef STRUCTURES
#define STRUCTURES


enum Comand_names {
    HTL    = 0x118e7 ,
    OUT    = 0x22ac3 ,
    POP    = 0x24f77 ,
    POP_R  = 0xe70a8d ,
    PUSH   = 0xe7f60f ,
    PUSH_R = 0x5a9c1ded ,
    ADD    = 0x12f ,
    SUB    = 0x2c6f1 ,
    DIV    = 0x7865 ,
    MUL    = 0x1dc9b ,
    CALL   = 0x1e88d7
};

struct Comand {
        Comand_names comand_name;
        int comand_size_to_bait_code;
        void (*operation)(struct Stack_t* program_stack, double argument, double* regs);
        int hash;
        //get аргкмент труктруу с информацией
};

// const int COMANDS_AMOUNT = sizeof(Comands_list/Comands_list[0]);
const int COMANDS_AMOUNT = 11;


// Comand_names* comand_names[11] {
//                                             HTL   ,
//                                             OUT   ,
//                                             POP   ,
//                                             POP_R ,
//                                             PUSH  ,
//                                             PUSH_R,
//                                             ADD   ,
//                                             SUB   ,
//                                             DIV   ,
//                                             MUL   ,
//                                             CALL  };

// const int COMANDS_AMOUNT = 11;


#endif //STRUCTURES
