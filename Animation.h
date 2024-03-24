#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;
class Animation
{
public:
    Animation();
    void InitPlayerAnimation();
    void UpdatePlayerAnimation(sf::RectangleShape);

    void InitEnemyAnimation();
    void SpawnEnemyAnimation();
    void UpdateEnemyAnimation(vector<sf::RectangleShape>);
    void DeleteEnemyAnimation(int);
    
    void InitBackGround();

    void InitDynamicBackGround();
    void SpawnDynamicBackGround();
    void UpdateDynamicBackGround();
    void DeleteDynamicBackGround();

    void InitFire();
    void UpdateFire(sf::RectangleShape);

protected:
    int screenWidht = 600;
    int screenHeight = 800;
    //player
    sf::Texture texturePlayer;
    sf::Sprite spritePlayer;
    sf::IntRect rectPlayer;
    float scalePlayer = 5.f;
    //enemy
    sf::Texture textureEnemy;
    sf::Sprite spriteEnemy;
    vector<sf::Sprite> spriteEnemys;
    sf::IntRect rectEnemy;
    float scaleEnemy = 5.f;

    //backgroundStatic
    sf::Texture textureBackGround;
    sf::Sprite spriteBackGround;
    sf::IntRect rectBackGround;

    //backgroundDynamic
    sf::Sprite spriteBackGround_D;
    vector<sf::Sprite> spriteBackGround_Ds;
    sf::IntRect rectBackGround_D;
    //speed
    float speedBackGround;
    
    //time
    float timeSpawnBack = 0.f;
    float timeMaxSpawnBack = 1000.f;
    bool firstSpawn = true;

    //fire
    sf::Texture textureFire;
    sf::Sprite spriteFire;
    sf::IntRect rectFire;

    //timeFire
    float timeFire = 0.f;
    float timeMaxFire = 10.f;
};
#endif