#ifndef ACP_MESH_SUB_MESH_H_
#define ACP_MESH_SUB_MESH_H_

#include <glm/glm.hpp>
#include <vector>

#include <assimp/mesh.h>

namespace acp
{

struct VertexData
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

using VertexList = std::vector<VertexData>;
using IndexList = std::vector<uint32_t>;

class SubMesh
{
public:

	explicit SubMesh(aiMesh* mesh);

	size_t process();
	
	size_t serialize(const std::string& targetDirectory);

private:

	
	aiMesh* m_mesh;

	VertexList m_vtxList;
	IndexList m_idxList;

	std::string m_name;


};

} // acp

#endif // ACP_MESH_SUB_MESH_H_