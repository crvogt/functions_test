x = 'myFile'
y = '.csv'

#Two different methods for doing file names with different values

for i in range(0, 4):
	j = "%d" % i
	print x + j + y

print x + str(i) + y