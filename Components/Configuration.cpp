#include "Configuration.hpp"

ResourceManager<sf::Texture, int> Configuration::backgrounds;
ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Music, int> Configuration::musics;

void Configuration::initialize()
{
	initBackgrounds();
	initTextures();
	initFonts();
	initSounds();
	initMusics();

	// TODO: create MusicHelper
	musics.get(Musics::MainTheme).setLoop(true);
	musics.get(Musics::MainTheme).play();

	musics.get(Musics::GameOverTheme).setLoop(true);
}

void Configuration::initBackgrounds()
{
	backgrounds.load(Backgrounds::MainMenu, "Media/Backgrounds/MainMenuBackground.png");
	backgrounds.load(Backgrounds::PauseMenu, "Media/Backgrounds/PauseMenuBackground.png");
	backgrounds.load(Backgrounds::GameBack, "Media/Backgrounds/GameBackground.png");
	backgrounds.load(Backgrounds::ItemsMenu, "Media/Backgrounds/ItemMenuBackground.png");
	backgrounds.load(Backgrounds::InfoMenu, "Media/Backgrounds/InfoMenuBackground.png");
	backgrounds.load(Backgrounds::GameOver, "Media/Backgrounds/GameOverBackground.png");
	backgrounds.load(Backgrounds::GameWin, "Media/Backgrounds/GameWinBackground.png");
}

void Configuration::initTextures()
{
	textures.load(Textures::GameMap, "Media/Textures/Map/gameMap.png");

	textures.load(Textures::WoodTower, "Media/Textures/Towers/woodTower.png");
	textures.load(Textures::WoodTower_weapon, "Media/Textures/Towers/woodTower_weapon.png");
	textures.load(Textures::WoodTower_bullet, "Media/Textures/Towers/woodTower_bullet.png");

	textures.load(Textures::StoneTower, "Media/Textures/Towers/stoneTower.png");
	textures.load(Textures::StoneTower_weapon, "Media/Textures/Towers/stoneTower_weapon.png");
	textures.load(Textures::StoneTower_bullet, "Media/Textures/Towers/stoneTower_bullet.png");

	textures.load(Textures::GalacticTower, "Media/Textures/Towers/galacticTower.png");
	textures.load(Textures::GalacticTower_weapon, "Media/Textures/Towers/galacticTower_weapon.png");
	textures.load(Textures::GalacticTower_bullet, "Media/Textures/Towers/galacticTower_bullet.png");

	textures.load(Textures::LeafbugEnemy, "Media/Textures/Enemies/leafbug.png");
	textures.load(Textures::MagmaCrab, "Media/Textures/Enemies/magmaCrab.png");
	textures.load(Textures::Scorpion, "Media/Textures/Enemies/scorpion.png");
}

void Configuration::initFonts()
{
	fonts.load(Fonts::MenuGUI, "Media/Fonts/MenuGUI.otf");
	fonts.load(Fonts::GameGUI, "Media/Fonts/GameGUI.otf");
}

void Configuration::initSounds()
{
	/*sounds.load(Sounds::AttackWoodTower, "media/sounds/woodTower_attackSound.ogg");
	sounds.load(Sounds::AttackStoneTower, "media/sounds/stoneTower_attackSound.ogg");
	sounds.load(Sounds::AttackGalacticTower, "media/sounds/galacticTower_attackSound.ogg");*/
}
void Configuration::initMusics()
{
	musics.load(Musics::MainTheme, "Media/Musics/mainTheme.ogg");
	musics.load(Musics::GameOverTheme, "Media/Musics/GameOverTheme.ogg");
}