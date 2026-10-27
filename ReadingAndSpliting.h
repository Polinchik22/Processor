#ifndef READING_AND_SPLITING
#define READING_AND_SPLITING

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

void checking_opening_file(int file_descriptor);
void reading_file(int poem_file_descriptor, char* all_poem, off_t poem_size);
size_t Counting_action(char* all_poem, size_t poem_size);
int Spliting_for_action(char* all_poem, char* lines_address[], size_t lines_amount);


#endif //READING_AND_SPLITING
