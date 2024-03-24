#include "Animation.h"
Animation::Animation()
{
    InitPlayerAnimation();
    InitEnemyAnimation();
    InitFire();
    InitDynamicBackGround();
    InitBackGround();
}
void Animation::InitPlayerAnimation(){
    texturePlayer.loadFromFile("SpaceShooterAssetPack_Ships.png");
    spritePlayer.setTexture(texturePlayer);
    rectPlayer.left = 32;
    rectPlayer.top = 64;
    rectPlayer.height = 16;
    rectPlayer.width = 16;
    spritePlayer.setTextureRect(rectPlayer);
    spritePlayer.scale(scalePlayer, -scalePlayer);
    spritePlayer.setOrigin(rectPlayer.width / 2, rectPlayer.height / 2 + 2);
}
void Animation::UpdatePlayerAnimation(sf::RectangleShape player){
    spritePlayer.setPosition(player.getPosition());
}
void Animation::InitEnemyAnimation(){
    textureEnemy.loadFromFile("SpaceShooterAssetPack_Ships.png");
    spriteEnemy.setTexture(textureEnemy);
    rectEnemy.left = 32;
    rectEnemy.top = 48;
    rectEnemy.height = 16;
    rectEnemy.width = 16;
    spriteEnemy.setTextureRect(rectEnemy);
    spriteEnemy.scale(scaleEnemy, scaleEnemy);
    spriteEnemy.setOrigin(rectEnemy.width / 2, rectEnemy.height / 2);
}
void Animation::SpawnEnemyAnimation(){
    int a = rand() % 3;
    switch (a)
    {
    case 0:
        rectEnemy.left = 32;
        break;
    case 1:
        rectEnemy.left = 48;
        break;
    case 2:
        rectEnemy.left = 64;
        break;
    default:
        break;
    }
    spriteEnemy.setTextureRect(rectEnemy);
    spriteEnemys.push_back(spriteEnemy);
}
void Animation::UpdateEnemyAnimation(vector<sf::RectangleShape> enemys){
    for (int i = 0; i < enemys.size(); i++)
    {
        spriteEnemys[i].setPosition(enemys[i].getPosition());
    }
}
void Animation::DeleteEnemyAnimation(int i){
    spriteEnemys.erase(spriteEnemys.begin() + i);
}
void Animation::InitBackGround(){
    textureBackGround.loadFromFile("SpaceShooterAssetPack_BackGrounds.png");
    spriteBackGround.setTexture(textureBackGround);
    rectBackGround.left = 256;
    rectBackGround.top = 256;
    rectBackGround.height = 256;
    rectBackGround.width = 128;
    spriteBackGround.setOrigin(rectBackGround.width / 2, rectBackGround.height / 2);
    spriteBackGround.setScale(4.5f,4.5f);
    spriteBackGround.setPosition(screenWidht / 2, screenHeight / 2);
    spriteBackGround.setTextureRect(rectBackGround);
}
void Animation::InitDynamicBackGround(){
    textureBackGround.loadFromFile("SpaceShooterAssetPack_BackGrounds.png");
    spriteBackGround_D.setTexture(textureBackGround);
    rectBackGround_D.left = 128;
    rectBackGround_D.top = 256;
    rectBackGround_D.height = 256;
    rectBackGround_D.width = 128;
    spriteBackGround_D.setScale(4.5f,4.5f);
    spriteBackGround_D.setOrigin(rectBackGround_D.width / 2, rectBackGround_D.height / 2);
    spriteBackGround_D.setPosition(screenWidht / 2, -(rectBackGround_D.height * 2 + 10));
    spriteBackGround_D.setTextureRect(rectBackGround_D);
}
void Animation::SpawnDynamicBackGround(){
    if (firstSpawn)
    {
        spriteBackGround_Ds.push_back(spriteBackGround_D);
        firstSpawn = false;
    }
    if (timeSpawnBack >= timeMaxSpawnBack)
    {
        spriteBackGround_Ds.push_back(spriteBackGround_D);
        timeSpawnBack = 0.f;
    }
    else
        timeSpawnBack++;
}
void Animation::UpdateDynamicBackGround(){
    for (auto &i : spriteBackGround_Ds)
    {
        i.move(0.f, 1.f);
    }
}
void Animation::DeleteDynamicBackGround(){
    for (int i = 0; i < spriteBackGround_Ds.size(); i++)
    {
        if (spriteBackGround_Ds[i].getPosition().y >= screenHeight + rectBackGround_D.top + 250)
        {
            spriteBackGround_Ds.erase(spriteBackGround_Ds.begin() + i);
        }
    }
}
void Animation::InitFire(){
    textureFire.loadFromFile("SpaceShooterAssetPack_Miscellaneous.png");
    spriteFire.setTexture(textureFire);
    rectFire.left = 40;
    rectFire.top = 24;
    rectFire.width = 8;
    rectFire.height = 8;
    spriteFire.setScale(5.f,5.f);
    spriteFire.setOrigin(rectFire.width / 2, rectFire.height);
    spriteFire.setTextureRect(rectFire);
}
void Animation::UpdateFire(sf::RectangleShape player){
    if (timeFire >= timeMaxFire)
    {
        if (rectFire.left >= 40 && rectFire.left <= 56)
        {
            rectFire.left += 8;
        }
        else
            rectFire.left = 40;
        
        timeFire = 0;
    }
    else
        timeFire++;
    
    spriteFire.setTexture(textureFire);
    spriteFire.setPosition(player.getPosition().x, player.getPosition().y + texturePlayer.getSize().y - 10);
    spriteFire.setOrigin(rectFire.width / 2, rectFire.height);
    spriteFire.setTextureRect(rectFire);
}