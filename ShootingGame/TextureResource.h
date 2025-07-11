#pragma once


class TextureResource
{
public:
	void Load(wstring fileName, EObjectType type);

	// 해당 리소스가 그려지는 부분
	void Render(HDC hdc, Vector pos);

	void DividRender(HDC hdc, Vector pos, int vertic, int horizen, int index, int offset = 0);
	void RnderBackGround(HDC hdc, Vector pos, int Moveoffset);

	int32 GetTextureSize_X() { return _sizeX; }
	int32 GetTextureSize_Y() { return _sizeY; }

	Vector GetTextureSize() { return Vector(_sizeX, _sizeY); }

private:
	// 텍스처를 그리기위한 변수
	HDC		_textureHdc = 0;
	HBITMAP _bitmap;
	int32 _transparent = -1;	// 투명하게 보여야하는 색상
	int32 _sizeX = 0;
	int32 _sizeY = 0;
};

