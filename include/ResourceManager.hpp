#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__

#include <map>
#include <memory>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceManager
{
    public:
        void load(Identifier id, const std::string& filename);                   // On ajoute une ressource avec le fichier et l'ID voulu
        Resource& get(Identifier id);                                            // Permet de récupérer une resource via son ID  
        const Resource& get(Identifier id) const;                                // Permet de récupérer une resource via son ID
     private: 
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);  // On ajoute une resource  à la map
    private:
        std::map<Identifier, std::unique_ptr<Resource>>	_resourceMap;            // La std::map dans laquelle on stocke les ressources
};


template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))                // Si le chargement de la ressource échoue
		throw std::runtime_error("ResourceManager::load - Error while loading " + filename); // Erreur
	insertResource(id, std::move(resource));              // sinon on l'ajoute comme prévu
}


template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end()); // Si map::end est retourné, c'est que la ressource demandée est introuvable -> problème
	return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end()); // Si map::end est retourné, c'est que la ressource demandée est introuvable -> problème
	return *found->second;
}


template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second); // true si l'élément a été inséré donc on vérifie
}


#endif // __RESOURCEMANAGER_HPP__