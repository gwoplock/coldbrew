#! /usr/bin/env python3
# NOTE: requires Python 3 to be installes, otherwise SOL
# Brew parser prototype
# Will be rewritten in C once I figure out how things work
# For testing purposes, pass args in cmdline
# ./brew_parse [brew formula]

from sys import argv

if len(argv) < 2:
  print("Please provide a filename")
  quit (-1)

with open(argv[1], "r") as infile:
  desc = "NULL"
  homepage = "NULL"
  url = "NULL"
  sha256 = "NULL"
  instructions = {}

  lines = infile.readlines()
  cx = 0
  length = len(lines)
  while cx < length:
    line = lines[cx].strip()
    if len(line) < 1 or line[0] is "#":
      del lines[cx]
      length = length - 1
    else:
      lines[cx] = line
      cx = cx + 1

  for line in lines:
    print(line)

  print("Desc:", desc)
  print("Homepage:", homepage)
  print("URL:", url)
  print("SHA-256:", sha256)
