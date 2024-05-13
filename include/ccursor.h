#ifndef CCURSOR_HEADER
#define CCURSOR_HEADER

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Char cursor handle
 *
 * This structure holds the char cursor handle.
 * The handle keeps track of the current position in the buffer for parsing
 * operations.
 */
typedef struct {
  char *buffer;
  uint32_t buffer_size;
  char *read_position;
} ccursor_handle_t;

/**
 * @brief Macro to define a single shot char cursor handle
 *
 * This macro creates a single shot char cursor handle.
 * The handle is used for parsing operations on a single string.
 */
#define SINGLE_SHOT(_str)                                                      \
  &(ccursor_handle_t) {                                                        \
    .buffer = _str, .buffer_size = strlen(_str), .read_position = _str         \
  }

/**
 * @brief Initializes the char cursor with a given buffer and its size
 *
 * This function initializes the char cursor handle with the provided buffer
 * and its size. The handle keeps track of the current position in the buffer
 * for parsing operations.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[in]     buffer        - The buffer to be parsed
 * @param[in]     buffer_size   - The size of the buffer
 * @return true on parsing success, else false
 */
bool ccursor_init(ccursor_handle_t *handle, char *buffer, uint32_t buffer_size);

/**
 * @brief Retrieves the current available/left over characters in the buffer
 *
 * @param[in]     handle        - The char cursor handle
 * @return The number of available characters in the buffer
 */
size_t ccursor_available(ccursor_handle_t *handle);

/**
 * @brief Checks if the stream is empty
 *
 * This function checks if the char cursor handle has reached the end of the
 * buffer.
 *
 * @param[in]     handle        - The char cursor handle
 * @return true if the stream is empty, else false
 */
bool ccursor_is_empty(ccursor_handle_t *handle);

/**
 * @brief Retrieves a 32-bit unsigned integer from the stream
 *
 * This function retrieves a 32-bit unsigned integer from the char cursor
 * handle. It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u32(ccursor_handle_t *handle, uint32_t *value);

/**
 * @brief Retrieves a 16-bit unsigned integer from the stream
 *
 * This function retrieves a 16-bit unsigned integer from the char cursor
 * handle. It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u16(ccursor_handle_t *handle, uint16_t *value);

/**
 * @brief Retrieves an 8-bit unsigned integer from the stream
 *
 * This function retrieves an 8-bit unsigned integer from the char cursor
 * handle. It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u8(ccursor_handle_t *handle, uint8_t *value);

/**
 * @brief Retrieves a 32-bit integer from the stream
 *
 * This function retrieves a 32-bit integer from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i32(ccursor_handle_t *handle, int32_t *value);

/**
 * @brief Retrieves a 16-bit integer from the stream
 *
 * This function retrieves a 16-bit integer from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i16(ccursor_handle_t *handle, int16_t *value);

/**
 * @brief Retrieves an 8-bit integer from the stream
 *
 * This function retrieves an 8-bit integer from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i8(ccursor_handle_t *handle, int8_t *value);

/**
 * @brief Retrieves a 32-bit unsigned integer from the stream as little-endian
 *
 * This function retrieves a 32-bit unsigned integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u32_le(ccursor_handle_t *handle, uint32_t *value);

/**
 * @brief Retrieves a 16-bit unsigned integer from the stream as little-endian
 *
 * This function retrieves a 16-bit unsigned integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u16_le(ccursor_handle_t *handle, uint16_t *value);

/**
 * @brief Retrieves an 8-bit unsigned integer from the stream as little-endian
 *
 * This function retrieves an 8-bit unsigned integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u8_le(ccursor_handle_t *handle, uint8_t *value);

/**
 * @brief Retrieves a 32-bit signed integer from the stream as little-endian
 *
 * This function retrieves a 32-bit signed integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i32_le(ccursor_handle_t *handle, int32_t *value);

/**
 * @brief Retrieves a 16-bit signed integer from the stream as little-endian
 *
 * This function retrieves a 16-bit signed integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i16_le(ccursor_handle_t *handle, int16_t *value);

/**
 * @brief Retrieves an 8-bit signed integer from the stream as little-endian
 *
 * This function retrieves an 8-bit signed integer from the char cursor
 * handle as little-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i8_le(ccursor_handle_t *handle, int8_t *value);

/**
 * @brief Retrieves a 32-bit unsigned integer from the stream as big-endian
 *
 * This function retrieves a 32-bit unsigned integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u32_be(ccursor_handle_t *handle, uint32_t *value);

/**
 * @brief Retrieves a 16-bit unsigned integer from the stream as big-endian
 *
 * This function retrieves a 16-bit unsigned integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u16_be(ccursor_handle_t *handle, uint16_t *value);

/**
 * @brief Retrieves an 8-bit unsigned integer from the stream as big-endian
 *
 * This function retrieves an 8-bit unsigned integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit unsigned integer
 * @return true on parsing success, else false
 */
