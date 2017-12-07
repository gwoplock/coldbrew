#! /usr/bin/env python3
# NOTE: requires Python 3 to be installes, otherwise SOL
# Brew parser prototype
# Will be rewritten in C once I figure out how things work
# For testing purposes, pass args in cmdline
# ./brew_parse [brew formula]

from sys import argv

with open (argv[1], "r") as (inf, err):
    if err:
	print ("File not found: %s" % argv[1])
    else
	print ("File exists")
