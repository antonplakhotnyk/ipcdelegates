#ifndef AV_NUM_ARGS 
#error this class can be included only intentionally it expect defined AV_NUM_ARGS
#endif

// _p1 , _p2
#define	AV_VALUES_P REPEAT_JOIN_N_1(_p,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// const PX1 &_p1 , const PX2 &_p2
#define AV_PARAMS_CONST_REF REPEAT_JOIN_N_2(const PX, AV_XN, &_p, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// class PX1 , class PX2
#define	AV_TMPLATE_PARAMS_TP REPEAT_JOIN_N_1(class PX,AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)


template<AV_TMPLATE_PARAMS_TP>
AV_CLS(AV_PARAMS_CONST_REF): AV_T_BASE(AV_VALUES_P)
{
}

#undef AV_VALUES_P
#undef AV_PARAMS_CONST_REF
#undef AV_TMPLATE_PARAMS_TP


#undef AV_NUM_ARGS
