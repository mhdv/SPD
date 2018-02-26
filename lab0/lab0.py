import sys
import os

n = 0
m = 0


if len(sys.argv) != 2:
	print("Wrong usage of script.")
	exit()
else:
	file = open(sys.argv[1])

for i,line in enumerate(file):
	if i == 0:
		n = int(line.split()[0])
		m = int(line.split()[1])
		array = [[0 for x in range(m)] for y in range(n)]
	else:
		for v in range(m):
			array[i-1][v] = int(line.split()[v])
			
time = 0
c = 0

for v in range(n):
	for i in range(m):
		if v == 0 and i == 0:
			c += array[v][i]

		# elif v == 0 and not i == 0:
		# 	c += array[v][i-1]
		elif not v == 0 and i == 0:
			c += array[v][i]
		# else:
			# c += max(array[v][i-1], array[v-1][i])

print(array)
print(c)