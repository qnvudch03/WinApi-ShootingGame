#pragma once
template<typename T>
class Collider
{
public:

	Collider(int sizeX, int sizeY)
	{
		_sizeX = (float)sizeX * 1.1;
		_sizeY = (float)sizeY * 1.1;
	};

	Collider(Vector size)
	{
		_sizeX = size.x * 1.1;
		_sizeY = size.y * 1.1;
	};

	void Update(float deltatime);
	void Render(HDC hdc);

	Vector GetPos() { return _pos; }
	void SetPos(Vector pos) { _pos = pos; }

	float GetSizeX() { return _sizeX; }
	float GetSizeY() { return _sizeY; }

	template<typename U>
	bool CheckCollision(Collider<U>* Collider)
	{
		float leftA = _pos.x - _sizeX * 0.5f;
		float rightA = _pos.x + _sizeX * 0.5f;
		float topA = _pos.y - _sizeY * 0.5f;
		float bottomA = _pos.y + _sizeY * 0.5f;

		float leftB = Collider->GetPos().x - Collider->GetSizeX() * 0.5f;
		float rightB = Collider->GetPos().x + Collider->GetSizeX() * 0.5f;
		float topB = Collider->GetPos().y - Collider->GetSizeY() * 0.5f;
		float bottomB = Collider->GetPos().y + Collider->GetSizeY() * 0.5f;

		if (rightA < leftB || leftA > rightB) return false;
		if (bottomA < topB || topA > bottomB) return false;

		return true;
	}

	T* GetOwner() { return _owner; }
	void SetOwner(T* owner) { _owner = owner; }

private:
	float _sizeX = 0;
	float _sizeY = 0;

	Vector _pos;

	T* _owner = nullptr;
};

