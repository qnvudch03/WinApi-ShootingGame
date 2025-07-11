#include "pch.h"
#include "Enemy.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include <random>

Enemy::Enemy(EMonsterType SpawnedMonster, Vector spawnposition)
{
	_monsterType = SpawnedMonster;

	string EnemyName = "";

	switch (SpawnedMonster)
	{
	case EMonsterType::BigBlue:
		EnemyName = "BigBlue";

		_monsterInfo.HP = 3;
		_monsterInfo.Speed = 200.0f;
		_monsterInfo.texture = ResourceManager::GetInstance()->GetTexture(EnemyName);
		_attackTime = 1.2;
		break;
	case EMonsterType::BlgGreen:
		EnemyName = "BlgGreen";

		_monsterInfo.HP = 2;
		_monsterInfo.Speed = 200.0f;
		_monsterInfo.texture = ResourceManager::GetInstance()->GetTexture(EnemyName);
		_attackTime = 1;
		break;
	case EMonsterType::Red:
		EnemyName = "Red";

		_monsterInfo.HP = 1;
		_monsterInfo.Speed = 350.0f;
		_monsterInfo.texture = ResourceManager::GetInstance()->GetTexture(EnemyName);
		_attackTime = 0.7;
		break;
	case EMonsterType::Blud:
		EnemyName = "Blud";

		_monsterInfo.HP = 1;
		_monsterInfo.Speed = 400.0f;
		_monsterInfo.texture = ResourceManager::GetInstance()->GetTexture(EnemyName);
		_attackTime = 0.5;
		break;
	case EMonsterType::Moster_Max:
		_monsterInfo.HP = 0;
		_monsterInfo.Speed = 0.0f;
		_monsterInfo.texture = ResourceManager::GetInstance()->GetTexture("BigBlue");
		break;
	default:
		break;
	}

	//Vector TextureSize = ResourceManager::GetInstance()->GetTexture(EnemyName)->GetTextureSize();
	_collider = new Collider<Enemy>(_monsterInfo.texture->GetTextureSize());
	_collider->SetOwner(this);

	_attackTimer = _attackTime;
	_monsterInfo.pos = spawnposition;
}

void Enemy::Update(float deltatime)
{
	_attackTimer -= deltatime;
	_directionTimer -= deltatime;

	if (_directionTimer <= 0)
	{
		_directionTimer = 3.0f;
		srand(time(0));

		_direction = (rand() & 1) ? 1 : -1;
	}

	if (_monsterInfo.pos.x >= GWinSizeX)
		_direction = -1;

	if (_monsterInfo.pos.x <= 0)
		_direction = 1;

	if (_attackTimer <= 0)
	{
		_attackTimer = _attackTime;

		GameScene::GetGameScene()->CallMakeMissile(_monsterInfo.pos, EMissileType::Missile_Enemy, (int)_monsterType);
	}

	_monsterInfo.pos.y += deltatime * 30;
	_monsterInfo.pos.x += _direction * deltatime * _monsterInfo.Speed;

	_collider->SetPos(_monsterInfo.pos);

}

void Enemy::Render(HDC hdc)
{
	_monsterInfo.texture->Render(hdc, _monsterInfo.pos);
	//_collider->Render(hdc);
}
