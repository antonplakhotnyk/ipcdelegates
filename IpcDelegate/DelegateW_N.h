// Этот файл НЕ должен включатся непосредственно
// он включается изнутри Delegate.h 
#ifndef INCLUDE_DELEGATEN_H 
#error this file must be included only from Delegate.h
#endif

//-------------------------------------------------------


#if AV_NUM_ARGS == 0
#  define COMA_IF_ARGS
#  define DOUBLE_DOT_IF_ARGS
#else
#  define COMA_IF_ARGS ,
#  define DOUBLE_DOT_IF_ARGS :
#endif


// class PX1 , class PX2
#define	AV_TMPLATE_PARAMS_TP REPEAT_JOIN_N_1(class PX,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// class PD1 , class PD2
#define	AV_TMPLATE_PARAMS_PDN REPEAT_JOIN_N_1(class PD,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// class PH1 , class PH2 
#define	AV_TMPLATE_PARAMS_PHN REPEAT_JOIN_N_1(class PH,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// PX1 tp1 , PX2 tp2
#define AV_PROC_PARAMS REPEAT_JOIN_N_2(PX,AV_XN, tp, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// PX1, PX2
#define	AV_TYPES REPEAT_JOIN_N_1(PX,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// PD1, PD2
#define	AV_TYPES_PDN REPEAT_JOIN_N_1(PD,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// PH1, PH2
#define	AV_TYPES_PHN REPEAT_JOIN_N_1(PH,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// TypePX1 p1 ; TypePX2 p2
#define	AV_TYPE_PX_DECLARE REPEAT_JOIN_N_2(TypePX,AV_XN, p,AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS) 

// typedef PX1 TypePX1 ; typedef PX2 TypePX2
#define	AV_TYPEDEF_PX_DECLARE REPEAT_JOIN_N_2(typedef PX,AV_XN, TypePX,AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS) 

// typedef typename AVInternal_NS::NoRefType<PX1 >::Type& TypePX1; typedef typename AVInternal_NS::NoRefType<PX2 >::Type& TypePX2
#define AV_NOREF_TYPES_DECLARE REPEAT_JOIN_N_2(typedef typename AVInternal_NS::NoRefType<PX,AV_XN, >::Type& TypePX, AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS)

// typename AVInternal_NS::NoRefType<PX1 >::Type p1; typename AVInternal_NS::NoRefType<PX2 >::Type p2
#define AV_NOREF_MEMBERS_DECLARE REPEAT_JOIN_N_2(typename AVInternal_NS::NoRefType<PX,AV_XN, >::Type p,AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS)

// p1 (params.p1) , p2 (params.p2)
#define AV_PARAMS_INIT REPEAT_JOIN_N_2(p, AV_XN, params.p, AV_EARL_XN_EARR, AV_COMA_DELEGATE, AV_NUM_ARGS)

// const P1 &_p1 , const P2 &_p2
#define AV_PARAMS_CONST_REF REPEAT_JOIN_N_2(const P, AV_XN, &_p, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// x1, x2
#define	AV_VALUES REPEAT_JOIN_N_1(x,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// typename InfoDelproc<TDelProc>::TypePX1 x1 , typename InfoDelproc<TDelProc>::TypePX2 x2
#define	AV_DELPROC_TYPE_PX_DECLARE REPEAT_JOIN_N_2(typename InfoDelproc<TDelProc>::TypePX,AV_XN, x,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) 

// p1 , p2
#define	AV_VALUES_P REPEAT_JOIN_N_1(p,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// int A1 , int A2
#define AV_TYPE_INT_AN_MAX REPEAT_JOIN_N_1(int A, AV_XN, AV_COMA_DELEGATE, NUM_ARGS_MAX)

// int A1=1 , int A2=2
#define AV_TYPE_INT_AN_EQN_MAX REPEAT_JOIN_N_2(int A, AV_XN, , AV_EQU_XN, AV_COMA_DELEGATE, NUM_ARGS_MAX)

