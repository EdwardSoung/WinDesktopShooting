#pragma once

template <typename T>
class Singleton
{
public:
	static T& Instance() {
		static T Instance;
		return Instance;
	}
private:
	Singleton() = default;		//기본 생성자를 private로 해서 생성불가
	Singleton(const Singleton&) = delete;		//복사 생성자 제거
	Singleton& operator=(const Singleton&) = delete; //대입 연산자 삭제
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;		//이동대입연산자 제거

};

