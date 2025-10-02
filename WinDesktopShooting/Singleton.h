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
	Singleton() = default;		//�⺻ �����ڸ� private�� �ؼ� �����Ұ�
	virtual ~Singleton() = default;
	
	Singleton(const Singleton&) = delete;		//���� ������ ����
	Singleton& operator=(const Singleton&) = delete; //���� ������ ����
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;		//�̵����Կ����� ����

};

/* �� 5����
* 1. �Ҹ���, 2. ���� ������, 3. ���� ������, 4. �̵� ������, 5. �̵� ���� ������.
* �ټ����� �׸� �� �ϳ��� ���� ���������� ������ �װ����� ���� �����ϰų� ��������� = default / = delete �ؾ��Ѵ�.
*/