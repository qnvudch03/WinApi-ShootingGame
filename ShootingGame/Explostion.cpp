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
	//폭발 이미지가 2픽셀 정도 뭐가 있길래 잘라볼려고 했더니만, 3 4 5 이미지가 너무 이상해짐
	_texture->DividRender(hdc, _pos, _vertic, _horizen, _renderingIndex);

}
