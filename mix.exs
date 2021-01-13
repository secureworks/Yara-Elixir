defmodule Mix.Tasks.Compile.YaraElixir do
  @doc """
  Returns GCC arguments depending on `:os.type/0`.
  """
  def os_args() do
    if elem(:os.type(), 1) == :darwin do
      [
        "-fPIC",
        "-flat_namespace",
        "-undefined",
        "suppress",
        "-I/usr/local/Cellar/erlang/23.2.1/lib/erlang/usr/include",
        "-L/usr/local/Cellar/erlang/23.2.1/lib/erlang/usr/lib",
        "-lyara",
        "-L/usr/local/Cellar/yara/4.0.2/lib"
      ]
    else
      [
        "-fPIC",
        "-shared",
        "-I/usr/lib/erlang/usr/include",
        "-lyara"
      ]
    end
  end

  @doc """
  Returns compiler definitions depending on `Mix.env()/0`.
  """
  def env_args() do
    cond do
      Mix.env() == :dev -> ["-DCHATTY"]
      true -> []
    end
  end

  def run(_args) do
    gcc_args = os_args() ++ env_args()
    cmd_args = gcc_args ++ ["shared/yara_elixir.c", "-o", "yara_elixir.so"]
    {result, _errcode} = System.cmd("gcc", cmd_args, stderr_to_stdout: true)
    IO.puts(result)
  end
end

defmodule YaraElixir.MixProject do
  use Mix.Project

  def project do
    [
      app: :yara_elixir,
      version: "0.1.0",
      elixir: "~> 1.10",
      start_permanent: Mix.env() == :prod,
      deps: deps(),
      compilers: [:yara_elixir] ++ Mix.compilers()
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # {:dep_from_hexpm, "~> 0.3.0"},
      # {:dep_from_git, git: "https://github.com/elixir-lang/my_dep.git", tag: "0.1.0"}
    ]
  end
end
