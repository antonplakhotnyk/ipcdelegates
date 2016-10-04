#pragma once

#include <stdint.h>
#include <vector>
#include "IpcCallTransport.h"

class IpcCallPacket
{
public:

	// |-- size 4B --|-- type 4B --|-- data (size B) --|
	enum PacketType { pt_call, pt_return, pt_enumerate };
	static const int c_net_call_packet_type_size = 4;


	IpcCallPacket();
	~IpcCallPacket();

	bool				IsEnoughPacketData(IpcCallTransport* in_data);
	PacketType			ReadType(IpcCallTransport* in_data);
	void				ReadData(IpcCallTransport* in_data, std::vector<uint8_t>* data_replace);

	static void SendData(const std::vector<uint8_t>& out_data_buf, PacketType type, IpcCallTransport* out_data);

private:

	uint32_t	m_packet_size;
};

