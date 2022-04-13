#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "File.h"
#include "IResource.h"

class Resources;

template<class T>
class ResourceHandler
{
private:
	std::unordered_map<size_t, std::shared_ptr<T>> m_resources;
public:
	std::shared_ptr<T> GetResource(const std::string& _path, Resources* _resources, const bool _load = true)
	{
		// The return value
		std::shared_ptr<T> resource;

		const size_t key = std::hash<std::string>()(_path);

		// Check to see if the key exists within the hash map already.
		const auto iterator = m_resources.find(key);
		if (iterator == m_resources.end())
		{
			// If the resource does not exist, create a new one loaded from the given path and insert it into the hash map.
			resource = std::make_unique<T>();
			if (_load)
			{
				std::dynamic_pointer_cast<IResource>(resource)->Load(File::EvaluatePath(_path), _resources);
			}

			m_resources.insert(std::make_pair(key, resource));
		}
		else
		{
			// Otherwise, return the resource as it exists.
			resource = iterator->second;
		}

		return resource;
	}
	
	std::shared_ptr<T> GetResource(const std::string& _path, Resources* _resources, bool& _alreadyLoaded, const bool _load = true)
	{
		// The return value
		std::shared_ptr<T> resource;

		const size_t key = std::hash<std::string>()(_path);

		// Check to see if the key exists within the hash map already.
		const auto iterator = m_resources.find(key);
		if (iterator == m_resources.end())
		{
			// If the resource does not exist, create a new one loaded from the given path and insert it into the hash map.
			resource = std::make_unique<T>();
			if (_load)
			{
				std::dynamic_pointer_cast<IResource>(resource)->Load(File::EvaluatePath(_path), _resources);
			}

			m_resources.insert(std::make_pair(key, resource));
		}
		else
		{
			// Otherwise, return the resource as it exists.
			resource = iterator->second;
			_alreadyLoaded = true;
		}

		return resource;
	}
};
