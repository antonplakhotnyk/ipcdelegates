#pragma once

#include <stdint.h>
#include "IpcCallPacket.h"
#include "IpcCallBindlObj.h"


class IpcCall
{
public:

	IpcCall(IpcCallTransport* caller);

	IpcCallBindlObj_NS::SyncCall operator [](const char* proc_name);
	IpcCallBindlObj_NS::AsyncCall operator ()(const char* proc_name);


	template<class TDelegateW>
	void AddHandler(const char* proc_name, const TDelegateW& del);

	void ProcessTransport();

private:

	void ProcessTransport_Internal(bool* pt_return_processed, std::vector<uint8_t>* result);

	void InvokeLocal(const std::vector<uint8_t>& call_info_data, bool* send_return, std::vector<uint8_t>* result) const;
	void InvokeRemote(const std::vector<uint8_t>& call_info_data, std::vector<uint8_t>* result);

	void AddProcSignature(const char* proc_name, std::string& params_type, IpcCallBindlObj_NS::CallInfo* call_info);

	static void DeserializeNameSignature(IpcCallDataStream* call_info, std::string* proc_name, bool* send_return, std::string* return_type, std::string* params_type);

private:

	friend class IpcCallBindlObj_NS::RetVal;


	bool						m_wait_void_return;
	OPtr<IpcCallTransport>		m_transport;
	IpcCallBindlObj_NS::ProcMap	m_proc_map;


	IpcCallPacket			m_packet_parser;
};


//-------------------------------------------------------

template<class TDelegateW>
void IpcCall::AddHandler(const char* proc_name, const TDelegateW& del)
{
 	auto* call_info = new typename IpcCallBindlObj_NS::Impl_Selector<TDelegateW>::Res(del); 
	std::string params_type;
	IpcCallBindlObj_NS::ProcSignature<typename IpcCallBindlObj_NS::Impl_Selector<TDelegateW>::TDelProcUnified>::GetSignature(&params_type);
	AddProcSignature(proc_name, params_type, call_info);
}
