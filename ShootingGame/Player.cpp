#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "GameScene.h"
//#include "Game.h"

void Player::Init()
{
	_texture = ResourceManager::GetInstance()->GetTexture("Player");
	_HPtexture = ResourceManager::GetInstance()->GetTexture("PlayerHP");

	//_collider = new Collider(_texture->GetTextureSize_X(), _texture->GetTextureSize_Y());
	_collider = new Collider<Player>(_texture->GetTextureSize());
	_collider->SetOwner(this);

	_pos = Vector(GWinSizeX/2, GWinSizeY/2);
}

void Player::Update(float deltaTime)
{
	if (!bIsAlive)
		return;


	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W))
	{
		// 이동 거리 = 시간 * 속도
		// 1초당 10만큼 이동한다.
		_pos.y -= (deltaTime * _speed);	// 모든 PC가 1프레임당 동일한 거리를 이동한다.
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S))
	{
		_pos.y += (deltaTime * _speed);
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A))
	{
		_pos.x -= (deltaTime * _speed);
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D))
	{
		_pos.x += (deltaTime * _speed);
	}

	{
		if (_pos.x > GWinSizeX)
			_pos.x = GWinSizeX;

		if (_pos.x < 0.0f)
			_pos.x = 0;

		if (_pos.y > GWinSizeY)
			_pos.y = GWinSizeY;

		if (_pos.y < 0.0f)
			_pos.y = 0;
	}
	
	if (InputManager::GetInstance()->GetButtonUp(KeyType::SpaceBar))
	{
		GameScene::GetGameScene()->CallMakeMissile(_pos, EMissileType::Missile_Player);
	}

	_collider->SetPos(_pos);

}

void Player::Render(HDC hdc)
{
	_texture->Render(hdc, _pos);

	//자기 HP 그리기
	for (int i = 1; i <= _HP; i++)
	{
		Vector HPPos = Vector(i*35, GWinSizeY - 50);
		_HPtexture->Render(hdc, HPPos);
	}
}

void Player::DeleteCollider()
{
	delete _collider;
	_collider = nullptr;


}
