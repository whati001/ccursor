#include <assert.h>
#include <stdbool.h>
#include <string.h>


#include "ccursor.h"

void test_error() {
  {
    ccursor_ret_t ret;
    char *str = "";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // generates a E_CCURSOR_ERR_PARAM
    assert(true == CCURSOR_IS_ERROR(ret));
    assert(false == CCURSOR_IS_OK(ret));

    // now we apply a parsing error and validate if both errors can be matched
    uint8_t num;
    char *str2 = "-10";
    ret |= ccursor_init(&handle, str2, strlen(str2));
    ret |= ccursor_read_u8(&handle, &num);
    // generates a E_CCURSOR_ERR_PARAM
    assert(true == CCURSOR_IS_ERROR(ret));
    assert(false == CCURSOR_IS_OK(ret));
  }
}

int main() { test_error(); }