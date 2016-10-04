#include "stdafx.h"
#include "IpcCallPacket.h"
#include "IpcCallDataStream.h"

static const uint32_t c_invalid_packet_size = -1;

IpcCallPacket::IpcCallPacket()
	:m_packet_size(c_invalid_packet_size)
{
}


IpcCallPacket::~IpcCallPacket()
{
}

bool IpcCallPacket::IsEnoughPacketData(IpcCallTransport* in_data)
{
	if( m_packet_size==c_invalid_packet_size )
	{
		if( in_data->ReadBytesAvailable()>=sizeof(m_packet_size)+c_net_call_packet_type_size )
		{
			uint8_t data_raw[sizeof(m_packet_size)];
			in_data->Read(data_raw, sizeof(data_raw));
			IpcCallDataStream connection_stream(data_raw, sizeof(data_raw));

			connection_stream>>m_packet_size;
		}
	}
	
	bool res = (in_data->ReadBytesAvailable() >= m_packet_size+c_net_call_packet_type_size);
	return res;

}

IpcCallPacket::PacketType IpcCallPacket::ReadType(IpcCallTransport* in_data)
{
	uint32_t type_raw;

	uint8_t data_raw[sizeof(type_raw)];
	in_data->Read(data_raw, sizeof(data_raw));
	IpcCallDataStream connection_stream(data_raw, sizeof(data_raw));

	connection_stream>>type_raw;
	return (PacketType)type_raw;
}

void IpcCallPacket::ReadData(IpcCallTransport* in_data, std::vector<uint8_t>* data_replace)
{
	auto size = m_packet_size;
	m_packet_size = c_invalid_packet_size;
	data_replace->resize(size);
	if( size!=0 )
		in_data->Read(&(*data_replace)[0], size);
}

void IpcCallPacket::SendData(const std::vector<uint8_t>& out_data_buf, PacketType type, IpcCallTransport* out_data)
{
	std::vector<uint8_t> out_data_raw_buf;
	IpcCallDataStream out_data_raw(&out_data_raw_buf);

	out_data_raw<<uint32_t(out_data_buf.size())<<uint32_t(type);
	if( !out_data_buf.empty() )
		out_data_raw.WriteRawData(&out_data_buf[0], out_data_buf.size());
	
	out_data->Write(&out_data_raw_buf[0], out_data_raw_buf.size());
}
