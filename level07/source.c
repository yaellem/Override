#include <stdio.h>
#include <string.h>
#include <inttypes.h>

// all the address where eip is stored, are at an offset from the base addr, 
// which, divided by 4, gives 0 after modulo 3...
void	clear_stdin()
{
// eip = 0xffffd4bc
// ebp = 0xffffd4b8
	char s[0x5];
	int i;			// 0xffffd4af	-0x9(ebp)
	char s1[0xf];   // 0xffffd4a0

	i = 0;
	
	while (i != '\n')
	{
		if (i == -1)
			return;
		i = getchar();
	}
	return ;
}

int get_unum(void)
{
// eip = 0xffffd4ec
// ebp = 0xffffd4e8
	int tab[3];		// 0xffffd4dc	-0xc(ebp)
	char s[0x1c];	// 0xffffd4c0

	tab[0] = 0;
//	fflush(stdout);
	scanf("%u", &tab);
	clear_stdin();
	return tab[0];
}

int store_number(uint64_t param)
{
// eip = 0xffffd51c
// ebp = 0xffffd518
	int i;			//	0xffffd514 -0x4(ebp)
	int j;			//	0xffffd510 -0x8(ebp)
	int index = 0;	//	0xffffd50c -0xc(ebp)
	int number = 0;	//	0xffffd508 -0x10(ebp)
	char s[0x18];	//  0xffffd4f0

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();
	if (index % 3 == 0 || number >> 0x18 == 0xb7)
	{
		puts(" *** ERROR! ***");
    	puts("   This index is reserved for wil!");
    	puts(" *** ERROR! ***");
		return 1;
	}
// system
//					 printf .got.plt 0x804a000		% 3
//					 scanf  .got.plt 0x804a024  (-1040108872)
//					getchar .got.plt 0x804a008	
//					fflush  .got.plt 0x804a004
//					fgets   .got.plt 0x804a00c		% 3
//							main eip 0xffffd70c		% 3
//						clear_stdin  0xffffd4bc		% 3
//						get_unum     0xffffd4ec		% 3
// param = 0xffffd544	target eip = 0xffffd51c	(-10) % 3 
// index == (eip - param) / 4 = 456 / 4 = 114 (-1040108879 -1040108880)
// number == 0xf7e6aed0 = 4159090384
// number == 0x08048630 = 134514224 function addr
// index % 3 == 0 so:
//		let's  write 0xaed00000 at 0xffffd70e
//		let's  write 0x0000f7e6 at 0xffffd70a


// /bin/sh
//					getchar param stack addr: 0xffffd4a0
//					 fflush param stack addr: 0xffffd4c0 	(-33)
//							main eip + 8 0xffffd714
// param = 0xffffd544	target eip + 8 = 0xffffd524
// index = (eip - param + 8) / 4 = 464 / 4 = -8(4294967288)  116 (-41)
// number = 0xf7f897ec = 4160264172
	*(unsigned int *)(param + index * 4) = number;
	return 0;
}

int	read_number(uint64_t param)
{
// eip = 0xffffd51c
// ebp = 0xffffd518
	uint64_t i;
	uint64_t j;
	uint64_t index = 0;	//	-0xc(ebp)
	char s[0x1c];	// 0xffffd4f0

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, *(unsigned int*)(index * 4 + param));
	return 0;
}

int main(int ac, char **av, char **env)
{
// 0xffffd730 x
// 0xffffd72c v
// 0xffffd728 v
// 0xffffd724 x 
// 0xffffd720 v
// 0xffffd71c v
// 0xffffd718 x 
// 0xffffd714 v
// 0xffffd710 v
// eip = 0xffffd70c x
// ebp = 0xffffd708
	uint64_t edi;			// 0xffffd704
	uint64_t esi;			// 0xffffd700
	uint64_t ebx;			// 0xffffd6fc
	char align[0xc];		// 0xffffd6f0
	uint64_t stack_protect;	// 0xffffd6ec	0x1cc(esp)
	uint64_t	a = 0;		// 0xffffd6e8	0x1c8(esp)
	uint64_t	b = 0;		// 0xffffd6e4	0x1c4(esp)
	uint64_t	c = 0;		// 0xffffd6e0	0x1c0(esp)
	uint64_t	d = 0;		// 0xffffd6dc	0x1bc(esp)
	uint64_t	e = 0;		// 0xffffd6d8	0x1b8(esp)
	uint64_t	f = 0;		// 0xffffd6d4	0x1b4(esp)
	uint64_t tab[0x64];		// 0xffffd544	0x24(esp)
	uint64_t	g;			// 0xffffd540	0x20(esp)
	char **save_av;			// 0xffffd53c	0x1c(esp)
	char **save_env;		// 0xffffd538	0x18(esp)
	uint64_t idx;			// 0xffffd534	0x14(esp)
	char fill[0x14];		// 0xffffd520	(esp)

	printf("address e = %p\n", &e);
	save_av = av;
	save_env = env;
	for (int i = 0; i < 0x64; i++)
		tab[i] = 0;
	while (*save_av != NULL)
	{
		memset(*save_av, 0, strlen(*save_av));
		save_av++;
	}
	while (*save_env != NULL)
	{
		memset(*save_env, 0, strlen(*save_env));
		save_env++;
	}
	puts("----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                           \n    store - store a number into the data storage    \n    read   - read a number from the data storage     \n    quit  - exit the program                         \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n");
	while (1)
	{
		printf("Input command: ");
		f = 1;
		fgets((char *)(&e), 0x14, stdin);
		g = (uint64_t)(&e);
		idx = 0xffffffffffffffff;
		while (*(char*)(g) != '\0' && idx != 0)
		{
			idx--;
			g++;
		}
		idx = ~idx;
// store 0 where is the '\n'	
		*(char*)((uint64_t)(&e) + idx - 1) = 0;
		if (strncmp((char*)(&e), "store", 0x5) == 0)
			f = store_number(&tab);
		else if (strncmp((char*)(&e), "read", 0x4) == 0)
			f = read_number(&tab);
		else if (strncmp((char*)(&e), "quit", 0x4) == 0)
			return 0;
		if (f == 0)
			printf(" Completed %s command successfully\n",(char*)&e);
		else
			printf(" Failed to do %s command\n",(char*)&e);
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
	}
	return 0;
}














