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
#include <chrono>
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


	oglShaderProgram* s = (oglShaderProgram*)rd->createShader(spd);

	spd.filename = "tests/res/shaders/test.glsl";
	oglShaderProgram* s2 = (oglShaderProgram*)rd->createShader(spd);
	spd.filename = "tests/res/shaders/water.fx.glsl";
	oglShaderProgram* waterEffect = (oglShaderProgram*)rd->createShader(spd);



	if (s == nullptr || s2 == nullptr || waterEffect == nullptr)
	{
		rd->terminate();
		return 1;
	}

	// glGetUniformLocation

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

	float fboQuad[] =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
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

	/*BufferDescription perObjectBufferDesc =
	{
		.type = buffer_t::UNIFORM,
		.size = sizeof(float),
		.count = 1,
		.data = nullptr,
		.binding = 4
	};

	IBuffer* poub = rd->createBuffer(perObjectBufferDesc);*/

	auto perObjectUB = s->createUniformBuffer(2, sizeof(TestPerObjectData), 2);
	auto stest = s2->createUniformBuffer(1, sizeof(float), 4);
	s->setPerObjectUniformBuffer(perObjectUB, sizeof(TestPerObjectData));

	s->updateUniformBuffer(perObjectUB, 0, &t1, sizeof(TestPerObjectData));
	s->updateUniformBuffer(perObjectUB, 1, &t2, sizeof(TestPerObjectData));

	auto perPassUB = s->createUniformBuffer(1, sizeof(TestPerPassData), 3);
	s->setPerPassUniformBuffer(perPassUB, sizeof(TestPerPassData));

	s->updateUniformBuffer(perPassUB, 0, &mainCamera.position, sizeof(TestPerPassData));
	float data = 10.0f;
	s2->updateUniformBuffer(stest, 0, &data, sizeof(float));


	RenderItem list[] =
	{
		{
			.vertexBuffer = vbuffer1, .indexBuffer = ibuffer1, .uniformIndex = 0
		},
		{
			.vertexBuffer = vbuffer2, .indexBuffer = ibuffer1, .uniformIndex = 1
		}
	};

	glUseProgram(waterEffect->m_shaderID);
	unsigned int u_fbo_texture = glGetUniformLocation(waterEffect->m_shaderID, "fbo_texture");
	unsigned int u_offset = glGetUniformLocation(waterEffect->m_shaderID, "offset");
	glUniform1i(u_fbo_texture, 0);

	GLuint fbo;
	unsigned int rbo;
	unsigned int fbtex;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fbtex);
	glBindTexture(GL_TEXTURE_2D, fbtex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbtex, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	unsigned int qVBO, qVAO;

	glGenVertexArrays(1, &qVAO);
	glGenBuffers(1, &qVBO);

	glBindVertexArray(qVAO);
	glBindBuffer(GL_ARRAY_BUFFER, qVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fboQuad), &fboQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	std::chrono::time_point<std::chrono::high_resolution_clock> start;

	auto prevtime = std::chrono::high_resolution_clock::now();
	bool offset = true;



	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		test->processEvents();

		auto curTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> delta = curTime - prevtime;

		prevtime = curTime;
		if (GetKeyState(VK_UP) & 0x8000)
			mainCamera.position.z += 0.005;
		else if (GetKeyState(VK_DOWN) & 0x8000)
			mainCamera.position.z -= 0.005;
		if (GetKeyState(VK_LEFT) & 0x8000)
			mainCamera.position.x += 0.005;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			mainCamera.position.x -= 0.005;

		if (GetKeyState(VK_SPACE) & 0x8000)
			offset = !offset;

		t1.worldViewProj = mainCamera.getProjectionMatrix() * mainCamera.getViewMatrix() * math::Mat4x4(loc1);
		t2.worldViewProj = mainCamera.getProjectionMatrix() * mainCamera.getViewMatrix() * math::Mat4x4(loc2);

		TestPerObjectData ts[] = { t1,t2 };

		s->updateUniformBuffer(perPassUB, 0, &mainCamera.position, sizeof(TestPerPassData));
		s->updateUniformBuffer(perObjectUB, 0, ts, sizeof(TestPerObjectData) * 2);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		rd->clear();
		glEnable(GL_DEPTH_TEST);
		glUseProgram(s->m_shaderID);
		glBindBufferRange(GL_UNIFORM_BUFFER, 3, perPassUB, 0, sizeof(TestPerPassData));

		((oglBuffer*)vbuffer1)->bindVAO();
		((oglBuffer*)vbuffer1)->bind();
		((oglBuffer*)ibuffer1)->bind();


		glBindBufferRange(GL_UNIFORM_BUFFER, 2, perObjectUB, 0, sizeof(TestPerObjectData));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//glUseProgram(s2->m_shaderID);
		//glBindBufferRange(GL_UNIFORM_BUFFER, 3, perPassUB, 0, sizeof(TestPerPassData));
		//	
		//((oglBuffer*)vbuffer2)->bindVAO();
		//((oglBuffer*)vbuffer2)->bind();
		//((oglBuffer*)ibuffer1)->bind();


		//glBindBufferRange(GL_UNIFORM_BUFFER, 2, perObjectUB, 0, sizeof(TestPerObjectData));
		//glBindBufferRange(GL_UNIFORM_BUFFER, 4, stest, 0, sizeof(float));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(waterEffect->m_shaderID);

		glBindVertexArray(qVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbtex);

		glUniform1f(u_offset, (float)offset);
		glUniform1i(u_fbo_texture, 0);


		glDrawArrays(GL_TRIANGLES, 0, 6);
		rd->swapBuffers();


		printf("%f\n", delta.count());

	}

	vbuffer1->destroy();
	vbuffer2->destroy();
	ibuffer1->destroy();
	delete s;
	test->destroy();

	return 0;

}