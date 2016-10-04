
// int A1 , int A2
#define AV_TYPE_INT_AN REPEAT_JOIN_N_1(int A, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)

// A1 , A2
#define AV_AN REPEAT_JOIN_N_1(A, AV_XN, AV_COMA_DELEGATE, AV_NUM_ARGS)




#if AV_NUM_ARGS == 0
#  define COMA_IF_ARGS
#  define DOUBLE_DOT_IF_ARGS
#else
#  define COMA_IF_ARGS ,
#  define DOUBLE_DOT_IF_ARGS :
#endif


//-------------------------------------------------------

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& Bind(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const = TDelConst())
{
	return this->Bind<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res>(hand_proc, hand_ptr, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindS(const THandProc& hand_proc, const TDelConst& call_const = TDelConst())
{
	return this->BindS<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res>(hand_proc, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindD(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
{
	return this->BindD<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindD(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del)
{
	return this->BindD<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, Del::Const<DelegateW_NS::DelConstStub>());
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindE(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const = TDelConst())
{
	return this->BindE<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, THandPtr, TDelConst>(hand_proc, hand_ptr, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindES(const THandProc& hand_proc, const TDelConst& call_const = TDelConst())
{
	return this->BindES<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, TDelConst>(hand_proc, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
const DelegateW& BindED(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
{
	return this->BindED<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr>
const DelegateW& BindED(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del)
{
	return this->BindED<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, Del::Const<DelegateW_NS::DelConstStub>());
}

//-------------------------------------------------------

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
{
	return this->BindAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst>
const DelegateW& BindAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const)
{
	return this->BindAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, Del::add_back, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindSAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
{
	return this->BindSAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, TDelConst >(hand_proc, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst>
const DelegateW& BindSAdd(const THandProc& hand_proc, const TDelConst& call_const)
{
	return this->BindSAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, TDelConst >(hand_proc, Del::add_back, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = Del::Const<DelegateW_NS::DelConstStub>() )
{
	return this->BindDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back)
{
	return this->BindDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, add_type, Del::Const<DelegateW_NS::DelConstStub>());
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
{
	return this->BindDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, Del::add_back, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindEAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
{
	return this->BindEAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class THandPtr, class TDelConst>
const DelegateW& BindEAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const)
{
	return this->BindEAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, Del::add_back, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
const DelegateW& BindESAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
{
	return this->BindESAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, TDelConst >(hand_proc, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, class THandProc, class TDelConst>
const DelegateW& BindESAdd(const THandProc& hand_proc, const TDelConst& call_const)
{
	return this->BindESAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, THandProc, TDelConst >(hand_proc, Del::add_back, call_const);
}


template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type, const TDelConst& call_const)
{
	return this->BindEDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, add_type, call_const);
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr >
const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back)
{
	return this->BindEDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, add_type, Del::Const<DelegateW_NS::DelConstStub>());
}

template<int A0 COMA_IF_ARGS AV_TYPE_INT_AN, template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
{
	return this->BindEDAdd<typename DelegateW_NS::SigMap_Selector<TDelProc, A0 COMA_IF_ARGS AV_AN>::Res, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, Del::add_back, call_const);
}

//-------------------------------------------------------

#undef AV_TYPE_INT_AN
#undef AV_AN


#undef AV_NUM_ARGS
#undef COMA_IF_ARGS
#undef DOUBLE_DOT_IF_ARGS