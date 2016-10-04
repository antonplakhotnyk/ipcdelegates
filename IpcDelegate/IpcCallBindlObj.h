#pragma once

#include "AVMacros.h"
#include "AVPreprocessorRepeatJoin.h"
#include "AVInternal_NS.h"
#include <typeinfo>
#include <map>
#include "IpcCallDataStream.h"
#include <stdint.h>

class IpcCall;
class IpcCallTransport;


namespace IpcCallBindlObj_NS
{

class BaseCall;

//-------------------------------------------------------

class RetVal
{
protected:

	BaseCall& m_call_proc;
	bool	m_conversion_called;

public:

	RetVal(BaseCall& call_proc);
	RetVal(const RetVal& other);
	~RetVal();

public:

	static void InvokeRemote(IpcCall* obj, const std::vector<uint8_t>& call_info_data, std::vector<uint8_t>* result);

protected:

	void InvokeRemote_RetValAsync(const std::string& params_type);
	void InvokeRemote_RetValNo(const std::string& params_type);
	void InvokeRemote_RetVal(const std::string& params_type, const std::string& return_type, std::vector<uint8_t>* result_buf);
	void SerializeCallInfo(IpcCallDataStream* call_info, bool send_return, const std::string& return_type, const std::string& params_type);

	virtual void SerializeArgs(IpcCallDataStream* call_info) = 0;

private:
	RetVal& operator=(const RetVal& other);

};


//-------------------------------------------------------

class CallInfo: public AVRefCounter
{
public:

	virtual void Invoke(IpcCallDataStream* res, IpcCallDataStream* params) const = 0;
	virtual const char* GetSignature_RetType() const = 0;
};


class ProcMap
{
public:

	void FindCallInfo(const std::string& name, std::string& signature, OPtr<const CallInfo>* call_info) const
	{
		auto it_procs = m_name_procs.find(name);
		if( it_procs==m_name_procs.end() )
			return;

		auto it_signature = it_procs->second.m_signature_call.find(signature);
		if( it_signature==it_procs->second.m_signature_call.end() )
			return;

		*call_info = it_signature->second;
	}

public:

	struct NameProcs
	{
		std::map<std::string, OPtr<CallInfo> > m_signature_call;
	};

	std::map<std::string, NameProcs> m_name_procs;
};

template<class TDelProc>
class Sig_RetVoidNo;

template<class TDelProc>
class Sig_RetVoid;

template<class TFunction>
struct InfoDelproc;

}

//-------------------------------------------------------
										 

AV_IPC_TYPE_SIGNATURE(void);
AV_IPC_TYPE_SIGNATURE(int8_t);
AV_IPC_TYPE_SIGNATURE(uint8_t);
AV_IPC_TYPE_SIGNATURE(int16_t);
AV_IPC_TYPE_SIGNATURE(uint16_t);
AV_IPC_TYPE_SIGNATURE(int32_t);
AV_IPC_TYPE_SIGNATURE(uint32_t);
AV_IPC_TYPE_SIGNATURE(int64_t);
AV_IPC_TYPE_SIGNATURE(uint64_t);
// AV_IPC_TYPE_SIGNATURE(int);
AV_IPC_TYPE_SIGNATURE(bool);
AV_IPC_TYPE_SIGNATURE(float);
AV_IPC_TYPE_SIGNATURE(double);

//-------------------------------------------------------

namespace IpcCallBindlObj_NS
{

template<class TUnifiedFunction>
struct ProcSignature;

// template<class TRet>
// struct ProcSignature<TRet(*)()>
// {
// 	static void GetSignature(std::string* params_type)
// 	{
// 	};
// };
// 
// template<class TRet, class TP1>
// struct ProcSignature<TRet(*)(TP1)>
// {
// 	static void GetSignature(std::string* params_type)
// 	{
// 		*params_type += IpcTypeSignature<TP1>::GetSignature();
// 	};
// };
// 
// template<class TRet, class TP1, class TP2>
// struct ProcSignature<TRet(*)(TP1, TP2)>
// {
// 	static void GetSignature(std::string* params_type)
// 	{
// 		*params_type += IpcTypeSignature<TP1>::GetSignature();
// 		*params_type += IpcTypeSignature<TP2>::GetSignature();
// 	};
// };

//-------------------------------------------------------

#define	AV_NUM_ARGS 0
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 1
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 2
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 3
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 4
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 5
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 6
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 7
#include "IpcCallBindlObjN1.h"
#define	AV_NUM_ARGS 8
#include "IpcCallBindlObjN1.h"

template<class TDelegate>
class Impl_Selector
{
	typedef decltype(&TDelegate::operator()) TDelProc;
public:

	typedef typename InfoDelproc<TDelProc>::THandProcUnifiedType_RetType TDelProcUnified;

	typedef typename
		AVInternal_NS::IsVoid<typename InfoDelproc<TDelProc>::TRetType,

		Sig_RetVoid<typename InfoDelproc<TDelProc>::THandProcUnifiedType_RetType>,
		Sig_RetVoidNo<typename InfoDelproc<TDelProc>::THandProcUnifiedType_RetType> >::Res

		::template Imp<TDelegate> Res;
};


class BaseCall
{
private:

	IpcCall* const m_obj;
	const char* m_proc_name;
	size_t m_ret_val_count;

	friend class RetVal;

public:

	bool IsLastInstance()
	{
		return (m_ret_val_count==1);
	}

	BaseCall(IpcCall* obj, const char* proc_name)
		: m_obj(obj)
		, m_proc_name(proc_name)
		, m_ret_val_count(0)
	{}
};

class SyncCall: public BaseCall
{
private:

	class Error_only_void_return_type;
	class Check
	{
	public:
		typedef int ResOk;
	};


public:

	SyncCall(IpcCall* obj, const char* proc_name)
		:BaseCall(obj, proc_name)
	{}


#define	AV_NUM_ARGS 0
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 1
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 2
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 3
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 4
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 5
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 6
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 7
#include "IpcCallBindlObjN2.h"
#define	AV_NUM_ARGS 8
#include "IpcCallBindlObjN2.h"

};

class AsyncCall: public BaseCall
{
private:

	class Error_only_void_return_type;
	class Check
	{
	public:
		typedef int ResOk;
	};

public:

	AsyncCall(IpcCall* obj, const char* proc_name)
		:BaseCall(obj, proc_name)
	{}


#define	AV_NUM_ARGS 0
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 1
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 2
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 3
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 4
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 5
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 6
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 7
#include "IpcCallBindlObjN4.h"
#define	AV_NUM_ARGS 8
#include "IpcCallBindlObjN4.h"

};


#define	AV_NUM_ARGS 0
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 1
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 2
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 3
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 4
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 5
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 6
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 7
#include "IpcCallBindlObjN3.h"
#define	AV_NUM_ARGS 8
#include "IpcCallBindlObjN3.h"

}// namespace IpcCallBindlObj_NS;


