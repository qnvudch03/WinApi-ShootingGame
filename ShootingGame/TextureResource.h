#pragma once


class TextureResource
{
public:
	void Load(wstring fileName, EObjectType type);

	// �ش� ���ҽ��� �׷����� �κ�
	void Render(HDC hdc, Vector pos);

	void DividRender(HDC hdc, Vector pos, int vertic, int horizen, int index, int offset = 0);
	void RnderBackGround(HDC hdc, Vector pos, int Moveoffset);

	int32 GetTextureSize_X() { return _sizeX; }
	int32 GetTextureSize_Y() { return _sizeY; }

	Vector GetTextureSize() { return Vector(_sizeX, _sizeY); }

private:
	// �ؽ�ó�� �׸������� ����
	HDC		_textureHdc = 0;
	HBITMAP _bitmap;
	int32 _transparent = -1;	// �����ϰ� �������ϴ� ����
	int32 _sizeX = 0;
	int32 _sizeY = 0;
};

