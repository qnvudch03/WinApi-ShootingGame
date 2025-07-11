#pragma once
#include "Scence.h"
#include "Collider.h"
class GameScene : public Scence
{
public:

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;

	static GameScene* GetGameScene();
	

public:
	/*void CreateMissile(float posX, float posY, float angle, bool chase);
	void RemoveMissile(class Missile* missile);*/

	void CallMakeMissile(Vector Plyaerpos, EMissileType missiletype, int EnemyType = 0);

	void CheckPlayerCollision();
	void CheckEnemyColiision();


	// 게임이 진행줄일떄 필요한 객체
private:

	int _GameScore = 0;

	float _deltatime = 0.0;

	int _PlayerMissileLimit = 3;
	int _CurrentPlayerMissile = 0;

	int _BackGroundMoveOffset = 0;
	int _BackGroundMoveSpeed = 200;

	// 포인터로 안하고, 객체 그대로 선언해도 된다.
	class Player* _player = nullptr;

	// vector? 뭘로 하지? 고민이 될거에요. 미리 고민하면 답이 없어요.
	// 나중에 기능 점점 추가되면서, vector로는 한계가 있네.


	//충돌체크 후, 포인터를 통한 오브젝트를 찾아야 해서, set으로 변경 -> 그럼 포인터에 대한 연산자 오버로딩을 해야 해???(오바)   -> algorism을 쓰자
	vector<class Missile*>	_missileVector;
	//set<class Missile*>	_missileVector;
	vector<class Enemy*> _enemyVec;

	//콜리아더 맵을 만들고, 서로 근저해 있는 부분만 검사
	//class Collider* ColliderArray[GWinSizeY][GWinSizeX];

	//아싸리 콜라이더 벡터를 만들고, 근접해 있는 경우에만 서로 처리
	vector<class Collider<Missile>*> EnemyMissileColliderVec;
	vector<class Collider<Missile>*> PlayerMissileColliderVec;

	//순회에 좋지 않아, 또 또 벡터로 선언
	//set<class Explostion*> ExplostionList;
	vector<class Explostion*> ExplostionList;

	float Enemy_spawnTime = 0.7f;

	class TextureResource* GameBackGroundTexture = nullptr;
};

