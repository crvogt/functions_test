import numpy as np
from random import randint

z = np.zeros((6, 2, 2))
z[[1,3],1, 1] = 6
print("z")
print(z.shape)
print(z)

numList = [1, 3]

f = z[numList]

print("f")
print(f.shape)
print(f)


