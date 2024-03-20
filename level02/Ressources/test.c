#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	char s0[10];
	char str[22];
	char s1[0xa];

/*	str[0] = '0';
	str[1] = '1';
	str[2] = '2';
	str[3] = '3';
	str[4] = '4';
	str[5] = '5';
	str[6] = '6';
	str[7] = '7';
	str[8] = '8';
	str[9] = '9';
*/	
	s0[0] = '0';
//	printf("strcspn(): %d, strspn(): %d\n", strcspn(str, "c"), strspn(str, "c"));
//	printf("strcspn(): %d, strspn(): %d\n", strcspn(str, "be"), strspn(str, "be"));
//	printf("strcspn(): %d, strspn(): %d\n", strcspn(str, "A"), strspn(str, "A"));
//	printf("strcspn(): %d, strspn(): %d\n", strcspn(str, "ddwuswwss"), strspn(str, "ddwuswwss"));
	printf("strcspn(): %d sizeof(int): %d\n",  strcspn(str, "\n"), sizeof(int));
	printf("addr s0: %p, str: %p s1: %p s0[0] = %c\n", &s0, &str, &s1, s0[0]);
	*(char*)(str + 10) = 'b';
	printf("addr str + 11 = %p s0[0] = %c\n", (char*)(str+11), s0[0]);
	printf("strncmp(): %d\n", strncmp("", av[1], 0x29));
	printf("strcmp(): %d\n", strcmp("1234", av[1]));
	int i = 0;
	int j = 0;
	printf("\x28\x12\x60\x29\x12\x60%127c%07$n%16261c%8$n", '1', '2', '3', '4', '5', '6', &i, &j);
	printf("val i: %x, j: %x\n", i, j);
	return 0;
}
