#include "pch.h"
#include "ResourceManager.h"
//#include "LineMesh.h"
#include "TextureResource.h"

void ResourceManager::Init()
{
    //// 모~든 라인메시를 다 로드해서 가지고 있자.
    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"Player.txt");
    //    //mesh->Load("Missile.txt");
    //    //mesh->Load("Enemy.txt");

    //    _lineMeshes["Player"] = mesh;
    //}

    //Robby
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Roby.bmp", EObjectType::Type_Robby);
        _textures["Roby"] = texture;
    }


    //Player
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Player.bmp", EObjectType::Type_Player);
        _textures["Player"] = texture;
    }

    //HP 하트
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"PlayerHP.bmp", EObjectType::Type_Player);
        _textures["PlayerHP"] = texture;
    }

    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"BG.bmp", EObjectType::Type_Enemy);
        _textures["BackGround"] = texture;
    }


    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"PlayerBullet.bmp", EObjectType::Type_Enemy);
        _textures["PlayerBullet"] = texture;
    }

    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"EnemyBullet.bmp", EObjectType::Type_Enemy);
        _textures["EnemyBullet"] = texture;
    }

    //Mister Textrue
    {
        {
            TextureResource* texture = new TextureResource();
            texture->Load(L"Enemy1.bmp", EObjectType::Type_Enemy);
            _textures["BigBlue"] = texture;
        }

        {
            TextureResource* texture = new TextureResource();
            texture->Load(L"Enemy2.bmp", EObjectType::Type_Enemy);
            _textures["BlgGreen"] = texture;
        }

        {
            TextureResource* texture = new TextureResource();
            texture->Load(L"Enemy3.bmp", EObjectType::Type_Enemy);
            _textures["Red"] = texture;
        }

        {
            TextureResource* texture = new TextureResource();
            texture->Load(L"Enemy4.bmp", EObjectType::Type_Enemy);
            _textures["Blud"] = texture;
        }
    }


    //Explostion
    {
        {
            TextureResource* texture = new TextureResource();
            texture->Load(L"Explosion.bmp", EObjectType::Type_Explosion);
            _textures["Explosion"] = texture;
        }
    }
    
}

void ResourceManager::Destroy()
{
    for (auto iter : _textures)
    {
        delete iter.second;
    }
    _textures.clear();
}

TextureResource* ResourceManager::GetTexture(string meshName)
{
    // 전체적으로 관리하고 있는 모든 라인메시중에 meshName 해당하는 리소스를 반환한다.
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // 로딩이 안됐거나, 이름이 잘못됐거나
    return nullptr;
}
