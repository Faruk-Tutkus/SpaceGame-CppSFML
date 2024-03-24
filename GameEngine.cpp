#include "GameEngine.h"
GameEngine::GameEngine()
{
    srand(unsigned(time(NULL)));
    InitWindow();
    //player
    InitPlayer();
    //enemy
    InitEnemy();
    //bullet
    InitBullet();
    //wall
    InitWall();
    //randomkey
    InitRandomKey();
    //material
    InitGameItems();
    WindowUpdate();
}
GameEngine::~GameEngine(){
    delete window;
    delete event;
}
void GameEngine::InitWindow(){
    this->window = new sf::RenderWindow(sf::VideoMode(screenWidht, screenHeight), "SFML");
    this->event = new sf::Event;
    this->window->setVerticalSyncEnabled(true);
}
void GameEngine::WindowUpdate(){
    while (this->window->isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            GameRestart();
        }
        //window
        UpdateEvent();
        if (!isPause)
        {
            //bullet
            SpawnBullet();
            UpdateBullet();
            DeleteBullet();
            //player
            MovePlayer();
            //enemy
            SpawnEnemy();
            DeleteEnemey();
            UpdateEnemy();
            //GameSpeed
            GameSpeedUp();
            //RandomKey
            SpawnRandomKey();
            UpdateRandomKey();
            DeleteRandomKey();
            UpdateGetTimeRandomKey();
            //gameitem
            UpdateGameItems();
            //Animation
            Animation::UpdatePlayerAnimation(player);
            Animation::UpdateEnemyAnimation(enemys);
            Animation::SpawnDynamicBackGround();
            Animation::UpdateDynamicBackGround();
            Animation::DeleteDynamicBackGround();
            Animation::UpdateFire(player);
        }
        
        //render
        RenderWindow();
    }
}
void GameEngine::UpdateEvent(){
    while (this->window->pollEvent(*(this->event)))
    {       
        switch (this->event->type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                this->window->close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                GamePause();
            }
            break;
        }
    }
}
void GameEngine::RenderWindow(){
    this->window->clear();
    for (auto &i : Animation::spriteBackGround_Ds)
    {
        this->window->draw(i);
    }
    this->window->draw(Animation::spriteBackGround);
    this->window->draw(textHealth);
    this->window->draw(textPoint);
    for (auto &i : bullets)
    {
        this->window->draw(i);
    }
    for (auto &i : enemys)
    {
        this->window->draw(i);
    }
    for (auto &i : randomKeys)
    {
        this->window->draw(i);
    }
    this->window->draw(Animation::spritePlayer);
    for (auto &i : Animation::spriteEnemys)
    {
        this->window->draw(i);
    }
    this->window->draw(spriteFire);
    this->window->draw(player);
    this->window->draw(wall_L);
    this->window->draw(wall_R);
    this->window->draw(wall_U);
    this->window->draw(wall_D);
    
    this->window->display();
}
void GameEngine::InitWall(){
    //wall_L
    wall_L.setFillColor(sf::Color::Red);
    wall_L.setSize(sf::Vector2f(10.f,screenHeight));

    //wall_R
    wall_R.setFillColor(sf::Color::Red);
    wall_R.setSize(sf::Vector2f(10.f,screenHeight));
    wall_R.setPosition(screenWidht - wall_R.getSize().x, 0.f);

    //wall_U
    wall_U.setFillColor(sf::Color::Red);
    wall_U.setSize(sf::Vector2f(screenWidht, 10.f));

    //wall_D
    wall_D.setFillColor(sf::Color::Red);
    wall_D.setSize(sf::Vector2f(screenWidht, 10.f));
    wall_D.setPosition(0.f, screenHeight - wall_D.getSize().y);
}
void GameEngine::RandomColorWalls(){
    wall_R.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255 ));
    wall_L.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255 ));
    wall_U.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255 ));
    wall_D.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255 ));
}
void GameEngine::InitPlayer(){
    player.setSize(sf::Vector2f(80.f,30.f));
    player.setOrigin(player.getSize().x / 2, player.getSize().y / 2);
    player.setPosition(screenWidht / 2, 700);
    player.setFillColor(sf::Color(0,255,0,0));
}
void GameEngine::MovePlayer(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (player.getPosition().x < screenWidht - player.getSize().x / 2 - 10)
        {
            player.move(speedPlayer, 0.f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (player.getPosition().x > player.getSize().x / 2 + 10)
        {
            player.move(-speedPlayer, 0.f);
        }
    }
}
void GameEngine::InitBullet(){
    bullet.setFillColor(sf::Color::White);
    bullet.setSize(sf::Vector2f(10.f,20.f));
    bullet.setOrigin(bullet.getSize().x / 2, bullet.getSize().y / 2);
}
void GameEngine::SpawnBullet(){
    if (timeSpawnBullet >= timeMaxBullet)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            timeSpawnBullet = 0;
            bullet.setPosition(player.getPosition().x, player.getPosition().y);
            bullets.push_back(bullet);
        }
    }
    else
        timeSpawnBullet++;
}
void GameEngine::UpdateBullet(){
    for (auto &i : bullets)
    {
        i.move(0.f, -speedBullet);
    }
}
void GameEngine::DeleteBullet(){
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].getPosition().y <= 0)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}
void GameEngine::InitEnemy(){
    enemy.setFillColor(sf::Color(255,0,0,0));
    enemy.setSize(sf::Vector2f(65.f, 50.f));
    enemy.setOrigin(enemy.getSize().x / 2, enemy.getSize().y / 2);
}
void GameEngine::SpawnEnemy(){
    if (timeSpawnEnemy >= timeMaxEnemy)
    {
        Animation::SpawnEnemyAnimation();
        enemy.setPosition(rand() % (screenWidht - 100) + 50, -25.f);
        enemys.push_back(enemy);

        timeSpawnEnemy = 0;
    }
    else
        timeSpawnEnemy++;
}
void GameEngine::UpdateEnemy(){
    for (auto &i : enemys)
    {
        i.move(0.f, speedEnemy);
    }
}
void GameEngine::DeleteEnemey(){
    for (int i = 0; i < enemys.size(); i++)
    {
        if (enemys[i].getPosition().y >= 800)
        {
            RandomColorWalls();
            Animation::DeleteEnemyAnimation(i);
            enemys.erase(enemys.begin() + i);
            health--;
        }
        if (enemys[i].getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            RandomColorWalls();
            Animation::DeleteEnemyAnimation(i);
            enemys.erase(enemys.begin() + i);
            health--;
        }
        for (int j = 0; j < bullets.size(); j++)
        {
            if (enemys[i].getGlobalBounds().intersects(bullets[j].getGlobalBounds()))
            {
                RandomColorWalls();
                Animation::DeleteEnemyAnimation(i);
                enemys.erase(enemys.begin() + i);
                bullets.erase(bullets.begin() + j);
                point++;
            }
        }
    }
}
void GameEngine::GameSpeedUp(){
    if (timeGame >= timeMaxGame)
    {
        timeGame = 0;
        if (timeMaxEnemy >= 20)
        {
            timeMaxEnemy--;
            timeSpawnMaxRandomKey--;
        }
    }
    else
        timeGame++;
}
void GameEngine::GamePause(){
    if (isPause)
    {
        isPause = false;
    }
    else
        isPause = true;
    
}
void GameEngine::GameRestart(){
    if (isRestart)
    {
        isRestart = false;
        timeSpawnBullet = 0.f;
        timeSpawnEnemy = 0.f;
        timeGame = 0.f;
        timeSpawnRandomKey = 0.f;
        timeSpawnRandomKey = 0.f;
        totalTimeRandomKey = 0.f;
        //default max
        timeMaxBullet = 20.f;
        timeMaxEnemy = 100.f;
        timeMaxGame = 250.f;
        timeSpawnMaxRandomKey = 750.f;
        totalTimeMaxRandomKey = 500.f;
        active = false;
        tempTimeMaxBullet = 20.f;
        health = 5;
        point = 0;
        for (int i = 0; i < enemys.size(); i++)
        {
            enemys.erase(enemys.begin() + i);
            Animation::spriteEnemys.erase(Animation::spriteEnemys.begin() + i);
        }
        for (int i = 0; i < randomKeys.size(); i++)
        {
            randomKeys.erase(randomKeys.begin() + i);
        }
        
    }
    else
        isRestart = true;
    
}
void GameEngine::InitRandomKey(){
    randomKey.setFillColor(sf::Color::Blue);
    randomKey.setSize(sf::Vector2f(25.f,25.f));
    randomKey.setOrigin(randomKey.getSize().x / 2, randomKey.getSize().y / 2);
}
void GameEngine::SpawnRandomKey(){
    if (timeSpawnRandomKey >= timeSpawnMaxRandomKey)
    {
        randomKey.setPosition(rand() % (screenWidht - 100) + 50, -25.f);
        randomKeys.push_back(randomKey);
        timeSpawnRandomKey = 0;
    }
    else
        timeSpawnRandomKey++;
}
void GameEngine::UpdateRandomKey(){
    for (auto &i : randomKeys)
    {
        i.move(0.f, speedRandomKey);
    }
}
void GameEngine::DeleteRandomKey(){
    for (int i = 0; i < randomKeys.size(); i++)
    {
        if (randomKeys[i].getPosition().y >= 800)
        {
            randomKeys.erase(randomKeys.begin() + i);
        }
        if (randomKeys[i].getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            randomKeys.erase(randomKeys.begin() + i);
            GetRandomKey();
        }
    }
}
void GameEngine::GetRandomKey(){
    int a = rand() % 4;
    float tempTimeMaxBullet = timeMaxBullet;
    switch (a)
    {
    case 0: //bulletSpawnUp
        health++;
        break;
    case 1:
        timeMaxBullet = 5.f;
        break;
    case 2:
        timeMaxBullet = 2.5f;
        break;
    case 3:
        health += 2;
        break;
    }
    active = true;
}
void GameEngine::UpdateGetTimeRandomKey(){
    if (active)
    {
        if (totalTimeRandomKey >= totalTimeMaxRandomKey)
        {
            timeMaxBullet = tempTimeMaxBullet;
            active = false;
            totalTimeRandomKey = 0.f;
        }
        else
            totalTimeRandomKey++;
    }
}
void GameEngine::InitGameItems(){
    font.loadFromFile("Hello Candy.otf");
    //health
    textHealth.setFont(font);
    textHealth.setCharacterSize(80);
    textHealth.setFillColor(sf::Color(0,250,50,150));

    //point
    textPoint.setFont(font);
    textPoint.setCharacterSize(200);
    textPoint.setFillColor(sf::Color(255,255,255,100));
}
void GameEngine::UpdateGameItems(){
    //point
    textPoint.setString(to_string(point));
    widthPoint = textPoint.getGlobalBounds().width;
    heightPoint = textPoint.getGlobalBounds().height;
    textPoint.setPosition(screenWidht / 2 - widthPoint / 2, screenHeight / 2 - heightPoint);

    //health
    textHealth.setString(to_string(health));
    widthHealth = textHealth.getGlobalBounds().width;
    heightHealth = textHealth.getGlobalBounds().height;
    textHealth.setPosition(screenWidht / 2 - widthHealth / 2, screenHeight / 2 - heightHealth);

    if (health <= 0)
    {
        GameRestart();
    }
    
}