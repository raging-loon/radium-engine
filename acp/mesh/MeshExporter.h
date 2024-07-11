#ifndef ACP_MESH_MESH_EXPORTER_H_
#define ACP_MESH_MESH_EXPORTER_H_

#include <cstdint>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "SubMesh.h"

namespace acp
{

struct MeshHeader
{
	const uint32_t magic = 0x77687601;

	uint32_t vertexOffset;
	uint32_t vertexSize;
	uint32_t indexOffset;
	uint32_t indexSize;
};


class MeshExporter
{
public:

	explicit MeshExporter(std::string& filename);
	~MeshExporter();
	size_t process();

	void serialize(std::string targetDirectory);

private:

	size_t interalProcess(const aiNode* cRoot);

	const aiScene* m_meshScene;

	std::vector<SubMesh* > m_subMeshes;
	std::string m_filename;
};

} // acp


#endif // ACP_MESH_MESH_EXPORTER_H_