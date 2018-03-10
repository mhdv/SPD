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


array_new=[[0 for x in range(m)] for y in range(n)]
array_tmp=[[0 for x in range(m)] for y in range(n)]
i=0

for x in range(n):
        if x==0:
                print 'przed dodaniem elementu:', array_new
                array_new[x]=array[x]
                print 'po dodaniu elementu:', array_new
        else:
                i=x

                print 'przed dodaniem elementu:', array_new
                array_new[x]=array[x]
                print 'po dodaniu elementu:', array_new
                for k in range(n):
                        array_tmp[k] = array_new[k]
                cmax_tmp = cmax(array_tmp)
                print 'cmax z elementem na koncu:', cmax_tmp
                #print 'dodanie elementu: ',array_tmp
                for z in range(x):
                        #print 'tmp:',cmax_tmp,'cmax:',cmax(array_tmp)
                        
                                cmax_tmp=cmax(array_tmp)
                                if not i<1:
                                        print 'przed zamiana: cmax:',cmax(array_tmp),'najlepszy dotychczas:', cmax(array_new)
                                        array_tmp[i],array_tmp[i-1]=array_tmp[i-1],array_tmp[i]
                                        i-=1
                                        print 'po zamianie: cmax:', cmax(array_tmp),'najlepszy dotychczas:', cmax(array_new)
                                if cmax_tmp > cmax(array_tmp):
                                        print 'znalezienie lepszej konfiguracji, przypisanie:',array_tmp
                                        cmax_tmp=cmax(array_tmp)
                                        for k in range(n):
                                                array_new[k] = array_tmp[k]
                       
print array_new, cmax(array_new)

