#ifndef __STEP_DEFINITIONS_H
#define __STEP_DEFINITIONS_H

void initial_permutation(const unsigned char[], unsigned char[]);
void feistel(const unsigned char[], const unsigned char[], unsigned char[]);
void enlarge_permutation(const unsigned char[], unsigned char[]);
void exclusive_or(const unsigned char[], const unsigned char[], const int, unsigned char[]);
void select_permutation(const unsigned char[], unsigned char[]);
unsigned char select_n_permutation(const unsigned char, const int);
void pure_permutation(const unsigned char[], unsigned char[]);
void final_permutation(const unsigned char[], unsigned char[]);
void select_change_permutation(const unsigned char[], unsigned char[]);
void ring_shift_left(const int, const unsigned char[], unsigned char[]);
void compress_permutation(const unsigned char[], unsigned char[]);

#endif
