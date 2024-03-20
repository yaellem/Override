#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	secret_backdoor() // 0x000055555555488c
{
// rbp = 0x7fffffffe5c8
	char s[128];	// 0x7FFFFFFFE548
  
	fgets(s,0x80,stdin);
	system(s);
	return;
}

void	set_username(char *param)
{
// rip = 0x7fffffffe4f8
// rbp = 0x7fffffffe4f0
	int		i;				// 0x7fffffffe4ec
	char	s[0x8c];		// 0x7fffffffe460
	char	*save;			// 0x7fffffffe458
	uint64_t	j;			// 0x7fffffffe450

	save = param;

	for (int c = 0; c < 0x80; c++)
		s[c] = 0;
	
	puts(">: Enter your username");
	printf(">>: ");
	fgets((char *)&s, 0x80, stdin);
	
	i = 0;
	while (i <= 0x28 && s[(long)i] != '\0')
	{
		param[0x8c + (long)i] = s[(long)i];
		i++;	
	}

	printf(">: Welcome, %s", param + 0x8c);
	return ;
}

void	set_msg(char *param)
{
// rip = 0x7fffffffe4f8
// rbp = 0x7fffffffe4f0

	char s[0x400];			// 0x7fffffffe0f0 
	char *save;				// 0x7fffffffe0e8
	uint64_t j;				// 0x7fffffffe0e0

	save = param;
		
	for (int i = 0; i != 0x400 ; i++)
		s[i] = 0;
	
	puts(">: Msg @Unix-Dude");
  	printf(">>: ");
	fgets(s, 0x400, stdin);

/*								0x8c				*/
	strncpy(param, s, (long)*(int*)(param + 0xb4));
	return ;
}

void	handle_msg()
{
//  rip = 0x7fffffffe5c8
//	rbp = 0x7fffffffe5c0
	uint64_t buf;			// 0x7fffffffe5b8
	uint32_t LEN = 0x8c;	// 0x7fffffffe5b4
	uint64_t i = 0;			// 0x7fffffffe5ac
	uint64_t j = 0;			// 0x7fffffffe5a4
	uint64_t k = 0;			// 0x7fffffffe59c
	uint64_t l = 0;			// 0x7fffffffe594
	uint64_t m = 0;			// 0x7fffffffe58c
	char s[0x8c];	// 0x7fffffffe500

	set_username((char *)&s);
	set_msg((char *)&s);
	puts(">: Msg sent!");
	return ;
}

int		main()
{
// rip = 0x7fffffffe5d8
// rbp = 0x7fffffffe5d0
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
	handle_msg();
	return 0;
}
