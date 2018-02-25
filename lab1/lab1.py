import sys
import heapq

n = 0

class Jack:
	def __init__(self, r, p):
		self.r = r
		self.p = p
	def __str__(self):
		return str(self.r) + "and" + str(self.p)
	def getR(self):
		return self.r
	def getP(self):
		return self.p

if len(sys.argv) != 2:
	print("Wrong usage of script.")
	exit()
else:
	file = open(sys.argv[1])

data = []

for i,line in enumerate(file):
	if i == 0:
		n = int(line)
	else:
		tmpJack = Jack(int(line.split()[0]),int(line.split()[1]))
		heapq.heappush(data, (tmpJack.getR(), tmpJack.getP()))
		
array = [0] * (n+1)

for v in range(n):
	tmp = heapq.heappop(data)
	if array[v] > tmp[0]:
		array[v+1] = array[v] + tmp[1]
	else:
		array[v+1] = tmp[0] + tmp[1]

print(array[n])
		