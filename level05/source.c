#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
__attribute__((force_align_arg_pointer)) void main()
{
// ebp = 0xffffd708 0xffffd738
	char pushed_reg[0x8];	// 0xffffd700
	int i = 0;				// 0xffffd6fc
	char s0[0x6c];			// 0xffffd698 0xFFFFD694 
	int j;					// 0xffffd694
	int k;					// 0xffffd690
	int len = 0;			// 0xffffd68c
	char s2[0x1c];			// 0xffffd670

	fgets(s0, 0x64, stdin);
	while (s0[len])
		len++;
	while (i < len)
	{
		if (s0[i] >= 0x41 && s0[i] <= 0x59)
			s0[i] = s0[i] ^ 0x20;
		i++;
	}
	printf(s0);
	exit(0);
}
