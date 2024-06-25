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


env.add_source_files = add_source_files


opts = Variables(['custom.py'], ARGUMENTS)

# Targets
opts.Add(EnumVariable("target", "Compilation Target", "editor_debug", ("editor_debug", "editor_release", "blob_debug", "blob_release")))
opts.Add(EnumVariable("platform", "Target Platform", "auto", ("auto", "win32", "linux64")))
opts.Add(BoolVariable("tests", "Build unit tests", False))
opts.Add(BoolVariable("vsproj", "Build Visual Studio project", False))

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

if env["platform"] == "win32":
	# use C++20 and disable exceptions
	env.Append(CCFLAGS=["/std:c++20","/EHsc"])
	# Add debug symbols and optimizaion
	env.Append(LIBS = ["kernel32", "user32", "gdi32", "winspool", "comdlg32", "advapi32",
					   "shell32", "ole32", "oleaut32", "uuid", "odbc32", "odbccp32"])
	
	if(env.is_debug):
		env.Append(CCFLAGS=["/DEBUG","/Od"])
	else:
		env.Append(CPPDEFINES=["RAD_WIN32_RELEASE"])
		
	
	if(env["opengl"]):
		env.Append(CPPDEFINES=["GLEW_STATIC", "RAD_API_OPENGL"])
		env.Append(LIBS = ["opengl32"])
		env.Append(CPPPATH=['thirdparty/glew/include','thirdparty/glext/include'])
		env.source_files.append('thirdparty/glew/src/glew.c')


	env.Append(CPPDEFINES=["RAD_PLATFORM_WIN32"])

# add current directory to includepath ~~~~~~~~~~~~v
env.Append(CPPPATH=['thirdparty/spdlog/include', os.path.abspath('.').replace('\\','/')])


Export("env")

SConscript("core/SCsub")

if not env["tests"]:
	SConscript("main/SCsub")
else:
	env.Append(CPPDEFINES=["RAD_ENABLE_TESTS"])
	SConscript("tests/unit/SCsub")

SConscript("platform/SCsub")

SConscript("drivers/SCsub")
	
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
		