import glob
import os

def add_source_files(env, files):
	newfiles = []

	if files[0] == '*':
		newfiles = glob.glob(os.path.abspath('./') + '/' + files)
	else:
		
		
		path = os.path.abspath('./') + '/'
		for i in files.split(','):
			#if not os.path.exists(path + i):
			#	print(f"{} does not exist!", path + i)
			newfiles.append(path + i)
	for file in newfiles:
		env.source_files.append(file)
