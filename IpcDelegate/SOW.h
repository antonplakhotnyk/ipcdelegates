#pragma once

#include "AVPreprocessorRepeatJoin.h"

template<typename TCls>
class SOW: public AVBaseWeak, public TCls
{
public:

	SOW()
	{
	}

#define AV_NUM_ARGS 1
#include "SOW_N.h"
#define AV_NUM_ARGS 2
#include "SOW_N.h"
#define AV_NUM_ARGS 3
#include "SOW_N.h"
#define AV_NUM_ARGS 4
#include "SOW_N.h"
#define AV_NUM_ARGS 5
#include "SOW_N.h"
#define AV_NUM_ARGS 6
#include "SOW_N.h"
#define AV_NUM_ARGS 7
#include "SOW_N.h"
#define AV_NUM_ARGS 8
#include "SOW_N.h"

};
