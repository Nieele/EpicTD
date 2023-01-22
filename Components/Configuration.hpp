#pragma once

#include <mutex>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ResourceManager.hpp"

class Configuration
{
public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    const enum Backgrounds : int {
        MainMenu,
        PauseMenu,
        GameBack,
        ItemsMenu,
        InfoMenu,
        GameOver,
        GameWin
    };
    static ResourceManager<sf::Texture, int> backgrounds;

    const enum Textures : int {
        GameMap,

        WoodTower,
        WoodTower_weapon,
        WoodTower_bullet,

        StoneTower,
        StoneTower_weapon,
        StoneTower_bullet,

        GalacticTower,
        GalacticTower_weapon,
        GalacticTower_bullet,

        LeafbugEnemy,
        MagmaCrab,
        Scorpion
    };
    static ResourceManager<sf::Texture, int> textures;

    enum Fonts : int { 
        MenuGUI,
        GameGUI
    };
    static ResourceManager<sf::Font, int> fonts;

    enum Sounds : int {
        AttackWoodTower,
        AttackStoneTower,
        AttackGalacticTower
    };
    static ResourceManager<sf::SoundBuffer, int> sounds;

    enum Musics : int {
        MainTheme,
        GameOverTheme
    };
    static ResourceManager<sf::Music, int> musics;

    static void initialize();

private:
    static void initBackgrounds();
    static void initTextures();
    static void initFonts();
    static void initSounds();
    static void initMusics();
};