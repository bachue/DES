#include "step_definitions.h"
#include "functions.h"
#include <iostream>

int main(int argc, const char *argv[])
{
	// unsigned char cleartext[8] = {85, 85, 85, 85, 85, 85, 85, 85};
	unsigned char cleartext[8] = {172, 183, 194, 205, 216, 227, 238, 249};
	unsigned char key[8] = {220, 221, 222, 223, 224, 225, 226, 227}, result[8], result2[8];

	std::cout << "bits:\n";
	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((cleartext[y] >> x) & 1) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	std::cout << std::endl;

	encrypt(cleartext, key, true, result);

	std::cout << "result:\n";
	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((result[y] >> x) & 1) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << std::endl;

	encrypt(result, key, false, result2);

	std::cout << "restore:\n";
	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			std::cout << ((result2[y] >> x) & 1) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	
	return 0;
}
