#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include"Animation.cpp"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;
#pragma once
class GameEngine : public Animation
{
public:
    //class
    GameEngine();
    ~GameEngine();
    //window
    void InitWindow();
    void WindowUpdate();
    void UpdateEvent();
    void RenderWindow();

    //wall
    void InitWall();
    void RandomColorWalls();
    //player
    void InitPlayer();
    void MovePlayer();

    //bullet
    void InitBullet();
    void SpawnBullet();
    void UpdateBullet();
    void DeleteBullet();

    //enemy
    void InitEnemy();
    void SpawnEnemy();
    void UpdateEnemy();
    void DeleteEnemey();

    //GameWhile
    void GameSpeedUp();
    void GamePause();
    void GameRestart();
    //RandomKey
    void InitRandomKey();
    void SpawnRandomKey();
    void UpdateRandomKey();
    void DeleteRandomKey();
    void GetRandomKey();
    void UpdateGetTimeRandomKey();
    //GameItems
    void InitGameItems();
    void UpdateGameItems();

protected:
    //window
    int screenWidht = 600;
    int screenHeight = 800;
    sf::RenderWindow *window;
    sf::Event *event;
    
    //wall
    sf::RectangleShape wall_L;
    sf::RectangleShape wall_R;
    sf::RectangleShape wall_U;
    sf::RectangleShape wall_D;

    //player
    sf::RectangleShape player;
    float speedPlayer = 7.5f;

    //bullet
    sf::RectangleShape bullet;
    vector<sf::RectangleShape> bullets;
    float speedBullet = 25.f;

    //timeBullet
    float timeSpawnBullet = 0.f;
    float timeMaxBullet = 20.f;

    //enemy
    sf::RectangleShape enemy;
    vector<sf::RectangleShape> enemys;
    float speedEnemy = 5.f;

    //timeEnemy
    float timeSpawnEnemy = 0.f;
    float timeMaxEnemy = 100.f;
    //timeGame
    float timeGame = 0.f;
    float timeMaxGame = 250.f;

    //randomKey
    sf::RectangleShape randomKey;
    vector<sf::RectangleShape> randomKeys;
    //timeRandom
    float timeSpawnRandomKey = 0.f;
    float timeSpawnMaxRandomKey = 750.f;
    //totalTime
    float totalTimeRandomKey = 0.f;
    float totalTimeMaxRandomKey = 500.f;
    //speedRandomKey
    float speedRandomKey = 2.5f;
    //active
    bool active = false;
    //temp
    float tempTimeMaxBullet = 20.f;

    //health
    int health = 5;
    float widthHealth;
    float heightHealth;
    //point
    int point = 0;
    float widthPoint;
    float heightPoint;
    //font and text

    sf::Font font;
    sf::Text textHealth;
    sf::Text textPoint;

    //gameEvents
    bool isPause;
    bool isRestart;
};
#endif