bool ccursor_read_u8_be(ccursor_handle_t *handle, uint8_t *value);

/**
 * @brief Retrieves a 32-bit signed integer from the stream as big-endian
 *
 * This function retrieves a 32-bit signed integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 32-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i32_be(ccursor_handle_t *handle, int32_t *value);

/**
 * @brief Retrieves a 16-bit signed integer from the stream as big-endian
 *
 * This function retrieves a 16-bit signed integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 16-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i16_be(ccursor_handle_t *handle, int16_t *value);

/**
 * @brief Retrieves an 8-bit signed integer from the stream as big-endian
 *
 * This function retrieves an 8-bit signed integer from the char cursor
 * handle as big-endian. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved 8-bit signed integer
 * @return true on parsing success, else false
 */
bool ccursor_read_i8_be(ccursor_handle_t *handle, int8_t *value);

/**
 * @brief Retrieves a byte from the stream
 *
 * This function retrieves a byte from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    byte          - The retrieved byte
 * @return true on parsing success, else false
 */
bool ccursor_read_byte(ccursor_handle_t *handle, uint8_t *byte);

/**
 * @brief Retrieves a boolean value from the stream
 *
 * This function retrieves a boolean value from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    value         - The retrieved boolean value
 * @return true on parsing success, else false
 */
bool ccursor_read_bool(ccursor_handle_t *handle, bool *value);

/**
 * @brief Retrieves a character from the stream
 *
 * This function retrieves a character from the char cursor handle.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    c             - The retrieved character
 * @return true on parsing success, else false
 */
bool ccursor_read_char(ccursor_handle_t *handle, char *c);

/**
 * @brief Skips a character in the stream
 *
 * This function skips a character in the char cursor handle. It advances the
 * current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[in]     c             - The character to skip
 * @return true on parsing success, else false
 */
bool ccursor_skip_char(ccursor_handle_t *handle, char c);

/**
 * @brief Skips characters in the stream until a specified character is found
 *
 * This function skips characters in the char cursor handle until the
 * specified character is found. It advances the current position in the buffer
 * accordingly such that the specified character is also skipped.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[in]     c             - The character to stop skipping after it
 * @return true on parsing success, else false
 */
bool ccursor_skip_until_char(ccursor_handle_t *handle, uint8_t c);

/**
 * @brief Skips substring at the beginning of the stream
 *
 * This function skips the requested substring at the beginning of the stream.
 * It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[in]     substr        - The substring to skip
 * @return true on parsing success, else false
 */
bool ccursor_skip_substr(ccursor_handle_t *handle, const char *substr);

/**
 * @brief Skips characters in the stream until a specified substring is found
 *
 * This function skips characters in the char cursor handle until the
 * specified substring is found. It advances the current position in the buffer
 * accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[in]     substr        - The substring to stop skipping at
 * @return true on parsing success, else false
 */
bool ccursor_skip_until_substr(ccursor_handle_t *handle, const char *substr);

/**
 * @brief Reads a substring from the stream
 *
 * This function reads a substring from the char cursor handle. It advances
 * the current position in the buffer accordingly. The provided substring buffer
 * must have enough space to store the substring and a null terminator.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    substr        - The retrieved substring
 * @param[in]     size          - The size of the substring (excluding null
 *                                terminator)
 * @return true on parsing success, else false
 */
bool ccursor_read_substr(ccursor_handle_t *handle, char *substr, size_t size);

/**
 * @brief Reads a substring from the stream until a specified character is found
 *
 * This function reads a substring from the char cursor handle until the
 * specified character is found. It advances the current position in the buffer
 * accordingly such that the specified character is also skipped.
 *
 * @param[in,out] handle        - The char cursor handle
 * @param[out]    substr        - The retrieved substring
 * @param[in]     size          - The size of the substring (excluding null
 *                                terminator)
 * @param[in]     c             - The character to stop reading at
 * @param[out]    written       - The number of characters written to the substr
 *                                buffer
 * @return true on parsing success, else false
 */
bool ccursor_read_substr_until_char(ccursor_handle_t *handle, char *substr,
                                    size_t size, char c, size_t *written);

/**
 * @brief Trims leading whitespace characters from the stream
 *
 * This function trims leading whitespace characters from the char cursor
 * handle. It advances the current position in the buffer accordingly.
 *
 * @param[in,out] handle        - The char cursor handle
 * @return true on parsing success, else false
 */
bool ccursor_trim_left(ccursor_handle_t *handle);

#endif // CCURSOR_HEADER
