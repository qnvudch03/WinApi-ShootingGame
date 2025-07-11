#pragma once
class Explostion
{
public:
	Explostion(Vector pos, float speed = 10)
	{
		_pos = pos;
		_renderingspeed = speed;

		Init();
	}

	void Update(float deltatime);
	void Render(HDC hdc);
	void Init();
	
	float GetTimer() { return _StackTimer; }
	float GetTimeLimit() { return _RenderTimeLimit; }

	//void SetRenderingSpeed(float speed) { _speed = speed; }

private:
	Vector _pos;

	class TextureResource* _texture = nullptr;
	int _renderingIndex = 0;
	int _vertic = 6;
	int _horizen = 2;

	float _renderingspeed = 10;
	float _StackTimer = 0;
	float _RenderTimeLimit;
};

