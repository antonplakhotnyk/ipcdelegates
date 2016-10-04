#pragma once

class LockInt
{
public:
	LockInt(int* lock);
	~LockInt();

private:

	int* m_lock;
};

