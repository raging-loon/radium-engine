#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "core/config/Hash.h"
#include "core/Variant.h"
#include "graphics/IDisplay.h"
#include "graphics/IBuffer.h"
#include "graphics/IShaderProgram.h"
#include "platform/win32/Win32Display.h"
#include "drivers/opengl/oglRenderDriver.h"


#include <cstdio>
#include <unordered_map>
#include <string.h>
#include <fstream>

using namespace radium;

int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr freeman");
	
	auto& cfgmgr = radium::Config::getSingleton();

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;
	
	RAD_ENGINE_INFO("Window Width: {}", cfgmgr["wwidth"]);

	radium::IDisplay* test = new radium::win32::Win32Display();

	test->create(
		cfgmgr["wwidth"], cfgmgr["wheight"],
		cfgmgr["windowed"],
		"don't forget to add a config"
	);
	
	radium::RenderAPI api = static_cast<radium::RenderAPI>((int)cfgmgr["api"]);

	auto driverConfig = test->createRenderDriverConfig();
	
	radium::IRenderDriver* rd = nullptr;
	
	if (api == radium::RenderAPI::OPENGL)
	{
		rd = new radium::oglRenderDriver;
	}

	rd->init(driverConfig);
	rd->setClearColor(0.5, 0.50, 0.5, 1.0);
	rd->setViewport(0, 0, 800, 600);

	ShaderProgramDescription spd;
	ShaderDescription vdesc
	{
		.type = IShaderProgram::VERTEX,
		.sectionName = "VS"
	};
	ShaderDescription psdesc
	{
		.type = IShaderProgram::PIXEL,
		.sectionName = "PS"
	};

	spd =
	{
		.vertexShader = &vdesc,
		.pixelShader = &psdesc,
		.filename = "tests/res/shaders/basic.glsl"

	};

	auto s = rd->createShader(spd);

	test->show();
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	
	BufferDescription vbd = {
		.type = buffer_t::VERTEX,
		.size = sizeof(float),
		.count = 12,
		.data = &vertices
	};

	BufferDescription ibd = {
		.type = buffer_t::INDEX,
		.size = sizeof(unsigned int),
		.count = 6,
		.data = &indices
	};

	auto* vbuffer = rd->createBuffer(vbd);
	auto* ibuffer = rd->createBuffer(ibd);


	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		test->processEvents();
		rd->clear();
		glUseProgram(s);
		((oglBuffer*)vbuffer)->bindVAO();
		((oglBuffer*)vbuffer)->bind();
		((oglBuffer*)ibuffer)->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		rd->swapBuffers();
	}

	vbuffer->destroy();
	ibuffer->destroy();
	test->destroy();

	return 0;

}