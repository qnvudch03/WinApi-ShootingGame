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


	// ������ �������ϋ� �ʿ��� ��ü
private:

	int _GameScore = 0;

	float _deltatime = 0.0;

	int _PlayerMissileLimit = 3;
	int _CurrentPlayerMissile = 0;

	int _BackGroundMoveOffset = 0;
	int _BackGroundMoveSpeed = 200;

	// �����ͷ� ���ϰ�, ��ü �״�� �����ص� �ȴ�.
	class Player* _player = nullptr;

	// vector? ���� ����? ����� �ɰſ���. �̸� ����ϸ� ���� �����.
	// ���߿� ��� ���� �߰��Ǹ鼭, vector�δ� �Ѱ谡 �ֳ�.


	//�浹üũ ��, �����͸� ���� ������Ʈ�� ã�ƾ� �ؼ�, set���� ���� -> �׷� �����Ϳ� ���� ������ �����ε��� �ؾ� ��???(����)   -> algorism�� ����
	vector<class Missile*>	_missileVector;
	//set<class Missile*>	_missileVector;
	vector<class Enemy*> _enemyVec;

	//�ݸ��ƴ� ���� �����, ���� ������ �ִ� �κи� �˻�
	//class Collider* ColliderArray[GWinSizeY][GWinSizeX];

	//�ƽθ� �ݶ��̴� ���͸� �����, ������ �ִ� ��쿡�� ���� ó��
	vector<class Collider<Missile>*> EnemyMissileColliderVec;
	vector<class Collider<Missile>*> PlayerMissileColliderVec;

	//��ȸ�� ���� �ʾ�, �� �� ���ͷ� ����
	//set<class Explostion*> ExplostionList;
	vector<class Explostion*> ExplostionList;

	float Enemy_spawnTime = 0.7f;

	class TextureResource* GameBackGroundTexture = nullptr;
};

