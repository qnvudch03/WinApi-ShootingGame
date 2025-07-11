#pragma once

//  �츮�� �����ϴ� ���� �����.
constexpr int GWinSizeX = 400;
constexpr int GWinSizeY = 800;

// ������ ������ ����ϴ� ��� & �𸮾� �̷��� ���ϴ�.
using int8 = char;					// ���� �����ϴµ� 1bit ¥��
using int16 = short;
using int32 = int;
using int64 = long long;		// �Ź� long long ���� �����Ƽ� int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

float RadianToDegree(float radian);
float DegreeToRadian(float degree);

// �𸮾󿡼� ������.
#define SMALL_NUMBER			(1.e-8f)


enum EObjectType
{
	Type_Player,
	Type_Enemy,
	Type_Explosion,
	Type_Robby,
	Type_Max
};

enum EMissileType
{
	Missile_Player,
	Missile_Enemy,
	Missile_Max
};

enum EMonsterType
{
	BigBlue,
	BlgGreen,
	Red,
	Blud,
	Moster_Max
};


// vector ���� ((����+ũ��)�� ��Ÿ���� ����)
struct Vector
{
	// ��ǥ
	float x = 0;
	float y = 0;

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x(pt.x), y(pt.y) {}

	//Vector p1;
	//Vector p2;
	//Vector p3 = Vector(p1.x + p2.x, p1.y + p2.y);
	//Vector p3 = p1 + p2;
	//p1 += p2;	// �̷� ������ �Ҽ� ��������
	//
	//int a = 10;
	//a += 1;

	// ��Ģ���� ����
	// +, - , *, / 
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	Vector operator*(float ratio)
	{
		Vector ret;
		ret.x = x * ratio;
		ret.y = y * ratio;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	// ���͸� ������������ ������ �ʴ�...
	// ������ �ȸ��� ������ ���Ǿ�����.


	// ������ ���� ���ϱ�
	// ���� ���캸��, Legnth, LengthSquared (���ʹ� ���� ���̸� �����ϴ� �Լ��� 2����)
	// sqrt(��Ʈ) ������ �������� ��α� ������, �� ��¥ ���̰� �ʿ��� ��찡 �ƴϸ�,
	// LengthSquared (���� ����) ������ ����ϴ°� �� ����.
	float Length()
	{
		return ::sqrt(x * x + y * y);
	}

	// ������ ���� ����
	float LengthSquared()
	{
		return (x * x + y * y);
	}

	// �̰͵� ���Ӹ���ٰ�. �پ��� ������ �ʿ��ϸ� ���⿡ ������ �ϸ� �ǿ�.
	void Normalize()
	{
		// ������ ��ֶ����� �ϴ� ������ ���������.
		// ������ ��ֶ����� ���� �ʰ�, �����ϴ� ������ �߰��� ������� �־��.

		// ������ ũ�⸦ ���ؼ�, ũ�⸸ŭ ������ ���ָ� �ȴ�.
		float length = Length();

		// �𸮾� ������ Ǯ ���¼ҽ�. �𸮾� �����ؼ� �����ص� �����ϴ�.
		//length �� 0�̰ų� ��û ������ �ִ�
		if (length < SMALL_NUMBER)
			return;	// ���� ����ȭ���ϰ� ����

		// ����ȭ.
		x /= length;
		y /= length;
	}

	// ������ Dot 
	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// radian ������ŭ ȸ����Ű��.
	Vector Rotate(float radian)
	{
		float cosA = ::cosf(radian);
		float sinA = ::sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}

	// ������ Cross
	float Cross(const Vector& other)
	{
		//2D ��, ��Į�󰪸� ��ȯ�� �Ѵ�. 
		// ���� ���Ͱ� �ʿ��Ѱ� �ƴϰ�, ��ȣ�� �Ǵ��ϴ� ��Į���� �ʿ��ϴ�.
		return x * other.y - y * other.x;
	}
};
