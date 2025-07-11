#include "pch.h"
#include "Missile.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void Missile::Setdirection(Vector directionVector)
{

	_directionVec = directionVector;
}

Missile::Missile(Vector spawnPosition, float deltatime, EMissileType missiletype, int EnemyType)
{
	_textureIndex = EnemyType;
	_MissilePosition = spawnPosition;
	_deltatime = deltatime;

	_MissileType = missiletype;

	switch (missiletype)
	{
	case EMissileType::Missile_Player:
		_MissileTexture = ResourceManager::GetInstance()->GetTexture("PlayerBullet");
		break;
		
	case EMissileType::Missile_Enemy:
		_MissileTexture = ResourceManager::GetInstance()->GetTexture("EnemyBullet");
		break;
	case EMissileType::Missile_Max:
		break;
	default:
		break;
	}

	_collider = new Collider<Missile>(_MissileTexture->GetTextureSize().x / _textureVertic, _MissileTexture->GetTextureSize().y);
	_collider->SetOwner(this);

}

void Missile::Render(HDC hdc)
{
	if(_MissileType == EMissileType::Missile_Player)
		_MissileTexture->Render(hdc, _MissilePosition);

	else if(_MissileType == EMissileType::Missile_Enemy)
		_MissileTexture->DividRender(hdc, _MissilePosition, _textureVertic, _textureHorizen, _textureIndex);

	//_collider->Render(hdc);
	//_MissileTexture->DividRender(hdc, _MissilePosition, 5, 1, 4);
}

void Missile::Update()
{
	//타겟이 지정되어 있는 유도기능
	/*if (_Target != nullptr)
	{
		Vector TargetPos = _Target->GetPos();

		Vector Newdirection = Vector(TargetPos.x - _MissilePosition.x, TargetPos.y - _MissilePosition.y);
		_directionVec = Newdirection;
	}*/

	_directionVec.Normalize();
	_MissilePosition.x += _deltatime * _directionVec.x * _MissileSpeed;
	_MissilePosition.y += _deltatime * _directionVec.y * _MissileSpeed;

	_collider->SetPos(_MissilePosition);
}