// A1 , A2, A3 , A4, A5 , A6
#define AV_AN_MAX REPEAT_JOIN_N_1(A, AV_XN, AV_COMA_DELEGATE, NUM_ARGS_MAX)

// A1 , A2, A3 , A4, A5
#define AV_AN_MAX_DEC REPEAT_JOIN_N_1(A, AV_XN, AV_COMA_DELEGATE, NUM_ARGS_MAX_DECREMENT)

// SelArgX<TSigMap::HA1 ,typename InfoHandproc<THandProc>::TypePX1 ,CallParamsDel<TDelProc> ,TDelConst ,DataType >::Val(&m, data) , SelArgX<TSigMap::HA2 ,typename InfoHandproc<THandProc>::TypePX2 ,CallParamsDel<TDelProc> ,TDelConst ,DataType >::Val(&m, data)
//#define AV_PARAMS_CALL_SELECT_DATA REPEAT_JOIN_N_3(SelArgX<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst >::Val(&m, data), AV_COMA_X, AV_COMA_DELEGATE, AV_NUM_ARGS)

// SelArgX<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst>::Val(this, data), SelArgX<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst>::Val(this, data)
#define AV_PARAMS_CALL_SELECT_DEL REPEAT_JOIN_N_3(SelArgX<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst>::Val(this, data),AV_COMA_X, AV_COMA_DELEGATE, AV_NUM_ARGS)

// typename WptrLock<typename SelArgType<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst>::Res>::Res p1 = SelArgX<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst >::Val(&m, data); typename WptrLock<typename SelArgType<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst>::Res>::Res p2 = SelArgX<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst >::Val(&m, data)
#define AV_PARAMS_LOCK_DECLARE REPEAT_JOIN_N_6(typename WptrLock<typename SelArgType<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst>::Res>::Res p, AV_COMA_XN, = SelArgX<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst >::Val(&m, data), AV_COMA_X, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS)

// typename SelArgType<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst>::Res p1 = SelArgX<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst >::Val(this, data); typename SelArgType<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst>::Res p2 = SelArgX<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst >::Val(this, data)
#define AV_DEL_CALL_PARAMS_DECLARE REPEAT_JOIN_N_6(typename SelArgType<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst>::Res p, AV_COMA_XN, = SelArgX<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst >::Val(this, data), AV_COMA_X, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS)


// WptrLockCheck<typename SelArgType<TSigMap::HA1, CallParamsDel<TDelProc>, TDelConst>::Res>::IsOk(p1) && WptrLockCheck<typename SelArgType<TSigMap::HA2, CallParamsDel<TDelProc>, TDelConst>::Res>::IsOk(p2)
#define AV_PARAMS_LOCK_CHECK REPEAT_JOIN_N_4(WptrLockCheck<typename SelArgType<TSigMap::HA, AV_XN, CallParamsDel<TDelProc>, AV_COMA_X, TDelConst>::Res>::IsOk, AV_COMA_X, p, AV_EARL_XN_EARR, AV_SS_DELEGATE, AV_NUM_ARGS)
#	if AV_NUM_ARGS == 0
#undef AV_PARAMS_LOCK_CHECK
#define AV_PARAMS_LOCK_CHECK true
#endif
//-------------------------------------------------------


namespace Del
{

#	if AV_NUM_ARGS == 0

//template<int A1=1, int A2=2>
template<int A0 = 0, AV_TYPE_INT_AN_EQN_MAX>
class Map
{
public:
	static const int HA0 = A0;
	REPEAT_JOIN_N_2(static const int HA, AV_XN, A, AV_EQU_XN, AV_DOTCOMA_DELEGATE, NUM_ARGS_MAX);
	// 	static const int HA1=A1;
	// 	static const int HA2=A2;
};


#endif // AV_NUM_ARGS == 0

#	if (AV_NUM_ARGS != 0) && (AV_NUM_ARGS<NUM_ARGS_MAX)

// template<class P1, class P2>
// class Del::Const<P1,P2>
// {
// public:
// 
// 	Del::Const(const P1& _p1, const P2& _p2)
// 		:p1(_p1)
// 		,p1(_p1){}
// 
// 		P1 p1;
// 		P2 p2;
// };
template<REPEAT_JOIN_N_1(class P, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)>
class Const<REPEAT_JOIN_N_1(P, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)>
{
public:

