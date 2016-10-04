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
#define	TYPES REPEAT_JOIN_N_1(TP,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 , TP2 , TP3 , TP4
#define	ARGS REPEAT_JOIN_N_1(tp,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // tp1 , tp2 , tp3 , tp4
#define PARAMS REPEAT_JOIN_N_2(TP,AV_XN, tp, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS) // TP1 tp1 , TP2 tp2 , TP3 tp3 , TP4 tp4
#define ASYNC_RETVAL_N JOIN_XY(ASYNC_RETVAL_, AV_NUM_ARGS) // ASYNC_RETVAL_4



#if AV_NUM_ARGS>0

template<TMPLATE_PARAMS>
ASYNC_RETVAL_N<TYPES> operator ()(PARAMS)
{
	return ASYNC_RETVAL_N<TYPES>(*this COMA ARGS);
}

template<TMPLATE_PARAMS>
friend class ASYNC_RETVAL_N;

#else

ASYNC_RETVAL_N operator ()(PARAMS)
{
	return ASYNC_RETVAL_N(*this COMA ARGS);
}

friend class ASYNC_RETVAL_N;

#endif


#undef AV_NUM_ARGS
#undef TMPLATE_PARAMS_SKIP
#undef COMA
#undef TMPLATE_PARAMS
#undef TYPES
#undef ARGS
#undef PARAMS
#undef ASYNC_RETVAL_N
