

#ifndef AV_NUM_ARGS 
#error AV_NUM_ARGS must be defined as parameter for include
#endif


// class PX1 , class PX2
#define	AV_TMPLATE_PARAMS_TP REPEAT_JOIN_N_1(class PX,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// const PX1 &tp1 , const PX2 &tp2
#define AV_PARAMS_CONST_REF REPEAT_JOIN_N_2(const PX, AV_XN, &tp, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// PX1, PX2
#define	AV_TYPES REPEAT_JOIN_N_1(PX,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// tp1, tp2
#define	AV_VALUES REPEAT_JOIN_N_1(tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

#if AV_NUM_ARGS == 0
#  define COMA_IF_ARGS
#else
#  define COMA_IF_ARGS ,
#endif


template<AV_TMPLATE_PARAMS_TP COMA_IF_ARGS class TProc, class TCls>
void DeferredCall(const TProc& proc, const TCls& cls COMA_IF_ARGS AV_PARAMS_CONST_REF)
{
	DelegateW<void(AV_TYPES)> call;
	call.BindE(proc, cls);
	call(AV_VALUES);
}


template<AV_TMPLATE_PARAMS_TP COMA_IF_ARGS class TProc>
void DeferredCallS(const TProc& proc COMA_IF_ARGS AV_PARAMS_CONST_REF)
{
	DelegateW<void(AV_TYPES)> call;
	call.BindES(proc);
	call(AV_VALUES);
}

#undef AV_TMPLATE_PARAMS_TP
#undef AV_PARAMS_CONST_REF
#undef AV_TYPES
#undef AV_VALUES

#undef AV_NUM_ARGS
#undef COMA_IF_ARGS
