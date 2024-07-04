import os
import glob
import sys


env = Environment()

env.source_files = []

def add_source_files(self, files):
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

# make it available to sub constructs
env.add_source_files = add_source_files

###############################
########### Options ###########
###############################

opts = Variables(['custom.py'], ARGUMENTS)

# Targets
opts.Add(EnumVariable("target", "Compilation Target", "editor_debug", ("editor_debug", "editor_release", "blob_debug", "blob_release")))
opts.Add(EnumVariable("platform", "Target Platform", "auto", ("auto", "win32", "linux64")))

# misc
opts.Add(BoolVariable("tests", "Build unit tests", False))
opts.Add(BoolVariable("vsproj", "Build Visual Studio project", False))
# TODO: specify which are supported by GCC/Clang
opts.Add(EnumVariable("sanitizer", "Run selected sanitizer[s]", "none", ("none", "address", "memory", "leak", "thread", "undefined")))

# Render Drivers
opts.Add(BoolVariable("opengl", "Enable OpenGL Render Driver", True))
opts.Add(BoolVariable("d3d12", "Enable D3D12 Render Driver", False))
opts.Add(BoolVariable("vulkan", "Enable Vulkan Render Driver", False))


opts.Update(env)

env.is_debug = env["target"].endswith("debug")
env.is_release = env["target"].endswith("release")

if(env.is_debug):
	env.Append(CPPDEFINES=["RAD_DEBUG"])

#####################
# Platform Specific #
#####################
if(env["platform"] == "auto"):
	if(sys.platform == "win32"):
		env["platform"] = "win32"


#######################
# Win32 Build Options #
#######################
if env["platform"] == "win32":
	from buildlib.win32 import addWin32Options

	addWin32Options(env)



# add current directory to includepath ~~~~~~~~~~~~v
env.Append(CPPPATH=['thirdparty/spdlog/include', 'thirdparty/glm/', os.path.abspath('.').replace('\\','/')])

#######################################
########## Chain Load Engine ##########
#######################################

Export("env")

SConscript("core/SCsub")
SConscript("math/SCsub")

SConscript("graphics/SCsub")

SConscript("drivers/SCsub")
SConscript("platform/SCsub")
SConscript("scene/SCsub")

if not env["tests"]:
	SConscript("main/SCsub")
else:
	env.Append(CPPDEFINES=["RAD_ENABLE_TESTS"])
	SConscript("tests/unit/SCsub")

	
target = env.Program(target='build/radium-engine', source=env.source_files)

if(env["platform"] == "win32" and env["vsproj"]):
	env.MSVSProject(
		target='radium-engine.vcxproj',# + env["MSVSPROJETSUFFIX"],
		srcs = env.source_files,
		incs = [str(i) for i in env["CPPPATH"]],
		localincs = [],
		resources = [],
		misc = [],
		# TODO: fix v
		buildtargets = ['build/radium-engine.exe', 'build/radium-engine.exe'],
		variant=('Debug','Release'),
		cmdargs=f'platform=win32'
	)
		