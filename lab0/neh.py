import sys
import os
import itertools

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
                cmax_tab=[0 for x in range(m)]
                cmax_after=[[0 for x in range(m)] for y in range(n)]
	else:
		for v in range(m):
			array[i-1][v] = int(line.split()[v])
			

q = 0



cmax_tab=[0 for x in range(m)]


array.sort(key=sum, reverse=True)

def cmax(inp_array):
        q=0
        cmax_tab=[0 for x in range(m)]
        cmax_after=[[0 for x in range(m)] for y in range(n)]
        for v in range(m):
                for i in range(n):
                        if v==0:
                                cmax_tab[v]+=array[i][v]
                                cmax_after[i][0]=cmax_tab[v]
                        elif i==0 and not v==0:
                                q=v
                                while not q==-1:
                                        cmax_tab[v]+=array[0][q]
                                        cmax_after[i][v]=cmax_tab[v]
                                        q-=1
                        else:
                        
                                tmp1=max(cmax_tab[v],cmax_after[i][v-1])
                                cmax_tab[v]+=(tmp1-cmax_tab[v])+array[i][v]
                                cmax_after[i][v]=cmax_tab[v]
        return max(cmax_tab)

kurwa_tab=[[0 for x in range(m)] for y in range(n)]
print kurwa_tab,cmax(kurwa_tab)

array_new=[[0 for x in range(m)] for y in range(n)]

cmax_tmp=cmax(array)
i=0

for x in range(n):
        if x==0:
                for y in range(m):
                        array_new[x][y]=array[x][y]
        else:
                i=x
                for z in range(x):
                        array_tmp=array_new
                        for y in range(m):
                                array_tmp[x][y]=array[x][y]
                        if cmax_tmp > cmax(array_tmp):
                                array_new=array_tmp
                                cmax_tmp=cmax(array_tmp)
                        if not i<1:
                                array_tmp[i],array_tmp[i-1]=array_tmp[i-1],array_tmp[i]
                                i-=1
      

#print array_new

