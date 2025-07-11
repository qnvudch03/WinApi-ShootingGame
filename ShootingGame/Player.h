#pragma once
#include "Collider.h"
class Player
{
public:

	~Player()
	{
		delete _collider;
	}

	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);

	void DeleteCollider();

	Vector GetForwardVector();	// ��� ���������� ���溤�͸� Forward Vector
	Vector GetPos() { return _pos; }

	void SetHP(int HP) { _HP = HP; }
	int GetHP() { return _HP; }

	void SetAlive(bool alive) {bIsAlive = alive;}
	bool IsAlive() { return bIsAlive; }

	class Collider<Player>* GetCollider() { return _collider; }

private:
	class TextureResource* _texture = nullptr;
	class TextureResource* _HPtexture = nullptr;

	Collider<Player>* _collider = nullptr;

	Vector _pos;
	float _speed = 300.0f;	// 1�ʴ� �̵��ϴ� �ӵ�
	int _HP = 5;

	bool bIsAlive = true;

};

