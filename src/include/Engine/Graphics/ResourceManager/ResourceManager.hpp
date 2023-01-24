#pragma once

#include <map>
#include <unordered_map>
#include <string>

#include "Engine/Prerequisites.hpp"
#include "Engine/Graphics/ResourceManager/Resource.hpp"

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) = 0;

private:
	std::unordered_map<std::wstring, ResourcePtr> m_resources;
};
