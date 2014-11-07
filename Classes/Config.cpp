#include "Config.h"

CCArray *play_bullet;
CCArray *enemy_bullet;
CCArray *enemy_items;
CCArray *balk_items;

static  Config *g_config = NULL;

/**这里用的单例做的全局参数。JS版的直接就定义了一堆全局数组，真是方便


*/
Config::Config():m_scoreValue(0),m_life(1),m_isAudioOn(true)
{
    CCAssert(g_config == NULL, "Attempted to allocate a second instance of a singleton.");
    EnemyInfo temp;
	//一直往前走，不要停
	temp.showType = 0;
	temp.showTime = 1;
	temp.types[0] = 0;
	temp.types[1] = 0;
	m_enemies.push_back(temp);

	//快速一直往前走，不要停
    temp.showType = 1;
    temp.showTime = 2;
	temp.types[0] = 1;
    temp.types[1] = 1;
    m_enemies.push_back(temp);

	//横向移动
	temp.showType = 2;
	temp.showTime = 16;
	temp.types[0] = 2;
	temp.types[1] = 2;
	m_enemies.push_back(temp);

	//斜下
	temp.showType = 3;
	temp.showTime = 8;
	temp.types[0] = 3;
	temp.types[1] = 3;
	m_enemies.push_back(temp);

	//闪电移动
	temp.showType = 4;
	temp.showTime = 16;
	temp.types[0] = 4;
	temp.types[1] = 4;
	m_enemies.push_back(temp);

	//后方出现
	temp.showType = 5;
	temp.showTime = 32;
	temp.types[0] = 5;
	temp.types[1] = 5;
	m_enemies.push_back(temp);
    
	//前进，然后重复横向移动
	temp.showType = 6;
	temp.showTime = 2;
	temp.types[0] = 6;
	temp.types[1] = 6;
    m_enemies.push_back(temp);

	temp.showType = 7;
	temp.showTime = 16;
	temp.types[0] = 7;
	temp.types[1] = 7;
	m_enemies.push_back(temp);

	temp.showType = 8;
	temp.showTime = 10;
	temp.types[0] = 8;
	temp.types[1] = 8;
	m_enemies.push_back(temp);

	temp.showType = 9;
	temp.showTime = 16;
	temp.types[0] = 9;
	temp.types[1] = 9;
	m_enemies.push_back(temp);

    EnemyType enemyType;
	//一直往前走，不要停
    enemyType.type = 0;
    enemyType.textureName = "E0.png";
    enemyType.bulletType = "W2.png";
    enemyType.hp = 1;
	enemyType.bulletSpeed = -400;
    enemyType.moveType = 0; 
    enemyType.scoreValue = 1;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
    m_enemyTypes.push_back(enemyType);
    
	//快速一直往前走，不要停
    enemyType.type = 1;
    enemyType.textureName = "E1.png";
    enemyType.bulletType = "W2.png";
    enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
    enemyType.moveType = 1;
    enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
    m_enemyTypes.push_back(enemyType);
    
	//横向移动
    enemyType.type = 2 ;
    enemyType.textureName = "E2.png";
    enemyType.bulletType = "W2.png";
    enemyType.hp = 3;
	enemyType.bulletSpeed = -400;
    enemyType.moveType = 2;
    enemyType.scoreValue = 3;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
    m_enemyTypes.push_back(enemyType);
    
	//斜下
    enemyType.type = 3;
    enemyType.textureName = "E3.png";
    enemyType.bulletType = "W2.png";
    enemyType.hp = 3;
	enemyType.bulletSpeed = -400;
    enemyType.moveType = 3;
    enemyType.scoreValue = 3;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
    m_enemyTypes.push_back(enemyType);
    
	//闪电移动
	enemyType.type = 4;
	enemyType.textureName = "E4.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 3;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 4;
	enemyType.scoreValue = 2;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
	m_enemyTypes.push_back(enemyType);

	//后方出现
	enemyType.type = 5;
	enemyType.textureName = "E5.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 5;
	enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = false;
	m_enemyTypes.push_back(enemyType);

	//前进，然后重复横向移动
	enemyType.type = 6;
	enemyType.textureName = "E6.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 6;
	enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = true;
	m_enemyTypes.push_back(enemyType);

	enemyType.type = 7;
	enemyType.textureName = "E7.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 7;
	enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = true;
	m_enemyTypes.push_back(enemyType);

	enemyType.type = 8;
	enemyType.textureName = "E8.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 8;
	enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = true;
	m_enemyTypes.push_back(enemyType);

	enemyType.type = 9;
	enemyType.textureName = "E9.png";
	enemyType.bulletType = "W2.png";
	enemyType.hp = 2;
	enemyType.bulletSpeed = -400;
	enemyType.moveType = 9;
	enemyType.scoreValue = 2;
	enemyType.shootTime = 1;
	enemyType.attackMode = 1;
	enemyType.isShoot = true;
	m_enemyTypes.push_back(enemyType);
}
Config::~Config()
{
    play_bullet->release();
    enemy_bullet->release();
    enemy_items->release();
	balk_items->release();
    enemy_items = NULL;
    play_bullet = NULL;
    enemy_bullet = NULL;
	balk_items = NULL;
    CCLOG("release config");

}

Config *Config::sharedConfig()
{
    if (!g_config) {
        g_config = new Config();
    }
    return g_config;
}

vector<EnemyInfo> Config::getEnemise()
{
    return m_enemies;
}

vector<EnemyType> Config::getEnemyType()
{
    return m_enemyTypes;
}

int Config::getScoreValue()
{
    return m_scoreValue;
}

void Config::setScoreValue(int score)
{
    m_scoreValue += score;
}

int Config::getLifeCount()
{
    return m_life;
}


void Config::setLifeCount( int life )
{
	m_life=life;
}

void Config::updateLifeCount()
{
    m_life--;
}

bool Config::getAudioState()
{
    return m_isAudioOn;
}

void Config::updateAudioState(bool isOn)
{
    m_isAudioOn = isOn;
}

void Config::resetConfig()
{
    m_scoreValue = 0;
    m_life = 1;
//    m_isAudioOn = true;
}