import sys
import heapq

n, t, k, cmax = 0, 0, 0, 0

class Schrage:
	def __init__(self, r, p, q):
		self.r = r
		self.p = p
		self.q = q
	def getR(self):
		return self.r
	def getP(self):
		return self.p
	def getQ(self):
		return self.q

# OPEN FILE

if len(sys.argv) != 2:
	print("Wrong usage of script.")
	exit()
else:
	file = open(sys.argv[1])

N = []
G = []

for i,line in enumerate(file):
	if i == 0:
		n = int(line)
	else:
		tmpSchrage = Schrage(int(line.split()[0]),int(line.split()[1]), int(line.split()[2]))
		N.append(tmpSchrage)

e = N[0]

# ALGORITHM

while N or G:
	for v in N:
		if v.getR() <= t:
			e = v
			G.append(v)
			N.remove(v)
	if not G:
		t = N[0].getR()
		for v in N:
			if v.getR() <= t:
				t = v.getR()
	else:
		tmp = []
		for v in G:
			tmp.append(v.getQ())
		for v in G:
			if v.getQ() == max(tmp):
				e = v
				G.remove(v)
				break
		t = t + e.getP()
		cmax = max(cmax, t+e.getQ())

print(cmax)
		