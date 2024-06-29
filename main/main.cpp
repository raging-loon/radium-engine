#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "core/config/Hash.h"
#include "core/Variant.h"
#include "graphics/IDisplay.h"
#include "graphics/IBuffer.h"
#include "graphics/IShaderProgram.h"
#include "platform/win32/Win32Display.h"
#include "drivers/opengl/oglRenderDriver.h"
#include "drivers/opengl/oglShaderProgram.h"
#include "math/math.h"

#include "scene/component/Camera.h"

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
	 -0.75f,  0.5f, 0.0f,  // Top-left
	-0.25f,  0.5f, 0.0f,  // Top-right
	-0.25f, -0.5f, 0.0f,  // Bottom-right
	-0.75f, -0.5f, 0.0f   // Bottom-left
	};

	float vertices2[] =
	{

	 0.25f,  0.5f, 0.0f,  // Top-left
	 0.75f,  0.5f, 0.0f,  // Top-right
	 0.75f, -0.5f, 0.0f,  // Bottom-right
	 0.25f, -0.5f, 0.0f
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



	auto* vbuffer1 = rd->createBuffer(vbd);
	auto* ibuffer1 = rd->createBuffer(ibd);

	
	vbd.data = vertices2;

	auto* vbuffer2 = rd->createBuffer(vbd);

	
	float color[] = { 0.5, 0.0, 0.0, 1.0 };
	float color2[] = { 0.0, 0.0, 0.5, 1.0 };
	math::Vec3 loc1(0, 0, 0);
	math::Vec3 loc2(10, 10, 1);
	
	TestPerObjectData t1 =
	{
		.color = { 0.5, 0.0, 0.0, 1.0 }
	};

	TestPerObjectData t2 =
	{
		.color = {0.0, 0.0, 0.5, 1.0f}
	};

	Camera mainCamera(90, 800 / 600, 0.1f, 1000.0f);

	auto perObjectUB = s->createUniformBuffer(2, sizeof(TestPerObjectData), 2);
	s->setPerObjectUniformBuffer(perObjectUB, sizeof(TestPerObjectData));

	s->updateUniformBuffer(perObjectUB, 0, &t1, sizeof(TestPerObjectData));
	s->updateUniformBuffer(perObjectUB, 1, &t2, sizeof(TestPerObjectData));

	auto perPassUB = s->createUniformBuffer(1, sizeof(TestPerPassData), 3);
	s->setPerPassUniformBuffer(perPassUB, sizeof(TestPerPassData));

	s->updateUniformBuffer(perPassUB, 0, &mainCamera.position, sizeof(TestPerPassData));


	RenderItem list[] =
	{
		{
			.vertexBuffer = vbuffer1, .indexBuffer = ibuffer1, .uniformIndex = 0
		},
		{
			.vertexBuffer = vbuffer2, .indexBuffer = ibuffer1, .uniformIndex = 1
		}
	};

	

	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		test->processEvents();
		


		if (GetKeyState(VK_UP) & 0x8000)
			mainCamera.position.z += 0.1;

		rd->clear();


		t1.worldViewProj =  mainCamera.getProjectionMatrix() * mainCamera.getViewMatrix() * math::Mat4x4(loc1);
		t2.worldViewProj =  mainCamera.getProjectionMatrix() * mainCamera.getViewMatrix() * math::Mat4x4(loc2);

		s->updateUniformBuffer(perObjectUB, 0, &t1, sizeof(TestPerObjectData));
		s->updateUniformBuffer(perObjectUB, 1, &t2, sizeof(TestPerObjectData));
		((oglRenderDriver*)rd)->draw(s, list, 2);

		rd->swapBuffers();
	}

	vbuffer1->destroy();
	vbuffer2->destroy();
	ibuffer1->destroy();
	delete s;
	test->destroy();

	return 0;

}