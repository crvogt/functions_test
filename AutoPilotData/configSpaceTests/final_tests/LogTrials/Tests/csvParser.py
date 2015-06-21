import csv

#---------------------------------------------------------#
"""
def csv_reader(file_obj):

	#Read a csv file

	reader = csv.reader(file_obj)
	for row in reader:
		print(" ".join(row))

#---------------------------------------------------------#

if __name__ == "__main__":
	csv_path = "csvTest.csv"
	with open(csv_path, "rb") as f_obj:
		csv_reader(f_obj)

"""

with open("gridFlight1.csv") as filein:
	reader = csv.reader(filein, quoting=csv.QUOTE_NONNUMERIC)
	#xs, ys, zs = zip(*reader)
	compass, airspeed, relalt, groundspeed, vfrcomp, climb, \
	throttle, latitude, longitude, altitude, X, Y, Z, arm, \
	guided, voltage, current, remaining, pressure, time = zip(*reader)

cropcompass = []
cropairspeed = []
croprelalt = []
cropgroundspeed = []
croplatitude = []
croplongitude = []
cropaltitude = []
croppressure = []
croptime = []

length = xrange(len(cropCompass))

outFile = open("compass.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(compass[i]))
	else:
		outFile.write("\n{}".format(compass[i]))
outFile.close()

outFile = open("airspeed.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(airspeed[i]))
	else:
		outFile.write("\n{}".format(airspeed[i]))
outFile.close()

outFile = open("relalt.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(relalt[i]))
	else:
		outFile.write("\n{}".format(relalt[i]))
outFile.close()

outFile = open("groundspeed.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(groundspeed[i]))
	else:
		outFile.write("\n{}".format(groundspeed[i]))
outFile.close()

outFile = open("latitude.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(latitude[i]))
	else:
		outFile.write("\n{}".format(latitude[i]))
outFile.close()

outFile = open("longitude.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(longitude[i]))
	else:
		outFile.write("\n{}".format(longitude[i]))
outFile.close()

outFile = open("altitude.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(altitude[i]))
	else:
		outFile.write("\n{}".format(altitude[i]))
outFile.close()

outFile = open("pressure.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(pressure[i]))
	else:
		outFile.write("\n{}".format(pressure[i]))
outFile.close()

outFile = open("time.csv", "w")
for i in length:
	if i == 0:
		outFile.write("{}".format(time[i]))
	else:
		outFile.write("\n{}".format(time[i]))
outFile.close()