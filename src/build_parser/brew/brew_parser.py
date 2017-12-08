#! /usr/bin/env python3
# NOTE: requires Python 3 to be installes, otherwise SOL
# Brew parser prototype
# Will be rewritten in C once I figure out how things work
# For testing purposes, pass args in cmdline
# ./brew_parse [brew formula]

from sys import argv

# TODO: FIX!!!!!
@contextmanager
def opened_w_error (filename, mode="r"):
	try:
		f = open (filename, mode)
	except Error:
		yield None, True
	else:
		try:
			yield f, False
		finally:
			f.close ()

if len(argv) < 2:
	print ("Please provide a filename")
	quit (-1)

with opened_w_error (argv[1], "r") as (infile, err):
	if err:
		print ("File not found: %s" % argv[1])
		quit (-1)
	else:
		print ("File exists")
		quit (0)
