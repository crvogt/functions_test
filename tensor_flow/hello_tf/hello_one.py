import tensorflow as tf 

input_value = tf.constant(1.0)
weight = tf.Variable(0.8)
another_weight = tf.Variable(1.6)
output_value = weight * input_value
output_value2 = another_weight * output_value * input_value

graph = tf.get_default_graph()
operations = graph.get_operations()
# print operations
# print operations[0].node_def
# print input_value

init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)
value = sess.run(input_value)
print value
print output_value

for op in graph.get_operations():
	print op.name

print "\nOp input"
for op_input in op.inputs:
	print op_input
print "Op inputs length: "
print len(op.inputs)

print "\nOutput value"
print(sess.run(output_value))
print "\nAnother weight"
print(sess.run(another_weight))
print "\nOutput value 2"
print(sess.run(output_value2))


