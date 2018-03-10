import sys
import os
import itertools
import numpy as np

n, m = 0, 0

# FILE READ

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

array.sort(key=sum, reverse=True)
# array = zip(*array)

# CMAX IN RANGE

# def cmax(data, length):
# 	data = zip(*data)
# 	length = len(data)
# 	# print("lool")
# 	if length > len(data):
# 		print("Wrong data length!")
# 		exit()
# 	else:
# 		c_max = []
# 		for v in range(length):
# 			if v > 0:
# 				c_max.append(data[v][0]+c_max[v-1])
# 			else:
# 				c_max.append(data[v][0])
# 		for v in range(len(c_max)):
# 			for i in range(1, len(data[length-1])):
# 				c_max[v] += data[v][i]
# 		return max(c_max)

def cmax(inp_array):
        q=0
        cmax_tab=[0 for x in range(m)]
        cmax_after=[[0 for x in range(m)] for y in range(len(inp_array))]
        for v in range(m):
                for i in range(len(inp_array)):
                        if v==0:
                                cmax_tab[v]+=inp_array[i][v]
                                cmax_after[i][0]=cmax_tab[v]
                        elif i==0 and not v==0:
                                q=v
                                while not q==-1:
                                        cmax_tab[v]+=inp_array[0][q]
                                        cmax_after[i][v]=cmax_tab[v]
                                        q-=1
                        else:
                        
                                tmp1=max(cmax_tab[v],cmax_after[i][v-1])
                                cmax_tab[v]+=(tmp1-cmax_tab[v])+inp_array[i][v]
                                cmax_after[i][v]=cmax_tab[v]
        return max(cmax_tab)

# NEH ALGORITHM

def neh(arr):
	if len(arr) < 2:
		print("Wrong array!")
		exit()
	else:
		for v in range(2, len(arr)+1):
			final = float("inf")
			tmp = arr[:v]
			for i in range(v, 0, -1):
				tmp2 = tmp[0:-1]
				tmp2.insert(i-1,tmp[-1])
				cm = cmax(tmp2)
				if cm < final:
					final = cm
					tmp3 = tmp2
			arr[:v] = tmp3
	return final
print(neh(array))

# print(array)
# print(list(itertools.permutations(array))[0])
# print(list(itertools.permutations(array))[1])