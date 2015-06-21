"""print "How old are you?"
age = raw_input()
print "How tall are you?"
height = raw_input()
print "How much do you weigh?"
weight = raw_input('->->->')

print "You are %s years old, %s inches tall, and weigh %s pounds" % (age, height, weight)

#Or you can type it as

age = int(raw_input("How old are you?: "))
height = int(raw_input("How tall are you?: "))
weight = int(raw_input("How much do you weigh?: "))

print "You are %d years old, %d inches tall, and weigh %d pounds" % (age, height, weight)
"""


#from sys import argv

#script, first, second, third = argv

"""
Format for getting this to work:
python ex1.py first second third
^put this in at command line
"""

#print "Script called:", script
#print "first var:", first
#print "second var:", second
#print "third var:", third