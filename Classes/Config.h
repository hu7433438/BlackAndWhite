
#ifndef MoonWarriorsx_Config_h
#define MoonWarriorsx_Config_h

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;

extern cocos2d::CCArray *play_bullet;
extern cocos2d::CCArray *enemy_bullet;
extern cocos2d::CCArray *enemy_items;
extern cocos2d::CCArray *balk_items;

typedef struct Enemies
{
    int showType;
    int showTime;
    int types[2];
    Enemies()
    {
        showType = 0;
        showTime = 0;
        types[0] = 0;
        types[1] = 0; 
    }
}EnemyInfo;

typedef struct
{
    int type;
    string textureName;
    string bulletType;
    int hp;
	int bulletSpeed;
    int moveType;
    int scoreValue;
	float shootTime;
	int attackMode;
	bool isShoot;
}EnemyType;


class Config : public CCObject
{
private:
    vector<EnemyInfo> m_enemies;
    vector<EnemyType> m_enemyTypes;
    int m_scoreValue;
    int m_life;
    bool m_isAudioOn;
    Config();
public:
    ~Config();
    static Config* sharedConfig();
    vector<EnemyInfo> getEnemise();
    vector<EnemyType> getEnemyType();
    int getLifeCount();
	void setLifeCount(int life);
    bool getAudioState();
    void updateAudioState(bool isOn);
    int getScoreValue();
    void updateLifeCount();
    void setScoreValue(int score);
    void resetConfig();
};


#endif
