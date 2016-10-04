#pragma once
//-------------------------------------------------------

// ¬ макрос нужно передавать 
// AV_COMA_DELEGATE или AV_DOTCOMA_DELEGATE
// _SEPAR допишетс€ внутри
#define	AV_COMA_DELEGATE_SEPAR ,
#define	AV_DOTCOMA_DELEGATE_SEPAR ;
#define	AV_SS_DELEGATE_SEPAR &&
#define AV_EMPTY_SEPAR

#define AV_COMA2_LATE ,
#define AV_COMA ,
#define AV_COMA2 JOIN(AV_COMA2_LATE,)

#define JOIN(x,y) x##y
#define JOIN_XY(x,y) JOIN(x,y)

#define AV_XN(p1,p2) p1##p2
#define AV_COMA_XN(p1,p2) ,p1##p2
#define AV_X(p1,p2) p1
#define AV_COMA_X(p1,p2) ,p1
#define AV_EQU_X(p1,p2) =p1
#define AV_X_EQU_N(p1,p2) p1=p2
//#define AV_X_EQUEQU_N(p1,p2) p1==p2
#define AV_EQU_XN(p1,p2) =p1##p2
#define AV_EARL_XN(p1,p2) (p1##p2
#define AV_EARL_XN_EARR(p1,p2) (p1##p2)
//#define AV_EAR_L(p1,p2) (
#define AV_EAR_R(p1,p2) )
//#define EQU_EQUE_XN_ARR_(p1,p2) ==p1##p2)
//#define X_EQU_EARL_(p1,p2) p1=(

#define REPEAT_N(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ,count)REPEAT_ ## count (macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ)

#define REPEAT_0(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) 
#define REPEAT_1(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,1)
#define REPEAT_2(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_1(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,2)
#define REPEAT_3(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_2(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,3)
#define REPEAT_4(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_3(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,4)
#define REPEAT_5(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_4(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,5)
#define REPEAT_6(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_5(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,6)
#define REPEAT_7(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_6(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,7)
#define REPEAT_8(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8, separ) REPEAT_7(macro,p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,separ) separ##_SEPAR macro(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,p8,j8,8)

#define REPEAT_SIMPLE(p1,stub1,stub2,n) p1
#define JOIN_N_1(p1,j1,d1,d2,d3,d4,d5,d6,d7,d8,d9,dA,dB,dC,dD,dE,n) j1(p1,n)
#define JOIN_N_2(p1,j1,p2,j2,d1,d2,d3,d4,d5,d6,d7,d8,d9,dA,dB,dC,n) j1(p1,n) j2(p2,n)
#define JOIN_N_3(p1,j1,p2,j2,p3,j3,d1,d2,d3,d4,d5,d6,d7,d8,d9,dA,n) j1(p1,n) j2(p2,n) j3(p3,n)
#define JOIN_N_4(p1,j1,p2,j2,p3,j3,p4,j4,d1,d2,d3,d4,d5,d6,d7,d8,n) j1(p1,n) j2(p2,n) j3(p3,n) j4(p4,n)
#define JOIN_N_5(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,d1,d2,d3,d4,d5,d6,n) j1(p1,n) j2(p2,n) j3(p3,n) j4(p4,n) j5(p5,n)
#define JOIN_N_6(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,d1,d2,d3,d4,n) j1(p1,n) j2(p2,n) j3(p3,n) j4(p4,n) j5(p5,n) j6(p6,n)
#define JOIN_N_7(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,d1,d2,n) j1(p1,n) j2(p2,n) j3(p3,n) j4(p4,n) j5(p5,n) j6(p6,n) j7(p7,n)

#define REPEAT_COUNT(p1,separ,count) REPEAT_N(REPEAT_SIMPLE, p1,,, separ, count)

#define REPEAT_JOIN_N_1(p1,j1,separ,count) REPEAT_N( JOIN_N_1 , p1,j1,,,,,,,,,,,,,,, separ, count)
#define REPEAT_JOIN_N_2(p1,j1,p2,j2,separ,count) REPEAT_N(JOIN_N_2, p1,j1, p2,j2,,,,,,,,,,,,, separ, count)
#define REPEAT_JOIN_N_3(p1,j1,p2,j2,p3,j3,separ,count) REPEAT_N(JOIN_N_3, p1,j1,p2,j2,p3,j3,,,,,,,,,,, separ, count)
#define REPEAT_JOIN_N_4(p1,j1,p2,j2,p3,j3,p4,j4,separ,count) REPEAT_N(JOIN_N_4, p1,j1,p2,j2,p3,j3,p4,j4,,,,,,,,, separ, count)
#define REPEAT_JOIN_N_5(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,separ,count) REPEAT_N(JOIN_N_5, p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,,,,,,, separ, count)
#define REPEAT_JOIN_N_6(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,separ,count) REPEAT_N(JOIN_N_6, p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,,,,, separ, count)
#define REPEAT_JOIN_N_7(p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,separ,count) REPEAT_N(JOIN_N_7, p1,j1,p2,j2,p3,j3,p4,j4,p5,j5,p6,j6,p7,j7,,, separ, count)

#define NUM_ARGS_MAX 8
#define NUM_ARGS_MAX_DECREMENT 7

//-------------------------------------------------------
