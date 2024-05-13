#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccurser.h"

void test_skip_char() {
  // test valid skip
  {
    bool ret = false;
    char *str = "BC";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret &= ccursor_skip_char(&handle, 'B');
    ret &= ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'C');
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "BC";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_char(&handle, 'C');
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'B');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_skip_until_char() {
  // test valid skip
  {
    bool ret = false;
    char *str = "AK_TEST";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret &= ccursor_skip_until_char(&handle, '_');
    ret &= ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'T');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "AK_TEST";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_until_char(&handle, ' ');
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_skip_substr() {
  // test valid skip
  {
    bool ret = false;
    char *str = "AK_T";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret &= ccursor_skip_substr(&handle, "AK_");
    ret &= ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'T');
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "AK_T";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_substr(&handle, "__");
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "AK_TEST_AFTER";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_substr(&handle, "TEST");
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_skip_until_substr() {
  // test valid skip
  {
    bool ret = false;
    char *str = "AK_T";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret &= ccursor_skip_until_substr(&handle, "AK_");
    ret &= ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'T');
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test skip until
  {
    bool ret = false;
    char *str = "AK_TEST_AFTER";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_until_substr(&handle, "TEST_");
    assert(ret == true);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test skip until
  {
    bool ret = false;
    char *str = "AK_TEST_AFTER";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_until_substr(&handle, "AFTER");
    assert(ret == true);
    ret = ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "AK_T";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_until_substr(&handle, "__");
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test invalid skip
  {
    bool ret = false;
    char *str = "AK_TEST";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret = ccursor_skip_until_substr(&handle, "TESTA");
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_read_substr() {
  // test valid substr read
  {
    bool ret = false;
    char *str = "AK_TEST_AFTER";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = ' ';
    char buf[100];
    ret = ccursor_read_substr(&handle, buf, 3);
    assert(ret == true);
    assert(0 == strncmp("AK_", buf, 3));
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'T');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test valid substr read
  {
    bool ret = false;
    char *str = "AK";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = ' ';
    char buf[100];
    ret = ccursor_read_substr(&handle, buf, 3);
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_substr_until_char() {
  // test valid substr read
  {
    bool ret = false;
    char *str = "AK_TEST_AFTER";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    size_t read = 0;
    char value = ' ';
    char buf[100];
    ret = ccursor_read_substr_until_char(&handle, buf, 100, 'T', &read);
    assert(ret == true);
    assert(read == 3);
    assert(0 == strncmp("AK_", buf, 3));
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'E');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test valid substr read
  {
    bool ret = false;
    char *str = "AK";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    size_t read = 0;
    char value = ' ';
    char buf[100];
    ret = ccursor_read_substr_until_char(&handle, buf, 100, '_', &read);
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_trim_left() {
  // test valid trim left
  {
    bool ret = false;
    char *str = "   AK_TEST";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = ' ';
    char buf[100];
    ret = ccursor_trim_left(&handle);
    assert(ret == true);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test valid trim left
  {
    bool ret = false;
    char *str = "   ";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = ' ';
    char buf[100];
    ret = ccursor_trim_left(&handle);
    assert(ret == true);
    ret = ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test invalid trim left
  {
    bool ret = false;
    char *str = "AK_TEST";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = ' ';
    char buf[100];
    ret = ccursor_trim_left(&handle);
    assert(ret == false);
    ret = ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'A');
    ret = ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

int main() {
  test_skip_char();
  test_skip_until_char();

  test_skip_substr();
  test_skip_until_substr();
  test_read_substr();
  test_substr_until_char();
  test_trim_left();
  return 0;
}