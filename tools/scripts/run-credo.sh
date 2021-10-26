#!/usr/bin/env bash
mix local.hex --force
mix deps.get
exec mix credo
