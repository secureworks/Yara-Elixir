# Yara-Elixir

Proof-of-concept NIF implementation of Yara from Elixir.

## Getting Started

Install [Elixir][Elixir], [Erlang][Erlang], and [YARA][YARA]. A build
environment that includes [GCC][GCC] is expected as well.

Run `mix test` to build and execute the test suite.

If build failures are encountered, the GCC arguments in `mix.exs` may need to
be modified according to your environment.

[Elixir]: https://elixir-lang.org
[Erlang]: https://www.erlang.org
[YARA]: https://virustotal.github.io/yara/
[GCC]: https://gcc.gnu.org
