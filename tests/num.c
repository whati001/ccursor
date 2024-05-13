#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ccursor.h"

void test_u32() {
  // test max value
  {
    bool ret = false;
    char *str = "4294967295";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32(&handle, &num);
    assert(ret == true);
    assert(num == 4294967295);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some min value
  {
    bool ret = false;
    char *str = "0";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32(&handle, &num);
    assert(ret == true);
    assert(num == 0);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermidiate value
  {
    bool ret = false;
    char *str = "2711";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32(&handle, &num);
    assert(ret == true);
    assert(num == 2711);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "-10";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test something invalid
  {
    bool ret = false;
    char *str = "xx";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u16() {
  // test max value
  {
    bool ret = false;
    char *str = "65535";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16(&handle, &num);
    assert(ret == true);
    assert(num == 65535);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some min value
  {
    bool ret = false;
    char *str = "0";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16(&handle, &num);
    assert(ret == true);
    assert(num == 0);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16(&handle, &num);
    assert(ret == true);
    assert(num == 1234);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "-10";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test something invalid
  {
    bool ret = false;
    char *str = "xx";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u8() {
  // test max value
  {
    bool ret = false;
    char *str = "255";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8(&handle, &num);
    assert(ret == true);
    assert(num == 255);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some min value
  {
    bool ret = false;
    char *str = "0";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8(&handle, &num);
    assert(ret == true);
    assert(num == 0);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8(&handle, &num);
    assert(ret == true);
    assert(num == 42);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "-10";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }

  // test something invalid
  {
    bool ret = false;
    char *str = "xx";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i32() {
  // test max value
  {
    bool ret = false;
    char *str = "2147483647";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32(&handle, &num);
    assert(ret == true);
    assert(num == 2147483647);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test min value
  {
    bool ret = false;
    char *str = "-2147483648";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32(&handle, &num);
    assert(ret == true);
    assert(num == -2147483648);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermediate value
  {
    bool ret = false;
    char *str = "12345";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32(&handle, &num);
    assert(ret == true);
    assert(num == 12345);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "abc";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i16() {
  // test max value
  {
    bool ret = false;
    char *str = "32767";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16(&handle, &num);
    assert(ret == true);
    assert(num == 32767);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test min value
  {
    bool ret = false;
    char *str = "-32768";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16(&handle, &num);
    assert(ret == true);
    assert(num == -32768);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16(&handle, &num);
    assert(ret == true);
    assert(num == 1234);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i8() {
  // test max value
  {
    bool ret = false;
    char *str = "127";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8(&handle, &num);
    assert(ret == true);
    assert(num == 127);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test min value
  {
    bool ret = false;
    char *str = "-128";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8(&handle, &num);
    assert(ret == true);
    assert(num == -128);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);

    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8(&handle, &num);
    assert(ret == true);
    assert(num == 42);

    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }

  // test some invalid number
  {
    bool ret = false;
    char *str = "abc";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));

    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);

    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u32_le() {
  // test max value
  {
    bool ret = false;
    char *str = "fffffffe";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_le(&handle, &num);
    assert(ret == true);
    assert(num == 4278190079);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "00000000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_le(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "12345678";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_le(&handle, &num);
    assert(ret == true);
    assert(num == 2018915346);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u32_be() {
  // test max value
  {
    bool ret = false;
    char *str = "fffffffe";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_be(&handle, &num);
    assert(ret == true);
    assert(num == 4294967294);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "00000000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_be(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "12345678";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_be(&handle, &num);
    assert(ret == true);
    assert(num == 305419896);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint32_t num = 0;
    ret &= ccursor_read_u32_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u16_le() {
  // test max value
  {
    bool ret = false;
    char *str = "ffff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_le(&handle, &num);
    assert(ret == true);
    assert(num == 65535);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "0000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_le(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_le(&handle, &num);
    assert(ret == true);
    assert(num == 13330);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u16_be() {
  // test max value
  {
    bool ret = false;
    char *str = "ffff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_be(&handle, &num);
    assert(ret == true);
    assert(num == 65535);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "0000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_be(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_be(&handle, &num);
    assert(ret == true);
    assert(num == 4660);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint16_t num = 0;
    ret &= ccursor_read_u16_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u8_le() {
  // test max value
  {
    bool ret = false;
    char *str = "ff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_le(&handle, &num);
    assert(ret == true);
    assert(num == 255);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "00";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_le(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_le(&handle, &num);
    assert(ret == true);
    assert(num == 66);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_u8_be() {
  // test max value
  {
    bool ret = false;
    char *str = "ff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_be(&handle, &num);
    assert(ret == true);
    assert(num == 255);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some min value
  {
    bool ret = false;
    char *str = "00";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_be(&handle, &num);
    assert(ret == true);
    assert(num == 0);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_be(&handle, &num);
    assert(ret == true);
    assert(num == 66);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    uint8_t num = 0;
    ret &= ccursor_read_u8_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i32_le() {
  // test max value
  {
    bool ret = false;
    char *str = "7fffffff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_le(&handle, &num);
    assert(ret == true);
    assert(num == -129);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "80000000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_le(&handle, &num);
    assert(ret == true);
    assert(num == 128);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "12345678";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_le(&handle, &num);
    assert(ret == true);
    assert(num == 2018915346);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i16_le() {
  // test max value
  {
    bool ret = false;
    char *str = "7fff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_le(&handle, &num);
    assert(ret == true);
    assert(num == -129);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "8000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_le(&handle, &num);
    assert(ret == true);
    assert(num == 128);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_le(&handle, &num);
    assert(ret == true);
    assert(num == 13330);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i8_le() {
  // test max value
  {
    bool ret = false;
    char *str = "7f";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_le(&handle, &num);
    assert(ret == true);
    assert(num == 127);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "80";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_le(&handle, &num);
    assert(ret == true);
    assert(num == -128);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_le(&handle, &num);
    assert(ret == true);
    assert(num == 66);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_le(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i32_be() {
  // test max value
  {
    bool ret = false;
    char *str = "7fffffff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_be(&handle, &num);
    assert(ret == true);
    assert(num == 2147483647);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "80000000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_be(&handle, &num);
    assert(ret == true);
    assert(num == -2147483648);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "12345678";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_be(&handle, &num);
    assert(ret == true);
    assert(num == 305419896);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int32_t num = 0;
    ret &= ccursor_read_i32_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i16_be() {
  // test max value
  {
    bool ret = false;
    char *str = "7fff";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_be(&handle, &num);
    assert(ret == true);
    assert(num == 32767);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "8000";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_be(&handle, &num);
    assert(ret == true);
    assert(num == -32768);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "1234";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_be(&handle, &num);
    assert(ret == true);
    assert(num == 4660);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int16_t num = 0;
    ret &= ccursor_read_i16_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

void test_i8_be() {
  // test max value
  {
    bool ret = false;
    char *str = "7f";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_be(&handle, &num);
    assert(ret == true);
    assert(num == 127);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test min value
  {
    bool ret = false;
    char *str = "80";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_be(&handle, &num);
    assert(ret == true);
    assert(num == -128);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some random intermediate value
  {
    bool ret = false;
    char *str = "42";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    assert(ret == true);
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_be(&handle, &num);
    assert(ret == true);
    assert(num == 66);
    ret &= ccursor_is_empty(&handle);
    assert(ret == true);
  }
  // test some invalid number
  {
    bool ret = false;
    char *str = "xyz";
    ccursor_handle_t handle;
    ret = ccursor_init(&handle, str, strlen(str));
    // parse
    int8_t num = 0;
    ret &= ccursor_read_i8_be(&handle, &num);
    assert(ret == false);
    assert(num == 0);
    assert(handle.buffer == handle.read_position);
    ret &= ccursor_is_empty(&handle);
    assert(ret == false);
  }
}

int main() {
  test_u32();
  test_u16();
  test_u8();

  test_i32();
  test_i16();
  test_i8();

  test_u32_le();
  test_u16_le();
  test_u8_le();

  test_i32_le();
  test_i16_le();
  test_i8_le();

  test_u32_be();
  test_u16_be();
  test_u8_be();

  test_i32_be();
  test_i16_be();
  test_i8_be();
  return 0;
}
