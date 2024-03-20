#include <stdio.h>

char	*a_user_name; // 0x804a040


int	verify_user_name()
{
// ebp = 0xffffd698
	int i;
	char	*c = "dat_will";
// esp = 0xffffd690
	char	s[0x10]; // 0xffffd680
	puts("verifying username....\n");
	i = 0;
	while (a_user_name[i] == c[i] && i <= 7)
		i++	;
	return (a_user_name[i] - c[i]);
}

int	verify_user_pass(char *s1)
{
// ebp = 0xffffd698
	int i;
	char *c = "admin"; 
// esp = 0xffffd690
	esi = s1
	edi = c
	i = 
	while (s1[i] == c[i] && i <= 5)
		i++;
	return (s1[i] - c[i]);
}

__attribute__((force_align_arg_pointer)) int main()
{
// ebp = 0xffffd708
	char pushed_reg[0x8];
// esp = 0xffffd700
	int x; 			// 0xffffd6fc
	char s1[0x40];	// 0xffffd6bc
	char s[0x1c];	// 0xffffd6a0

	for (int i = 0x10; i != 0; i--)
	{
		*s1 = 0;
		s1++;
	}
	x = 0;
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 0x100, stdin);
	x = verify_user_name();
	if (x != 0)
	{
		puts("nope, incorrect username...\n");
		return 1;
	}
	puts("Enter Password: ");
	fgets(s1, 0x64, stdin);
	x = verify_user_pass(s1);
	if (x == 0 || x != 1)
	{
		puts("nope, incorrect password...\n");
		return 1;
	}
	else
		return 0;
}
