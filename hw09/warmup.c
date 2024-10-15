 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
	int len = 0;
	while (original[len] != '\0') {
		len++;
	}
	char* cop = (char*) malloc(sizeof(char) * (len + 1));
	for (int i = 0; i <= len; i++) {
		cop[i] = original[i];
	}	
	return cop;
}

int main(int argc, char *argv[]) {
	char s[] = "";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup("");
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);
	return EXIT_SUCCESS;
}
