#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__

#include <map>
#include <memory>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceManager
{
    public:
        void load(Identifier id, const std::string& filename);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;
    private:
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);
    private:
        std::map<Identifier, std::unique_ptr<Resource>>	_resourceMap;
};


template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceManager::load - Error while loading " + filename);
	insertResource(id, std::move(resource));
}


template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end());
	return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end());
	return *found->second;
}


template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}


#endif // __RESOURCEMANAGER_HPP__