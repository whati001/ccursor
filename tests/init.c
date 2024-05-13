#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccurser.h"

void success() {
  {
    bool ret = false;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    assert(ret == true);
    assert(handle.buffer == handle.read_position);
    assert(handle.buffer_size == strlen(str));

    size_t remaining = ccursor_available(&handle);
    assert(remaining == strlen(str));
  }
}

void fail() {
  {
    bool ret = false;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, 5);

    assert(ret == false);
    assert(handle.buffer == NULL);
    assert(handle.buffer_size == 0);

    size_t remaining = ccursor_available(&handle);
    assert(remaining == 0);
  }

  {
    bool ret = false;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, 50);

    assert(ret == false);
    assert(handle.buffer == NULL);
    assert(handle.buffer_size == 0);

    size_t remaining = ccursor_available(&handle);
    assert(remaining == 0);
  }

  {
    bool ret = false;
    char *str = "";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    assert(ret == false);
    assert(handle.buffer == NULL);
    assert(handle.buffer_size == 0);

    size_t remaining = ccursor_available(&handle);
    assert(remaining == 0);
  }
}

int main() {
  success();
  fail();
}