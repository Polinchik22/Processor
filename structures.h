#ifndef STRUCTURES
#define STRUCTURES


enum Codes_Comand_names {
    CODE_HTL    = 0x118e7 ,
    CODE_OUT    = 0x22ac3 ,
    CODE_POP    = 0x24f77 ,
    CODE_POP_R  = 0xe70a8d ,
    CODE_PUSH   = 0xe7f60f ,
    CODE_PUSH_R = 0x5a9c1ded ,
    CODE_ADD    = 0x12f ,
    CODE_SUB    = 0x2c6f1 ,
    CODE_DIV    = 0x7865 ,
    CODE_MUL    = 0x1dc9b ,
    CODE_CALL   = 0x1e88d7
};

enum Comand_names {
    HTL   ,
    OUT   ,
    POP   ,
    POP_R ,
    PUSH  ,
    PUSH_R,
    ADD   ,
    SUB   ,
    DIV   ,
    MUL   ,
    CALL
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
