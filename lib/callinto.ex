defmodule Mix.Tasks.Callinto do
  @moduledoc "Calls into the NIF"
  use Mix.Task

  def run(_args) do
    YaraElixir.init_yara()
    YaraElixir.destroy_yara()
  end

end
