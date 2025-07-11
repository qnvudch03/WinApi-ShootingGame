#include "pch.h"
#include "TextureResource.h"
#include "Game.h"

void TextureResource::Load(wstring fileName, EObjectType type)
{
	// WinAPI 텍스처 로딩하는 방법
	{
		fs::path fullPath = fs::current_path().parent_path() / L"Resources" / fileName;

		HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

		_textureHdc = ::CreateCompatibleDC(hdc);
		_bitmap = (HBITMAP)::LoadImageW(
			nullptr,
			fullPath.c_str(),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION
		);
		if (_bitmap == 0)
		{
			::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
			return;
		}

		if (type == EObjectType::Type_Player)
			_transparent = RGB(252, 0, 255);

		else if (type == EObjectType::Type_Enemy)
			_transparent = RGB(255, 0, 255);

		else if (type == EObjectType::Type_Explosion)
			_transparent = RGB(0, 0, 0);


		HBITMAP prev = (HBITMAP)::SelectObject(_textureHdc, _bitmap);
		::DeleteObject(prev);

		BITMAP bit = {};
		::GetObject(_bitmap, sizeof(BITMAP), &bit);

		_sizeX = bit.bmWidth;
		_sizeY = bit.bmHeight;
	}
}

void TextureResource::Render(HDC hdc, Vector pos)
{
	if (_transparent == -1)
	{
		::BitBlt(hdc,	// 백버퍼에
			(int32)pos.x - (_sizeX / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)pos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,	// 텍스쳐 그리기
			0,
			0,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)pos.x - (_sizeX / 2),
			(int32)pos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,
			0,
			0,
			_sizeX,
			_sizeY,
			_transparent);	// 어떤색상을 투명하게 그릴까
	}

}

void TextureResource::DividRender(HDC hdc, Vector pos, int vertic, int horizen, int index, int offset)
{
	int32 diviedXsize = _sizeX / vertic;
	int32 diviedYsize = _sizeY / horizen;
	int Line = 0;

	

	while (index > vertic)
	{
		index -= vertic;
		Line++;
	}

	int offsetX = (index == 0) ? 0 : offset;
	int offsetY = (Line == 0) ? 0 : offset;

	if (_transparent == -1)
	{
		::BitBlt(hdc,	// 백버퍼에
			(int32)pos.x - (_sizeX / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)pos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,	// 텍스쳐 그리기
			0,
			0,
			SRCCOPY);
	}
	else
	{
		//위치 / 크기 / 도화지 / 시작위치 / 가져올 크기
		::TransparentBlt(hdc,
			(int32)pos.x - (diviedXsize / 2),
			(int32)pos.y - (diviedYsize / 2),
			diviedXsize - offset,
			diviedYsize -offset,
			_textureHdc,
			index * (diviedXsize) + offsetX,
			Line * (_sizeY - diviedYsize) + offsetY,
			diviedXsize -offset,
			diviedYsize -offset,
			_transparent);	// 어떤색상을 투명하게 그릴까
	}
}

void TextureResource::RnderBackGround(HDC hdc, Vector pos, int Moveoffset)
{

	int BoundY = (int32)pos.y - (_sizeY / 2) + Moveoffset;

	////아래부분
	//::BitBlt(hdc,	// 백버퍼에
	//	(int32)pos.x - (_sizeX / 2),
	//	BoundY,
	//	_sizeX,
	//	_sizeY - Moveoffset,
	//	_textureHdc,	// 텍스쳐 그리기
	//	0,
	//	0,
	//	SRCCOPY);

	////윗부분
	//::BitBlt(hdc,	// 백버퍼에
	//	(int32)pos.x - (_sizeX / 2),
	//	0,
	//	_sizeX,
	//	BoundY,
	//	_textureHdc,	// 텍스쳐 그리기
	//	0,
	//	0,
	//	SRCCOPY);

	//아랫부분
	::TransparentBlt(hdc,
		(int32)pos.x - (_sizeX / 2),
		BoundY,
		_sizeX,
		_sizeY - Moveoffset,
		_textureHdc,
		0,
		0,
		_sizeX,
		_sizeY - Moveoffset,
		_transparent);

	//윗부분
	::TransparentBlt(hdc,
		(int32)pos.x - (_sizeX / 2),
		0,
		_sizeX,
		Moveoffset,
		_textureHdc,
		0,
		_sizeY - Moveoffset,
		_sizeX,
		Moveoffset,
		_transparent);

}
