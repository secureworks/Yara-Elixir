defmodule Mix.Tasks.Compile.YaraElixir do

  @doc """
  Returns compiler definitions depending on `Mix.env()/0`.
  """
  def env_args() do
    cond do
      Mix.env() == :dev -> ["-DCHATTY"]
      true -> []
    end
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
    ]
  end
end
