# Yara-Elixir

Proof-of-concept NIF implementation of Yara from Elixir.

## Getting Started

Install [Elixir][Elixir], [Erlang][Erlang], and [YARA][YARA]. A build
environment that includes [GCC][GCC] is expected as well.

Run `mix test` to build and execute the test suite.

### Example

```
$ mix test --trace


YaraElixirTest [test/yara_elixir_test.exs]
  * test does not raise a RuntimeError on destroy_yara (0.00ms) [L#13]
  * doctest YaraElixir.load_nifs/0 (1) (0.07ms) [L#3]
  * test does not raise a RuntimeError on init (0.00ms) [L#5]


Finished in 0.2 seconds
1 doctest, 2 tests, 0 failures
```

If build failures are encountered, the GCC arguments in `mix.exs` may need to
be modified according to your environment.

[Elixir]: https://elixir-lang.org
[Erlang]: https://www.erlang.org
[YARA]: https://virustotal.github.io/yara/
[GCC]: https://gcc.gnu.org
