#include "pch.h"
#include "Explostion.h"
#include"TextureResource.h"
#include "ResourceManager.h"

void Explostion::Init()
{
	_texture = ResourceManager::GetInstance()->GetTexture("Explosion");

	_RenderTimeLimit = _vertic * _horizen;
}

void Explostion::Update(float deltatime)
{
	_StackTimer += deltatime * _renderingspeed;

	_renderingIndex = (int)_StackTimer;

}

void Explostion::Render(HDC hdc)
{
	//���� �̹����� 2�ȼ� ���� ���� �ֱ淡 �߶󺼷��� �ߴ��ϸ�, 3 4 5 �̹����� �ʹ� �̻�����
	_texture->DividRender(hdc, _pos, _vertic, _horizen, _renderingIndex);

}
