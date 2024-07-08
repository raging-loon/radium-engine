import os
import platform
import shutil


def addWin32Options(env):
	# disable exceptions~~~~~~~~~~~~~~~~v
	env.Append(CCFLAGS=["/std:c++20", "/EHsc"])
	env.Append(CPPDEFINES=["RAD_PLATFORM_WIN32"])

	env.Append(LIBS = ["kernel32", "user32", "gdi32", "winspool", "comdlg32", "advapi32",
					   "shell32", "ole32", "oleaut32", "uuid", "odbc32", "odbccp32"])



	if env.is_debug:
		env.Append(CCFLAGS=["/Od", "/Zi"])
		env.Append(LINKFLAGS=["/DEBUG:FULL","/PDB:radium-engine.pdb"])
	else:
		env.Append(CCFLAGS=["/O2"])
		env.Append(CPPDEFINES=["RAD_WIN32_RELEASE"])


	########################
	##### Graphics API #####
	########################
	
	if env["opengl"]:
		env.Append(CPPDEFINES=["GLEW_STATIC", "RAD_API_OPENGL"])
		env.Append(LIBS = ["opengl32"])
		env.Append(CPPPATH=['thirdparty/glew/include'])
		env.source_files.append('thirdparty/glew/src/glew.c')


	########################
	##### ASAN support #####
	########################
	if env["sanitizer"] != "none":
		addSanitizers(env["sanitizer"], env)

def addSanitizers(slist, env):
	sanitizerList = []
	for i in slist.split(','):
		sanitizerList.append("/fsanitize=" + i)
	
	env.Append(CCFLAGS=sanitizerList)
	env.Append(LIBS = ["clang_rt.asan_dynamic-x86_64"])
	
	shutil.copyfile("thirdparty/asan/clang_rt.asan_dynamic-x86_64.dll", "build/clang_rt.asan_dynamic-x86_64.dll")
	