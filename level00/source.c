#include <stdio.h>
#include <stdlib.h>

__attribute__((force_align_arg_pointer)) int main()
{
	int	i; // stack = stack - 4
	char s[0x1c]; // stack = stack - 0x1c = -0x20
	
	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &i);
	printf("%p\n", i);
	if (i == 0x149c)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	else
		puts("\nInvalid Password!");	
	return 0;
}
