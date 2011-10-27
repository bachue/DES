#include "step_definitions.h"
#include "functions.h"

void encrypt(const unsigned char cleartext[], const unsigned char key[], const bool is_encrypt, unsigned char result[])
{
	unsigned char *left, *right;
	unsigned char after_initial_permutation[8];
	initial_permutation(cleartext, after_initial_permutation);
	for(int i = 0; i < 16; ++i)
	{
		round(after_initial_permutation, key, is_encrypt, false, left, right);
	}
	for(int i = 0; i < 4; ++i)
	{
		char tmp = after_initial_permutation[i]; 
		after_initial_permutation[i] = after_initial_permutation[i + 4]; 
		after_initial_permutation[i + 4] = tmp;
	}
	final_permutation(after_initial_permutation, result);
}

void generate_subkey(const unsigned char key[], unsigned char subkey[], const bool is_encrypt, const bool is_reset)
{
	static int times = 0;
	static unsigned char data[7];

	if(is_reset) times = 0;

	if(times == 0)
	{
		select_change_permutation(key, data);
	}

	if(times++ < 16)
	{
		unsigned char shifted_data[7];
		if(is_encrypt) ring_shift_left(times, data, shifted_data);
		else ring_shift_left(15 - times, data, shifted_data);
		compress_permutation(shifted_data, subkey);
	}
}
