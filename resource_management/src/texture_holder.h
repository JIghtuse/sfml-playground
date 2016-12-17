#pragma once

#include "textures.h"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class TextureHolder {
public:
    sf::Texture& get(Textures id);
    const sf::Texture& get(Textures id) const;
    void load(Textures id, const std::string& filename);

private:
    std::unordered_map<Textures, std::unique_ptr<sf::Texture>> _textureMap{};
};
