#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>

void	log_wrapper(FILE *backup_stream, char *sentence, char *first_s_main)
{
	size_t nm_char_not_bn;
	uint64_t compteur;
	uint64_t compteur2;
	char * backup_log_stream;
	char save_sentence [264];
	long stack_protect;
	char c;
	char *save;

	backup_log_stream = backup_back;
	strcpy(save_sentence,sentence);
	
	snprintf(save_sentence + (strlen(save_sentence)),0xfe - (strlen(save_sentence)),first_str_main);
	
	nm_char_not_bn = strcspn(save_sentence,"\n");
	save_sentence[nm_char_not_bn] = '\0';
	
	fprintf((FILE *)backup_log_stream,"LOG: %s\n",save_sentence);
	
	return;
}

int main(int ac, char **av)
{
	// rbp = 0x7fffffffe590
	// rsi = 0x7fffffffe4f0 (rbp - 0xa0) = **av = 0x00007fffffffe678
	int fd;
	int i;
	FILE *backup_log_stream;
	FILE *param_stream;
	uint64_t compteur;
	uint64_t *addr_name_backup;
	long in_FS_OFFSET;
	char c;
	char name_backup_dir[0xb];

	c = -1;
	if (ac != 2) {
		printf("Usage: %s filename\n",*av);
	}
	backup_log_stream = fopen("./backups/.log","w");
	if (backup_log_stream == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n","./backups/.log");
		exit(1);
	}
	log_wrapper(backup_log_stream,"Starting back up: ",av[1]);

	param_stream = fopen(av[1],"r");
	if (param_stream == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n",av[1]);
		exit(1);
	}

	*(uint64_t*)name_backup_dir = 0x70756b6361622f2e;
	name_backup_dir[8] = 0x73;
	name_backup_dir[9] = 0x2f;
	name_backup_dir[10] = '\0';
	strncat((char *)&name_backup_dir,av[1],99 - (strlen(name_backup_dir)));

	/*  user + group has read permission 
		user + group has write permission
	 */
	fd = open((char *)&name_backup_dir, O_CREATE|O_EXCL|O_WRONLY, S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
	if (fd < 0) {
		printf("ERROR: Failed to open %s%s\n","./backups/",av[1]);
		exit(1);
	}

	while( true ) {
		i = fgetc(param_stream);
		c = (char)i;
		if (c == -1) break;
		write(__fd,&c,1);
	}

	log_wrapper(backup_log_stream,"Finished back up ",av[1]);

	fclose(param_stream);
	close(fd);
	return 0;
}

}
