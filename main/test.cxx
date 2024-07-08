#include "core/debug/Log.h"
#include "core/config/Config.h"
#include "drivers/opengl/oglRenderDriver.h"
#include "drivers/opengl/oglShaderProgram.h"
#include "graphics/interface/IRenderDriver.h"
#include "graphics/interface/IBuffer.h"
#include "graphics/interface/IDisplay.h"
#include "graphics/component/UniformData.h"
#include "scene/component/DevCamera.h"
#include "core/input/Input.h"
#include "scene/resource/Mesh.h"
#include <fstream>
#include <filesystem>
#include <utility>
#include "math/math.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/event/EventSystem.h"
#include "core/event/Events.h"
#include "drivers/filesystem/filesystem.h"
#include <functional>

using namespace radium;
Ref<IRenderDriver> ord = nullptr;
DevCamera* mc = nullptr;
int main(int argc, char** argv)
{
	radium::Log::init();

	RAD_ENGINE_INFO("hello mr. freeman");

	Config cfgmgr;

	if (!cfgmgr.loadConfig("tests/engine.ini"))
		return 1;

	auto window = IDisplay::createDisplay();



	window->setWindowResizeCallback(
		[](WindowResizeEvent* w) -> void
		{
			RAD_ENGINE_INFO("Resize Event: New values: ({},{})", w->newWidth, w->newHeight);
			::mc->updateProjectionMatrix((float)w->newWidth / (float)w->newHeight);
			::ord->setViewport(0, 0, w->newWidth, w->newHeight);
		}
	);


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
	rd->setClearColor(0, 0, 0, 1.0);
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
		.count = 2,
		.data = nullptr,
		.binding = GLSL_OBJECT_DATA_BINDING
	};
	glUseProgram(s->m_shaderID);

	IBuffer* sceneDataBuffer = rd->createBuffer(sdbuf);
	IBuffer* objectDataBuffer = rd->createBuffer(objbuf);

	//std::ifstream testload("tests/res/Suzanne.mdl", std::ios::binary);
	//auto size = std::filesystem::file_size("tests/res/Suzanne.mdl");

	filesystem::File testload("tests/res/Suzanne.mdl", "rb");
	auto size = testload.size();
	byte* buffer = new byte[size];
	testload.read((char*)buffer, size);
	Mesh testmesh;
	testmesh.load(buffer, size, *rd);
	delete[] buffer;

	ObjectData tests[] =
	{
		{.color = {0.5, 0.0, 0.0, 1.0f}},
		{.color = {0.0, 0.5, 0.0, 1.0f}},

	};

	glm::vec3 testLoc{ 0, 0, 0 };
	glm::vec3 testLoc2{ -5, 0, 0 };

	DevCamera mainCamera(45.0f, (float)((float)800 / (float)600), 0.1f, 100.0f);
	mainCamera.updateProjectionMatrix(((float)800 / (float)600));
	glm::mat4x4& locMat = tests[0].model;
	glm::mat4x4& locMat2 = tests[1].model;
	locMat = glm::translate(glm::mat4x4(1.0f), testLoc);
	locMat2 = glm::translate(glm::mat4x4(1.0f), testLoc2);

	window->show();

	ord = rd;
	mc = &mainCamera;

	RenderItem ri[] =
	{
		{&testmesh, 0},
		{&testmesh, 1},
	};


	while (!Input::isKeyPressed(KeyCodes::ESCAPE))
	{
		window->processEvents();


		mainCamera.update();

		/*test.worldViewProjection =
			mainCamera.getProjectionMatrix() *
								   mainCamera.getViewMatrix() *
								   math::Mat4x4(testLoc);
								   */
		auto projMat = mainCamera.getProjectionMatrix();
		auto viewMat = mainCamera.getViewMatrix();


		rd->clear();
		glEnable(GL_DEPTH_TEST);
		
		glShadeModel(GL_SMOOTH);

		glUseProgram(s->m_shaderID);
		
		tests[0].worldViewProjection = projMat * viewMat * locMat;
		tests[1].worldViewProjection = projMat * viewMat * locMat2;


		objectDataBuffer->copySubData(sizeof(ObjectData) * 2, tests);
		sceneDataBuffer->copySubData(sizeof(SceneData), &mainCamera.position);
		//locMat = glm::rotate(locMat, glm::radians(1.0f), glm::vec3(0, 1, 0));
		
		for (int i = 0; i < 2; i++)
		{
			auto& cur = ri[i];

			((oglBuffer*)objectDataBuffer)->bindRange(i);

			((oglBuffer*)testmesh.m_vtxBuf)->bindVAO();
			((oglBuffer*)testmesh.m_vtxBuf)->bind();
			((oglBuffer*)testmesh.m_idxBuf)->bind();

			glDrawElements(GL_TRIANGLES, testmesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

		}


		rd->swapBuffers();

	}


	delete s;
	delete sceneDataBuffer;
	delete objectDataBuffer;

	return 0;
}