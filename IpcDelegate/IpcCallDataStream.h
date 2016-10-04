#pragma once

#include <stdint.h>
#include <vector>

//-------------------------------------------------------
#define AV_IPC_TYPE_SIGNATURE(type)		 \
template<class TType>					 \
struct IpcTypeSignature;				 \
										 \
template<>								 \
struct IpcTypeSignature<type>			 \
{										 \
	static const char* GetSignature()	 \
	{									 \
		return #type;					 \
	};									 \
};
//-------------------------------------------------------


class IpcCallDataStream
{
public:

	IpcCallDataStream(const uint8_t* data_read_only, size_t data_size);
	IpcCallDataStream(std::vector<uint8_t>* data_read_write);
	~IpcCallDataStream();

	IpcCallDataStream &operator>>(int8_t &i);
	IpcCallDataStream &operator>>(uint8_t &i);
	IpcCallDataStream &operator>>(int16_t &i);
	IpcCallDataStream &operator>>(uint16_t &i);
	IpcCallDataStream &operator>>(int32_t &i);
	IpcCallDataStream &operator>>(uint32_t &i);
	IpcCallDataStream &operator>>(int64_t &i);
	IpcCallDataStream &operator>>(uint64_t &i);

	IpcCallDataStream &operator>>(bool &i);
	IpcCallDataStream &operator>>(float &f);
	IpcCallDataStream &operator>>(double &f);

	IpcCallDataStream &operator<<(int8_t i);
	IpcCallDataStream &operator<<(uint8_t i);
	IpcCallDataStream &operator<<(int16_t i);
	IpcCallDataStream &operator<<(uint16_t i);
	IpcCallDataStream &operator<<(int32_t i);
	IpcCallDataStream &operator<<(uint32_t i);
	IpcCallDataStream &operator<<(int64_t i);
	IpcCallDataStream &operator<<(uint64_t i);
	IpcCallDataStream &operator<<(bool i);
	IpcCallDataStream &operator<<(float f);
	IpcCallDataStream &operator<<(double f);

	void ReadRawData(uint8_t* data, size_t len);
	void WriteRawData(const uint8_t* data, size_t len);

	int SkipRawData(size_t len);

public:

	bool IsReadAvailable(size_t size);

	template<class T>
	void WriteBytes(T t);

	template<class T>
	void ReadBytes(T* t);

	uint8_t* DataRW();
	size_t Size();
	void ResizeRW(size_t size);
	const uint8_t* DataR() const;

private:

	size_t	m_pos;

	std::vector<uint8_t>* const m_data_read_write;

	const uint8_t* const m_data_read_only;
	const size_t m_data_read_only_size;
};

//-------------------------------------------------------

// IpcCallDataStream& operator<<(IpcCallDataStream& stream, const int& v);
// IpcCallDataStream& operator>>(IpcCallDataStream& stream, int& v);

//-------------------------------------------------------

IpcCallDataStream& operator<<(IpcCallDataStream& stream, const std::string& v);
IpcCallDataStream& operator>>(IpcCallDataStream& stream, std::string& v);

AV_IPC_TYPE_SIGNATURE(std::string);

// template<class TType> 
// struct IpcTypeSignature; 
// template<> struct IpcTypeSignature<std::string> { static const char* GetSignature() { return "std::string"; }; };;

//-------------------------------------------------------
