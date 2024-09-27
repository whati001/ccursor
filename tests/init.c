#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccursor.h"

void success() {
  {
    ccursor_ret_t ret;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    assert(ret == E_CCURSOR_OK);
    assert(handle.buffer == handle.read_position);
    assert(handle.buffer_size == strlen(str));

    size_t remaining = ccursor_available(&handle);
    assert(remaining == strlen(str));
  }
}

void fail() {
  {
    ccursor_ret_t ret;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, 5);

    assert(ret == E_CCURSOR_ERR_NOT_TERMINATED);
    assert(handle.buffer == NULL);
    assert(handle.buffer_size == 0);

    size_t remaining = ccursor_available(&handle);
    assert(remaining == 0);
  }

  {
    ccursor_ret_t ret;
    char *str = "SKIP+10,20";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, 50);

    assert(ret == E_CCURSOR_ERR_NOT_TERMINATED);
    assert(handle.buffer == NULL);
    assert(handle.buffer_size == 0);

    size_t remaining = ccursor_available(&handle);
    assert(remaining == 0);
  }

  {
    ccursor_ret_t ret;
    char *str = "";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    assert(ret == E_CCURSOR_ERR_PARAM);
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