import sys
import random

# function which writes a test file with a specific n value
# m = radios
def writetestfile(file,m):

	print('Creating new test in file')

	try:
		ri = 10
		re = 200
		n = 10			# angles
		iso = 500		# isoterma
		ninst = 40 		# instances

		#write first line
		file.write('%i %i %i %i %i %i\n' % (ri ,re,m,n,iso,ninst))



		for inst in range(0,ninst):

			#write each b vector (100 in total) 
			ti1 = random.uniform(1000.0, 1500.0)
			te1= random.uniform(100.0, 900.0)
			print('%f %f' % (ti1,te1))
			#first n (tint)
			for i in range(0,n):
				ti = random.uniform(ti1-250.0, ti1+250.0)
				if ti < 800:
					ti = 800
				ti1 = ti
				file.write('%i ' % ti)
			#last n (text)
			for i in range(0,n):
				te = random.uniform(te1-250.0, te1+250.0)
				if te > 800:
					te = 800
				if te < 0:
					te = 0
				te1 = te
				file.write('%i ' % te)

			
			file.write('\n')


		file.close()
		
	except:
		print('Something went wrong')
		sys.exit(0) #quit python





#main function to generate test files
for m in range (5,81):
	file = open('generated_tests/testM'+str(m)+'.in','w')
	writetestfile(file,m)