	Const(REPEAT_JOIN_N_2(const P, AV_XN, &_p, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)):
		REPEAT_JOIN_N_3(p, AV_XN, _p, AV_EARL_XN, , AV_EAR_R, AV_COMA_DELEGATE, AV_NUM_ARGS){}

	REPEAT_JOIN_N_2(typedef P, AV_XN, TypeP, AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS);

	REPEAT_JOIN_N_2(P, AV_XN, p, AV_XN, AV_DOTCOMA_DELEGATE, AV_NUM_ARGS);
};

#	endif// (AV_NUM_ARGS != 0) && (AV_NUM_ARGS<NUM_ARGS_MAX)

}


namespace DelegateW_NS
{

//-------------------------------------------------------
#	if AV_NUM_ARGS == 0
template<class TCallData, class TConstData, class THP>
class SelArg<AV_NUM_ARGS, TCallData, TConstData, THP>
{
public:
	static THP RetVal(const TCallData& d, TConstData& c, THP r){ return r; };
};


template<class TDelProc, int A0 = 0, AV_TYPE_INT_AN_EQN_MAX>
class SigMap_Selector
{
public:

	typedef typename AVInternal_NS::IsVoid<typename InfoDelproc<TDelProc>::TRetType,
		Del::Map<0, A0, AV_AN_MAX_DEC>,
		Del::Map<A0, AV_AN_MAX> >::Res Res;
};


# else

template<class TCallData, class TConstData, class THP>
class SelArg<AV_NUM_ARGS, TCallData, TConstData, THP>
{
public:
	static THP Val(const TCallData& d, TConstData& c){ return (JOIN_XY(d.p, AV_NUM_ARGS)); };
	static THP RetVal(const TCallData& d, TConstData& c, THP r){ return (JOIN_XY(d.p, AV_NUM_ARGS)); };
};

template<class TCallData, class TConstData, class THP>
class SelArg<-AV_NUM_ARGS, TCallData, TConstData, THP>
{
public:
	static THP Val(const TCallData& d, TConstData& c){ return (JOIN_XY(c.p, AV_NUM_ARGS)); };
	static THP RetVal(const TCallData& d, TConstData& c, THP r){ return (JOIN_XY(c.p, AV_NUM_ARGS)); };
};
#	endif// AV_NUM_ARGS != 0
//-------------------------------------------------------

#	if AV_NUM_ARGS != 0

template<class TCallData, class TConstData>
struct SelArgType<AV_NUM_ARGS, TCallData, TConstData>
{
	typedef typename JOIN_XY(TCallData::TypePX, AV_NUM_ARGS) Res;
};

template<class TCallData, class TConstData>
struct SelArgType<-AV_NUM_ARGS, TCallData, TConstData>
{
	typedef typename JOIN_XY(TConstData::TypeP, AV_NUM_ARGS) Res;
};

#	endif// AV_NUM_ARGS != 0


#	if AV_NUM_ARGS == 0

template<class TCallData, class TConstData>
class SelArgX<AV_NUM_ARGS, TCallData, TConstData>
{
public:
	template<class TCallXMembers, class TRet>
	static typename AVInternal_NS::NoRefType<TRet>::Type& RetVal(const TCallXMembers* _this, const TCallData& d, TRet& r){ return r; };
};

# else

template<class TCallData, class TConstData>
class SelArgX<AV_NUM_ARGS, TCallData, TConstData>
{
public:
	typedef typename JOIN_XY(TCallData::TypePX, AV_NUM_ARGS) ParamType;

	template<class TCallXMembers>
	static typename AVInternal_NS::NoRefType<ParamType>::Type& Val(const TCallXMembers* _this, const TCallData& d){ return (JOIN_XY(d.p, AV_NUM_ARGS)); };

