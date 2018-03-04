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
			
time = 0
c = 0
q=0

perms=list(itertools.permutations(array))
cmax_total=0;

array=perms[0]

for p in range(len(perms)):
        array=perms[p]
        cmax_tab=[0 for x in range(m)]
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
        if p==0:
                cmax_total=max(cmax_tab)
        else:
                cmax_total=min(cmax_total,max(cmax_tab))
        if max(cmax_tab)==637:
                print cmax_tab
                print array
print 'Najkrotszy czas wykonania to',cmax_total
