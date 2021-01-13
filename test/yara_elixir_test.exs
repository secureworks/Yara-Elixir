defmodule YaraElixirTest do
  use ExUnit.Case
  doctest YaraElixir

  test "does not raise a RuntimeError on init" do
    try do
      YaraElixir.init_yara()
    rescue
      RuntimeError -> assert false
    end
  end

  test "does not raise a RuntimeError on destroy_yara" do
    try do
      YaraElixir.destroy_yara()
    rescue
      RuntimeError -> assert false
    end
  end
end
