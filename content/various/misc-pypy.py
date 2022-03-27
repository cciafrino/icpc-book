# read until eof
import sys

for line in sys.stdin:
	v = line.split()
	for x in v:
		x = int(x)
		
# create matrix Matrix[n][m]
n, m = 5, 10
Matrix = [[0 for j in range(m)] for i in range(n)]	

# print 2 decimal places
print("%.2f" % x)
