
imgRows = 480
imgCols = 640
imgChan = 7 # For the 4D parameterization

#Want to input 3 parameterization mats (480, 640, 4),
#Say we give it a stack, 3 input images (3,480, 640, 7)
#With the addition of an empty pose
#So final input is something like (480, 640, 25)
#Where the final four channels are an empty image,
#Made up only of the pose channels

#Input Shape(480, 640, 25)
#Output Shape(480, 640, 3)

#In effect our x should be the input
#Our y should have the same shape as the output
#But be the image against which we are comparing

'''
Another option, might be to shape the input as 
input
list 1: (3 480 640 3)
list 2: (4 2 1)

output: (480, 640, 3)

where list 2 is all of the corresponding poses, with fourth
pose for the actual input location
'''

inputShape = (480, 640, 25)
outputShape = (480, 640, 3)

model = Sequential()
model.add(Conv2D())

output = 
model = Model(inputs = , outputs = )