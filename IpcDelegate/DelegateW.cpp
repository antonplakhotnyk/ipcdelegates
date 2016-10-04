#include "stdafx.h"
#include "DelegateW.h"

namespace DelegateW_NS
{

void CheckThisCall(bool this_call)
{
	assert_if_equal(this_call, true);
}


}