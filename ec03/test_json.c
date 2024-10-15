#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "miniunit.h"
#include "json.h"


static int _test_parse_object_two_values() {
  mu_start();
  //──────────────────────────────────────────────────────

  char const* input = "{\"key1\": 123, \"key2\": \"value\"}ABC";
  char const* pos = input;
  BSTNode* root;
  bool is_success = parse_object(&root, &pos);
  mu_check(is_success);   // because the input is valid
  // I was too lazy to count the characters, so made C count it for me
  // the 3 is the trailing characters
  mu_check(pos == input + strlen(input) - 3); 
  mu_check(root != NULL);
  // we could check specific locations in the tree,
  // or we could just use the helper which does not care
  Element* a_element = get_element(root, "key1");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_INT);
  mu_check(a_element->as_int == 123);
  a_element = get_element(root, "key2");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_STRING);
  mu_check_strings_equal(a_element->as_string, "value");
//  print_element(root)
  free_element((Element){.as_object = root, .type = ELEMENT_OBJECT});
  //──────────────────────────────────────────────────────
  mu_end();
}

static int _test_parse_object_two_values_el() {
  mu_start();
  //──────────────────────────────────────────────────────

  char const* input = "{\"key1\": 123, \"key2\": \"value\"}ABC";
  char const* pos = input;
  Element el;
  bool is_success = parse_element(&el, &pos);
  mu_check(is_success);   // because the input is valid
  // I was too lazy to count the characters, so made C count it for me
  // the 3 is the trailing characters
  mu_check(pos == input + strlen(input) - 3); 
//  mu_check(el != NULL);
  // we could check specific locations in the tree,
  // or we could just use the helper which does not care
 /* Element* a_element = get_element(a_element->as_object, "key1");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_INT);
  mu_check(a_element->as_int == 123);
  a_element = get_element(a_element->as_object, "key2");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_STRING);
  mu_check_strings_equal(a_element->as_string, "value");*/
   print_element(el);
  free_element(el);//{.as_object = a_element->as_object, .type = ELEMENT_OBJECT});
  //──────────────────────────────────────────────────────
  mu_end();
}


static int _test_read_json() {
	mu_start();
	Element element;
	bool is_success = read_json("read_test.json", &element);
	mu_check(is_success);
	print_element(element);
//	mu_check(pos == input + 3);
//	mu_check(*pos == 't');
	free_element(element);
	mu_end();
}

static int _test_read_json1() {
	mu_start();
	Element element;
	bool is_success = read_json("read_test_inv.json", &element);
	mu_check(!is_success);
	//print_element(element);
//	mu_check(pos == input + 3);
//	mu_check(*pos == 't');
	//free_element(element);
	mu_end();
}

static int _test_read_json2() {
	mu_start();
	Element element;
	bool is_success = read_json("read_dakj.json", &element);
	mu_check(!is_success);
	//print_element(element);
//	mu_check(pos == input + 3);
//	mu_check(*pos == 't');
	//free_element(element);
	mu_end();
}

static int _test_read_json3() {
	mu_start();
	Element element;
	bool is_success = read_json("read_test_inv2.json", &element);
	mu_check(!is_success);
	//print_element(element);
//	mu_check(pos == input + 3);
//	mu_check(*pos == 't');
	//free_element(element);
	mu_end();
}

static int _test_parse_null_invalid() {
	mu_start();
	Element element;
	char* input = "ulta";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_check(*pos == 'u');
//	free_element(element);
	mu_end();
}

static int _test_parse_null_valid() {
	mu_start();
	Element element;
	char* input = "  nullify";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 6);
	mu_check(*pos == 'i');
	print_element(element);
	mu_end();
}


static int _test_parse_bool_invalid() {
	mu_start();
	bool res;
	char* input = " truly";
	char const* pos = input;
	bool is_success = parse_bool(&res, &pos);
	mu_check(!is_success);

	mu_check(pos == input + 4);
	mu_check(*pos == 'l');
	mu_end();
}


static int _test_parse_bool_valid() {
	mu_start();
	Element el;
	
	char* input = "true";
	char const* pos = input;
	bool is_success = parse_element(&el, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(*pos == '\0');
	print_element(el);
	free_element(el);
	mu_end();
}

static int _test_parse_bool_valid2() {
	mu_start();
	Element el;
	char* input = "falsehood";
	char const* pos = input;
	bool is_success = parse_element(&el, &pos);
	mu_check(is_success);
	mu_check(pos == input + 5);
	mu_check(*pos == 'h');
	print_element(el);
	free_element(el);
	mu_end();
}

static int _test_parse_int_valid() {
  mu_start();
  //──────────────────────────────────────────────────────
  int   result;
  char* input = "-2147483648";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);
   mu_check(pos == input + 11);
 mu_check(result == INT_MIN);
  //──────────────────────────────────────────────────────
  mu_end();
}
static int _test_parse_list_invalid() {
  	mu_start();
	//---
	Element element;
	char const* input = " ][1,2],12,\"ABC\"]";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == ']');
	//---
	mu_end();

}

static int _test_parse_list_cov() {
  	mu_start();
	//---
	char const* input = "  [12, $]";
	char const* pos = input;
	Node* head;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 7);
	mu_check(*pos == '$');
	//---
	mu_end();

}


static int _test_parse_list_invalid2() {
  	mu_start();
	//---
	Element element;
	char const* input = "[12, $]";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 5);
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
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input+15);
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
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
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
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input+5);
	mu_check(*pos == '\0');
	//---
	mu_end();

}