	template<class TCallXMembers, class TRet>
	static typename AVInternal_NS::NoRefType<ParamType>::Type& RetVal(const TCallXMembers* _this, const TCallData& d, TRet& r){ return (JOIN_XY(d.p, AV_NUM_ARGS)); };
};

template<class TCallData, class TConstData>
class SelArgX<-AV_NUM_ARGS, TCallData, TConstData>
{
public:
	typedef typename JOIN_XY(TConstData::TypeP, AV_NUM_ARGS) ConstType;

	template<class TCallXMembers>
	static typename AVInternal_NS::NoRefType<ConstType>::Type Val(const TCallXMembers* _this, const TCallData& d){ return (JOIN_XY(_this->call_const.p, AV_NUM_ARGS)); };

	template<class TCallXMembers, class TRet>
	static typename AVInternal_NS::NoRefType<ConstType>::Type RetVal(const TCallXMembers* _this, const TCallData& d, TRet& r){ return (JOIN_XY(_this->call_const.p, AV_NUM_ARGS)); };
};

#	endif// AV_NUM_ARGS != 0

//-------------------------------------------------------

// template<class TRet, class PX1, class PX2>
// struct CallParamsDel<TRet(PX1, PX2)>
// {
// 	typedef typename AVInternal_NS::NoRefType<PX1>::Type& TypePX1;
// 	typedef typename AVInternal_NS::NoRefType<PX2>::Type& TypePX2;
// 
// 	TypePX1 p1;
// 	TypePX2 p2;
// };
template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
struct CallParamsDel<TRet(AV_TYPES)>
{
	AV_NOREF_TYPES_DECLARE;

	AV_TYPE_PX_DECLARE;
};


// template<class TRet, class PX1, class PX2>
// class InfoDelproc<TRet(PX1, PX2)>
// {
// public:
// 	typedef TRet TRetType;
// 	typedef PX1 TypePX1;
// 	typedef PX2 TypePX2;
// };
template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class InfoDelproc<TRet(AV_TYPES)>
{
public:
	typedef TRet TRetType;
	AV_TYPEDEF_PX_DECLARE;

	typedef TRetType(THandProcType)(AV_TYPES);
	typedef TRetType(THandProcUnifiedType)(AV_TYPES);
};

// template<class TRet, class PX1, class PX2>
// struct CallParamsDeferredDel<TRet(PX1, PX2)>
// {
// 	CallParamsDeferredDel(const CallParamsDel<TRet(PX1, PX2)>& params):
// 		p1(params.p1), p2(params.p2) {}
// 
// 	typename AVInternal_NS::NoRefType<PX1>::Type p1;
// 	typename AVInternal_NS::NoRefType<PX2>::Type p2;
// };
template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
struct CallParamsDeferredDel<TRet(AV_TYPES)>
{
	CallParamsDeferredDel(const CallParamsDel<TRet(AV_TYPES)>& params) DOUBLE_DOT_IF_ARGS AV_PARAMS_INIT{};

	operator CallParamsDel<TRet(AV_TYPES)> ()
	{
		CallParamsDel<TRet(AV_TYPES)> res = {AV_VALUES_P};
		return res;
	}

