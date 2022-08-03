#include <stdio.h>
#include <string.h>
#include "Decryptor.h"
#include "xmalloc.h"

#define malloc xmalloc

int main() {
	char* file = malloc(sizeof(char) * 300);
	while (1)
	{
		printf("Path to conversation file: ");
		fgets(file, 300, stdin);
		/*Remove trailing /n from input*/
		file[strcspn(file, "\n")] = 0;
		if (strcmp(file, "exit") == 0 || strcmp(file, "quit") == 0)
			break;
		DecryptFile(file);
	}
	return 0;
}