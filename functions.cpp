#include "step_definitions.h"
#include "functions.h"

void round(const unsigned char cleartext[], const unsigned char key[], bool is_reset, unsigned char *&left_out, unsigned char *&right_out)
{
	static int times = 0;
	static unsigned char *left, *right;

	if(is_reset) times = 0;

	if(times == 0)
	{
		left = cleartext;
		right = cleartext[4];
	}

	if(times++ < 16)
	{
		unsigned char subkey[6], data_out[4];
		bool is_reset = false;
		if(times == 1) is_reset = true;
		generate_subkey(key, subkey, is_reset);
		feistel(right, subkey, data_out);
		exclusive_or(left, data_out, 4);
		data_out = left; left = right; right = data_out; left_out = left; right_out = right;
	}
}

void generate_subkey(const unsigned char key[], unsigned char subkey[], bool is_reset)
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
		ring_shift_left(times, data, shifted_data);
		compress_permutation(shifted_data, subkey);
	}
}