	AV_NOREF_MEMBERS_DECLARE;
};


// template<class THandCls, class TRet, class PX1, class PX2>
// class InfoHandproc<TRet(THandCls::*)(PX1, PX2)>
// {
// public:
// 	typedef TRet TRetType;
// 	typedef PX1 TypePX1;
// 	typedef PX2 TypePX2;
// 
// 	typedef THandCls THandClsType;
// 	typedef TRetType(THandCls::*THandProcType)(PX1, PX2);
// };
template<class THandCls, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class InfoHandproc<TRet(THandCls::*)(AV_TYPES)>
{
public:
	typedef TRet TRetType;
	AV_TYPEDEF_PX_DECLARE;
	
	typedef THandCls THandClsType;
	typedef TRetType(THandCls::*THandProcType)(AV_TYPES);
	typedef TRetType(THandCls::*THandProcUnifiedType)(AV_TYPES);
};

template<class THandCls, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class InfoHandproc<TRet(THandCls::*)(AV_TYPES) const>
{
public:
	typedef TRet TRetType;
	AV_TYPEDEF_PX_DECLARE;

	typedef THandCls THandClsType;
	typedef TRetType(THandCls::*THandProcType)(AV_TYPES) const;
	typedef TRetType(THandCls::*THandProcUnifiedType)(AV_TYPES);
};



#ifndef _WIN32_WCE
#ifndef __llvm__
#ifndef __GNUC__

// template<class THandCls, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
// class InfoHandproc<TRet(__stdcall THandCls::*)(AV_TYPES)>
// {
// public:
// 	typedef TRet TRetType;
// 	AV_TYPEDEF_PX_DECLARE;
// 
// 	typedef THandCls THandClsType;
// 	typedef TRetType(__stdcall THandCls::*THandProcType)(AV_TYPES);
// 	typedef TRetType(THandCls::*THandProcUnifiedType)(AV_TYPES);
// };
// 
// template<class THandCls, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
// class InfoHandproc<TRet(__stdcall THandCls::*)(AV_TYPES)const>
// {
// public:
// 	typedef TRet TRetType;
// 	AV_TYPEDEF_PX_DECLARE;
// 
// 	typedef THandCls THandClsType;
// 	typedef TRetType(__stdcall THandCls::*THandProcType)(AV_TYPES)const;
// 	typedef TRetType(THandCls::*THandProcUnifiedType)(AV_TYPES);
// };
// 
// template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
// class InfoHandproc<TRet(__stdcall *)(AV_TYPES)>
// {
// public:
// 	typedef TRet TRetType;
// 	AV_TYPEDEF_PX_DECLARE;
// 
// 	typedef TRetType(*THandProcType)(AV_TYPES);
// 	typedef TRetType(*THandProcUnifiedType)(AV_TYPES);
// };


#endif
#endif
#endif



template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class InfoHandproc<TRet(__cdecl *)(AV_TYPES)>
{
public:
	typedef TRet TRetType;
	AV_TYPEDEF_PX_DECLARE;

	typedef TRetType(*THandProcType)(AV_TYPES);
	typedef TRetType(*THandProcUnifiedType)(AV_TYPES);
};


//-------------------------------------------------------

template<class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class DelBase<TRet(AV_TYPES)>
{
protected:

	typedef TRet(TDelProc)(AV_TYPES);

	OPtr<CallBase<TDelProc> > m_call;

	typedef CallBase<TDelProc> TCallBaseType;
	//	typedef typename TDelProc TDelProcType;

	template<typename, template<class> class>
	friend class ::DelegateW;

public:

	typename InfoDelproc<TDelProc>::TRetType operator()(AV_DELPROC_TYPE_PX_DECLARE) const
	{
		CallParamsDel<TDelProc> data = {AV_VALUES};
		if( m_call )
			return m_call->Invoke(data);
 		return AVInternal_NS::ReturnNullIfRef<typename InfoDelproc<TDelProc>::TRetType>();
	}
};

template<AV_TMPLATE_PARAMS_TP>
class DelBase<void(AV_TYPES)>
{
protected:

	typedef void(TDelProc)(AV_TYPES);

	OPtr<CallBase<TDelProc> > m_call;

	typedef CallBase<TDelProc> TCallBaseType;
	//	typedef typename TDelProc TDelProcType;

	template<typename, template<class> class>
	friend class ::DelegateW;

public:

	void operator()(AV_DELPROC_TYPE_PX_DECLARE) const
	{
		CallParamsDel<TDelProc> data = {AV_VALUES};
		if( m_call )
			m_call->Invoke(data);
	}
};

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------


template<class THandRet, class THandCls COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidNo<THandRet(THandCls::*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataMember<THandProc, THandPtr, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return m.hand_ptr;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoHandPtr<THandPtr>::THandClsType> life_time(m.hand_ptr);

			if( life_time )
			{		    
				AV_PARAMS_LOCK_DECLARE;
				bool params_norm = AV_PARAMS_LOCK_CHECK;
				if( params_norm )
				{
					typename InfoHandproc<THandProc>::TRetType ret = (life_time->*(m.hand_proc))(AV_VALUES_P);
					return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(&m, data, ret);
				}
			}

			typename InfoHandproc<THandProc>::TRetType ret = AVInternal_NS::ReturnNullIfRef<typename InfoDelproc<TDelProc>::TRetType>();
			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(&m, data, ret);
		}

