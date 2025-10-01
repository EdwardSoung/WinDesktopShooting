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
	Singleton() = default;		//�⺻ �����ڸ� private�� �ؼ� �����Ұ�
	Singleton(const Singleton&) = delete;		//���� ������ ����
	Singleton& operator=(const Singleton&) = delete; //���� ������ ����
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;		//�̵����Կ����� ����

};

