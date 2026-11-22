*This project has been created as part of the 42 curriculum by hzheng2.*

## Description

**ft_printf** is a custom implementation of the standard C library function `printf`. The primary goal of this project is to understand variadic functions in C (`<stdarg.h>`) and build a clean, modular, and norm-compliant formatting engine compiled into a static library (`libftprintf.a`).

### Supported Conversions (Mandatory)
- `%c` — Prints a single character.
- `%s` — Prints a string (as defined by the common C convention).
- `%p` — Prints a `void *` pointer argument in hexadecimal format (`0x...`).
- `%d` — Prints a decimal (base 10) number.
- `%i` — Prints an integer in base 10.
- `%u` — Prints an unsigned decimal (base 10) number.
- `%x` — Prints a number in hexadecimal (base 16) lowercase format.
- `%X` — Prints a number in hexadecimal (base 16) uppercase format.
- `%%` — Prints a percent sign.

### Supported Flags & Modifiers (Bonus)
- **Flags:** `-` (left-justify), `0` (zero-padding), `#` (alternate form `0x`/`0X`), `+` (force sign), and ` ` (space before positive numbers).
- **Field Width:** Minimum field width handling across all supported conversions.
- **Precision:** `.` precision handling for strings and numeric conversions.

### Algorithm & Data Structure Overview
The implementation parses the format string sequentially using a central controller (`centor.c` / `centor_bonus.c`). When a `%` character is encountered, a dedicated format structure (`t_format`) stores all active flags, width, precision, and conversion specifier state (`set_format.c` / `set_format_bonus.c`). Depending on the specifier, specialized helper modules calculate output lengths (`count_len.c`) and write the formatted characters directly to standard output via `write(2)`, tracking and returning the total number of bytes printed.

---

## Instructions

### Compilation
Clone the repository and run `make` at the root directory to build the mandatory library (`libftprintf.a`):

```bash
git clone <your-repo-url> ft_printf
cd ft_printf
make
```

To compile with **bonus** features included:

```bash
make bonus
```

### Testing & Verification

1. **Check Norminette, Makefile relinking, and allowed external functions:**
```bash
norminette
make fclean && make && make
nm -u libftprintf.a
make fclean && make bonus && make bonus
nm -u libftprintf.a
```

2. **Run Tripouille's `printfTester`:**
```bash
git clone [https://github.com/Tripouille/printfTester.git](https://github.com/Tripouille/printfTester.git)
cd printfTester && make a && cd ..
```

3. **Run paulo-santana's `ft_printf_tester`:**
```bash
git clone [https://github.com/paulo-santana/ft_printf_tester.git](https://github.com/paulo-santana/ft_printf_tester.git)
cd ft_printf_tester && bash test a && cd ..
```

4. **Clean up test suites and build artifacts before pushing:**
```bash
rm -rf printfTester ft_printf_tester
make fclean
git status
```

---

## Resources

- **Documentation & Manuals:**
  - `man 3 printf` & `man 3 stdarg` — Official Linux/macOS manual pages for format specifications and variadic macros (`va_start`, `va_arg`, `va_copy`, `va_end`).
  - [CPPReference - Variadic functions](https://en.cppreference.com/w/c/variadic) — Reference on C variadic argument handling and standard type promotions.
- **AI Usage Disclosure:**
  - AI assistance was used during the final stages of development to debug Makefile relinking and header path rules (`-I. -Ibonus`), verify 42 Norminette compliance, and structure this `README.md` documentation. All core C implementation logic, parsing algorithms, and formatting routines were written and tested manually.
