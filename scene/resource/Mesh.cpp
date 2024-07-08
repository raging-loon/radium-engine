#include "Mesh.h"
#include "core/debug/Log.h"
#include "graphics/component/VertexData.h"
using namespace radium;

Mesh::Mesh()
	: m_vtxBuf(nullptr), m_idxBuf(nullptr), m_vertexCount(0), m_indexCount(0)
{

}

Mesh::~Mesh()
{
	if (m_idxBuf)
		delete m_idxBuf;
	if (m_vtxBuf)
		delete m_vtxBuf;

}

bool Mesh::load(const byte* data, U32 size, IRenderDriver& rd)
{
	MeshHeader* mh = (MeshHeader*)(data);

	if (mh->magic != MESH_FILE_HEADER_MAGIC)
	{
		RAD_ENGINE_ERROR("Mesh magic not match. Got {:02X}. Expected {:02X}", mh->magic, MESH_FILE_HEADER_MAGIC);
		return false;
	}

	U32 vertexCount = (U32)(mh->vtxCount / sizeof(VertexData));
	U32 indexCount = (U32)(mh->idxCount / sizeof(IndexData));

	RAD_ENGINE_INFO(
		"Loading Mesh. Verticies: {} | Indices: {}",
		vertexCount, indexCount
	);

	BufferDescription vbd
	{
		.type = buffer_t::VERTEX,
		.size = sizeof(VertexData),
		.count = vertexCount,
		.data = (void*)(data + mh->vtxOffset)
	};

	BufferDescription ibd
	{
		.type = buffer_t::INDEX,
		.size = sizeof(IndexData),
		.count = indexCount,
		.data = (void*)(data + mh->idxOffset)
	};

	m_vtxBuf = rd.createBuffer(vbd);
	m_idxBuf = rd.createBuffer(ibd);

	if (!m_vtxBuf || !m_idxBuf)
		return false;

	RAD_ENGINE_INFO("Mesh loaded successfully");
	m_indexCount = indexCount;
	m_vertexCount = vertexCount;
	return true;

}


