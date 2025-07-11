#pragma once
class Scence
{
public:

	virtual ~Scence() {}

	virtual void Init() {}
	virtual void Destroy() {};
	virtual void Update(float deltatTime) {}
	virtual void Render(HDC hdc) {}
};

