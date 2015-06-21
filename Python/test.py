compass = [54, 54, 54, 35, 63, 66, 66, 77]
lat = [22, 22, 22, 45, 243, 56, 56, 77]
cropCompass = []
cropLat = []

for i in range(0, len(compass)):
	if i == 0:
		cropCompass.append(compass[i])
		cropLat.append(lat[i])
	else:
		tempCompass = compass[i - 1]
		tempLat = lat[i - 1]
		
		if tempCompass == compass[i] and tempLat == lat[i]:
			#do nothing
			print "nothing"
		else:
			cropCompass.append(compass[i])
			cropLat.append(lat[i])

for j in xrange(0, len(cropCompass)):		
	print cropCompass[j]


