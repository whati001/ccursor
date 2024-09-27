# ccursor - a simple C char cursor parsing lib

Ccusor is a very simple, straightforward fixed string parsing library written and designed for C based projects. Working with strings in C is not trivial and requires a lot of caution to not mess around with the memory. This library aims to simplify string handling by implementing the cursor design pattern.  

## Installation

The library can be easily integrated into every [CMake](https://cmake.org/) based project. Simply either add the repository as submodule or copy based the source files into your project.
We recommend to add the library as a submodule and include it via the [CMake](https://cmake.org/) features `add_subdirectory` and `target_link_library`.

## Porting

The library can be easily ported to different architectures/toolchains, by simply implementing the macros defined in `ccursor_port.h`.
At the moment, a single port exists for clib based toolchains.

## Usage

The library can be used as follows to parse an integer value from a fixed sized string.

```c
// fixed string to parse
char* str = "PRE+10,20,0x1234";

// initiate new ccursor handle
ccursor_ret_t ret = false; 
ccursor_handle_t handle;
ret = ccursor_init(&handle, str, strlen(str));

// scan through the string
uint8_t first = 0;
uint16_t second = 0;
uint32_t third = 0;

ret |= ccursor_skip_substr(&handle, "PRE+");
ret |= ccursor_read_u8(&handle, &first);
ret |= ccursor_skip_char(&handle, ',');
ret |= ccursor_read_u16(&handle, &second);
ret |= ccursor_skip_char(&handle, ',');
ret |= ccursor_read_u32_be(&handle, &third);
ret |= ccursor_is_empty(&handle);

// validate values
assert(ret == E_CCURSOR_OK);
assert(first == 10);
assert(second == 20);
assert(third == 0x1234);
```

If it is only desired to parse a single value, the library provides the `SINGLE_SHOT` macro which removes the boilerplate of initiating a new cursor. Please find below an example:

```c
// parse a single value
uint8_t value = 0;
ccursor_ret_t ret = ccursor_read_u8(SINGLE_SHOT("20"), &value);
assert(value == 20);
```

## Contributing

Please feel free to contribute via PRs. We only accept changes, which are covered by unit tests. Please have a look into the `tests` directory.

## Contact

* [whati001](https://whati001.rehka.dev)
