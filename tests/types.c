#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccurser.h"

void test_byte() {
  // test byte value
  {
    bool ret = false;
    char *str = "B";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint8_t value = 0;
    ret &= ccursor_read_byte(&handle, &value);
    assert(ret == true);
    assert(value == 'B');
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
}

void test_char() {
  // test byte value
  {
    bool ret = false;
    char *str = "B";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    char value = '0';
    ret &= ccursor_read_char(&handle, &value);
    assert(ret == true);
    assert(value == 'B');
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
}

int main() {
  test_byte();
  test_char();
  return 0;
}