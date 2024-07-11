#include "SubMesh.h"
#include "MeshExporter.h"

#include <fstream>

#include <assimp/mesh.h>
#include <spdlog/spdlog.h>
using acp::SubMesh;

SubMesh::SubMesh(aiMesh* mesh)
	: m_mesh(mesh)
{
	if (!mesh)
	{
		spdlog::error("SubMesh: invalid mesh");
	}
}

size_t SubMesh::process()
{
	if (!m_mesh)
		return -1;

	spdlog::info("Processing New mesh '{}' | {} vertices", 
		m_mesh->mName.C_Str(), m_mesh->mNumVertices);

	m_name = m_mesh->mName.C_Str();

	unsigned int numVerticesWithoutTexCoords = 0;

	for (unsigned int i = 0; i < m_mesh->mNumVertices; i++)
	{
		VertexData vtx{};

		vtx.position.x = m_mesh->mVertices[i].x;
		vtx.position.y = m_mesh->mVertices[i].y;
		vtx.position.z = m_mesh->mVertices[i].z;
	
		vtx.normal.x = m_mesh->mNormals[i].x;
		vtx.normal.y = m_mesh->mNormals[i].y;
		vtx.normal.z = m_mesh->mNormals[i].z;

		if (m_mesh->mTextureCoords[0])
		{
			vtx.texCoord.x = m_mesh->mTextureCoords[0][i].x;
			vtx.texCoord.y = m_mesh->mTextureCoords[0][i].y;
		}
		else
		{
			numVerticesWithoutTexCoords++;
			vtx.texCoord.x = 0;
			vtx.texCoord.y = 0;
		}

		m_vtxList.push_back(vtx);
	}


	for (unsigned int i = 0; i < m_mesh->mNumFaces; i++)
	{
		aiFace& face = m_mesh->mFaces[i];


		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			m_idxList.push_back(face.mIndices[j]);
		}
	}


	if (numVerticesWithoutTexCoords > 0)
		spdlog::warn("{} has {} vertices without texture coordinates.", m_name, numVerticesWithoutTexCoords);

	return (m_idxList.size() * sizeof(uint32_t)) + (m_vtxList.size() * sizeof(VertexData));
}


size_t SubMesh::serialize(const std::string& targetDirectory)
{
	size_t targetSize = sizeof(MeshHeader) + (m_idxList.size() * sizeof(uint32_t)) + (m_vtxList.size() * sizeof(VertexData));


	unsigned char* outBuf = new unsigned char[targetSize];

	uint32_t vertexSize = m_vtxList.size() * sizeof(VertexData);
	uint32_t indexSize = m_idxList.size() * sizeof(uint32_t);

	MeshHeader mh =
	{
		.vertexOffset = sizeof(mh),
		.vertexSize = vertexSize,

		.indexOffset = sizeof(mh) + mh.vertexSize,
		.indexSize = indexSize
	};

	size_t offset = 0;

	memcpy_s(
		(void*)outBuf,
		targetSize,
		&mh,
		sizeof(MeshHeader)
	);

	offset += sizeof(MeshHeader);

	memcpy_s(
		(void*)(outBuf + offset),
		targetSize,
		m_vtxList.data(),
		vertexSize
	);
	
	offset += vertexSize;

	memcpy_s(
		(void*)(outBuf + offset),
		targetSize,
		m_idxList.data(),
		indexSize
	);

	std::string filename = targetDirectory + '/' + m_name + ".mdl";
	spdlog::info("Serializeing mesh '{}' to {} : {} bytes",
		m_name, filename, targetSize	
	);

	std::ofstream out(filename, std::ios::binary);

	if (!out.good())
	{
		spdlog::error("Failed to create/open file at {}", filename);
		delete[] outBuf;
		return -1;
	
	}

	out.write(
		(char*)outBuf,
		targetSize
	);

	delete[] outBuf;

	return targetSize;
}

