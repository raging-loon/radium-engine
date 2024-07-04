#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "graphics/IRenderDriver.h"
#include "drivers/opengl/oglRenderDriver.h"
#include "drivers/opengl/oglShaderProgram.h"
#include "graphics/IBuffer.h"
#include "graphics/IDisplay.h"
#include "graphics/UniformData.h"
#include "scene/component/Camera.h"
#include "core/input/Input.h"
#include "scene/resource/Mesh.h"
#include <fstream>
#include <filesystem>
using namespace radium;

int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr. freeman");

	auto& cfgmgr = Config::getSingleton();

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;

	
	auto window = IDisplay::createDisplay();

	window->create(
		cfgmgr["wwidth"],
		cfgmgr["wheight"],
		cfgmgr["windowed"],
		"don't forget to add title config"
	);

	auto driverConfig = window->createRenderDriverConfig();

	auto rd = IRenderDriver::createRenderDriver(
		static_cast<RenderAPI>((int)cfgmgr["api"])
	);

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

	std::ifstream testload("tests/res/monke.mdl", std::ios::binary);
	auto size = std::filesystem::file_size("tests/res/monke.mdl");
	byte* buffer = new byte[size + 1];

	testload.read((char*)buffer, size);

	Mesh testmesh;
	
	testmesh.load(buffer, size, *rd);


	ObjectData test =
	{
		.color = {0.5, 0.0, 0.0, 1.0f}
	};

	math::Vec3 testLoc = { 0, 0, 0};

	Camera mainCamera(0.785398f, (float)((float)800 /(float) 600), 0.1f, 100.0f);
	window->show();

	while (!Input::isKeyPressed(KeyCodes::ESCAPE))
	{
		window->processEvents();


		if (Input::isKeyPressed(KeyCodes::UP))
			mainCamera.position.z += 0.05;
		else if (Input::isKeyPressed(KeyCodes::DOWN))
			mainCamera.position.z -= 0.05;
		if (Input::isKeyPressed(KeyCodes::RIGHT))
			mainCamera.position.x += 0.05;
		else if (Input::isKeyPressed(KeyCodes::LEFT))
			mainCamera.position.x -= 0.05;


		/*test.worldViewProjection = 
			mainCamera.getProjectionMatrix() * 
								   mainCamera.getViewMatrix() * 
								   math::Mat4x4(testLoc);
								   */
		auto projMat = mainCamera.getProjectionMatrix();
		auto viewMat = mainCamera.getViewMatrix();
		auto locMat  = math::Mat4x4(1);

		test.worldViewProjection = projMat * viewMat * locMat;

		rd->clear();
		glEnable(GL_DEPTH_TEST);
		glUseProgram(s->m_shaderID);
		objectDataBuffer->copySubData(sizeof(ObjectData), &test);
		sceneDataBuffer->copySubData(sizeof(SceneData), &mainCamera.position);


		((oglBuffer*)objectDataBuffer)->bindRange(0);

		((oglBuffer*)testmesh.m_vtxBuf)->bindVAO();
		((oglBuffer*)testmesh.m_vtxBuf)->bind();
		((oglBuffer*)testmesh.m_idxBuf)->bind();
		
		glDrawElements(GL_TRIANGLES,testmesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

		rd->swapBuffers();

	}


	delete s;
	delete sceneDataBuffer;
	delete objectDataBuffer;

	return 0;
}