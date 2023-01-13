defmodule YaepExampleTest do
  use ExUnit.Case
  doctest YaepExample

  test "greets the world" do
    assert YaepExample.hello() == :world
  end
end
