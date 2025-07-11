#pragma once

template<typename T>
class singleTon
{
public:
	
	static T* GetInstance()
	{
		return &_instance;
	}


protected:
	singleTon() = default;
	virtual ~singleTon() = default;

private:

	singleTon(const singleTon&) = delete;
	singleTon& operator=(const singleTon&) = delete;

	static T _instance;
};

template<typename T>
T singleTon<T>::_instance;