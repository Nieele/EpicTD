#pragma once

#include <mutex>
#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr
#include <stdexcept> //runtime_error
#include <utility> //forward

#include "SFML/Audio.hpp" //sf::Music

template<typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager() = default;

	template<typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);

	RESOURCE& get(const IDENTIFIER& id)const;

private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
	std::mutex locker;
};

template<typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER>
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager() = default;

	template<typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);


	sf::Music& get(const IDENTIFIER& id)const;

private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> _map;
};

template<typename RESOURCE, typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<RESOURCE> ptr(new RESOURCE);
	if (not ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Impossible to load file");
	if (_map.emplace(id, std::move(ptr)).second == false)
		throw std::runtime_error("Impossible to emplace in map. Object already load?");
}

template<typename RESOURCE, typename IDENTIFIER>
RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id)const
{
	return *_map.at(id);
}

//sf::Music special case
template<typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);

	if (not ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Impossible to load file");
	if (_map.emplace(id, std::move(ptr)).second == false)
		throw std::runtime_error("Impossible to emplace in map. Object aleardy load?");
};

template<typename IDENTIFIER>
sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *_map.at(id);
}