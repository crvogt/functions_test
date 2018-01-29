items = [('name', 'Gumby'), ('age', 42)]
d = dict(items)

print d
print d['name']

print 'Number of values in dict %d'%len(d)
v = 'Lenart'
d['name'] = v 
print 'Printing v', v
# d = dict(name='Gumby', age=42)
print d
print d['name']

#Simple dictionary example
#A simple database

#A dictionary with person names as keys. Each person is represented as
#another dictionary with the keys 'phone' and 'addr' referring to their phone
#number and address, respectively

people = {
	'Alice':{
		'phone': '2341',
		'addr': 'Foo Drive'
	},

	'Beth':{
		'phone': '9102',
		'addr': 'Bar street 42'
	},

	'Cecil':{
		'phone': '9122',
		'addr': 'Baz ave'
	}
}

#Descriptive labels for the phone number and address. These will be used
#when printing the output
labels = {
	'phone': 'phone number',
	'addr': 'address'
}

name = raw_input('Name: ')

#Are we looking for a phone number or an address?
request = raw_input('Phone number (p) or address (a)?')

#Use the correct key:
if request == 'p': key = 'phone'
if request == 'a': key = 'addr'

#Only try to print information if the name is a valid key in 
#our dictionary
if name in people: print "%s's %s is %s." % (name, labels[key], people[name][key])