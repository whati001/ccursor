
#include "ccursor.h"
#include "ccursor_port.h"

#define CCURSOR_END(handle) (handle->buffer + handle->buffer_size)
#define CCURSOR_REMAINING_SIZE(handle)                                         \
  (CCURSOR_END(handle) - handle->read_position)
/**
 * @brief Convert char HEX character into a nibble
 *
 * @param[out] nibble - parsed nibble value
 * @param[in]  c      - character to parse
 * @return true on success, else false
 */
static bool ccursor_hex_char_to_nibble(uint8_t *nibble, const char c) {
  if (c >= '0' && c <= '9') {
    *nibble = (c - '0');
    return true;
  } else if (c >= 'a' && c <= 'f') {
    *nibble = (c - 'a' + 10);
    return true;
  } else if (c >= 'A' && c <= 'F') {
    *nibble = (c - 'A' + 10);
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Inline swaps the byte order of a given value
 *
 * @param[in,out] value - value to swap bytes
 * @param[in]     size  - size of value
 */
static void ccursor_byte_swap(uint8_t *value, size_t size) {
  for (size_t i = 0; i < size / 2; i++) {
    uint8_t temp = value[i];
    value[i] = value[size - i - 1];
    value[size - i - 1] = temp;
  }
}

ccursor_ret_t ccursor_init(ccursor_handle_t *handle, char *buffer,
                           uint32_t buffer_size) {
  if (handle == NULL || buffer == NULL || buffer_size == 0) {
    return E_CCURSOR_ERR_PARAM;
  }

  memset(handle, 0, sizeof(ccursor_handle_t));

  char *termination = buffer + buffer_size;
  if (*termination != '\0') {
    return E_CCURSOR_ERR_NOT_TERMINATED;
  }

  handle->buffer = buffer;
  handle->buffer_size = buffer_size;
  handle->read_position = buffer;

  return E_CCURSOR_OK;
}

size_t ccursor_available(ccursor_handle_t *handle) {
  if (handle == NULL) {
    return 0;
  }

  return CCURSOR_REMAINING_SIZE(handle);
}

ccursor_ret_t ccursor_is_empty(ccursor_handle_t *handle) {
  if (handle == NULL) {
    return E_CCURSOR_ERR_PARAM;
  }
  if (handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_OK;
  }

  return E_CCURSOR_ERR;
}

ccursor_ret_t ccursor_read_u32(ccursor_handle_t *handle, uint32_t *value) {
  if (handle == NULL || value == NULL ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  char *endptr = NULL;
  unsigned long num = _strtoul(handle->read_position, &endptr, 10);

  // Check for various possible errors
  if (endptr == handle->read_position || num > _UINT32_MAX) {
    return E_CCURSOR_ERR_PARSE;
  }

  // Check if endptr is outside of the buffer
  if (endptr > CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARSE;
  }

  *value = (uint32_t)num;
  handle->read_position = endptr;

  return E_CCURSOR_OK;
}

ccursor_ret_t ccursor_read_u16(ccursor_handle_t *handle, uint16_t *value) {
  uint32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_u32(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num <= _UINT16_MAX) {
      *value = (uint16_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_u8(ccursor_handle_t *handle, uint8_t *value) {
  uint32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_u32(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num <= _UINT8_MAX) {
      *value = (uint8_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_i32(ccursor_handle_t *handle, int32_t *value) {
  if (handle == NULL || value == NULL ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  char *endptr = NULL;
  long num = _strtol(handle->read_position, &endptr, 10);

  // Check for various possible errors
  if (endptr == handle->read_position || num < INT32_MIN || num > INT32_MAX) {
    return E_CCURSOR_ERR_PARSE;
  }

  // Check if endptr is outside of the buffer
  if (endptr > CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARSE;
  }

  *value = (int32_t)num;
  handle->read_position = endptr;

  return E_CCURSOR_OK;
}

ccursor_ret_t ccursor_read_i16(ccursor_handle_t *handle, int16_t *value) {
  int32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_i32(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num >= _INT16_MIN || num <= _INT16_MAX) {
      *value = (int16_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_i8(ccursor_handle_t *handle, int8_t *value) {
  int32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_i32(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num >= _INT8_MIN || num <= _INT8_MAX) {
      *value = (int8_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_u32_be(ccursor_handle_t *handle, uint32_t *value) {
  if (handle == NULL || value == NULL ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  ccursor_ret_t ret;
  char next = ' ';
  uint8_t nibble = 0;
  uint32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ret = ccursor_trim_left(handle);
  if (ret == E_CCURSOR_OK) {
    // trimmed leading spaces
  }

  ret = ccursor_skip_substr(handle, "0x");
  if (ret == E_CCURSOR_OK) {
    // skipped leading 0x of hex string
  }

  uint8_t idx = 0;
  for (idx = 0; idx < (sizeof(uint32_t) * 2); idx++) {
    ret = ccursor_read_char(handle, &next);
    if (ret == E_CCURSOR_OK) {
      bool converted = ccursor_hex_char_to_nibble(&nibble, next);
      if (converted == true) {
        num = num << 4 | nibble;
      } else {
        // current char is not a valid nibble, revert read
        handle->read_position--;
        break;
      }
    } else {
      // nothing more to read
      break;
    }
  }

  // if we have already read some nibbles, parsing is done
  if (idx > 0) {
    *value = num;
    return E_CCURSOR_OK;
  } else {
    // parsing failed because first char was already crap
    handle->read_position = read_position_pre;
    return E_CCURSOR_ERR_PARSE;
  }
}

ccursor_ret_t ccursor_read_u16_be(ccursor_handle_t *handle, uint16_t *value) {
  uint32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_u32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num <= _UINT16_MAX) {
      *value = (uint16_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_u8_be(ccursor_handle_t *handle, uint8_t *value) {
  uint32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_u32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num <= _UINT8_MAX) {
      *value = (uint8_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_i32_be(ccursor_handle_t *handle, int32_t *value) {
  return ccursor_read_u32_be(handle, (uint32_t *)value);
}

ccursor_ret_t ccursor_read_i16_be(ccursor_handle_t *handle, int16_t *value) {
  int32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_i32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num >= _INT16_MIN || num <= _INT16_MAX) {
      *value = (int16_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_i8_be(ccursor_handle_t *handle, int8_t *value) {
  int32_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_i32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num >= _INT8_MIN || num <= _INT8_MAX) {
      *value = (int8_t)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_u32_le(ccursor_handle_t *handle, uint32_t *value) {
  uint32_t num = 0;
  ccursor_ret_t ret = ccursor_read_u32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(uint32_t));
    *value = num;
    return E_CCURSOR_OK;
  }

  return ret;
}

ccursor_ret_t ccursor_read_u16_le(ccursor_handle_t *handle, uint16_t *value) {
  uint16_t num = 0;
  ccursor_ret_t ret = ccursor_read_u16_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(uint16_t));
    *value = num;
    return E_CCURSOR_OK;
  }
  return ret;
}

ccursor_ret_t ccursor_read_u8_le(ccursor_handle_t *handle, uint8_t *value) {
  uint8_t num = 0;
  ccursor_ret_t ret = ccursor_read_u8_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(uint8_t));
    *value = num;
    return E_CCURSOR_OK;
  }
  return ret;
}

ccursor_ret_t ccursor_read_i32_le(ccursor_handle_t *handle, int32_t *value) {
  int32_t num = 0;
  ccursor_ret_t ret = ccursor_read_i32_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(int32_t));
    *value = num;
    return E_CCURSOR_OK;
  }
  return ret;
}

ccursor_ret_t ccursor_read_i16_le(ccursor_handle_t *handle, int16_t *value) {
  int16_t num = 0;
  ccursor_ret_t ret = ccursor_read_i16_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(int16_t));
    *value = num;
    return E_CCURSOR_OK;
  }
  return ret;
}

ccursor_ret_t ccursor_read_i8_le(ccursor_handle_t *handle, int8_t *value) {
  int8_t num = 0;
  ccursor_ret_t ret = ccursor_read_i8_be(handle, &num);
  if (ret == E_CCURSOR_OK) {
    ccursor_byte_swap((uint8_t *)&num, sizeof(int8_t));
    *value = num;
    return E_CCURSOR_OK;
  }
  return ret;
}

ccursor_ret_t ccursor_read_byte(ccursor_handle_t *handle, uint8_t *byte) {
  return ccursor_read_char(handle, (char *)byte);
}

ccursor_ret_t ccursor_read_bool(ccursor_handle_t *handle, bool *value) {
  uint8_t num = 0;
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_byte(handle, &num);
  if (ret == E_CCURSOR_OK) {
    if (num == 0 || num == 1) {
      *value = (bool)num;
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return ret;
}

ccursor_ret_t ccursor_read_char(ccursor_handle_t *handle, char *c) {
  if (handle == NULL || handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  *c = *handle->read_position;
  handle->read_position++;
  return E_CCURSOR_OK;
}

ccursor_ret_t ccursor_skip_char(ccursor_handle_t *handle, char c) {
  char next = ' ';
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_read_char(handle, &next);
  if (ret == E_CCURSOR_OK) {
    if (next == c) {
      // cursor already advanced in ccursor_read_char function
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return E_CCURSOR_ERR_PARSE;
}

ccursor_ret_t ccursor_skip_until_char(ccursor_handle_t *handle, uint8_t c) {
  if (handle == NULL || handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  ccursor_ret_t ret = false;
  char next = ' ';
  char *const read_position_pre = handle->read_position;

  do {
    ret = ccursor_read_char(handle, &next);
    if (ret == E_CCURSOR_OK) {
      if (next == c) {
        // cursor already advanced in ccursor_read_char function
        return E_CCURSOR_OK;
      }
    }
  } while (ret == E_CCURSOR_OK);

  handle->read_position = read_position_pre;
  return E_CCURSOR_ERR_PARSE;
}

ccursor_ret_t ccursor_skip_until_substr(ccursor_handle_t *handle,
                                        const char *substr) {
  if (handle == NULL || substr == NULL ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  size_t substr_length =
      strnlen(substr, (CCURSOR_END(handle) - handle->read_position));
  char *found_position = strstr(handle->read_position, substr);

  // Check if the substring was found and if it's inside the buffer
  if (found_position == NULL || found_position >= CCURSOR_END(handle) ||
      (found_position + substr_length) > CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARSE;
  }

  // Move the current position to the character following the found substring
  handle->read_position = found_position + _strlen(substr);

  return E_CCURSOR_OK;
}

ccursor_ret_t ccursor_skip_substr(ccursor_handle_t *handle,
                                  const char *substr) {
  char *const read_position_pre = handle->read_position;

  ccursor_ret_t ret = ccursor_skip_until_substr(handle, substr);
  if (ret == E_CCURSOR_OK) {
    if ((read_position_pre + _strlen(substr)) == handle->read_position) {
      return E_CCURSOR_OK;
    }
  }

  handle->read_position = read_position_pre;
  return E_CCURSOR_ERR_PARSE;
}

ccursor_ret_t ccursor_read_substr(ccursor_handle_t *handle, char *substr,
                                  size_t size) {
  if (handle == NULL || substr == NULL || size == 0 ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  size_t remaining_size = CCURSOR_REMAINING_SIZE(handle);
  if (remaining_size < size) {
    return E_CCURSOR_ERR_PARSE;
  }

  _strncpy(substr, handle->read_position, size);
  substr[size] = '\0';
  handle->read_position += size;
  return E_CCURSOR_OK;
}

ccursor_ret_t ccursor_read_substr_until_char(ccursor_handle_t *handle,
                                             char *substr, size_t size, char c,
                                             size_t *written) {
  if (handle == NULL || substr == NULL || written == NULL || size == 0 ||
      handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }
  char *const read_position_pre = handle->read_position;

  size_t remaining_size = CCURSOR_REMAINING_SIZE(handle);
  if (remaining_size < size) {
    size = remaining_size;
  }

  size_t idx = 0;
  for (idx = 0; idx < size; idx++) {
    // also skip stop character
    if (*(handle->read_position) == c) {
      handle->read_position++;
      substr[idx] = '\0';
      *written = idx;
      return E_CCURSOR_OK;
    }
    substr[idx] = *(handle->read_position);
    handle->read_position++;
  }

  // character not found and either buffer or cursor end reached
  handle->read_position = read_position_pre;
  return E_CCURSOR_ERR_PARSE;
}

ccursor_ret_t ccursor_trim_left(ccursor_handle_t *handle) {
  if (handle == NULL || handle->read_position >= CCURSOR_END(handle)) {
    return E_CCURSOR_ERR_PARAM;
  }

  while (*(handle->read_position) == ' ') {
    handle->read_position++;
    if (handle->read_position >= CCURSOR_END(handle)) {
      return E_CCURSOR_OK;
    }
  }

  return E_CCURSOR_OK;
}
