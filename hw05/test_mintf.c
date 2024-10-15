#include <limits.h>
#include <stdlib.h>
#include "mintf.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	//Test 00: empty test
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
  	//Expect: -$8.74
	return EXIT_SUCCESS;
}
