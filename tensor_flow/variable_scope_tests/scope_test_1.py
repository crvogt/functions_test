import tensorflow as tf 

# with tf.variable_scope("foo"):
# 	with tf.variable_scope("bar"):
# 		v = tf.get_variable("v", [1])
# 		print v
# 		assert v.name == "foo/bar/v:0"	

# #Basic example of sharing a variable AUTO_REUSE:

# def foo():
# 	with tf.variable_scope("foo", reuse=tf.AUTO_REUSE):
# 		v = tf.get_variable("v", [1])
# 	return v 

# def fooTwo():
# 	with tf.variable_scope("fooTwo", reuse=tf.AUTO_REUSE):
# 		x = tf.get_variable("v", [1])
# 	return x

# def fooThree():
# 	with tf.variable_scope("foo", reuse=tf.AUTO_REUSE):
# 		z = tf.get_variable("v", [1])
# 	return z

# v1 = foo() #Creates v 
# v2 = fooTwo() #Gets the same, existing v 
# v3 = fooThree()
# # v2 = 5
# # assert v1 == v2
# if v1 == v2:
# 	print "v1 and v2 are equal!"
# elif v1 == v3:
# 	print "v1 and v3 are equal!"

#Now looking at name scope 
# with tf.name_scope("my_scope"):
# 	v1 = tf.get_variable("var1", [1], dtype=tf.float32)
# 	v2 = tf.Variable(1, name="var2", dtype=tf.float32)
# 	a = tf.add(v1, v2)

# print(v1.name) #var1:0
# print(v2.name) #my_scope/var2:0
# print(a.name) #my_scope/Add:0

# #The only way to place a variable accessed using tf.get-variable
# #in a scope is to use a variable scope, as in the following example
# with tf.variable_scope("my_scope"):
# 	v1 = tf.get_variable("var1", [1], dtype=tf.float32)
# 	v2 = tf.Variable(1, name="var2", dtype=tf.float32)
# 	a = tf.add(v1, v2)

# print()
# print(v1.name)
# print(v2.name)
# print(a.name)

# #Lets see with different name scopes
# with tf.name_scope("foo"):
# 	with tf.variable_scope("var_scope"):
# 		v = tf.get_variable("var", [1])
# with tf.name_scope("bar"):
# 	with tf.variable_scope("var_scope", reuse=True):
# 		v1 = tf.get_variable("var", [1])
# if v1 == v:
# 	print("v1 and v are equal")

# print(v.name)
# print(v1.name)

#Ok, so why name and variable scopes?
def scoping(fn, scope1, scope2, vals):
	with fn(scope1):
		a = tf.Variable(vals[0], name='a')
		b = tf.get_variable('b', initializer=vals[1])
		c = tf.constant(vals[2], name='c')

		with fn(scope2):
			d = tf.add(a * b, c, name='d')

		print '\n '.join([scope1, a.name, b.name, c.name, d.name]), '\n'
	return d 

d1 = scoping(tf.variable_scope, 'scope_vars', 'res', [1, 2, 3])
d2 = scoping(tf.name_scope, 'scope_name', 'res', [1, 2, 3])

with tf.Session() as sess:
	writer = tf.summary.FileWriter('logs', sess.graph)
	sess.run(tf.global_variables_initializer())
	writer.close()