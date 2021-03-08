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

  test "does not raise a RuntimeError on create_compiler" do
    try do
      YaraElixir.create_compiler()
    rescue
      RuntimeError -> assert false
    end
  end

  test "does not raise a RuntimeError on destroy_compiler" do
    try do
      compiler = YaraElixir.create_compiler()
      YaraElixir.destroy_compiler(compiler)
    rescue
      RuntimeError -> assert false
    end
  end

  test "needs a compiler to destroy_compiler" do
    results = YaraElixir.destroy_compiler(nil)
    assert results == {:error, :not_a_reference}
  end

  test "needs a compiler to compile rules" do
    results = YaraElixir.compile_string(nil, nil)
    assert results == {:error, :not_a_reference}
  end

  test "needs a string to compile rules" do
    try do
      compiler = YaraElixir.create_compiler()
      results = YaraElixir.compile_string(compiler, nil)
      assert results == {:error, :not_a_binary}
      YaraElixir.destroy_compiler(compiler)
    rescue
      RuntimeError -> assert false
    end
  end

  test "can compile simple rules" do
    try do
      true_rule = "rule True { condition: true }"
      compiler = YaraElixir.create_compiler()
      errors = YaraElixir.compile_string(compiler, true_rule)
      assert errors == 0
      YaraElixir.destroy_compiler(compiler)
    rescue
      RuntimeError -> assert false
    end
  end

  test "conveys compilation errors" do
    try do
      bad_rule = "rule BadRule { condtion: invalid_identifier }"
      compiler = YaraElixir.create_compiler()
      errors = YaraElixir.compile_string(compiler, bad_rule)
      assert errors == 1
      YaraElixir.destroy_compiler(compiler)
    rescue
      RuntimeError -> assert false
    end
  end
end
