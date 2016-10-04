#pragma once


//-------------------------------------------------------
// LogMsg

#ifdef _DEBUG
#if defined(AV_CHECK_POINT_NO_FILE)
#define AV_CHECK_POINT_FILE NULL
#define AV_CHECK_POINT_LINE 0
#else
#define AV_CHECK_POINT_FILE __FILE__
#define AV_CHECK_POINT_LINE __LINE__
#endif
#define check_point AVLogMsg(AV_CHECK_POINT_FILE, AV_CHECK_POINT_LINE, __FUNCTION__)
#define check_point_manual(file,line) AVLogMsg(file, line, __FUNCTION__)
#else					  
#ifdef DEBUG_POINT_IN_RELEASE
#define check_point AVLogMsg(__FILE__, __LINE__, __FUNCTION__)
#define check_point_manual(file,line) AVLogMsg(file, line, __FUNCTION__)
#else					  
#define check_point 
#define check_point_manual(file,line)
#endif// DEBUG_POINT_IN_RELEASE
#endif// _DEBUG

#ifdef _DEBUG
#define time_point(point_name) TimePoint time_point_latent_name(__FILE__, __LINE__,__FUNCTION__); time_point_latent_name(#point_name)
#else					  
#ifdef DEBUG_POINT_IN_RELEASE
#define time_point(point_name) TimePoint time_point_latent_name(__FILE__, __LINE__,__FUNCTION__); time_point_latent_name(#point_name)
#else					  
#define time_point
#endif// DEBUG_POINT_IN_RELEASE
#endif// _DEBUG

//-------------------------------------------------------

#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define STATIC_ASSERT( x_true_ok, msg ) typedef char __STATIC_ASSERT__[( x_true_ok )?1:-1];

#define SAFE_ASSIGN(pointer_to,value_from) {if(pointer_to!=NULL){*pointer_to=value_from;}}
#define DELETE_IF_NOT_NULL (pointer) {if(pointer){delete pointer; pointer=NULL;}}

#define AV_NO_COPYABLE_DECLARE(ClassName)\
ClassName(ClassName const&) = delete;\
ClassName& operator=(ClassName const&) = delete;

//-------------------------------------------------------

#define assert_if_equal_msg(x1,x2,msg_a)		{ if( (x1) == (x2) ) { av_assert(msg_a ); } }
#define assert_if_not_equal_msg(x1,x2,msg_a)	{ if( (x1) != (x2) ) { av_assert(msg_a ); } }

#define assert_if_equal(x1,x2)						{ if( (x1) == (x2) ) { av_assert(#x1" EQUAL "#x2 ); } }
#define assert_if_not_equal(x1,x2)					{ if( (x1) != (x2) ) { av_assert(#x1" NOT EQUAL "#x2 ); } }

#define return_if_equal(x1,x2)						{ if( (x1) == (x2) ) { av_assert(#x1" EQUAL "#x2 );		return; } }
#define return_if_not_equal(x1,x2)					{ if( (x1) != (x2) ) { av_assert(#x1" NOT EQUAL "#x2 );	return; } }
#define return_if_not_equal_msg(x1,x2,msg_a)		{ if( (x1) != (x2) ) { av_assert(msg_a ); 				return; } }
#define return_if_equal_msg(x1,x2,msg_a)			{ if( (x1) == (x2) ) { av_assert(msg_a ); 				return; } }
#define return_x_if_not_equal(x1,x2,x)				{ if( (x1) != (x2) ) { av_assert(#x1" NOT EQUAL "#x2 );	return x; } }
#define return_x_if_equal(x1,x2,x)					{ if( (x1) == (x2) ) { av_assert(#x1" EQUAL "#x2 );		return x; } }
#define return_x_if_not_equal_msg(x1,x2,x,msg_a)	{ if( (x1) != (x2) ) { av_assert(msg_a ); 				return x; } }
#define return_x_if_equal_msg(x1,x2,x,msg_a)		{ if( (x1) == (x2) ) { av_assert(msg_a ); 				return x; } }


#define return_if_equal_final(x1,x2,finalize)					{ if( (x1) == (x2) ) { av_assert(#x1" EQUAL "#x2 );		{finalize} return; } }
#define return_if_not_equal_final(x1,x2,finalize)				{ if( (x1) != (x2) ) { av_assert(#x1" NOT EQUAL "#x2 );	{finalize} return; } }
#define return_if_not_equal_msg_final(x1,x2,msg_a,finalize)		{ if( (x1) != (x2) ) { av_assert(msg_a ); 				{finalize} return; } }
#define return_if_equal_msg_final(x1,x2,msg_a,finalize)			{ if( (x1) == (x2) ) { av_assert(msg_a ); 				{finalize} return; } }
#define return_x_if_not_equal_final(x1,x2,x,finalize)			{ if( (x1) != (x2) ) { av_assert(#x1" NOT EQUAL "#x2 );	{finalize} return x; } }
#define return_x_if_equal_final(x1,x2,x,finalize)				{ if( (x1) == (x2) ) { av_assert(#x1" EQUAL "#x2 );		{finalize} return x; } }
#define return_x_if_not_equal_msg_final(x1,x2,x,msg_a,finalize)	{ if( (x1) != (x2) ) { av_assert(msg_a ); 				{finalize} return x; } }
#define return_x_if_equal_msg_final(x1,x2,x,msg_a,finalize)		{ if( (x1) == (x2) ) { av_assert(msg_a ); 				{finalize} return x; } }

#define return_if_null(x)			return_if_equal(x,NULL)
#define assert_ok( x )				assert_if_not_equal(S_OK,x)


#define av_assert_msg(hr,msg_a) { if(ErrorPool::Raise(__FILE__,__LINE__,__FUNCTION__)) {/*AssertProc(msg_a,__FILE__,__LINE__,__FUNCTION__);*/ } }
#define av_assert( hr )	{ if(ErrorPool::Raise(__FILE__,__LINE__,__FUNCTION__)) {/*AssertProc(msg_a,__FILE__,__LINE__,__FUNCTION__);*/ } }


#define return_msg(msg_a)			{ av_assert_msg( msg_a ); return; }
#define continue_x()				{ av_assert(); continue; }
#define return_x( x )				{ av_assert(); return x; }

//-------------------------------------------------------

#define AV_BIT_SET(var, bit_shift_number)     (var | (1 << bit_shift_number))
#define AV_BIT_CLEAR(var, bit_shift_number)   (var &( ~(1 << bit_shift_number)))
#define AV_BIT_SET_VAL(var, bit_shift_number, bool_val)     (bool_val?AV_BIT_SET(var, bit_shift_number):AV_BIT_CLEAR(var, bit_shift_number))
#define AV_BIT_GET(var, bit_shift_number)     (((var >> bit_shift_number)&1)!=0)
#define AV_BIT(bit_shift_number)     (1 << bit_shift_number)
#define AV_MASK_SET_VAL(var,actual_bits_mask,new_val) ((var & (~actual_bits_mask)) | new_val)
