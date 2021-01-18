defmodule YaraElixir do
  @moduledoc """
  Documentation for `YaraElixir`.
  """

  @doc """
  Hello world.

  ## Examples

      iex> YaraElixir.init_yara()
      0

  """
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('./libyara_elixir', 0)
  end

  def init_yara do
    raise "NIF not implemented: init_yara/0"
  end

  def destroy_yara do
    raise "NIF not implemented: destroy_yara/0"
  end
end
