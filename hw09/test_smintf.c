#include <limits.h>
#include <stdlib.h>
#include "smintf.h"
#include <stdio.h>
#include "miniunit.h"


int _test_strings() {
	mu_start();
	char* a[] = {smintf(""), smintf("HELLO WORLD"), smintf("%z + %k "), smintf("abc aa")};
	//---
	mu_check_strings_equal(a[0], "");//empty string
	free(a[0]);
	mu_check_strings_equal(a[1], "HELLO WORLD");//string
	free(a[1]);
	mu_check_strings_equal(a[2], "%z + %k ");//empty string
	free(a[2]);
	mu_check_strings_equal(a[3], "abc aa");//empty string
	free(a[3]);
	//----
	mu_end();
}

int _test_percent() {
	mu_start();
	char* a[] = {smintf("hello %\n"), smintf("percent sign check %%")};
	mu_check_strings_equal(a[0], "hello %\n");//percent at end
	free(a[0]);
	mu_check_strings_equal(a[1], "percent sign check %");//percent precent
	free(a[1]);
	mu_end();
}

int _test_char() {
	mu_start();

	char* a[] = {smintf("%c", 'y'), smintf("%c,%c,%c", 'y', 89, 'a')};
	mu_check_strings_equal(a[0], "y");//percent at end
	free(a[0]);
	mu_check_strings_equal(a[1], "y,Y,a");//percent precent
	free(a[1]);
	mu_end();
}

int _test_string() {
	mu_start();
	char* a = smintf("hello %s", "world");
	mu_check_strings_equal(a, "hello world");//percent at end
	free(a);
	mu_end();
}

int _test_numbers() {
	mu_start();

	char* a[] = {smintf("%d", 3), smintf("%d", -3),smintf("%d", 11), smintf("%d", INT_MAX),smintf("%x", 11, 11 ),smintf("%b", 2, 2 ),smintf("%x", -11, -11 ), smintf("%b",-2,-2 ),smintf("%x", -9), smintf("%x", 1892 )};
	mu_check_strings_equal(a[0], "3");//percent at end
	free(a[0]);
	mu_check_strings_equal(a[1], "-3");//percent at end
	free(a[1]);
	mu_check_strings_equal(a[2], "11");//percent at end
	free(a[2]);
	mu_check_strings_equal(a[3], "2147483647");//percent at end
	free(a[3]);
	mu_check_strings_equal(a[4], "0xb");//percent precent
	free(a[4]);
	mu_check_strings_equal(a[5], "0b10");//percent precent
	free(a[5]);
	mu_check_strings_equal(a[6], "-0xb");//percent precent
	free(a[6]);
	mu_check_strings_equal(a[7], "-0b10");//percent precent
	free(a[7]);
	mu_check_strings_equal(a[8], "-0x9");//percent precent
	free(a[8]);
	mu_check_strings_equal(a[9], "0x764");//percent precent
	free(a[9]);
	mu_end();
}


int _test_money() {
	mu_start();
	char* a[] = {smintf("%$", 0), smintf("%$", 10 ), smintf("%$", -252 ), smintf("%$", 198279 ), smintf("%$",-5)};
	mu_check_strings_equal(a[0], "$0.00");//percent at end
	free(a[0]);
	mu_check_strings_equal(a[1], "$0.10");//percent precent
	free(a[1]);
	mu_check_strings_equal(a[2], "-$2.52");//percent precent
	free(a[2]);
	mu_check_strings_equal(a[3], "$1982.79");//percent precent
	free(a[3]);
	mu_check_strings_equal(a[4], "-$0.05");//percent at end
	free(a[4]);
	mu_end();

}

/*int _test_fail() {
	mu_start();
	char a[2147483647];
	char *res = smintf(a);
	if (res == NULL) {
		mu_check(1 == 1);
	}
	else {
		mu_check(0 == 1);
	}
	mu_end();
}*/


int main(int argc, char *argv[]) {
	mu_run(_test_strings);
	mu_run(_test_percent);
	mu_run(_test_char);
	mu_run(_test_string);
	mu_run(_test_numbers);
	mu_run(_test_money); 
//	mu_run(_test_fail);
	/*//Test 00: empty test
  	//Expect: ""
  
  	//Test 01: empty string
	mintf("");
    fputc('\n', stdout);
	//Expect: ""
  
	//Test 02: printing a string
	mintf("Hello World! 12345\n");
  	//Expect: Hello World! 12345
  
	//Test 03: printing a lone %
  	mintf("hello %\n");
  	//Expect: hello %
 
	//Test 04: printing a percentage sign
  	mintf("percent sign check %%\n");
  	// Expect: percent sign check %
	
	//Test 05: printing a character
  	mintf("char %c\n", 'y');
  	//Expect: char y
	
	//Test 06: printing a string
  	mintf("hello %s\n", "world");
  	//Expect: hello world

 	//Test 07: printing a int using %d format specifier
	mintf("%d\n", 3);
	//Expect: 3
  
  	//Test 08: printing an int in hexadecimal format
  	mintf("%d becomes %x in hexadecimal\n", 11, 11);
  	//Expect: 11 becomes 0xb in hexadecimal

  	//Test 09: printing an int in binary format
  	mintf("%d becomes %b in binary\n", 2, 2);
  	//Expect: 2 becomes 0b10 in binary
  	
  	//Test 10: printing a currency
  	mintf("money = %$\n", 765);
  	//Expect: money = $7.65
  	  
  	//Test 11: printing format as is with a %z
  	mintf("%z\n");
  	//Expect: %z

  	//Test 12: ignore excess parameters
  	mintf("%d %s\n", 12, "abc", 34);
  	//Expect: 12 abc

  	//Test 13: negative money
  	mintf("%$\n", -874);
  	//Expect: -$8.74*/
	return EXIT_SUCCESS;
}
