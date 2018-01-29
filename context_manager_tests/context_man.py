# files = []

#Leads to too many open files
# for x in range(10000):
# for x in range(1000):
# 	files.append(open('foo.txt', 'w'))

#Lesson: Don't leak file descriptors!
#Leaking occurs by not closing opened files

#One example on how to fix it
# files = []
# for x in range(10000):
# 	f = open('foo.txt', 'w')
# 	f.close()
# 	files.append(f)
# 	# print files #For fun

#An even better way to do this
#Context managers provide a convenient method for 
#cleaning up a variable that requires it. It guarantees
#that cleanup will happen
#Using with, we can call anything that returns a Context managers
#(like the built-in open() function). We assign it to a variable
#using ... as <variable_name>. Importantly, the variable only
#exists within the indented block below the with statement.
#YOu can think of with as creating a mini-function, we can use the variable
#freely in the indented portion, but once that block ends, the 
#variable goes out of scope. When the variable goes out of scope,
#it automatically calls a special method that contains the code to clean up the 
#resource.
#Where is the code that is actually being called when the variable
#goes out of scope? Wherever the context manager is defined.
#Several ways to create a context manager. The simplest is to 
#define a class that contains two special methods: __enter__()
#and __exit__()
#__enter__() returns the resource to be managed (like a file object
#in the case of open()). __exit__() does any cleanup work and returns nothing

#To make things more clear, let's create a totally redundant context manager 
#for working with files:
class File():
	def __init__(self, filename, mode):
		print("Creating class")
		self.filename = filename
		self.mode = mode

	def __enter__(self):
		self.open_file = open(self.filename, self.mode)
		return self.open_file

	def __exit__(self, *args):
		self.open_file.close()

files = []
for _ in range(10000):
	with File('foobar.txt', 'w') as infile:
		infile.write('foo')
		files.append(infile)