angRes = 15

#Stock Dimensions
saiHEIGHT = 100
saiWIDTH = 100
saiCHANNELS = 3

# For brightness net
bHEIGHT = 100
bWIDTH = 100
bCHANNELS = 4

# For depth net
dHEIGHT = 100
dWIDTH = 100
dCHANNELS = 200

# For color net
cHEIGHT = 200
cWIDTH = 200
# Channels are all warped images, depth map, and positions (x, y)
cCHANNELS = 228

# lfBaseLocation = "/home/carson/libs/SAI_output/"
lfBaseLocation = "/home/carson/libs/raytrix_gp_data/raytrixImages"
h5Location = "/home/carson/libs/saved_models/light_and_dark_sais.h5"
modelLocation = "/home/carson/libs/saved_models/model.h5"