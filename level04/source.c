#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/ptrace.h>

__attribute__((force_align_arg_pointer)) int main()
{
// ebp = 0xffffd708
	char pushed_reg[0x8];	// 0xffffd700	esp + 0xb0
	pid_t pid;				// 0xffffd6fc	esp + 0xac
	int	a;					// 0xffffd6f8	esp + 0xa8
	int	b;					// 0xffffd6f4	esp + 0xa4
	int	c;					// 0xffffd6f0	esp + 0xa0
	char s1[0x80];			// 0xffffd670	esp + 0x20
	int	stat_loc;			// 0xffffd66c	esp + 0x1c
	char s2[0x1c];			// 0xffffd650	esp

	pid = fork();
	for (int i = 0; i < 0x20; i++)
	{
		s1[i] = 0;
	}
	a = 0;
	stat_loc = 0;
	if (pid == 0)
	{
// set the signal that the child will receives when its parent 
// process will terminate
		prctl(PR_SET_PDEATHSIG, SIGHUP);// 1, 1
// The calling process will be traced by its parent 
// Tout signal (sauf SIGKILL) reçu par le processus l'arrêtera
// Le père sera notifié grâce à wait().
// Les appels ultérieurs à execve() par ce processus lui
//										 enverront SIGTRAP
		ptrace(PT_TRACE_ME, 0, NULL, 0);
		puts("Give me some shellcode, k"); // addr 0x8048903
		gets(s1);
	}
	else
	{
		while (a != 0xb)
		{
			wait(&stat_loc);
			c = stat_loc;
			b = stat_loc;
			printf("wait status: %d\n", stat_loc);
			if ((c & 0x7f) == 0 || ((c & 0x7f) + 1) >> 1 > 0)
			{
				puts("child is exiting");
				return 0;
			}
// Lire un mot à l'adresse 'addr' dans l'espace USER du fils
// La valeur est renvoyée en résultat de ptrace().
// data est ignoré
//0x2c means the offset from the register space in the child, which gives
// orig_eax
			a = ptrace(PT_TRACE_PEEKUSER, pid, 0x2c, 0);
		}
    	puts("no exec() for you");
    	kill(pid, 9);
	}
	return 0;
}		
