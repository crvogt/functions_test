x = "%d types of people" % 10
binary = 'binary'
do_not = 'don\'t'
y = "Those who know %s and those who %s" % (binary, do_not)

print x
print y

print "First said: %r" % x
print "Then said: %s" % x

hilarious = False 
joke_evaluation = "Is that joke funny? %r"

print joke_evaluation % hilarious

w = "The first part of a "
e = "two part string"

print w + e