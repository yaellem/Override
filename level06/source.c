#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth(char *log, int serial)
{
// ebp = 0xffffd6a8
	int i;			// 0xffffd69c	-0x0c (ebp)
	int	key;		// 0xffffd698	-0x10 (ebp)
	int	j;			// 0xffffd694	-0x14 (ebp)
	char s1[0x14];	// 0xffffd680	(esp)

	*(log + strcspn(log, "\n")) = '\0';
	i = strnlen(log, 0x20);
	if (i <= 5)
		return 1;
	if (ptrace(PT_TRACEME, 0, 1, 0) == -1)
	{
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return 1;
	}
// exemple: log = 012345
	key = (int)((log[3]) ^ 0x1337) + 0x5eeded;
// exemple: key = 0x33 ^ 0x1337 = 0x1304 + 0x5eeded = 0x5F00F1	
	j = 0;
	while (j < i)
	{
		if (log[j] < ' ')
			return 1;
/*		Real op
		ecx = log[j] ^ key; 
		edx = (0x88233b2b * ecx) >> 32; 
		eax = ((((ecx - edx) >> 1) + edx) >> 10) * 0x539;
		eax = edx - eax; 
*/

//		Ghidra simplification
		key = key + ((log[j] ^ key) % 0x539) ;
// 		Exemple
// 0 0x5F00F1 + (0x30 ^ 0x5F00F1)0x5F00C1 % 0x539 = + 0x411 = 0x5F0502
// 1 0x5F0502 + (0x31 ^ 0x5F0502)0x5F0533 % 0x539 = + 0x34a = 0x5F084C
// 2 0x5F084C + (0x32 ^ 0x5F084C)0x5F087E % 0x539 = + 0x15c = 0x5F09A8
// 3 0x5F09A8 + (0x33 ^ 0x5F09A8)0x5F099B % 0x539 = + 0x279 = 0x5F0C21
// 4 0x5F0C21 + (0x34 ^ 0x5F0C21)0x5F0C15 % 0x539 = + 0x4f3 = 0x5F1114
// 5 0x5F1114 + (0x35 ^ 0x5F1114)0x5F1121 % 0x539 = + 0x4c6 = 0x5F15DA
		j++; 
	}
	if (serial != key)
		return 1;
	return 0;
}

int main(int ac, char **av)
{
//ebp = 0xffffd708
//esp = 0xffffd700
	int	stack_protect;		// 0xffffd6fc	0x4c (esp)
	char log[0x10];			// 0xffffd6dc	0x2c (esp)
	int	 serial;			// 0xffffd6d8	0x28 (esp)
	char *save = (char*)av; // 0xffffd6cc	0x1c (esp)
	char s2[0x1c];			// 0xffffd6b0 	(esp)

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	
	fgets(log, 0x20, stdin);
	
	puts("***********************************");
  	puts("***** NEW ACCOUNT DETECTED ********");
  	puts("***********************************");
  	printf("-> Enter Serial: ");
	scanf("%u", serial);
	if (auth(log, serial) == 0)
	{
		puts("Authenticated!");
    	system("/bin/sh");
		return 0;
	}
	return 1;
}
