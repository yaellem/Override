#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char *s;
	int i = 0;
	int tab[3];
	char *s1 = "coucou";
	
	i = 0xffffffff;	
	while (*s1 != '\0')
	{
		i--;
		s1++;
	}
	i = ~i;
	i -= 2;
	printf("i = %p\n", i);
	tab[0] = 0;
	scanf("%u", &tab);
	printf("tab[0] = %u\n", tab[0]);
	printf("&s = %p s = %p\n", &s, s);
	s = malloc(1);
	printf("&s = %p s = %p\n", &s, s);
	while ((i = getchar()) != ' ')
	{
		printf("i = %d\n", i);
	}
	return 0;
}
