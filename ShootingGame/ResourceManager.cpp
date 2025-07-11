#include "pch.h"
#include "ResourceManager.h"
//#include "LineMesh.h"
#include "TextureResource.h"

void ResourceManager::Init()
{
    //// ��~�� ���θ޽ø� �� �ε��ؼ� ������ ����.
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

    //HP ��Ʈ
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
    // ��ü������ �����ϰ� �ִ� ��� ���θ޽��߿� meshName �ش��ϴ� ���ҽ��� ��ȯ�Ѵ�.
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // �ε��� �ȵưų�, �̸��� �߸��ưų�
    return nullptr;
}
