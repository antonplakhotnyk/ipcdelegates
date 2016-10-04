#ifndef AV_NUM_ARGS
#error this file must be included only from IpcCallBindlObj.h
#endif

// Защита от повторного включения здень не нужна, потому что этот
// файл будет намерено включатся несколько раз.
//#pragma once

#if	AV_NUM_ARGS>0
#define	COMA ,
#else
#define	COMA
#endif
#define	TMPLATE_PARAMS REPEAT_JOIN_N_1(class TP,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // class TP1 , class TP2 , class TP3 , class TP4
#define	TYPES REPEAT_JOIN_N_1(TP,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 , TP2 , TP3 , TP4
#define	ARGS REPEAT_JOIN_N_1(tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // tp1 , tp2 , tp3 , tp4
#define PARAMS REPEAT_JOIN_N_2(TP,AV_XN, tp, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 tp1 , TP2 tp2 , TP3 tp3 , TP4 tp4
#define SYNC_RETVAL_N JOIN_XY(SYNC_RETVAL_, AV_NUM_ARGS) // SYNC_RETVAL_4
#define ASYNC_RETVAL_N JOIN_XY(ASYNC_RETVAL_, AV_NUM_ARGS) // ASYNC_RETVAL_4
#define	SERIAL_ARGS REPEAT_JOIN_N_1(<<m_tp,AV_XN, AV_EMPTY, AV_NUM_ARGS) // <<m_tp1  <<m_tp2  <<m_tp3  <<m_tp4

#if defined(AV_INCLUDED_FROM_CPP) || (AV_NUM_ARGS>0)

//-------------------------------------------------------

#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
void SYNC_RETVAL_N
#if AV_NUM_ARGS>0
<TYPES>
#endif
::SerializeArgs(IpcCallDataStream* call_info)
{
	(*call_info) SERIAL_ARGS;
}

#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
SYNC_RETVAL_N
#if AV_NUM_ARGS>0
<TYPES>
#endif
::~SYNC_RETVAL_N()
{
	if( this->m_call_proc.IsLastInstance() && !m_conversion_called )
	{
		typedef void(*TreatProc)(PARAMS);
		std::string params_type;
		ProcSignature<TreatProc>::GetSignature(&params_type);
		InvokeRemote_RetValNo(params_type);
	}
}


//-------------------------------------------------------


#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
void ASYNC_RETVAL_N
#if AV_NUM_ARGS>0
<TYPES>
#endif
::SerializeArgs(IpcCallDataStream* call_info)
{
	(*call_info) SERIAL_ARGS;
}

#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
ASYNC_RETVAL_N
#if AV_NUM_ARGS>0
<TYPES>
#endif
::~ASYNC_RETVAL_N()
{
	if( this->m_call_proc.IsLastInstance() )
	{
		typedef void(*TreatProc)(PARAMS);
		std::string params_type;
		ProcSignature<TreatProc>::GetSignature(&params_type);
		InvokeRemote_RetValAsync(params_type);
	}
}

//-------------------------------------------------------

#endif

#if !defined(AV_INCLUDED_FROM_CPP)

#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
template<typename TRetType>
SYNC_RETVAL_N
#if AV_NUM_ARGS>0
<TYPES>
#endif
::operator TRetType()
{
	m_conversion_called = true;

	typedef TRetType(*TreatProc)(PARAMS);
	std::string return_type;
	std::string params_type;
	return_type = IpcTypeSignature<TRetType>::GetSignature();
	ProcSignature<TreatProc>::GetSignature(&params_type);

	std::vector<uint8_t> result_buf;
	InvokeRemote_RetVal(params_type, return_type, &result_buf);
	{
		TRetType res;
		if( !result_buf.empty() )
		{
			IpcCallDataStream result(&result_buf[0], result_buf.size());
			result>>res;
		}
		return res;
	}
}

#endif

#undef AV_NUM_ARGS
#undef TMPLATE_PARAMS_SKIP
#undef COMA
#undef TMPLATE_PARAMS
#undef TYPES
#undef ARGS
#undef PARAMS
#undef SERIAL_ARGS
#undef SYNC_RETVAL_N
#undef ASYNC_RETVAL_N
#if defined(AV_INCLUDED_FROM_CPP)
#undef AV_INCLUDED_FROM_CPP
#endif