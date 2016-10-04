#include "stdafx.h"
#include "IpcCall.h"


IpcCall::IpcCall(IpcCallTransport* caller)
	:m_transport(caller)
	, m_wait_void_return(true)
{
}


IpcCallBindlObj_NS::SyncCall IpcCall::operator [](const char* proc_name)
{
	return IpcCallBindlObj_NS::SyncCall(this, proc_name);
}

IpcCallBindlObj_NS::AsyncCall IpcCall::operator ()(const char* proc_name)
{
	return IpcCallBindlObj_NS::AsyncCall(this, proc_name);
}

void IpcCall::DeserializeNameSignature(IpcCallDataStream* call_info, std::string* proc_name, bool* send_return, std::string* return_type, std::string* params_type)
{
	(*call_info)>>(*proc_name)>>(*send_return)>>(*return_type)>>(*params_type);
}

void IpcCall::InvokeLocal(const std::vector<uint8_t>& call_info_data, bool* send_return, std::vector<uint8_t>* result) const
{
	std::string return_type;
	std::string params_type;
	std::string proc_name;


	IpcCallDataStream call_info_data_str(&call_info_data[0], call_info_data.size());
	DeserializeNameSignature(&call_info_data_str, &proc_name, send_return, &return_type, &params_type);

	OPtr<const IpcCallBindlObj_NS::CallInfo>	call_info;

	m_proc_map.FindCallInfo(proc_name, params_type, &call_info);
	return_if_not_equal(call_info, true);

	if( !return_type.empty() )
	{
		const std::string& return_type_call = call_info->GetSignature_RetType();
		return_if_not_equal(return_type, return_type_call);
	}

	if( *send_return )
	{
		IpcCallDataStream result_str(result);
		call_info->Invoke(&result_str, &call_info_data_str);
	}
	else
		call_info->Invoke(NULL, &call_info_data_str);
}

void IpcCall::InvokeRemote(const std::vector<uint8_t>& call_info_data, std::vector<uint8_t>* result)
{
	IpcCallPacket::SendData(call_info_data, IpcCallPacket::pt_call, m_transport);

	if(result)
	{
		bool pt_return_processed = false;
		while( !pt_return_processed )
		{
			m_transport->WaitRespound();
			ProcessTransport_Internal(&pt_return_processed, result);
		}
	}
}

void IpcCall::ProcessTransport_Internal(bool* pt_return_processed, std::vector<uint8_t>* result)
{
	while( m_packet_parser.IsEnoughPacketData(m_transport) )
	{
		IpcCallPacket::PacketType data_type = m_packet_parser.ReadType(m_transport);

		switch( data_type )
		{
			case IpcCallPacket::pt_call:
			{
				std::vector<uint8_t> in_data;
				m_packet_parser.ReadData(m_transport, &in_data);

				std::vector<uint8_t> result;
				bool send_return = false;
				InvokeLocal(in_data, &send_return, &result);

				if( send_return )
					m_packet_parser.SendData(result, IpcCallPacket::pt_return, m_transport);
			}
			break;
			case IpcCallPacket::pt_return:
			{
				return_if_equal(result,NULL);
				m_packet_parser.ReadData(m_transport, result);
				assert_if_equal(pt_return_processed,NULL);
				if( pt_return_processed )
					*pt_return_processed = true;
			}
			break;
			case IpcCallPacket::pt_enumerate:
				break;
			default:
				break;
		}
	}
}

void IpcCall::ProcessTransport()
{
	ProcessTransport_Internal(NULL, NULL);
}

void IpcCall::AddProcSignature(const char* proc_name, std::string& params_type, IpcCallBindlObj_NS::CallInfo* call_info)
{
	auto it_name = m_proc_map.m_name_procs.find(proc_name);
	if( it_name == m_proc_map.m_name_procs.end() )
	{
		m_proc_map.m_name_procs[proc_name] = IpcCallBindlObj_NS::ProcMap::NameProcs();
		it_name = m_proc_map.m_name_procs.find(proc_name);
	}

	auto it_params = it_name->second.m_signature_call.find(params_type);
	return_if_not_equal(it_params, it_name->second.m_signature_call.end() );
	it_name->second.m_signature_call[params_type] = call_info;
}

//-------------------------------------------------------
