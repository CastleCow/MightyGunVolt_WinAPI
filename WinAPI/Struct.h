#pragma once

//========================================
//##				����					##
//========================================

struct Vector
{
	float x;
	float y;

	Vector()
	{
		x = 0;
		y = 0;
	}

	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}

	Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector operator-(const Vector& other)
	{
		return Vector(x - other.x, y - other.y);
	}

	Vector& operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template <typename T>
	Vector operator*(T num)
	{
		return Vector(x * num, y * num);
	}

	template <typename T>
	Vector& operator*=(T num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	template <typename T>
	Vector operator/(T num)
	{
		assert(0 != num);
		return Vector(x / num, y / num);
	}

	template <typename T>
	Vector& operator/=(T num)
	{
		assert(0 != num);
		x /= num;
		y /= num;
		return *this;
	}

	float Magnitude()
	{
		return sqrtf(x * x + y * y);
	}

	// �Ÿ�����(��Ÿ���)�� ��Ʈ������ ������ ���� �ð��� �䱸�ϱ� ������
	// �Ÿ��� ���̸� ���ϰ� ���� ��� ��Ʈ������ ���� ���� ������ �������� ��
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return Magnitude();
	}

	// ����ȭ(ǥ��ȭ) : ���̰� 1�� ����(��������)�� ��ȯ
	// ���⼺���Ϳ� ���� ���̰� 1�� ���Ͱ� �ʿ��� ��� ��ȯ
	void Normalize()
	{
		if (SqrMagnitude() == 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			float length = Length();
			x = x / length;
			y = y / length;
		}
	}

	// �������͸� ��ȯ
	Vector Normalized()
	{
		if (SqrMagnitude() == 0)
		{
			return Vector(0, 0);
		}
		else
		{
			float length = Length();
			return Vector(x / length, y / length);
		}
	}
};

//========================================
//##				����					##
//========================================

struct Color
{
	Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 1;
	}

	Color(BYTE r, BYTE g, BYTE b, FLOAT a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	BYTE r, g, b;
	FLOAT a;
};