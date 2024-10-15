#include <stdbool.h>
#include <string.h>
#include "clog.h"

#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#define __mu_line_check 0
#define mu_start() int __mu_local = __mu_line_check
#define mu_end() return __mu_local
#define mu_check(condition) 						\
	do { 											\
		if ((condition) == 1) {}					\
		else {										\
			(__mu_local == 0)?(__mu_local = __LINE__):(__mu_local = __mu_local);											  \
			mu_end();								\
		}											\
	} while(false) 

#define mu_check_strings_equal(s1,s2) mu_check(!strcmp(s1,s2))

#define mu_run(function) 									\
	do {													\
		int res = function();								\
		if (res == 0) {										\
			printf_green("Test passed: %s\n", #function);	\
		}													\
		else {												\
			printf_red("Test failed: %s at line %d\n", #function, res);	\
		}													\
	} while(false)

#endif /*end of include guard: __MINIUNIT_H__ */
