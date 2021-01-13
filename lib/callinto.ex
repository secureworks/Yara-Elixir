defmodule Mix.Tasks.Callinto do
  use Mix.Task

  def run(_args) do
    YaraElixir.init_yara()
    YaraElixir.destroy_yara()
  end
end
