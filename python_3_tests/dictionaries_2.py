from copy import deepcopy

x = {}
print x
y = x
x['key'] = 'value'
print x
print y
x = {}
print x
print y

x.clear()

x = {'username': 'admin', 'machines': ['foo', 'bar', 'baz']}
y = x.copy()
print x
print y
print 'Clearing x'
# x.clear()
print x
print y
print y['machines'][0][0]
y['machines'].remove('bar')
y['username'] = 'carson'
print x
print y

d = {}
d['names'] = ['Jack', 'Hugh']
c = d.copy()
dc = deepcopy(d)
d['names'].append('Clive')
print c
print dc