#pragma once
#include "singleTon.h"

class TimeManager : public singleTon<TimeManager>
{
public:
	friend singleTon<TimeManager>;

private:
	TimeManager() {}

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency = 0;	// CPU Ŭ��
	uint64 _prevCount = 0;

	// ���������Ӱ� ���� ������ ������ �ð� ����
	float _deltaTime = 0.f;

private:

	// �ʴ� �� ����������
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;
};

