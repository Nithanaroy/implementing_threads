"""
A script to extract the function names of the format void test_...()
"""

def main():
	import sys
	if len(sys.argv) is not 2:
		print '\nInvalid command line args. Example:'
		print '\tpython extract_test_function_names.py filename.c\n'
		return

	f = open(sys.argv[1], 'r').read().splitlines()
		
	m = extract_function_names(f)

	for func in m:
		print func + ";"

def extract_function_names(f):
	"""
	given the lines array of a file, returns the function names of the form, void test_...()
	"""
	import re
	m = []
	for l in f:
		x = re.match(r'void (test_.*\(\))', l)
		if x:
			m.append(x.group(1))
	return m

if __name__ == "__main__":
	main()