	public:

		ImplBase(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const):m(hand_proc, hand_ptr, call_const)
		{
		}

	};

};

template<class THandRet, class THandCls COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidDel<THandRet(THandCls::*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataMember<THandProc, THandPtr, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return m.hand_ptr;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoHandPtr<THandPtr>::THandClsType> life_time(m.hand_ptr);

			if( life_time )
			{
				AV_PARAMS_LOCK_DECLARE;
				bool params_norm = AV_PARAMS_LOCK_CHECK;
				if( params_norm )
					(life_time->*(m.hand_proc))(AV_VALUES_P);
			}
		}

	public:

		ImplBase(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const):m(hand_proc, hand_ptr, call_const)
		{
		}

	};

};


template<class THandRet, class THandCls COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidHand<THandRet(THandCls::*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataMember<THandProc, THandPtr, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return m.hand_ptr;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoHandPtr<THandPtr>::THandClsType> life_time(m.hand_ptr);

			if( life_time )
			{
				AV_PARAMS_LOCK_DECLARE;
				bool params_norm = AV_PARAMS_LOCK_CHECK;
				if( params_norm )
					(life_time->*(m.hand_proc))(AV_VALUES_P);
			}

			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::Val(&m, data);
		}

	public:

		ImplBase(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const):m(hand_proc, hand_ptr, call_const)
		{
		}

	};

};

template<class THandRet, class THandCls COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidAll<THandRet(THandCls::*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataMember<THandProc, THandPtr, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return m.hand_ptr;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoHandPtr<THandPtr>::THandClsType> life_time(m.hand_ptr);

			if( life_time )
			{
				AV_PARAMS_LOCK_DECLARE;
				bool params_norm = AV_PARAMS_LOCK_CHECK;
				if( params_norm )
					(life_time->*(m.hand_proc))(AV_VALUES_P);
			}
		}

	public:


		ImplBase(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const):m(hand_proc, hand_ptr, call_const)
		{
		}

	};

};

//-------------------------------------------------------
//-------------------------------------------------------
template<class THandRet COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidNo<THandRet(*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataStatic<THandProc, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return true;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			AV_PARAMS_LOCK_DECLARE;
			bool params_norm = AV_PARAMS_LOCK_CHECK;
			if( params_norm )
			{
				typename InfoHandproc<THandProc>::TRetType ret =
					(m.hand_proc)(AV_VALUES_P);

				return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(&m, data, ret);
			}

			typename InfoHandproc<THandProc>::TRetType ret = AVInternal_NS::ReturnNullIfRef<typename InfoDelproc<TDelProc>::TRetType>();
			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(&m, data, ret);
		}

	public:

		ImplBase(const THandProc& hand_proc, const TDelConst& call_const):m(hand_proc, call_const)
		{
		}

	};

};


template<class THandRet COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidDel<THandRet(*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataStatic<THandProc, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return true;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			AV_PARAMS_LOCK_DECLARE;
			bool params_norm = AV_PARAMS_LOCK_CHECK;
			if( params_norm )
				(m.hand_proc)(AV_VALUES_P);
		}

	public:

		ImplBase(const THandProc& hand_proc, const TDelConst& call_const):m(hand_proc, call_const)
		{
		}

	};

};


template<class THandRet COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidHand<THandRet(*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataStatic<THandProc, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return true;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			AV_PARAMS_LOCK_DECLARE;
			bool params_norm = AV_PARAMS_LOCK_CHECK;
			if( params_norm )
				(m.hand_proc)(AV_VALUES_P);

			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::Val(&m, data);
		}

	public:

		ImplBase(const THandProc& hand_proc, const TDelConst& call_const):m(hand_proc, call_const)
		{
		}

	};

};

