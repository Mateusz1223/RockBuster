#pragma once

#include "common.h"

class TexturePack
{
public:
	sf::Texture backgroundTexture;

	// Player textures
	sf::Texture normalPlayerTexture;
	sf::Texture brokenPlayerTexture;

	// Rock textures
	sf::Texture rockTextures[10];
	sf::Texture fireTexture;

	// Bullet texture
	sf::Texture bulletTexture;

	// Bonus texture
	sf::Texture bonusTexture;

	// Explosion texture
	sf::Texture explosionTexture;

	TexturePack();
	~TexturePack() {};
};

