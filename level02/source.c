#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
//	edi == ac		 rsi == av

// rbp = rsp = 0x7fffffffe5a0
	FILE *file_flux;// 0x7fffffffe598
	int	 y;			// 0x7fffffffe594
	char s0[0x64];  // 0x7fffffffe530
	char s1[0x30];  // 0x7fffffffe500
	char s2[0x70];  // 0x7fffffffe490
	int  my_ac;     // 0x7fffffffe48c
	char my_av[0xC];// 0x7fffffffe480

	my_ac = ac;
	my_av = av;
	for (int i = 0; i < (0xC * 8)/* 0x60 */ ; i++)
		s0[i] = 0;
	*(s0 + 0x60) = 0;

	for (int i = 0; i < (0x5 * 8)/* 0x28 */ ; i++)
		s1[i] = 0;
	*(s1 + 0x28) = 0;

	for (int i = 0; i < (0xC * 8)/* 0x60 */ ; i++)
		s2[i] = 0;
	*(s2 + 0x60) = 0;

	file_flux = 0;
	y = 0;
	file_flux = fopen("/home/users/level03/.pass", "r");
	if (file_flux == 0)
	{
		fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
		exit(1);
	}
	y = fread(s1, 1, 0x29, file_flux);
	*(s1 + strcspn(s1, "\n")) = 0;
	if (y == 0)
	{
		fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
		fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
		exit(1);
	}
	fclose(file_flux);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	
	printf("--[ Username: ");
	fgets(s0, 0x64, stdin);
	*(s0 + strcspn(s0, "\n")) = 0;
	
	printf("--[ Password: ");
	fgets(s2, 0x64, stdin);
	*(s2 + strcspn(s2, "\n")) = 0;
	
	puts("*****************************************");
	
	if (strncmp(s1, s2, 0x29) == 0)
	{
		printf("Greetings, %s!\n",s0);
		system("/bin/sh");
		return 0;
	}	
	printf(s0);
	puts(" does not have access!");
	exit(1);
}
