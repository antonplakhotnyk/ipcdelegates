#pragma once

// virutal AVObject::Uninit() �����
//		������������� ����������
//		� ������ ������ ����� ��������� ����� � ��� �������� ����� (�������� ��� �� ��������)
//
// AVObject::AddChild(AVObject* child)
// AVObject::RemoveChild(AVObject* child)
//		��������� ������� ������� � ������ � ����������� ���������� ������ ��� ��������� ������� �����
//
// AVObject::SubscribeDelete(AVObject* handler)
// AVObject::UnsubscribeDelete(AVObject* handler)
//		����������� � ���������� ������ handler �� ����������� �� �������� ������� this 
//		������ ������� ���������� ������������ ��� ������� �������, ���������� �������� ������. 
//
// virtual AVObject::OnDelete(void* destroyed);
//		����������� �� �������� ������� destroyed. ������� �� ����� ������� AVObject
//		������� �� ������ ����������� � �������� ��������, � � ���� ������ �������,
//		��� ����� ������ ���������� � AVObject* ��� ���� ����� ��������� �������������� �� 
//		����������� ����� ������ (�.�. � ����� �������� ��������� �� ���� ��������� ����� �������)
//
// ������� ������
//		AVRefCounter
//		AVDeleteNotify
//		ChildrenStorage
//		Uninit
//		Cleaner
//
// * ����������� (Handlers)
//
// Cleaner::Cleaner(AVObject* parent, Template& cleaned);
//		� �������� �������� ������� ������ cleaned ���� cleaned=Template();
//
// ��������� �� ����������� �������� � ��������� ��� ��� �������� ������ �� ���������, 
//		�� ����� ��������� � � ��������� ������.
//		
// �������� ������������ ����������� �� �������� �����������, ������ ��������� �� �����������
//
// * ��������� � ������� ������.
//
// SmartPtr
//		����� ��� �� ���. 
//			* ��������������� (��������� �������� ������ ������ ����������)
//			* ����������� (�� ������� ��������� - ��������)
//			* �������� ��� ������������� (����������� ������� ������ ����������, delete on demand)
//		������������� ������� ���� ����������
//			�������� �� ��� ����� ���������� ���� � �������� ��������������� �������� 
//			������������� ������� ���� ��� ��������� �� ��������� ������ (��������� ����������� ��������).
//			�� ���, �.�. � �������� �������� ����� �������� ���� ����������� ���� ���������������. 
//			��� ����� ����� ���������, �� ������� ��������� ��������� ���������, 
//			�������� ��������� ������ ������� ��������. �� ����� ������� ������� ������ ��.
//			��� ���������� ������ ������ ����������� � ������ �++ �.�. ����� ������ ����������
//			��� ������� ���������� ������ �� ��������� ������.
//		���������� � �������� �������� � ��� ����� ���������� ����������� ��������� �� ������ �� ��������� ������.
//			��� ������ �� ������� �.�. ���� ������� �������� ��������� �� ������ �� ��������� ������
//			� ���������� ������ ����� ���������� ������ ���� ���� ����� ������ �����������.
//		
// ��������
//		* ������� ������ ���� �������
//			��������� �����������
//			��������� ��� weak-ptr
//			������� ������ (���������� delete)
//		* ��������������� �������� (������� ��������� �������� ������ supper-owner ���� �������)
//			������� ������������� ���� "���������" ���������� ������ �� ��������� ������ (����������)
//			� ������ ���� ����� �������� "���������" ������� ������ �� ������ ���� - �������� ������ ��������
//			������� �� ���� �������� ���-������ ��� � ��������� ������� ����������� ������.
//
// ������� ����� � ��������� ������, �������� �� �������� ������ � �������������
//
// DPtr - Data Pointer
//		������ ��������� �� ������� ��� ������ � ��������� �� ���������� ����������� AVObject
//		* ������ ����� ������� ������ ������������ ��������� � ��������� ������ �.�.
//		����������� ������ ����� �� ��������������.
//		* �� ��������� ������� ����������� �� ��������
//		* ����� ���������� � ������ ������.
//
// WPtrNotify - Weak Pointer
//		��������� ��� �������� ������
//
// OPtr - Owner Pointer
//		��������� ������������� ���������� ������
//
// WOPtr - Weak Owner Pointer
//		��������� ������������� ������� ������, 
//		������������� ���������� ��� �������� ������� �� ���������� ���� ���������� ������ ������� ������
//		�������� �������� � ���� �����������.
//
// SOPtr - Supper Owner Pointer
//		��������� ������������� ������� ������ ����� �������� (��������) ������
//		��������� �������������� ��������� ���������� �������� ������, �� ��������� ��������
//		���������� Uninit � ������ ������� � ����� ����������� ������ ���, 
//		���� ��������� ��� ������
//
// NPtr - Notify Pointer
//		* ����������� ��������� ��������� ������� ������������� ����������� � ���������� 
//		���� ������ �� ����������� �� �������� �������. � �������� ������� ������������� ������ ����� ���������
//		* ��� ��������� OPtr ������� � ������� ������ SubscribeDelete/UnsubscribeDelete 
//		* ���������� ����������� �������� ��� ���������� �������� ������ (weak-ptr)
//			�.�. ��� ������ ����� ����������� �� ����������� ���� ��� ������� ������
//		��� �����������:
//		NPtr <- NPtr ������ ����� �������� ����������� � ����������
//			���������� ����������� ���������� �� ONPtr � ONPtr (������)
//		NPtr <- Ptr ������ ������ �������� ���������� � ����� (Ptr) �����������.
//			�� ������� (�� NPtr) � NPtr ���������� ����������� ��� �������������� � NPtr 
//			������������� �� ����������� �� ������� (�� NPtr).
//
// ���� ��������� �������� ������������ ������, � ������� ������������ ������.
//		��������� ������� ������ - ��������� ����� ������ ������������ (weak-ptr)
//		������ ��������� ����� �������� ��������� �������� ������ (owner-count).
//		������� ����� ���� ������� ������ �����.

//-------------------------------------------------------

#include "AVWeakBase.h"
#include "AVRefCounter.h"
#include "AVNotifyBase.h"

#define AVBaseObject AVObject
#define AVBaseWeak AVNotifyWeakBase
#define AVBaseStrong AVRefCounter

class AVObject: public AVNotifyWeakBase, public AVRefCounter
{
protected:

	void OnSelfZeroRef() const override
	{
		AVNotifyWeakBase::Process_OnSelfZeroRef(&m_notifications);
	}

};