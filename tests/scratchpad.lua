

mainShader = createShader("mainShader.glsl")
waterShader = createShader("watershader.glsl")
skyboxShader = createShader("skyboxshader.glsl")

waterPlane = loadMesh("...")

box = loadMesh("...")
character = loadMesh("...")
skybox = loadTexture2D("...")

listOfLights = [...]

struct perPassObjects = 
{
	vec3 cameraLocation;

}

struct ObjectData = 
{
	mat4 mvp;
	vec4 color;
};


struct WaterData =
{
	float time;
	float intensity;
};

struct SkyBoxData
{
	texture2D skyboxtexture;
	mat4x4 rotation;
};

perPassUBO = createBuffer(UNIFORM, binding:1, count:1)

perObjectUBO = createBuffer(UNIFORM, binding:2, count:numMeshes)

waterUBO = createBuffer(UNIFORM, binding:3, count:numWaterMeshes, sizeof(WaterData))

skyboxUBO = createBuffer(UNIFORM, binding:3, count:1, sizeof(SkyBoxData));

waterShader.addUBO(id:1, waterUBO)
skyboxShader.addUBO(id:1, skyboxUBO)


opaqueObjects = {box, character}

opaqueMap = {mainShader, opaqueObjects}

waterObjects = {waterShader, waterPlane}



function drawManager()

	setUBO perPassUBO

	drawSkyBox(skyboxShader, skyboxUBO)

	draw(mainShader,opaqueObjects)
	draw(waterShader, waterObjects)
end

function draw(Shader, obectList)
	
	
	for object in obectList
		setUBO perObjectUBO + object.index

		glDrawElements(...)

	end

end