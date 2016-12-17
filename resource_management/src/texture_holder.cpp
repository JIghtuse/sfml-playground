#include "texture_holder.h"
#include <cassert>

void TextureHolder::load(Textures id, const std::string& filename)
{
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
    auto emplaced = _textureMap.emplace(id, std::move(texture));
    assert(emplaced.second);
}

sf::Texture& TextureHolder::get(Textures id)
{
    auto found = _textureMap.find(id);
    assert(found != _textureMap.end());

    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures id) const
{
    auto found = _textureMap.find(id);
    assert(found != _textureMap.end());

    return *found->second;
}
