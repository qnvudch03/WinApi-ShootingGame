#pragma once
#include "Scence.h"
class RobyScence : public Scence
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;

private:
	class TextureResource* _texture = nullptr;

	bool bIsVisible = true;
	float TextTimer = 0;
	float TextBlinkTime = 1.0f;

	bool waitPressbutton();
};

