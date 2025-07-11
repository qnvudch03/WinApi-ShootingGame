#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Missile.h"
#include "Enemy.h"
#include "Game.h"
#include "Collider.h"
#include "Explostion.h"

#include <algorithm>

void GameScene::Init()
{
	// �÷��̾� ����
	_player = new Player();
	_player->Init();

	// �� ����
	/*_enemy = new Enemy();
	_enemy->Init();*/

	GameBackGroundTexture = ResourceManager::GetInstance()->GetTexture("BackGround");
}

void GameScene::Destroy()
{
	SAFE_DELETE(_player);
	//SAFE_DELETE(_enemy);

	// ȭ��ȿ� �����ִ� �̻��ϵ� ����
	for (auto iter : _missileVector)
	{
		//delete iter;
		SAFE_DELETE(iter);
		//iter == nullptr;
	}
	_missileVector.clear();

	//�� ����
	for (auto iter : _enemyVec)
	{
		SAFE_DELETE(iter);
	}
	_enemyVec.clear();

	//���� ������ ����
	for (auto iter : ExplostionList)
	{
		SAFE_DELETE(iter);
	}
	ExplostionList.clear();

	//���ҽ� �Ŵ��� ����
	ResourceManager::GetInstance()->Destroy();
}

void GameScene::Update(float deltatTime)
{
	_deltatime = deltatTime;
	Enemy_spawnTime -= deltatTime;

	//�迭 ���
	{
	/*ColliderArray[0][0] = new Collider(Vector(0, 0));

	memset(ColliderArray, 0, sizeof(ColliderArray));*/
	}
	
	//���͹��
	EnemyMissileColliderVec.clear();
	PlayerMissileColliderVec.clear();

	if (_player)
	{
		_player->Update(deltatTime);
	}

	if (Enemy_spawnTime <= 0.0)
	{
		Enemy_spawnTime = 0.7;

		random_device rd;
		int randomEnmyIndex = (rd() % 4);

		Vector Spawnposition = Vector(rd() & GWinSizeX, 100);

		Enemy* newEnemy = new Enemy((EMonsterType)randomEnmyIndex, Spawnposition);
		_enemyVec.push_back(newEnemy);
	}

	if (!_missileVector.empty())
	{
		auto Iter = _missileVector.begin();
		while (Iter != _missileVector.end())
		{
			(*Iter)->Update();

			if ((*Iter)->GetMissilePosition().y < 0 || (*Iter)->GetMissilePosition().y > GWinSizeY)
			{
				/*delete *Iter;
				*Iter = nullptr;*/

				SAFE_DELETE(*Iter);
  				Iter = _missileVector.erase(Iter);
				continue;
			}

			//�� �̻��ϰ� �÷��̾��� �̻����� �и�
			if ((*Iter)->GetType() == EMissileType::Missile_Enemy)
			{
				EnemyMissileColliderVec.push_back((*Iter)->GetCollider());
			}

			else if ((*Iter)->GetType() == EMissileType::Missile_Player)
			{
				PlayerMissileColliderVec.push_back((*Iter)->GetCollider());
			}

			Iter++;
		}
	}


	if (!_enemyVec.empty())
	{
		auto Iter = _enemyVec.begin();
		while (Iter != _enemyVec.end())
		{
			(*Iter)->Update(_deltatime);

			if ((*Iter)->_monsterInfo.pos.y > GWinSizeY + 50)
			{
				SAFE_DELETE(*Iter);
				Iter = _enemyVec.erase(Iter);
				continue;
			}
			Iter++;
		}
	}

	if (!ExplostionList.empty())
	{
		auto Iter = ExplostionList.begin();
		while (Iter != ExplostionList.end())
		{
			(*Iter)->Update(_deltatime);

			if ((*Iter)->GetTimer() >= (*Iter)->GetTimeLimit())
			{
				SAFE_DELETE(*Iter);
				Iter = ExplostionList.erase(Iter);
				continue;
			}
			Iter++;
		}
	}


	if (!PlayerMissileColliderVec.empty())
		CheckEnemyColiision();

	if (!EnemyMissileColliderVec.empty())
		CheckPlayerCollision();


	//���ó��
	if (_player->GetHP() <= 0 && _player->IsAlive())
	{
		_player->SetAlive(false);
		_player->DeleteCollider();

		ExplostionList.push_back(new Explostion(_player->GetPos()));
	}

}

void GameScene::Render(HDC hdc)
{
	//�Ѿ��� �ҷ��� �׸���
	//GameBackGroundTexture->Render(hdc, Vector(200, 400));

	_BackGroundMoveOffset += _deltatime * _BackGroundMoveSpeed;

	if (_BackGroundMoveOffset >= GWinSizeY)
		_BackGroundMoveOffset = 0;

	GameBackGroundTexture->RnderBackGround(hdc, Vector(200, 400), _BackGroundMoveOffset);

	if (_player && _player->IsAlive())
	{
		_player->Render(hdc);
	}

	if (!_missileVector.empty())
	{
		for (auto& CurrentMissile : _missileVector)
		{
			CurrentMissile->Render(hdc);
		}
	}

	if (!_enemyVec.empty())
	{
		for (auto& CurrentEnemy : _enemyVec)
		{
			CurrentEnemy->Render(hdc);
		}
	}

	if (!ExplostionList.empty())
	{
		for (auto& Bomb : ExplostionList)
		{
			Bomb->Render(hdc);
		}
	}


	wstring scorestr = to_wstring(_GameScore);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, GWinSizeX - 50, 30, scorestr.c_str(), scorestr.length());
	
}

GameScene* GameScene::GetGameScene()
{
	return dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrentScence());
}

