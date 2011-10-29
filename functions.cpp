#include "step_definitions.h"
#include "functions.h"
#include "lib.h"
#include "string.h"

void encrypt(const unsigned char cleartext[], const unsigned char key[], const bool is_encrypt, unsigned char result[])
{
	unsigned char *left, *right;
	unsigned char after_initial_permutation[8];
	initial_permutation(cleartext, after_initial_permutation);
	for(int i = 0; i < 16; ++i)
	{
		round(after_initial_permutation, key, is_encrypt, i == 0 ? true : false, left, right);
	}
	memxchg(after_initial_permutation, after_initial_permutation + 4, 4);
	final_permutation(after_initial_permutation, result);
}

void generate_subkey(const unsigned char key[], unsigned char subkey[], const bool is_encrypt, const bool is_reset)
{
	static int times = 0;
	static unsigned char stored_subkey[16][7];

	if(is_reset) times = 0;

	if(times == 0)
	{
		unsigned char data[7], shifted_data[7];
		select_change_permutation(key, data);
		for(int i = 0; i < 16; ++i)
		{
			ring_shift_left(i, data, shifted_data);
			if(i != 15) memcpy(data, shifted_data, 7);
			compress_permutation(shifted_data, stored_subkey[i]);
		}
	}

	memcpy(subkey, stored_subkey[is_encrypt ? times : 16 - 1 - times ], 7);

	++times;
}
