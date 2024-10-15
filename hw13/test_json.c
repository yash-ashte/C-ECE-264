#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "miniunit.h"
#include "json.h"

static int _test_parse_int_valid() {
  mu_start();
  //──────────────────────────────────────────────────────
  int   result;
  char* input = "-2147483648";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);
  printf("%p\n", input + 1);
  mu_check(pos == input + 11);
 mu_check(result == INT_MIN);
  //──────────────────────────────────────────────────────
  mu_end();
}
static int _test_parse_list_invalid() {
  	mu_start();
	//---
	Element element;
	char const* input = "][1,2],12,\"ABC\"]";
	char const* pos = input;
	printf("in");
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	printf("%p\n", input);

	printf("%p\n", pos);
	mu_check(pos == input);
	printf("pe\n");
//	print_element(element);
//	free_element(element);
	mu_check(*pos == ']');
	//---
	mu_end();

}

static int _test_parse_list_invalid2() {
  	mu_start();
	//---
	Element element;
	char const* input = "[[1$2],12,\"ABC\"]";
	char const* pos = input;
	printf("in");
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	printf("%p\n", input);

	printf("%p\n", pos);
	mu_check(pos == input + 3);
	printf("pe\n");
//	print_element(element);
//	free_element(element);
	mu_check(*pos == '$');
	//---
	mu_end();

}

static int _test_parse_list_invalid3() {
  	mu_start();
	//---
	Element element;
	char const* input = "[[1,2],12,\"ABC\"";
	char const* pos = input;
	printf("in");
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	printf("%p\n", input+15);

	//printf("%p\n", pos);
	mu_check(pos == input+15);
//	printf("%c\n", *pos)
//	print_element(element);
//	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();

}

static int _test_parse_list_invalid4() {
  	mu_start();
	//---
	Node* head;
	char const* input = "A[]";
	char const* pos = input;
	printf("in");
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	printf("%p\n", input);

	//printf("%p\n", pos);
	mu_check(pos == input);
//	printf("%c\n", *pos)
//	print_element(element);
//	free_element(element);
	mu_check(*pos == 'A');
	//---
	mu_end();

}
static int _test_parse_list_invalid5() {
  	mu_start();
	//---
	Node* head;
	char const* input = " [12,";
	char const* pos = input;
	printf("in");
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	printf("%p\n", input+8);

	//printf("%p\n", pos);
	mu_check(pos == input+8);
//	printf("%c\n", *pos)
//	print_element(element);
//	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();

}

static int _test_parse_list_valid() {
  	mu_start();
	//---
	Element element;
	char const* input = "[[ 1,2], 12, \"ABC\"]";
	char const* pos = input;
	printf("in");
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	printf("%p\n", input);

	printf("%p\n", pos);
	mu_check(pos == input + 19);
	printf("pe\n");
	print_element(element);
	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();

}

static int _test_parse_list_valid2() {
  	mu_start();
	//---
	Element element;
	char const* input = "[]";
	char const* pos = input;
	printf("in");
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	printf("%p\n", input);

	printf("%p\n", pos);
	mu_check(pos == input + 2);
	printf("pe\n");
	print_element(element);
	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();

}


static int _test_parse_int_valid1() {
  mu_start();
  //──────────────────────────────────────────────────────
  int   result;  // will be initialized in parse_int(…)
  char* input = "-100-A";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  printf("%p\n", input + 1);
  mu_check(result == -100);
  mu_check(pos == input + 4);
  //--------------------------------------------------
  mu_end();
}


static int _test_parse_int_invalid() {
  mu_start();
  //──────────────────────────────────────────────────────
  int   result;  // will be initialized in parse_int(…)
  char* input = "-";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(!is_success);   // because the input is valid
  mu_check(pos == input + 1);
  //──────────────────────────────────────────────────────
	mu_end();
}



static int _test_parse_element_int_plain() {
	mu_start();
	//---
	Element element;
	char const* input = "123";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 3);
	print_element(element);
	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();
}


static int _test_parse_element_string_plain() {
	mu_start();
	//---
	Element element;
	char const* input = "\"ABCDEF\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	printf("%p\n", input + 8);
	mu_check(pos == input + 8);
	print_element(element);
	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();
}

static int _test_parse_element_wrong() {
	mu_start();
	//---
	Element element;
	char const* input = "\"ABC\n\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	printf("ab - %p\n", input + 4);
	mu_check(pos == input + 4);
//	print_element(element);
	//free_element(element);
	mu_check(*pos == '\n');
	//---
	mu_end();
}

static int _test_parse_element_wrong1() {
	mu_start();
	//---
	Element element;
	char const* input = "ABC\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	printf("ab - %p\n", input);
	mu_check(pos == input);
//	print_element(element);
	//free_element(element);
	mu_check(*pos == 'A');
	//---
	mu_end();
}

static int _test_parse_element_wrong2() {
	mu_start();
	//---
	Element element;
	char const* input = "  \"ABC\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	printf("ab - %p\n", input);
	mu_check(pos == input + 7);
	print_element(element);
	free_element(element);
	mu_check(*pos == '\0');
	//---
	mu_end();
}

static int _test_parse_string() {
	mu_start();
	//---
	int result;
	char const* input = "--4";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	//mu_check_strings_equal("--4", result);
	printf("%p\n", (input + 1));
	mu_check(pos == input + 1);
	mu_check(*pos == '-');
	//free(result);
	//---
	mu_end();
}
static int _test_parse_string2() {
	mu_start();
	//---
	char* result;
	char const* input = "ABC\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	//mu_check_strings_equal("--4", result);
	printf("%p\n", (input + 1));
	mu_check(pos == input);
	mu_check(*pos == 'A');
	//free(result);
	//---
	mu_end();
}


/*static int _test_invalid_input() {
	mu_start();
	//---
	int result;
	char const* input = NULL;
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	//mu_check_strings_equal("--4", result);

	mu_check(pos == input);
	mu_check(*pos == '-');
	//free(result);
	//---
	mu_end();
}*/



int main(int argc, char* argv[]) {
  
  mu_run(_test_parse_list_valid);

  mu_run(_test_parse_list_valid2);

  mu_run(_test_parse_list_invalid);

  mu_run(_test_parse_list_invalid2);

  mu_run(_test_parse_list_invalid3);

  mu_run(_test_parse_list_invalid4);

  mu_run(_test_parse_list_invalid5);
	mu_run(_test_parse_int_valid);
  mu_run(_test_parse_int_invalid);
  mu_run(_test_parse_element_int_plain);
  mu_run(_test_parse_int_valid1);
  mu_run(_test_parse_string);

  mu_run(_test_parse_string2);
  mu_run(_test_parse_element_string_plain);
  mu_run(_test_parse_element_wrong);
  mu_run(_test_parse_element_wrong1);
//  mu_run(_test_invalid_input);
  mu_run(_test_parse_element_wrong2);
//  mu_run(_test_parse_list_valid);
  return EXIT_SUCCESS;
}
