#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccursor.h"

void test_single_shot() {
  {
    ccursor_ret_t ret;

    ret = ccursor_skip_until_char(SINGLE_SHOT("SKIP+10,20"), '+');
    assert(ret == E_CCURSOR_OK);

    uint8_t value = 0;
    ret = ccursor_read_u8(SINGLE_SHOT("10,20"), &value);
    assert(ret == E_CCURSOR_OK);
    assert(value == 10);
  }
}

int main() { test_single_shot(); }