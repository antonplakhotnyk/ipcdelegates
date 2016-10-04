#pragma once

class ErrorPool
{
public:
	ErrorPool(void);
	~ErrorPool(void);

	// file func - указатели на статические строки с неограниченым временем жизни
	static bool Raise(const char* file, int line, const char* func);

	bool IsRaised();
	bool IsRaisedClear();

private:

	struct ErrorData
	{
		ErrorData(): file(NULL),line(0),func(NULL),raised(false){};
		const char* file;
		int line;
		const char* func;
		bool raised;
	};

	ErrorData m_data;

	ErrorPool* m_previous;
};
