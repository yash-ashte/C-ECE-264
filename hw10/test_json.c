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
  int   result;  // will be initialized in parse_int(…)
  char* input = "-2147483648";
  char const* pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  //printf("%p\n", input + 1);
  mu_check(pos == input + 1);
 mu_check(result == INT_MIN);
  //──────────────────────────────────────────────────────
/*  input = "500060";
  pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  mu_check(pos == input + 1);
  //
  input = "12345";
  pos = input;

  printf("%p\n", input + 1);
  is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  mu_check(pos == input + 1);

  //mu_check(result == 50);
*/
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
//  printf("%p\n", input + 1);
  mu_check(result == -100);
  mu_check(pos == input + 1);
 //mu_check(result == 446302);
  //──────────────────────────────────────────────────────
/*  input = "500060";
  pos = input;
  bool is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  mu_check(pos == input + 1);
  //
  input = "12345";
  pos = input;

  printf("%p\n", input + 1);
  is_success = parse_int(&result, &pos);
  mu_check(is_success);   // because the input is valid
  mu_check(pos == input + 1);

  //mu_check(result == 50);
*/
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
  mu_check(pos == input);
  //mu_check(result == 50);
  //──────────────────────────────────────────────────────
	mu_end();
}

int main(int argc, char* argv[]) {
  mu_run(_test_parse_int_valid);
  mu_run(_test_parse_int_invalid);

  mu_run(_test_parse_int_valid1);
  return EXIT_SUCCESS;
}

/*typedef struct {
    bool is_success;
    union {  // anonymous union (C11)
        Element element;
        long int error_idx;
    };
} ParseResult;


static ParseResult _parse_json(char* s) {
    int element;  // Not initialized because parse_element(…) *must* do so.
    char const* pos = s;
    bool is_success = parse_int(&element, &pos);
    if(is_success) {
        return (ParseResult) { .is_success = is_success, .element = element };
    }
    else {
        return (ParseResult) { .is_success = is_success, .error_idx = pos - s };
    }
}

static int _test_int() {
    mu_start();
    //────────────────────
    ParseResult result = _parse_json("0");
    mu_check(result.is_success);
    if(result.is_success) {
        mu_check(result.element.type == ELEMENT_INT);
        mu_check(result.element.as_int == 0);
        free_element(result.element);  // should do nothing
    }
    //────────────────────
    mu_end();
}



int main(int argc, char* argv[]) {
    mu_run(_test_int);
 //   mu_run(_test_string);
   // mu_run(_test_list_of_ints);
    return EXIT_SUCCESS;
}*/