void GameScene::CallMakeMissile(Vector Plyaerpos, EMissileType MissileType, int EnemyType)
{
	if (MissileType == EMissileType::Missile_Player)
	{

		Missile* NewMissile = new Missile(Plyaerpos, _deltatime, MissileType);

		//�ܼ��� ���� ���󰡰� ����
		NewMissile->Setdirection(Vector(0, -1));
		_missileVector.push_back(NewMissile);
	}

	else if (MissileType == EMissileType::Missile_Enemy)
	{
		Missile* NewMissile = new Missile(Plyaerpos, _deltatime, MissileType, EnemyType);

		//�ܼ��� ���� ���󰡰� ����
		NewMissile->Setdirection(Vector(0, 1));
		_missileVector.push_back(NewMissile);
	}
	
  	
}

void GameScene::CheckPlayerCollision()
{
	Collider<Player>* Playercollider = _player->GetCollider();

	if (Playercollider == nullptr)
		return;

	auto Iter = EnemyMissileColliderVec.begin();

	while (Iter != EnemyMissileColliderVec.end())
	{
		//�Ÿ��� 50�ȼ� �̻��̸� ����󿡼� ����
		if (abs(Playercollider->GetPos().x - (*Iter)->GetPos().x) > 50 || abs(Playercollider->GetPos().y - (*Iter)->GetPos().y) > 50)
		{
			Iter = EnemyMissileColliderVec.erase(Iter);
			continue;
		}

		else
		{
			//�浹�� �Ǿ��ٸ�
			if (Playercollider->CheckCollision((*Iter)))
			{
				auto CollidedMissile = find(_missileVector.begin(), _missileVector.end(), (*Iter)->GetOwner());
				Iter = EnemyMissileColliderVec.erase(Iter);

				SAFE_DELETE(*CollidedMissile);
				_missileVector.erase(CollidedMissile);

				int currentHP = _player->GetHP();
				currentHP--;

				_player->SetHP(currentHP);

				continue;
			}
		}

		Iter++;
	}
}

void GameScene::CheckEnemyColiision()
{
	if (PlayerMissileColliderVec.empty())
		return;


	auto Enemy = _enemyVec.begin();

	//������
	{
		//while(Enemy != _enemyVec.end())
	//{
 //		bool erased = false;

	//	Vector EnemyColliderPos = (*Enemy)->GetCollider()->GetPos();
	//	for (auto MissileCollider : PlayerMissileColliderVec)
	//	{
	//		bool bIsEnemyErased = false;

	//		//������ �ִٸ�
	//		if (abs(EnemyColliderPos.x - MissileCollider->GetPos().x) < 50 || abs(EnemyColliderPos.y - MissileCollider->GetPos().y) < 50)
	//		{
	//			//������ �¾Ҿ�q
 //				if ((*Enemy)->GetCollider()->CheckCollision(MissileCollider))
	//			{
	//				//�÷��̾��� �̻��� ����
	//				auto Tempiter = find(_missileVector.begin(), _missileVector.end(), MissileCollider->GetOwner());
	//				_missileVector.erase(Tempiter);

	//				//�� ü�� ���߱�
	//				(*Enemy)->_monsterInfo.HP -= 1;

	//				if ((*Enemy)->_monsterInfo.HP <= 0)
	//				{
	//					bIsEnemyErased = true;

	//				}
	//			}
	//		}

	//		erased = bIsEnemyErased;
	//	}

	//	if (erased)
	//	{
	//		Enemy = _enemyVec.erase(Enemy);
	//	}

	//	else
	//	{
	//		Enemy++;
	//	}

	//}
	}
	
	while (Enemy != _enemyVec.end())
	{
		bool erased = false;

		for (auto MissileCollider : PlayerMissileColliderVec)
		{
			//�ָ��ִ� �̻����� �˻� ����
			if (abs((*Enemy)->GetCollider()->GetPos().x - MissileCollider->GetPos().x) < 50 || abs(abs((*Enemy)->GetCollider()->GetPos().y - MissileCollider->GetPos().y) < 50))
			{
				if ((*Enemy)->GetCollider()->CheckCollision(MissileCollider))
				{
					auto Tempiter = find(_missileVector.begin(), _missileVector.end(), MissileCollider->GetOwner());
					if (Tempiter != _missileVector.end())
					{
						delete *Tempiter;
						_missileVector.erase(Tempiter); // �̻��� ����
					}
						

						(*Enemy)->_monsterInfo.HP -= 1;

						if ((*Enemy)->_monsterInfo.HP <= 0)
						{
							//���� ��ȯ
							ExplostionList.push_back(new Explostion((*Enemy)->_monsterInfo.pos, 30));

							delete *Enemy;
							Enemy = _enemyVec.erase(Enemy);
							erased = true;

							_GameScore += 100;

							break;
						}
				}
			}
			
		}

		if (!erased)
			++Enemy;
	}

}


//GameScene* GameScene::GetGameScene()
//{
//	return dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrScene());
//}

//void GameScene::CreateMissile(float posX, float posY, float angle, bool chase)
//{
//	Missile* missile = new Missile();
//	missile->Init(posX, posY, angle, chase);
//	_missile.push_back(missile);
//}
//
//void GameScene::RemoveMissile(Missile* missile)
//{
//	// ���͸� ���鼭 missile�� ������ ��ü�� ã�ƾ� �Ѵ�.
//	//for ();
//	auto it = std::find(_missile.begin(), _missile.end(), missile);
//	_missile.erase(it);
//
//	// ��ü�� �Ҹ��Ѵ�.
//	// ��ü�� ������ �Ҹ��� ��� Game�̶�� �Ŵ����� �Ѱ�
//	// �� �ڵ�� ���������? ������ �ڵ带 ������ �ϳ�.... ���߿� �ѹ� ����غ���.TODO
//	delete missile;
//}

