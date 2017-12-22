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

  for line in infile.readlines():
    line = line.strip()
    if len(line) < 1:
      continue
    elif line[0] is "#":
      continue
    elif "desc" in line:
      temp = line.split(" ")[1][1:-1]
      if temp is  not "":
        desc = temp
    elif "homepage" in line:
      temp = line.split(" ")[1][1:-1]
      if temp is  not "":
        homepage = temp
    elif "url" in line:
      temp = line.split(" ")[1][1:-1]
      if temp is  not "":
        url = temp
    elif "sha256" in line:
      temp = line.split(" ")[1][1:-1]
      if temp is  not "":
        sha256 = temp
    elif "def" in line:
      temp = line.split(" ")[1]
      instructions[temp] = "test"

  print("Desc:", desc)
  print("Homepage:", homepage)
  print("URL:", url)
  print("SHA-256:", sha256)
