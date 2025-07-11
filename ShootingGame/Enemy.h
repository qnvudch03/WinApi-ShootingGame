#pragma once
#include "Collider.h"
class Enemy
{
public:
	//체력, 속도, 몬스터 번호
	Enemy(EMonsterType SpawnedMonster, Vector spawnposition);

	~Enemy()
	{
		delete _collider;
	}

	struct MonsterInfo
	{
		int HP = 0;
		float Speed = 0.0;
		class TextureResource* texture = nullptr;
		Vector pos = Vector(0, 0);
	};

	EMonsterType _monsterType;
	MonsterInfo _monsterInfo;

	void Update(float deltatime);
	void Render(HDC hdc);

	class Collider<Enemy>* GetCollider() { return _collider; }

private:
	int _direction = 1;

	float _directionTimer = 2.0f;
	float _attackTime = 3;
	float _attackTimer = 0;
	class TextureResource* _texture = nullptr;

	Collider<Enemy>* _collider = nullptr;

};

