#pragma once

template <typename T>
class Singleton
{
public:
	static T& Instance() 
	{
		static T Instance;
		return Instance;
	}
	virtual void Initialize() = 0;
	virtual void OnDestroy() = 0;

protected:
	Singleton() = default;		//기본 생성자를 private로 해서 생성불가
	virtual ~Singleton() = default;
	
	Singleton(const Singleton&) = delete;		//복사 생성자 제거
	Singleton& operator=(const Singleton&) = delete; //대입 연산자 삭제
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;		//이동대입연산자 제거

};

/* 룰 5가지
* 1. 소멸자, 2. 복사 생성자, 3. 대입 연산자, 4. 이동 생성자, 5. 이동 대입 연산자.
* 다섯가지 항목 중 하나라도 직접 선언했으면 나머지 네가지도 직접 정의하거나 명시적으로 = default / = delete 해야한다.
*/