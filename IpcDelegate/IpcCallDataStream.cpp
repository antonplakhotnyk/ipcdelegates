#include "stdafx.h"
#include "IpcCallDataStream.h"
#include <cstring>



IpcCallDataStream::IpcCallDataStream(const uint8_t* data_read_only, size_t data_size)
	:m_pos(0)
	, m_data_read_write(NULL)
	, m_data_read_only(data_read_only)
	, m_data_read_only_size(data_size)
{
}

IpcCallDataStream::IpcCallDataStream(std::vector<uint8_t>* data_read_write)
	: m_pos(0)
	, m_data_read_write(data_read_write)
	, m_data_read_only(NULL)
	, m_data_read_only_size(0)
{
}

IpcCallDataStream::~IpcCallDataStream()
{
}

template<class T>
void IpcCallDataStream::WriteBytes(T t)
{
	return_if_equal(m_data_read_write,NULL);

	size_t pos = Size();
	ResizeRW(pos+sizeof(T));
	return_if_not_equal(Size(), pos+sizeof(t));

	uint8_t* bytes = DataRW()+pos;

	for( size_t i = 0; i<sizeof(T); i++ )
	{
		bytes[i] = (0xFF & t);
		t >>= 8;
	}
}

template<class T>
void IpcCallDataStream::ReadBytes(T* t)
{
	return_if_equal(IsReadAvailable(sizeof(*t)), false);
	const uint8_t* bytes = DataR()+m_pos;

	*t = 0;
	for( size_t i = 0; i<sizeof(T); i++ )
	{
		*t <<= 8;
		*t |= bytes[sizeof(T)-1-i];
	}

	m_pos += sizeof(T);
}


void IpcCallDataStream::ReadRawData(uint8_t* data, size_t len)
{
	return_if_equal(IsReadAvailable(len), false);
	const uint8_t* pos = DataR()+m_pos;
	memcpy(data, pos, len);
	m_pos += len;
}

void IpcCallDataStream::WriteRawData(const uint8_t* data, size_t len)
{
	return_if_equal(m_data_read_write, NULL);

	size_t pos = Size();
	ResizeRW(pos+len);
	return_if_not_equal(Size(), pos+len);

	uint8_t* bytes = DataRW()+pos;
	memcpy(bytes, data, len);
}

bool IpcCallDataStream::IsReadAvailable(size_t size)
{
	bool res = Size()-m_pos >= size;
	return res;
}

//-------------------------------------------------------

uint8_t* IpcCallDataStream::DataRW()
{
	return &(*m_data_read_write)[0];
}

size_t IpcCallDataStream::Size()
{
	if( m_data_read_write )
		return m_data_read_write->size();
	return m_data_read_only_size;
}

void IpcCallDataStream::ResizeRW(size_t size)
{
	m_data_read_write->resize(size);
}

const uint8_t* IpcCallDataStream::DataR() const
{
	if( m_data_read_write )
		return &(*m_data_read_write)[0];
	return m_data_read_only;
}

//-------------------------------------------------------


IpcCallDataStream &IpcCallDataStream::operator>>(int8_t &i)
{
	ReadBytes(&i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator>>(int16_t &i)
{
	ReadBytes(&i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator>>(int32_t &i)
{
	ReadBytes(&i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator>>(int64_t &i)
{
	ReadBytes(&i);
	return *this;
}


IpcCallDataStream &IpcCallDataStream::operator>>(bool &i)
{
	ReadRawData(reinterpret_cast<uint8_t*>(&i), sizeof(i));
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator>>(float &f)
{
	ReadRawData(reinterpret_cast<uint8_t*>(&f), sizeof(f));
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator>>(double &f)
{
	ReadRawData(reinterpret_cast<uint8_t*>(&f), sizeof(f));
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(int8_t i)
{
	WriteBytes(i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(int16_t i)
{
	WriteBytes(i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(int32_t i)
{
	WriteBytes(i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(int64_t i)
{
	WriteBytes(i);
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(bool i)
{
	WriteRawData(reinterpret_cast<uint8_t*>(&i), sizeof(i));
	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(float f)
{
	WriteRawData(reinterpret_cast<uint8_t*>(&f), sizeof(f));
 	return *this;
}

IpcCallDataStream &IpcCallDataStream::operator<<(double f)
{
	WriteRawData(reinterpret_cast<uint8_t*>(&f), sizeof(f));
	return *this;
}


IpcCallDataStream &IpcCallDataStream::operator>>(uint8_t &i)
{ 
	return *this >> reinterpret_cast<int8_t&>(i); 
}

IpcCallDataStream &IpcCallDataStream::operator>>(uint16_t &i)
{ 
	return *this >> reinterpret_cast<int16_t&>(i); 
}

IpcCallDataStream &IpcCallDataStream::operator>>(uint32_t &i)
{ 
	return *this >> reinterpret_cast<int32_t&>(i); 
}

IpcCallDataStream &IpcCallDataStream::operator>>(uint64_t &i)
{ 
	return *this >> reinterpret_cast<int64_t&>(i); 
}

IpcCallDataStream &IpcCallDataStream::operator<<(uint8_t i)
{ 
	return *this << int8_t(i); 
}

IpcCallDataStream &IpcCallDataStream::operator<<(uint16_t i)
{ 
	return *this << int16_t(i); 
}

IpcCallDataStream &IpcCallDataStream::operator<<(uint32_t i)
{ 
	return *this << int32_t(i); 
}

IpcCallDataStream &IpcCallDataStream::operator<<(uint64_t i)
{ 
	return *this << int64_t(i); 
}

//-------------------------------------------------------
// 
// IpcCallDataStream& operator<<(IpcCallDataStream& stream, const int& v)
// {
// 	STATIC_ASSERT(sizeof(v)==sizeof(int32_t), "unexpected size of int");
// 	return stream << int32_t(v);
// }
// 
// IpcCallDataStream& operator>>(IpcCallDataStream& stream, int& v)
// {
// 	STATIC_ASSERT(sizeof(v)==sizeof(int32_t), "unexpected size of int");
// 	return stream >> reinterpret_cast<int32_t&>(v);
// }

//-------------------------------------------------------


IpcCallDataStream& operator<<(IpcCallDataStream& stream, const std::string& v)
{
	stream<<(uint32_t)(v.length()*sizeof(char));
	stream.WriteRawData(reinterpret_cast<const uint8_t*>(v.c_str()), (uint32_t)(v.length()*sizeof(char)));
	return stream;
}

IpcCallDataStream& operator>>(IpcCallDataStream& stream, std::string& v)
{
	uint32_t length;
	stream>>length;
	v.resize(length/sizeof(char));
	char* raw_data = &v[0];
	if( length!=0 )
		stream.ReadRawData(reinterpret_cast<uint8_t*>(raw_data), length/sizeof(char));
	return stream;
}

//-------------------------------------------------------
