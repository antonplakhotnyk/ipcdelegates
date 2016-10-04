#include "StdAfx.h"
#include "IpcCall.h"
#include "IpcCallBindlObj.h"

namespace IpcCallBindlObj_NS
{

RetVal::RetVal(BaseCall& call_proc)
	:m_call_proc(call_proc)
	, m_conversion_called(false)
{
	m_call_proc.m_ret_val_count++;
}

RetVal::RetVal(const RetVal& other)
	: m_call_proc(other.m_call_proc)
	, m_conversion_called(other.m_conversion_called)
{
	m_call_proc.m_ret_val_count++;
}

RetVal::~RetVal()
{
	m_call_proc.m_ret_val_count--;
}

void RetVal::InvokeRemote(IpcCall* obj, const std::vector<uint8_t>& call_info_data, std::vector<uint8_t>* result)
{
	obj->InvokeRemote(call_info_data, result);
}

void RetVal::InvokeRemote_RetValAsync(const std::string& params_type)
{
	std::vector<uint8_t> call_info_data_buf;
	IpcCallDataStream call_info_data(&call_info_data_buf);

	std::string return_type;

	SerializeCallInfo(&call_info_data, false, return_type, params_type);
	InvokeRemote(this->m_call_proc.m_obj, call_info_data_buf, NULL);
}

void RetVal::InvokeRemote_RetValNo(const std::string& params_type)
{
 	std::vector<uint8_t> call_info_data_buf;
	IpcCallDataStream call_info_data(&call_info_data_buf);
	
	std::string return_type;
	std::vector<uint8_t> result_buf;

	SerializeCallInfo(&call_info_data, true, return_type, params_type);
	InvokeRemote(this->m_call_proc.m_obj, call_info_data_buf, &result_buf);
}

void RetVal::InvokeRemote_RetVal(const std::string& params_type, const std::string& return_type, std::vector<uint8_t>* result_buf)
{
	std::vector<uint8_t> call_info_data_buf;
	IpcCallDataStream call_info_data(&call_info_data_buf);
	SerializeCallInfo(&call_info_data, true, return_type, params_type);
	InvokeRemote(this->m_call_proc.m_obj, call_info_data_buf, result_buf);
}

void RetVal::SerializeCallInfo(IpcCallDataStream* call_info, bool send_return, const std::string& return_type, const std::string& params_type)
{
	(*call_info)<<std::string(this->m_call_proc.m_proc_name)<<send_return<<return_type<<params_type;
	SerializeArgs(call_info);
}


#define	AV_INCLUDED_FROM_CPP
#define	AV_NUM_ARGS 0
#include "IpcCallBindlObjN3.h"

}
