#ifndef SCENE_RESOURCE_MESH_H_
#define SCENE_RESOURCE_MESH_H_

#include "core/types.h"
#include "core/SmartPtr.h"
#include "graphics/interface/IBuffer.h"
#include "graphics/interface/IRenderDriver.h"
namespace radium
{

/* 
   Internal Mesh File Header 
   Used when reading mesh data
   from the disk
*/

constexpr U32 MESH_FILE_HEADER_MAGIC = 0x77687601;

struct MeshHeader
{
	U32 magic;
	/* Where vertex data starts */
	U32 vtxOffset;
	U32 vtxCount;
	/* Where index data starts */
	U32 idxOffset;
	U32 idxCount;
};



/* Mesh - holds vertices and indices */
class Mesh
{
public:
	/* Load mesh */
	Mesh();

	Mesh(const Mesh& m) = delete;
	Mesh& operator=(const Mesh&) = delete;

	~Mesh();

	inline U32 getVertexCount() const { return m_vertexCount; }
	inline U32 getIndexCount() const  { return m_indexCount; }


	bool load(const byte* data, U32 size, IRenderDriver& rd);
	// TODO: make these private when done testing
	IBuffer* m_vtxBuf;
	IBuffer* m_idxBuf;

private:
	U32 m_vertexCount;
	U32 m_indexCount;

};

} // radium


#endif // SCENE_RESOURCE_MESH_H_