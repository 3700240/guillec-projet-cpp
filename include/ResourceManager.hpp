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

#include <ResourceManager.inl>

#endif // __RESOURCEMANAGER_HPP__