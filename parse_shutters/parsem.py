import os
import shutil
import time

shutter_val = 250

shutter_dirs = '/home/carson/libs/raytrix_gp_data/raytrixImgVar'
img_dirs = '/media/carson/My Passport/raytrix_iccp/stationary'

shut_dir = shutter_dirs + '/shut_' + str(shutter_val)
if not os.path.isdir(shut_dir):
	os.mkdir(shut_dir)
else:
	print('Path:\n' + shut_dir + '\nexists!')

dir_num = 0
for root, dirs, files in os.walk(img_dirs):
	for dir_ in dirs:
		dir_num = dir_num + 1

for i in range(0, dir_num):
	scene_dir = img_dirs + '/scene_' + str(i) + '/'
	print(scene_dir)
	for root, dirs, files in os.walk(scene_dir):
		for file_ in files:
			str_list = file_.split('.')
			char_list = str_list[0]
			shut_list = char_list.split('_')
			if len(shut_list) == 3:
				type_list = shut_list[2]
				shut_list = shut_list[0]
				if len(shut_list) == 4 and type_list == 'Raw' and int(shut_list[1:4]) == shutter_val:
					src = scene_dir + file_
					dst = shut_dir + '/' + str(i) + '.png'
					print(file_)
					shutil.copy(src, dst)
				elif len(shut_list) == 3 and type_list == 'Raw' and int(shut_list[1:3]) == shutter_val:
					src = scene_dir + file_
					dst = shut_dir + '/' + str(i) + '.png'
					print(file_)
					shutil.copy(src, dst)
				elif len(shut_list) == 2 and type_list == 'Raw' and int(shut_list[1]) == shutter_val:
					src = scene_dir + file_
					dst = shut_dir + '/' + str(i) + '.png'
					print(file_)
					shutil.copy(src, dst)