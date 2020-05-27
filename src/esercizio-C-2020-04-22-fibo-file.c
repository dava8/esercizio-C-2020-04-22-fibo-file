#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>


unsigned long fibonacci(unsigned int n)
{
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	if(n>1)
		return fibonacci(n-1) + fibonacci(n-2);
	else
		exit(EXIT_FAILURE);
}

unsigned long * fibonacci_array(unsigned int n)
{
	unsigned long * f;
	f = calloc(n+1, sizeof(long));

	if (f == NULL)
	{
		perror("Calloc error!");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<=n; i++)
		f[i]=fibonacci(i);

	return f;
}


char * itoa(unsigned long number) {
	char * result;


	result = calloc(12, sizeof(char));

	snprintf(
			result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			12, // dimensione della zona di memoria
			"%lu\n", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}




int main(int argc, char * argv[]) {

	char * file_name;
	char * text_to_write;
	int text_to_write_len;
	int res;

	unsigned int n=39;
	unsigned long * fibonacci;

	fibonacci=malloc((n+1)*sizeof(unsigned long));
	fibonacci=fibonacci_array(n);


	file_name = "fibonacci.txt";


	int fd = open(file_name,
				  O_CREAT | O_TRUNC | O_WRONLY,
				  S_IRUSR | S_IWUSR
				  );

	if (fd == -1) {

		perror("open()");

		exit(EXIT_FAILURE);
	}

	printf("scrivo nel file %s\n", file_name);

	for(int i=0;i<=n;++i){

		text_to_write = itoa(fibonacci[i]);

		text_to_write_len = strlen(text_to_write);

		res = write(fd, text_to_write, text_to_write_len);

		if (res == -1) {
			perror("write()");
			exit(EXIT_FAILURE);
		}
	}


	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	printf("bye!\n");

	exit(EXIT_SUCCESS);
}


