from keras.layers import Layer
import keras.backend as K
from keras import activations
import time

# class MyDenseLayer(Layer):
#     def __init__(self, units,
#                  activation=None,
#                  use_bias=False,
#                  **kwargs):
#         self.units = units
#         self.activation = True
#         self.use_bias = use_bias
#         super(Dense, self).__init__(**kwargs)
#         if 'input_shape' not in kwargs:
#             print('add input shape!')
#
#     def build(self, input_shape):
#         assert len(input_shape) >= 2
#         # returns the last val of input shape to input dim
#         input_dim = input_shape[-1]
#
#         self.kernel = self.add_weight(shape=input_dim, self.units,
#                                       initializer='uniform',
#                                       name='kernel')
#
#         self.built = True
#
#         activations.tanh()
#
#     def call(self, inputs):
#         output = K.dot(inputs, self.kernel)




class MyLayer(Layer):

    def __init__(self, units, **kwargs):
        # self.output_dim = output_dim
        self.units = units
        self.activation = activations.get('relu')

        super(MyLayer, self).__init__(**kwargs)

    def build(self, input_shape):
        # print(input_shape)
        input_dim = input_shape[-1]
        # print(input_dim)
        # time.sleep(20)
        self.kernel = self.add_weight(name='kernel',
                                      shape=(input_dim, self.units),
                                      initializer='uniform',
                                      trainable=True)
        super(MyLayer, self).build(input_shape)

    def call(self, inputs):
        print('inputs, kernel')
        print(inputs.shape)
        print(self.kernel.shape)
        output = K.dot(inputs, self.kernel)
        output = self.activation(output)
        print(output.shape)
        print('in call')
        # self.output = output
        # time.sleep(20)

        return output

    def compute_output_shape(self, input_shape):
        return input_shape
