#include "string.h"

void move_bit_according_permutation_table(const int, const int[], const int, const int, const unsigned char[], unsigned char[]);

void permutation(const int permutation_table[], const int input_size, const int output_size, const unsigned char input[], unsigned char output[])
{
	memset(output, 0, output_size / 8);
	for(int i = 0; i < output_size; ++i)
	{
		move_bit_according_permutation_table(i, permutation_table, input_size, output_size, input, output);
	}
}

inline
void move_bit_according_permutation_table(const int i, 
			const int permutation_table[], const int input_size, const int output_size, const unsigned char input[], unsigned char output[])
{
	const int SIZEOF_CHAR = 8 * sizeof(unsigned char);
	output[ i / SIZEOF_CHAR ] |= (input[ (permutation_table[i] -1) / SIZEOF_CHAR ] >> (input_size - permutation_table[i]) % SIZEOF_CHAR & 1) << (output_size - i - 1) % SIZEOF_CHAR;
}
