// Этот файл НЕ должен включатся непосредственно
// он включается изнутри Delegate.h
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
#define	PARAMS_DECLARE REPEAT_JOIN_N_2(typedef TP,AV_XN, P,AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS) // typedef TP1 P1 ; typedef TP2 P2

#define	AV_TYPES REPEAT_JOIN_N_1(TP,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 , TP2 , TP3 , TP4
#define	ARGS REPEAT_JOIN_N_1(tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // tp1 , tp2 , tp3 , tp4
#define PARAMS REPEAT_JOIN_N_2(TP,AV_XN, tp, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 tp1 , TP2 tp2 , TP3 tp3 , TP4 tp4
#define SYNC_RETVAL_N JOIN_XY(SYNC_RETVAL_, AV_NUM_ARGS) // SYNC_RETVAL_4
#define ASYNC_RETVAL_N JOIN_XY(ASYNC_RETVAL_, AV_NUM_ARGS) // ASYNC_RETVAL_4
#define PARAMS_REF REPEAT_JOIN_N_3(TP,AV_XN, &,AV_X, tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 & tp1 , TP2 & tp2 , TP3 & tp3 , TP4 & tp4
#define	TYPES_INIT REPEAT_JOIN_N_3(m_tp,AV_XN, tp, AV_EARL_XN, ,AV_EAR_R, AV_COMA_DELEGATE, AV_NUM_ARGS) // m_tp1 (tp1 ) , m_tp2 (tp2 ) , m_tp3 (tp3 ) , m_tp4 (tp4 )
#define	TYPES_DECLARE REPEAT_JOIN_N_2(TP,AV_XN, m_tp, AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS) // TP1 m_tp1; TP2 m_tp2; TP3 m_tp3
#define	ARGS_M REPEAT_JOIN_N_1(m_tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // m_tp1, m_tp2, m_tp3
#define	SERIAL_ARGS REPEAT_JOIN_N_1(<<m_tp,AV_XN, AV_EMPTY, AV_NUM_ARGS) // <<m_tp1  <<m_tp2  <<m_tp3  <<m_tp4
#define	DESERIAL_ARGS REPEAT_JOIN_N_1(>>tp,AV_XN, AV_EMPTY, AV_NUM_ARGS)// >>tp1  >>tp2  >>tp3  >>tp4
#define	DeserializeParams_N JOIN_XY(DeserializeParams_, AV_NUM_ARGS) // DeserializeParams_4
// *params_type += IpcTypeSignature<TP1>::GetSignature(); *params_type += IpcTypeSignature<TP2>::GetSignature()
#define AV_TYPE_SIGNATURE REPEAT_JOIN_N_2(*params_type += IpcTypeSignature<TP, AV_XN, >::GetSignature(), AV_X, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS)

//-------------------------------------------------------
template<class TRet COMA TMPLATE_PARAMS>
struct ProcSignature<TRet(*)(AV_TYPES)>
{
	static void GetSignature(std::string* params_type)
	{
		AV_TYPE_SIGNATURE;
	};
};
//-------------------------------------------------------


#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
static void DeserializeParams_N(IpcCallDataStream* call_info COMA PARAMS_REF)
{
	(*call_info)DESERIAL_ARGS;
}

template<class TRet, class TCls COMA TMPLATE_PARAMS>
struct InfoDelproc<TRet(TCls::*)(AV_TYPES) const>
{
	PARAMS_DECLARE;
	typedef TRet TRetType;

	typedef TRet(*THandProcUnifiedType_RetType)(AV_TYPES);
	typedef void(*THandProcUnifiedType_RetVoid)(AV_TYPES);
};

//-------------------------------------------------------


template<class TRet COMA TMPLATE_PARAMS>
class Sig_RetVoidNo<TRet(*)(AV_TYPES)>
{
public:

	template<class TDelegate>
	class Imp: public CallInfo
	{
	private:

		TDelegate m_del;

	private:

		void Invoke(IpcCallDataStream* res, IpcCallDataStream* params) const override
		{
			TYPES_DECLARE;
			DeserializeParams_N(params COMA ARGS_M);
			TRet ret = m_del(ARGS_M);
			if( res )
				(*res)<<ret;
		}


		virtual const char* GetSignature_RetType() const override
		{
			return IpcTypeSignature<TRet>::GetSignature();
		}

	public:

		Imp(const TDelegate& del):m_del(del){};
	};

};



template<TMPLATE_PARAMS>
class Sig_RetVoid<void(*)(AV_TYPES)>
{
public:

	template<class TDelegate>
	class Imp: public CallInfo
	{
	private:

		TDelegate m_del;

	private:

		void Invoke(IpcCallDataStream* res, IpcCallDataStream* params) const override
		{
			TYPES_DECLARE;
			DeserializeParams_N(params COMA ARGS_M);
			m_del(ARGS_M);
		}

		virtual const char* GetSignature_RetType() const override
		{
			return IpcTypeSignature<void>::GetSignature();
		}

	public:

		Imp(const TDelegate& del):m_del(del){};
	};
};



#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
class SYNC_RETVAL_N: public RetVal
{
private:

	void SerializeArgs(IpcCallDataStream* call_info) override;

public:

	SYNC_RETVAL_N(BaseCall& call_proc COMA PARAMS):
		RetVal(call_proc)
		COMA TYPES_INIT
	{}

	~SYNC_RETVAL_N();


	template<typename TRetType>
	operator TRetType();

private:

	TYPES_DECLARE;
};

#if AV_NUM_ARGS>0
template<TMPLATE_PARAMS>
#endif
class ASYNC_RETVAL_N: public RetVal
{
private:

	void SerializeArgs(IpcCallDataStream* call_info) override;

public:

	ASYNC_RETVAL_N(BaseCall& call_proc COMA PARAMS):
		RetVal(call_proc)
		COMA TYPES_INIT
	{}

	~ASYNC_RETVAL_N();

private:

	TYPES_DECLARE;
};


#undef AV_NUM_ARGS
#undef COMA
#undef TMPLATE_PARAMS
#undef AV_TYPES
#undef ARGS
#undef PARAMS
#undef PARAMS_REF
#undef SYNC_RETVAL_N
#undef ASYNC_RETVAL_N
#undef DeserializeParams_N
#undef TYPES_INIT
#undef TYPES_DECLARE
#undef TMPLATE_PARAMS
#undef ARGS_M
#undef SERIAL_ARGS
#undef DESERIAL_ARGS
