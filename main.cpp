#include "step_definitions.h"
#include <iostream>

int main(int argc, const char *argv[])
{
	unsigned char keys[] = {
		1,   2,  3,  4,  5,  6,  7,  8
	};

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((keys[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char after_initial_permutation[8];

	initial_permutation(keys, after_initial_permutation);

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((after_initial_permutation[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char *right = &after_initial_permutation[4];

	unsigned char after_enlarge_permutation[6];

	enlarge_permutation(right, after_enlarge_permutation);

	for(int y = 0; y < 6; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((after_enlarge_permutation[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char after_select_permutation[4];

	select_permutation(after_enlarge_permutation, after_select_permutation);

	for(int y = 0; y < 4; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((after_select_permutation[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char after_pure_permutation[4];

	pure_permutation(after_select_permutation, after_pure_permutation);

	for(int y = 0; y < 4; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((after_pure_permutation[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char after_final_permutation[8];

	pure_permutation(after_initial_permutation, after_final_permutation);

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((after_final_permutation[y] >> x) & 1) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unsigned char after_select_change_permutation[7];

	select_change_permutation(keys, after_select_change_permutation);

	unsigned char in[8] = {187, 187, 187, 187, 187, 187, 187}, out[8];

	int i = 0;
	for(int y = 0; y < 7; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((in[y] >> x) & 1) << ' ';
			if(i++ == 27) std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;

	ring_shift_left(2, in, out);

	i = 0;
	for(int y = 0; y < 7; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((out[y] >> x) & 1) << ' ';
			if(i++ == 27) std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;
}

