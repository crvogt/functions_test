def my_gen():
	myList = range(3)
	print('printing my list')
	print(myList)
	for i in myList:
		yield i*i 

myGenerator = my_gen() #Creates a generator 

print(myGenerator) # It's an object!

for i in myGenerator:
	print('printed')
	print(i)