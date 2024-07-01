#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "graphics/IRenderDriver.h"
#include "drivers/opengl/oglRenderDriver.h"
#include "drivers/opengl/oglShaderProgram.h"
#include "graphics/IBuffer.h"
#include "graphics/IDisplay.h"
#include "graphics/UniformData.h"
#include "scene/component/Camera.h"
using namespace radium;

int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr. freeman");

	auto& cfgmgr = Config::getSingleton();

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;

	
	auto* window = IDisplay::createDisplay();

	window->create(
		cfgmgr["wwidth"],
		cfgmgr["wheight"],
		cfgmgr["windowed"],
		"don't forget to add title config"
	);

	auto driverConfig = window->createRenderDriverConfig();

	auto* rd = new oglRenderDriver;
	rd->init(driverConfig);
	rd->setClearColor(0.5, 0.5, 0.5, 1.0);
	rd->setViewport(0, 0, cfgmgr["wwidth"], cfgmgr["wheight"]);

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

	oglShaderProgram* s = (oglShaderProgram*)rd->createShader(spd);

	assert(s != nullptr);

	BufferDescription sdbuf =
	{
		.type = buffer_t::UNIFORM,
		.size = sizeof(SceneData),
		.count = 1,
		.data = nullptr,
		.binding = GLSL_SCENE_DATA_BINDING
	};

	BufferDescription objbuf =
	{
		.type = buffer_t::UNIFORM,
		.size = sizeof(ObjectData),
		.count = 1,
		.data = nullptr,
		.binding = GLSL_OBJECT_DATA_BINDING
	};
	glUseProgram(s->m_shaderID);

	IBuffer* sceneDataBuffer =  rd->createBuffer(sdbuf);
	IBuffer* objectDataBuffer = rd->createBuffer(objbuf);

	float vertices2[] =
	{

	 0.25f,  0.5f, 0.0f,  // Top-left
	 0.75f,  0.5f, 0.0f,  // Top-right
	 0.75f, -0.5f, 0.0f,  // Bottom-right
	 0.25f, -0.5f, 0.0f
	};

	unsigned int indices[] = {

		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	BufferDescription vbd = {
		.type = buffer_t::VERTEX,
		.size = sizeof(float),
		.count = 12,
		.data = &vertices2
	};

	BufferDescription ibd = {
		.type = buffer_t::INDEX,
		.size = sizeof(unsigned int),
		.count = 6,
		.data = &indices
	};



	auto* vbuffer1 = rd->createBuffer(vbd);
	auto* ibuffer1 = rd->createBuffer(ibd);

	ObjectData test =
	{
		.color = {0.5, 0.0, 0.0, 1.0f}
	};

	math::Vec3 testLoc = { 0, 0, 0};

	Camera mainCamera(90, 800 / 600, 0.1f, 1000.0f);
	window->show();

	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		window->processEvents();

		if (GetKeyState(VK_UP) & 0x8000)
			mainCamera.position.z += 0.005;
		else if (GetKeyState(VK_DOWN) & 0x8000)
			mainCamera.position.z -= 0.005;
		if (GetKeyState(VK_LEFT) & 0x8000)
			mainCamera.position.x += 0.005;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			mainCamera.position.x -= 0.005;



		test.worldViewProjection = mainCamera.getProjectionMatrix() * 
								   mainCamera.getViewMatrix() * 
								   math::Mat4x4(testLoc);
		rd->clear();
		glUseProgram(s->m_shaderID);
		objectDataBuffer->copySubData(sizeof(ObjectData), &test);
		sceneDataBuffer->copySubData(sizeof(SceneData), &mainCamera.position);


		((oglBuffer*)objectDataBuffer)->bindRange(0);

		((oglBuffer*)vbuffer1)->bindVAO();
		((oglBuffer*)vbuffer1)->bind();
		((oglBuffer*)ibuffer1)->bind();
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		rd->swapBuffers();

	}


	delete s;
	delete vbuffer1;
	delete ibuffer1;
	delete sceneDataBuffer;
	delete objectDataBuffer;
	delete window;
}