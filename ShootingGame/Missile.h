#pragma once
#include "Collider.h"
class Missile
{
public:
	void Update();
	void Render(HDC hdc);
	void Setdirection(Vector directionVector);
	void SetTarget(class Enemy* Target) { _Target = Target; }
	EMissileType GetType() { return _MissileType; }
	Vector GetMissilePosition() { return _MissilePosition; }

	class Collider<Missile>* GetCollider() { return _collider; }

	Missile(Vector spawnPosition, float deltatime, EMissileType missiletype, int EnemyType = 0);

	~Missile()
	{
		delete _collider;
		delete _Target;
	};

private:
	//pair<float, float> _MissilePosition;
	//pair<float, float> _directionVec;
	Vector _MissilePosition;
	Vector _directionVec;
	EMissileType _MissileType;
	pair<int, int> _windowSize;


	class TextureResource* _MissileTexture = nullptr;
	class Enemy* _Target = nullptr;
	int _textureIndex = 0;
	int _textureVertic = 5;
	int _textureHorizen = 1;

	float _MissileSpeed = 500;
	float _MissileSize = 7;
	float _deltatime = 0.0f;

	Collider<Missile>* _collider = nullptr;
};