static int _test_parse_list_valid() {
  	mu_start();
	//---
	Element element;
	char const* input = "[[ 1,2] , 12 , \"ABC\"]";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 21);
	print_element(element);
	write_json("example.json", element);
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
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 2);
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

static int _test_parse_int_cov() {
  mu_start();
  //──────────────────────────────────────────────────────
  int   result;  // will be initialized in parse_int(…)
  char* input = "  56";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  mu_check(pos == input + 4);
  //──────────────────────────────────────────────────────
	mu_end();
}

static int _test_parse_element_int_plain() {
	mu_start();
	//---
	Element element;
	char const* input = "  -123";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 6);
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
	mu_check(pos == input + 4);
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
	mu_check(pos == input);
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
	mu_check(pos == input);
	mu_check(*pos == 'A');
	//---
	mu_end();
}

static int _test_parse_null_cov() {
	mu_start();
	char* input = "  ayo";
	char const* pos = input;
	bool is_success = parse_null(&pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == 'a');
//	print_element(element);
	mu_end();
}

static int _test_parse_object_three_values() {
  mu_start();
  //──────────────────────────────────────────────────────

  char const* input = "  {\"number\" : 123, \"string\": \"Hello\", \"list\": [1, 2, 3]}";
  char const* pos = NULL;
  BSTNode* root = NULL;
 Element* a_element = get_element(root, "number");
  mu_check(root == NULL);
  mu_check(a_element == NULL);

  bool is_success = parse_object(&root, &pos);
  pos = input;
  is_success = parse_object(&root, &pos);
  mu_check(is_success);   // because the input is valid
  // I was too lazy to count the characters, so made C count it for me
  // the 3 is the trailing characters
  mu_check(pos == input + strlen(input)); 
  mu_check(root != NULL);
  // we could check specific locations in the tree,
  // or we could just use the helper which does not care
 /* Element* a_element = get_element(root, "number");
  mu_check(root == NULL);
  mu_check(a_element == NULL);*/
  a_element = get_element(root, "number");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_INT);
  mu_check(a_element->as_int == 123);
  a_element = get_element(root, "string");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_STRING);
  mu_check_strings_equal(a_element->as_string, "Hello");
  a_element = get_element(root, "list");
  mu_check(a_element->type == ELEMENT_LIST);
//  print_element(root)
  free_element((Element){.as_object = root, .type = ELEMENT_OBJECT});
  //──────────────────────────────────────────────────────
  mu_end();
}

static int _test_parse_object_inv() {
  mu_start();
  //──────────────────────────────────────────────────────

  char const* input = "  }\"number\": 123, \"string\": \"Hello\", \"list\": [1, 2, 3]}";
  char const* pos = NULL;
  BSTNode* root = NULL;
 Element* a_element = get_element(root, "number");
  mu_check(root == NULL);
  mu_check(a_element == NULL);

  bool is_success = parse_object(&root, &pos);
  pos = input;
  is_success = parse_object(&root, &pos);
  mu_check(!is_success);   // because the input is valid
  // I was too lazy to count the characters, so made C count it for me
  // the 3 is the trailing characters
  mu_check(pos == input + 2); 
  mu_check(root == NULL);
  input = "{}";
  pos = input;

  is_success = parse_object(&root, &pos);
  mu_check(is_success);
  mu_check(pos == input + 2);

  input = "{\"w_key: 123}";
  pos = input;

  is_success = parse_object(&root, &pos);
  
  mu_check(!is_success);
  
  input = "{\"w_key\"$ 123}";
  pos = input;

  is_success = parse_object(&root, &pos);
  
  mu_check(!is_success);

  input = "{\"w_key\": $123}";
  pos = input;

  is_success = parse_object(&root, &pos);
  
  mu_check(!is_success);

  input = "{\"key\": 123 , \"key\": 456, \"new\": 789";
  pos = input;

  is_success = parse_object(&root, &pos);
  
  mu_check(!is_success);
  //a_element = get_element(root, "key");
  //mu_check(a_element->as_int == 456);

  // because the input is valid
  // we could check specific locations in the tree,
  // or we could just use the helper which does not care
 /* Element* a_element = get_element(root, "number");
  mu_check(root == NULL);
  mu_check(a_element == NULL);*/
  /*a_element = get_element(root, "number");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_INT);
  mu_check(a_element->as_int == 123);
  a_element = get_element(root, "string");
  mu_check(a_element != NULL);
  mu_check(a_element->type == ELEMENT_STRING);
  mu_check_strings_equal(a_element->as_string, "Hello");
  a_element = get_element(root, "list");
  mu_check(a_element->type == ELEMENT_LIST);
//  print_element(root)
  free_element((Element){.as_object = root, .type = ELEMENT_OBJECT});*/
  //──────────────────────────────────────────────────────
  mu_end();
}



int main(int argc, char* argv[]) {

  mu_run(_test_parse_object_inv);
  mu_run(_test_parse_object_three_values);
  mu_run(_test_parse_object_two_values_el);
	mu_run(_test_parse_object_two_values);
  mu_run(_test_parse_int_cov);
  mu_run(_test_parse_null_cov);
  mu_run(_test_parse_list_cov);
  mu_run(_test_read_json3);
  mu_run(_test_read_json2);
  mu_run(_test_read_json1);
  mu_run(_test_read_json);
  mu_run(_test_parse_null_invalid);
  mu_run(_test_parse_null_valid);
  mu_run(_test_parse_bool_invalid);
  mu_run(_test_parse_bool_valid2);
  mu_run(_test_parse_bool_valid);
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
