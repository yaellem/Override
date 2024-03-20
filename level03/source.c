#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void 	decrypt(int j)
{
// ebp = 0xffffd6a8
	char *pushed_reg[0x8];	// 0xffffd6a0
// stackprotect: ebp + 0xc = gs:0x14
	int	stack_protector = 0x9936ee00; // 0xffffd69c
	char tmp;				// 0xffffd69b	ebp - 0xd
	char w[4];				// 0xffffd697 	ebp - 0x11
	char x[4];				// 0xffffd693	ebp - 0x15
	char y[4];				// 0xffffd68f	ebp - 0x19
	char z[4];				// 0xffffd68b	ebp - 0x1d
	char s1[0x3];
	int	a;					// 0xffffd684	ebp - 0x24
	int b;					// 0xffffd680	ebp - 0x28
	int c;					// 0xffffd67c	ebp - 0x2c
	const char *congrat = "Congratulations";
	char s2[0x1c];			// 0xffffd660	ebp - 0x48

	w[0] = '\x7d';
	w[1] = '\x7c';
	w[2] = '\x61';
	w[3] = '\x33';
	x[0] = '\x7e';
	x[1] = '\x73';
	x[2] = '\x66';
	x[3] = '\x7b';
	y[0] = '\x60';
	y[1] = '\x73';
	y[2] = '\x66';
	y[3] = '\x67';
	z[0] = '\x51';
	z[1] = '\x7d';
	z[2] = '\x7c';
	z[3] = '\x75';

	tmp = '\0';
	c = 0;
	while (z[c] != 0 && c <= 0xffffffff)
		c++;
	a = c - 1;
	b = 0;
	while ((unsigned int)b < (unsigned int)a)
	{
		z[b]  = z[b] ^ j;
		b++;
	}
	b = 0;
	while (b < 0x11)
	{
		if ((z[b++]) != *congrat)
			break;
		congrat++;
	}
	if (z[b] != *congrat)
		puts("\nInvalid Password");
	else
		system("/bin/sh");

//	if (stack_protector == in_GS_OFFSET + 0x14)
//		return;
		
//	__stack_chk_fail();
}

void	test(int i, int j)
{
// ebp = 0xffffd6d8
	char s1[0xc];	// 0xffffd6cc
	char s2[0x1c];	// 0xffffd6b0

	j = j - i;
	switch (j)
	{
		default:
			decrypt(rand());
			break;
		case 0x1:
			decrypt(j);
			break;	
		case 0x2:
			decrypt(j);
			break;	
		case 0x3:
			decrypt(j);
			break;	
		case 0x4:
			decrypt(j);
			break;	
		case 0x5:
			decrypt(j);
			break;	
		case 0x6:
			decrypt(j);
			break;	
		case 0x7:
			decrypt(j);
			break;	
		case 0x8:
			decrypt(j);
			break;	
		case 0x9:
			decrypt(j);
			break;	
		case 0x10:
			decrypt(j);
			break;	
		case 0x11:
			decrypt(j);
			break;	
		case 0x12:
			decrypt(j);
			break;	
		case 0x13:
			decrypt(j);
			break;	
		case 0x14:
			decrypt(j);
			break;	
		case 0x15:
			decrypt(j);
			break;	

//		((void(*)(void))*(&tab + (j * 4)))();
	}
	return ;	
}

__attribute__((force_align_arg_pointer)) int main()
{
// ebp = 0xffffd708
// esp = 0xffffd700
	int i;			// 0xffffd6fc
	char s[0x1c];	// 0xffffd6e0

	srand(time(0x0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");	
	scanf("%d", &i);
	test(i, 0x1337d00d);
	return 0;
}
