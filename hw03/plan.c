#include <stdlib.h>
#include "mintf.h"

int main(int argc, char *argv[]) {
	//Test 00: empty test
  	//Expect: ""
  
  	//Test 01: empty string
	mintf("");
	//Expect: ""
  
	//Test 02: printing a string
	mintf("Hello World! 12345");
  	//Expect: Hello World! 12345
  
 	//Test 03: printing a int using %d format specifier
  	mintf("%d", 12345);
	//Expect: 12345
  
  	//Test 04: printing an int in hexadecimal format
  	mintf("%d becomes %x in hexadecimal", 11, 2);
  	//Expect: 11 becomes 0xb in hexadecimal

  	//Test 05: printing an int in binary format
  	mintf("%d becomes %b in binary", 2, 2);
  	//Expect: 2 becomes 0b10 in binary

  	//Test 06: printing a percentage sign
  	mintf("percent sign check %%");
  	// Expect: percent sign check %
	  
  	//Test 07: printing a string
  	mintf("hello %s", "world");
  	//Expect: hello world

  	//Test 08: printing a currency
  	mintf("money = %$", 765);
  	//Expect: money = $7.65

  	//Test 09: printing a character
  	mintf("char %c", 'y');
  	//Expect: char y
  
  	//Test 10: printing char through ASCII
  	mintf("ASCII 89 is %c", 89);
  	//Expect: ASCII 89 is Y
  
  	//Test 11: printing format as is with a %z
  	mintf("%z");
  	//Expect: %z

  	//Test 12: printing a lone %
  	mintf("hello %");
  	//Expect: hello %

  	//Test 13: ignore excess parameters
  	mintf("%d %s", 12, "abc", 34);
  	//Expect: 12 abc

  	//Test 14: negative money
  	mintf("%$", -874);
  	//Expect: -$87.4
}
