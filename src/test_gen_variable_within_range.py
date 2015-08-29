import math
import random


##
## Este generador hace tests con las pequenias variaciones entre las tempereaturas internas, y entre las externes
## Ej, si una interna vael 1300, la de al lado va a vale 1300 +- 10 grados, y asi siguiendo
##



# ri, re, m+1 radios, n angulos, isoterma, ninst, n temps internas, n temps externas
ri = 0
while ri == 0:
	ri = random.random() + random.randint(1,50)
re = ri 
while re == ri:
	re = random.randint(math.ceil(ri),100) + random.random()
m = 10
n = random.randint(20,200)
isoterma = 500
ninst = 200
print str(ri) + " " + str(re) + " " + str(m) + " " + str(n) + " " + str(isoterma) + " " + str(ninst)

#for x in range(0,n):
	#print str(random.randint(0, 999)) + " ",
	#print str(random.randint(1000, 2000)) + " ",


for y in range(1,ninst+1):
	temps_intern = [random.randint(1400,1500)+random.random()]
	temps_extern = [random.randint(0,100)+random.random()]
	for x in range(0,n):
		temps_intern.append(temps_intern[x] + random.randint(-10,10) + random.random())
		temps_extern.append(temps_extern[x] + random.randint(-10,10) + random.random())
	for z in range(0,n):
		print str(temps_intern[z]) + " ",
	for z in range(0,n):
		print str(temps_extern[z]) + " ",
	print ""
	print " "



'''
>>> random.random()        # Random float x, 0.0 <= x < 1.0
0.37444887175646646
>>> random.uniform(1, 10)  # Random float x, 1.0 <= x < 10.0
1.1800146073117523
>>> random.randint(1, 10)  # Integer from 1 to 10, endpoints included
7
>>> random.randrange(0, 101, 2)  # Even integer from 0 to 100
26
>>> random.choice('abcdefghij')  # Choose a random element
'c'

>>> items = [1, 2, 3, 4, 5, 6, 7]
>>> random.shuffle(items)
>>> items
[7, 3, 2, 5, 6, 4, 1]

>>> random.sample([1, 2, 3, 4, 5],  3)  # Choose 3 elements
[4, 1, 5]
'''