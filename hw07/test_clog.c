#include <stdlib.h>
#include "clog.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	debugf("%d%% of Columbia live in %s.\n", 15, "Bogota");
	printf_red("%s\n", "RED");
	printf_green("%s\n", "GREEN");
	printf_yellow("%s\n", "YELLOW");
	printf_blue("%s\n", "BLUE");
	printf_magenta("%s\n", "MAGENTA");
	printf_cyan("%s\n", "CYAN"); 
	log_int(3 + 4);
	int result = 15;
	log_int(result);
	log_char('A');
	log_char(65);
	char* class_name = "ECE 264";
	//char a = 'c';
	log_char(class_name[0]);
	log_str(class_name);
	log_addr(class_name);
	log_float(1.0 / 8.0);
	log_bool(3 > 5);
	log_bool(3 > 1);
	return EXIT_SUCCESS;
}
