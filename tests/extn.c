#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccursor.h"

void test_single_shot() {
  {
    bool ret = false;

    ret = ccursor_skip_until_char(SINGLE_SHOT("SKIP+10,20"), '+');
    assert(ret == true);

    uint8_t value = 0;
    ret = ccursor_read_u8(SINGLE_SHOT("10,20"), &value);
    assert(ret == true);
    assert(value == 10);
  }
}

int main() { test_single_shot(); }