template<class THandRet COMA_IF_ARGS AV_TMPLATE_PARAMS_PHN>
class CallX_RetVoidAll<THandRet(*)(AV_TYPES_PHN)>
{
public:

	template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
	class ImplBase: public CallBase<TDelProc>
	{
	public:

		typedef CallX_DataStatic<THandProc, TDelConst, TStorePtr> DataType;

	private:

		DataType m;

	private:

		bool IsFilled() override
		{
			return true;
		};


		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			AV_PARAMS_LOCK_DECLARE;
			bool params_norm = AV_PARAMS_LOCK_CHECK;
			if( params_norm )
				(m.hand_proc)(AV_VALUES_P);
		}

	public:

		ImplBase(const THandProc& hand_proc, const TDelConst& call_const):m(hand_proc, call_const)
		{
		}

	};

};

//-------------------------------------------------------
//-------------------------------------------------------
template<template<class, template<class> class> class TDelegateDeduce, template<class> class TStorePtr, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class InfoDelegate<TDelegateDeduce<TRet(AV_TYPES), TStorePtr> >
{
public:

	typedef TRet(TDelProcType)(AV_TYPES);
	typedef CallParamsDel<TDelProcType> CallParamsType;
	typedef TRet(CallBase<TDelProcType>::*TInvokeProcType)(CallParamsDel<TDelProcType> const&);
	typedef TRet TRetType;
	typedef CallBase<TDelProcType> THandClsType;

	AV_TYPEDEF_PX_DECLARE;
};

template<template<class, template<class> class> class TDelegateDeduce, template<class> class TStorePtr, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class ImplD_RetVoidNo<TDelegateDeduce<TRet(AV_TYPES), TStorePtr> >
{
public:

	template<class TDelProc, class TDelegate, class TSigMap, class TDelConst>
	class ImplBase: public CallBase<TDelProc>
	{
	private:

		template<int TParam, class TCallData, class TConstData>
		friend class DelegateW_NS::SelArgX;

		OPtr<typename InfoDelegate<TDelegate>::THandClsType> m_hand_ptr;
		TDelConst call_const;

	private:

		bool IsFilled() override
		{
			return m_hand_ptr;
		};

		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoDelegate<TDelegate>::THandClsType> life_time(m_hand_ptr);
			if( life_time )
			{
				AV_DEL_CALL_PARAMS_DECLARE;
				typename InfoDelegate<TDelegate>::CallParamsType invoke_data = {AV_VALUES_P};
				typename InfoDelegate<TDelegate>::TRetType ret = life_time->Invoke(invoke_data);
				return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(this, data, ret);
			}

			typename InfoDelegate<TDelegate>::TRetType ret = AVInternal_NS::ReturnNullIfRef<typename InfoDelegate<TDelegate>::TRetType>();
			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::RetVal(this, data, ret);
		}

	public:

		ImplBase(typename InfoDelegate<TDelegate>::THandClsType* hand_ptr, const TDelConst& call_const_):m_hand_ptr(hand_ptr), call_const(call_const_)
		{
		}
	};
};



template<template<class, template<class> class> class TDelegateDeduce, template<class> class TStorePtr, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class ImplD_RetVoidDel<TDelegateDeduce<TRet(AV_TYPES), TStorePtr> >
{
public:

	template<class TDelProc, class TDelegate, class TSigMap, class TDelConst>
	class ImplBase: public CallBase<TDelProc>
	{
	private:

		template<int TParam, class TCallData, class TConstData>
		friend class DelegateW_NS::SelArgX;

		OPtr<typename InfoDelegate<TDelegate>::THandClsType> m_hand_ptr;
		TDelConst call_const;

	private:

		bool IsFilled() override
		{
			return m_hand_ptr;
		};

		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoDelegate<TDelegate>::THandClsType> life_time(m_hand_ptr);
			if( life_time )
			{
				AV_DEL_CALL_PARAMS_DECLARE;
				typename InfoDelegate<TDelegate>::CallParamsType invoke_data = {AV_VALUES_P};
				life_time->Invoke(invoke_data);
			}

		}

	public:

		ImplBase(typename InfoDelegate<TDelegate>::THandClsType* hand_ptr, const TDelConst& call_const_):m_hand_ptr(hand_ptr), call_const(call_const_)
		{
		}

	};
};


