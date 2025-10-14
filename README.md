# Libft Tester

A lightweight, self-contained tester for **42’s libft**.  
It builds your `libft.a`, compiles the tests, and runs them — just like **Francinette** does.



## Project Structure

```
libft/ # ------------------------------- target repo
├─ Makefile
├─ libft.h
├─ *.c
└─ libft-tester/ # ---------------------- this tester
	├─ run_tests.sh # ------------------ main script
	├─ Makefile # ---------------------- builds test binary
	├─ libft.a # ----------------------- copied automatically
	├─ libft_tester.c # ----------------- main orchestrator
	└─ tests/
		├─ test_framework.h
		├─ test_framework.c
		├─ test_strlen.c
		├─ test_memcpy.c
		├─ test_strjoin.c
		└─ ...
```


## Usage

From inside the target **libft** repository:

```bash

git clone https://github.com/Guirie92/tests_libft.git
cd tests_libft
./run_tests.sh

```
This will:

- Run your make in the parent libft repo
- Copy libft.a and libft.h into the tester folder
- Build and run all tests


## Run Specific Tests

You can limit the tests to specific functions:

```bash

./run_tests.sh strlen memcpy

```
Will only run the tests for "ft_strlen" and "ft_memcpy".

To run the bonus, you can use either -b or --bonus:
```bash

./run_tests.sh -b

```


## Adding Your Own Tests

Each test group lives in a separate file inside tests/.
You can easily add more tests inside the corresponding test files, or create new ones.
For newly created files, be sure to update the `test_libft.c` and `test_framework.h` files.


## Example Output

```yaml

Building target's libft...
Compiling libft_tests...

...
strlen      : 1.OK✔  2.OK✔  3.OK✔  4.OK✔  5.OK✔  6.OK✔  7.OK✔  8.OK✔
memcpy      : 1.OK✔  2.OK✔  3.OK✔  4.OK✔  5.OK✔  6.OK✔  7.OK✔  8.OK✔  9.OK✔ 
strjoin     : 1.OK✔  2.OK✔  3.OK✔  4.OK✔  5.OK✔  6.OK✔  7.OK✔  8.OK✔  9.OK✔  10.OK✔ 
...

All tests passed (43)

```
If any test fails, you’ll see detailed failure info:

```yaml
...
memcpy       : 1.KO✗ 2.OK✓ 3.KO✗ ...
memcpy (1): diff: expected='abcdef' | got='abcxef'
memcpy (3): diff: expected='012345' | got='01234'
...

```


## Requirements

- A valid Makefile that builds libft.a
- Bash shell (on macOS/Linux or WSL)


## License

MIT License (free to use and modify)