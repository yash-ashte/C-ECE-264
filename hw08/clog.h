#ifndef __CLOG_H__
#define __CLOG_H__

#include <stdio.h>
#include <stdbool.h>

#define debugf(...) do { \
	printf("[%s:%d] ", __FILE__, __LINE__);			\
	printf(__VA_ARGS__);			\
} while(false)

#define ANSI_RESET		"\x1b[0m"

#define printf_red(...) __mu_print_col("\x1b[31m", __VA_ARGS__) 
#define printf_green(...) __mu_print_col("\x1b[32m", __VA_ARGS__) 
#define printf_yellow(...) __mu_print_col("\x1b[33m", __VA_ARGS__) 
#define printf_blue(...) __mu_print_col("\x1b[34m", __VA_ARGS__) 
#define printf_magenta(...) __mu_print_col("\x1b[35m", __VA_ARGS__) 
#define printf_cyan(...) __mu_print_col("\x1b[36m", __VA_ARGS__) 

#define __mu_print_col(ANSI_CODE, ...) do { \
	printf(ANSI_CODE); \
	printf(__VA_ARGS__); \
	printf( ANSI_RESET); \
} while(false)

#define log_int(num) printf("%s == %d\n", #num, num)
#define log_char(ch) printf("%s == '%c'\n", #ch, ch);
#define log_str(str) printf("%s == \"%s\"\n", #str, str);
#define log_addr(str) printf("%s == %p\n", #str, (void*) str)
#define log_float(num) printf("%s == %.16f\n", #num, num)
#define log_bool(num) printf("%s == %s\n", #num, num?"true":"false" )
#endif /* end of include guard: __CLOG_H__ */
