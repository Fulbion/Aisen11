#include <filesystem>

#include "Engine/Graphics/ResourceManager/ResourceManager.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = std::filesystem::absolute(filePath);

	auto it = m_resources.find(fullPath);

	if (it != m_resources.end())
		return it->second;

	Resource* rawResource = this->createResourceFromFileConcrete(fullPath.c_str());

	if (rawResource)
	{
		ResourcePtr resource(rawResource);
		m_resources[fullPath] = resource;
		return resource;
	}

	return nullptr;
}