template<template<class, template<class> class> class TDelegateDeduce, template<class> class TStorePtr, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class ImplD_RetVoidHand<TDelegateDeduce<TRet(AV_TYPES), TStorePtr> >
{
public:

	template<class TDelProc, class TDelegate, class TSigMap, class TDelConst>
	class ImplBase: public CallBase<TDelProc>
	{
	private:

		template<int TParam, class TCallData, class TConstData>
		friend class DelegateW_NS::SelArgX;

		OPtr<typename InfoDelegate<TDelegate>::THandClsType> m_hand_ptr;
		TDelConst call_const;

	private:

		bool IsFilled() override
		{
			return m_hand_ptr;
		};

		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoDelegate<TDelegate>::THandClsType> life_time(m_hand_ptr);
			if( life_time )
			{
				AV_DEL_CALL_PARAMS_DECLARE;
				typename InfoDelegate<TDelegate>::CallParamsType invoke_data = {AV_VALUES_P};
				life_time->Invoke(invoke_data);
			}

			return SelArgX<TSigMap::HA0, CallParamsDel<TDelProc>, TDelConst>::Val(this, data);
		}

	public:

		ImplBase(typename InfoDelegate<TDelegate>::THandClsType* hand_ptr, const TDelConst& call_const_):m_hand_ptr(hand_ptr), call_const(call_const_)
		{
		}

	};

};


template<template<class, template<class> class> class TDelegateDeduce, template<class> class TStorePtr, class TRet COMA_IF_ARGS AV_TMPLATE_PARAMS_TP>
class ImplD_RetVoidAll<TDelegateDeduce<TRet(AV_TYPES), TStorePtr> >
{
public:

	template<class TDelProc, class TDelegate, class TSigMap, class TDelConst>
	class ImplBase: public CallBase<TDelProc>
	{
	private:

		template<int TParam, class TCallData, class TConstData>
		friend class DelegateW_NS::SelArgX;

		OPtr<typename InfoDelegate<TDelegate>::THandClsType> m_hand_ptr;
		TDelConst call_const;

	private:

		bool IsFilled() override
		{
			return m_hand_ptr;
		};

		typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
		{
			OPtr<typename InfoDelegate<TDelegate>::THandClsType> life_time(m_hand_ptr);
			if( life_time )
			{
				AV_DEL_CALL_PARAMS_DECLARE;
				typename InfoDelegate<TDelegate>::CallParamsType invoke_data = {AV_VALUES_P};
				life_time->Invoke(invoke_data);
			}

		}

	public:

		ImplBase(typename InfoDelegate<TDelegate>::THandClsType* hand_ptr, const TDelConst& call_const_):m_hand_ptr(hand_ptr), call_const(call_const_)
		{
		}
	};

};

//-------------------------------------------------------
//-------------------------------------------------------


}// namespace DelegateW_NS

#undef AV_PROC_PARAMS
#undef AV_TYPES
#undef AV_TYPE_PX_DECLARE
#undef AV_TYPEDEF_PX_DECLARE
#undef AV_NOREF_TYPES_DECLARE
#undef AV_NOREF_MEMBERS_DECLARE
#undef AV_PARAMS_INIT
#undef AV_PARAMS_CONST_REF
#undef AV_PARAMS_CALL_SELECT_DEL
#undef AV_PARAMS_LOCK_DECLARE
#undef AV_PARAMS_LOCK_CHECK
#undef AV_VALUES
#undef AV_DELPROC_TYPE_PX_DECLARE
#undef AV_VALUES_P
#undef AV_DEL_CALL_PARAMS_DECLARE

#undef AV_NUM_ARGS
#undef COMA_IF_ARGS
#undef DOUBLE_DOT_IF_ARGS