#pragma once

class IpcCallTransport: public AVBaseObject
{
public:

	virtual void	WaitRespound() = 0;

	virtual size_t	ReadBytesAvailable() = 0;
	virtual void	Read(uint8_t* data, size_t size) = 0;
	virtual void	Write(const uint8_t* data, size_t size) = 0;
};
