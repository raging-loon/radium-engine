#include "MeshExporter.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <spdlog/spdlog.h>

using acp::MeshExporter;
using acp::SubMesh;

MeshExporter::MeshExporter(std::string& filename)
	: m_meshScene(nullptr), m_subMeshes{}, m_filename(filename)
{

}

acp::MeshExporter::~MeshExporter()
{
	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		if (m_subMeshes[i])
			delete m_subMeshes[i];
	}

}

size_t MeshExporter::process()
{
	Assimp::Importer importer;

	m_meshScene = importer.ReadFile(m_filename, aiProcess_MakeLeftHanded | 
											    aiProcess_Triangulate | 
												aiProcess_JoinIdenticalVertices);

	if (!m_meshScene || m_meshScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_meshScene->mRootNode)
	{
		spdlog::error("Failed to import mesh: {}", importer.GetErrorString());
		return -1;
	}

	size_t data = interalProcess(m_meshScene->mRootNode);
	
	importer.FreeScene();

	return data;
}

void acp::MeshExporter::serialize(std::string targetDirectory)
{
	size_t total = 0;
	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		total += m_subMeshes[i]->serialize(targetDirectory);
	}

	spdlog::info("Wrote {} mesh[es] from {} to {}. Total: {}b",
		m_subMeshes.size(),
		m_filename,
		targetDirectory,
		total
	);

}

size_t MeshExporter::interalProcess(const aiNode* cRoot)
{
	size_t total = 0;
	for (unsigned int i = 0; i < cRoot->mNumMeshes; i++)
	{
		auto* sm = new SubMesh(m_meshScene->mMeshes[cRoot->mMeshes[i]]);
		
		auto bytes = sm->process();

		if (bytes == -1)
		{
			spdlog::info("Failed to process mesh");
			delete sm;
		}

		m_subMeshes.push_back(sm);

		total += bytes;
	}

	for (unsigned int i = 0; i < cRoot->mNumChildren; i++)
		interalProcess(cRoot->mChildren[i]);
	
	return total;
}
