#include "lib.h"
#include "table.h"
#include "string.h"
// #include <iostream>

#define GET_BIT(data, n) ((data & (1 << (8 - n))) >> (8 - n))
#define GET_2BIT(data, n) ((data & (0b11 << (7 - n))) >> (7 - n))
#define GET_BYTE_IN_INT(data, n) ((data & (0b11111111 << (24 - n))) >> (24 - n))
#define GET_4BIT_IN_INT(data, n) ((data & (0b1111 << (28 - n))) >> (28 - n))

void initial_permutation(const unsigned char data[], unsigned char result[])
{
	const int table_ip[64] = TABLE_IP;
	permutation(table_ip, 64, data, result);
}

void enlarge_permutation(const unsigned char data[], unsigned char result[])
{
	const int table_e[48] = TABLE_E;
	permutation(table_e, 48, data, result);
}

void select_permutation(const unsigned char data[], unsigned char result[])
{
	unsigned char select_n_permutation(const unsigned char, const int);
	long long res = 0;
	memset(result, 0, 4);
	for(int i = 0; i < 6; ++i)
	{
		res |= (long long)data[i] << i * 8;
	}
	for(int i = 0; i < 8; ++i)
	{
		result[i / 2] |= select_n_permutation((res >> i * 6) & 0b00111111, i) << i % 2 * 4;
	}
}

unsigned char select_n_permutation(const unsigned char input, const int n)
{
	const int table_s[8][64] = TABLE_S;
	const int y = ((input & 0b100000) >> 4) | (input & 0b000001);
	const int x = (input & 0b011110) >> 1;
	return (unsigned char) table_s[n][y * 16 + x];
}

void pure_permutation(const unsigned char data[], unsigned char result[])
{
	const int table_pp[32] = TABLE_PP;
	permutation(table_pp, 32, data, result);
}

void final_permutation(const unsigned char data[], unsigned char result[])
{
	const int table_fp[64] = TABLE_FP;
	permutation(table_fp, 64, data, result);
}

void select_change_permutation(const unsigned char data[], unsigned char result[])
{
	const int table_pc_1[56] = TABLE_PC_1;
	permutation(table_pc_1, 56, data, result);
}

void ring_shift_left(const int n, const unsigned char data[], unsigned char result[])
{
	const int table_rsl[16] = TABLE_RSL;
	const int result_offset[] = {4, 12, 20, 0, 8, 16, 24};
	memset(result, 0, 7);

	unsigned temp_var = 0, temp_c;
	if(table_rsl[n] == 1) temp_c = GET_BIT(data[0], 5);
	else if(table_rsl[n] == 2) temp_c = GET_2BIT(data[0], 5);

	for(int i = 0; i <= 2; ++i)
	{
		const int offset[] = {8, 8, 4};
		temp_var |= data[i];
		temp_var <<= offset[i];
	}
	temp_var |= (data[3] >> 4);
	temp_var <<= table_rsl[n];
	
	for(int i = 0; i <= 2; ++i)
	{
		result[i] = GET_BYTE_IN_INT(temp_var, result_offset[i]);
	}
	result[3] = ((temp_var & (0b11111111 >> 4) | temp_c) << 4);

	temp_var = 0;
	if(table_rsl[n] == 1) temp_c = GET_BIT(data[3], 5);
	else if(table_rsl[n] == 2) temp_c = GET_2BIT(data[3], 5);
	temp_var |= GET_4BIT_IN_INT(data[3], 28);
	for(int i = 4; i <= 6; ++i)
	{
		temp_var <<= 8;
		temp_var |= data[i];
	}
	temp_var <<= table_rsl[n];

	result[3] |= GET_4BIT_IN_INT(temp_var, 4);
	for(int i = 4; i <= 6; ++i)
	{
		result[i] = GET_BYTE_IN_INT(temp_var, result_offset[i]);
	}
	result[6] |= temp_c;
}
