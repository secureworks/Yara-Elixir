# Yara-Elixir

Proof-of-concept [NIF][NIF] implementation of Yara from Elixir.

## Getting Started

Install [Elixir][Elixir], [Erlang][Erlang], and [YARA][YARA]. A build
environment that includes [GCC][GCC], [CMake][CMake], and [GNU Make][GNU Make]
is expected as well.

### Build the NIF

First run "cmake":

```shell
$ cmake .
-- Using OTP lib: /usr/local/Cellar/erlang/24.1.2/lib/erlang/lib - found
-- Using erl_interface version: erl_interface-5.1
-- Using erts version: erts-12.1.2
-- Using YARA version: 4.1.3
-- Using YARA CFLAGS: -I/usr/local/Cellar/openssl@1.1/1.1.1l_1/include;-I/usr/local/Cellar/yara/4.1.3/include;-I/usr/local/Cellar/jansson/2.14/include
-- Using YARA LDFLAGS: -L/usr/local/Cellar/yara/4.1.3/lib;-lyara
-- Configuring done
-- Generating done
-- Build files have been written to: ~/Yara-Elixir
```

Then "make":

```shell
$ make
[ 33%] Building C object CMakeFiles/YE_NIF_TARGET.dir/shared/yara_elixir.c.o
[ 66%] Building C object CMakeFiles/YE_NIF_TARGET.dir/shared/debug.c.o
[100%] Linking C shared library libyara_elixir.so
[100%] Built target YE_NIF_TARGET
```

### Get Elixir Dependencies

Use Mix to get the project dependencies:

```shell
$ mix deps.get
Resolving Hex dependencies...
Dependency resolution completed:
...
```

### Execute the Tests

Use Mix to execute the tests:

```shell
$ mix test --trace


YaraElixirTest [test/yara_elixir_test.exs]
  * test does not raise a RuntimeError on create_compiler (0.05ms) [L#21]
  * test can compile simple rules (0.7ms) [L#59]
  * test needs a compiler to compile rules (0.00ms) [L#43]
  * test needs a string to compile rules (0.02ms) [L#48]
  * test does not raise a RuntimeError on destroy_compiler (0.02ms) [L#29]
  * doctest YaraElixir.load_nifs/0 (1) (0.05ms) [L#3]
  * test does not raise a RuntimeError on init (0.00ms) [L#5]
  * test does not raise a RuntimeError on destroy_yara (0.00ms) [L#13]
  * test conveys compilation errors (0.3ms) [L#71]
  * test needs a compiler to destroy_compiler (0.00ms) [L#38]


Finished in 0.1 seconds (0.00s async, 0.1s sync)
1 doctest, 9 tests, 0 failures
```

[Elixir]: https://elixir-lang.org
[Erlang]: https://www.erlang.org
[YARA]: https://virustotal.github.io/yara/
[GCC]: https://gcc.gnu.org
[NIF]: http://www1.erlang.org/doc/man/erl_nif.html
[CMake]: https://cmake.org
[GNU Make]: https://www.gnu.org/software/make/
