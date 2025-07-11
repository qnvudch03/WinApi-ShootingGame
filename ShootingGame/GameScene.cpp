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
	// 플레이어 생성
	_player = new Player();
	_player->Init();

	// 적 생성
	/*_enemy = new Enemy();
	_enemy->Init();*/

	GameBackGroundTexture = ResourceManager::GetInstance()->GetTexture("BackGround");
}

void GameScene::Destroy()
{
	SAFE_DELETE(_player);
	//SAFE_DELETE(_enemy);

	// 화면안에 남아있는 미사일도 정리
	for (auto iter : _missileVector)
	{
		//delete iter;
		SAFE_DELETE(iter);
		//iter == nullptr;
	}
	_missileVector.clear();

	//적 삭제
	for (auto iter : _enemyVec)
	{
		SAFE_DELETE(iter);
	}
	_enemyVec.clear();

	//폭발 포인터 삭제
	for (auto iter : ExplostionList)
	{
		SAFE_DELETE(iter);
	}
	ExplostionList.clear();

	//리소스 매니저 삭제
	ResourceManager::GetInstance()->Destroy();
}

void GameScene::Update(float deltatTime)
{
	_deltatime = deltatTime;
	Enemy_spawnTime -= deltatTime;

	//배열 방식
	{
	/*ColliderArray[0][0] = new Collider(Vector(0, 0));

	memset(ColliderArray, 0, sizeof(ColliderArray));*/
	}
	
	//벡터방식
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

			//적 미사일과 플레이어의 미사일을 분리
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


	//사망처리
	if (_player->GetHP() <= 0 && _player->IsAlive())
	{
		_player->SetAlive(false);
		_player->DeleteCollider();

		ExplostionList.push_back(new Explostion(_player->GetPos()));
	}

}

void GameScene::Render(HDC hdc)
{
	//총알의 불렛을 그리기
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

		//단순히 위로 날라가게 설정
		NewMissile->Setdirection(Vector(0, -1));
		_missileVector.push_back(NewMissile);
	}

	else if (MissileType == EMissileType::Missile_Enemy)
	{
		Missile* NewMissile = new Missile(Plyaerpos, _deltatime, MissileType, EnemyType);

		//단순히 위로 날라가게 설정
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
		//거리가 50픽셀 이상이면 계산대상에서 제외
		if (abs(Playercollider->GetPos().x - (*Iter)->GetPos().x) > 50 || abs(Playercollider->GetPos().y - (*Iter)->GetPos().y) > 50)
		{
			Iter = EnemyMissileColliderVec.erase(Iter);
			continue;
		}

		else
		{
			//충돌이 되었다면
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

	//폐기버젼
	{
		//while(Enemy != _enemyVec.end())
	//{
 //		bool erased = false;

	//	Vector EnemyColliderPos = (*Enemy)->GetCollider()->GetPos();
	//	for (auto MissileCollider : PlayerMissileColliderVec)
	//	{
	//		bool bIsEnemyErased = false;

	//		//근접해 있다면
	//		if (abs(EnemyColliderPos.x - MissileCollider->GetPos().x) < 50 || abs(EnemyColliderPos.y - MissileCollider->GetPos().y) < 50)
	//		{
	//			//심지어 맞았어q
 //				if ((*Enemy)->GetCollider()->CheckCollision(MissileCollider))
	//			{
	//				//플레이어의 미사일 제거
	//				auto Tempiter = find(_missileVector.begin(), _missileVector.end(), MissileCollider->GetOwner());
	//				_missileVector.erase(Tempiter);

	//				//적 체력 낮추기
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
			//멀리있는 미사일은 검사 제외
			if (abs((*Enemy)->GetCollider()->GetPos().x - MissileCollider->GetPos().x) < 50 || abs(abs((*Enemy)->GetCollider()->GetPos().y - MissileCollider->GetPos().y) < 50))
			{
				if ((*Enemy)->GetCollider()->CheckCollision(MissileCollider))
				{
					auto Tempiter = find(_missileVector.begin(), _missileVector.end(), MissileCollider->GetOwner());
					if (Tempiter != _missileVector.end())
					{
						delete *Tempiter;
						_missileVector.erase(Tempiter); // 미사일 제거
					}
						

						(*Enemy)->_monsterInfo.HP -= 1;

						if ((*Enemy)->_monsterInfo.HP <= 0)
						{
							//폭발 소환
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
//	// 벡터를 돌면서 missile과 동일한 객체를 찾아야 한다.
//	//for ();
//	auto it = std::find(_missile.begin(), _missile.end(), missile);
//	_missile.erase(it);
//
//	// 객체도 소멸한다.
//	// 객체의 생성과 소멸은 모두 Game이라는 매니저가 총괄
//	// 이 코드는 괜찮을까요? 위험한 코드를 만들어야 하네.... 나중에 한번 고민해보자.TODO
//	delete missile;
//}

