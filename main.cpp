#include "step_definitions.h"
#include "functions.h"
#include <string.h>
#include <unistd.h>

#define STDOUT 1

int main(int argc, const char *argv[])
{
	// unsigned char cleartext[8] = {85, 85, 85, 85, 85, 85, 85, 85};
	unsigned char cleartext[8] = {172, 183, 194, 205, 216, 227, 238, 249};
	unsigned char key[8] = {220, 221, 222, 223, 224, 225, 226, 227}, result[8], restore[8];

	char bits_str[8][16], result_str[8][16], restore_str[8][16];

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			bits_str[y][16 - 2 * x - 2] = ((cleartext[y] >> x) & 1) ? '1' : '0';
			bits_str[y][16 - 2 * x - 1] = ' ';
		}
		bits_str[y][15] = '\n';
	}

	encrypt(cleartext, key, true, result);

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			result_str[y][16 - 2 * x - 2] = ((result[y] >> x) & 1) ? '1' : '0';
			result_str[y][16 - 2 * x - 1] = ' ';
		}
		result_str[y][15] = '\n';
	}

	encrypt(result, key, false, restore);

	for(int y = 0; y < 8; ++y)
	{
		for(int x = 7; x >= 0; --x)
		{
			restore_str[y][16 - 2 * x - 2] = ((restore[y] >> x) & 1) ? '1' : '0';
			restore_str[y][16 - 2 * x - 1] = ' ';
		}
		restore_str[y][15] = '\n';
	}

	write(STDOUT, "bits:\n", strlen("bits:\n"));
	write(STDOUT, bits_str, 8 * 16);
	write(STDOUT, "\nresult:\n", strlen("\nresult:\n"));
	write(STDOUT, result_str, 8 * 16);
	write(STDOUT, "\nrestore:\n", strlen("\nrestore:\n"));
	write(STDOUT, restore_str, 8 * 16);
	
	return 0;
}
