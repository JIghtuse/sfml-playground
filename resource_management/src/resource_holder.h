#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
    void load(Identifier id, const std::string& filename);
    template<typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParameter);

private:
    std::unordered_map<Identifier, std::unique_ptr<Resource>> _resourceMap{};
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    auto emplaced = _resourceMap.emplace(id, std::move(resource));
    assert(emplaced.second);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParameter)
{
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename, secondParameter)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    auto emplaced = _resourceMap.emplace(id, std::move(resource));
    assert(emplaced.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = _resourceMap.find(id);
    assert(found != _resourceMap.end());

    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = _resourceMap.find(id);
    assert(found != _resourceMap.end());

    return *found->second;
}
