#include "stdafx.h"
#include "AVRefCounter.h"


// ������� ������, �������������� � ������ ����� ������� �
// ��� ������ ����������, ��� ��� ��� ������� ������� ������.
// ��� �� ������ �� �������� � ����������� ����������� ��������� ����� 
// ������������ ������
//
// m_naked_delete_notify ���� ������������, ��� �� ��� � ������� ������.
AVRefCounter::AVRefCounter(const AVRefCounter&):
m_ref_count(0)
{
	// �� �� ����� ��� � � ������� ������������
	//	AddRef();
}

// ������ ������ � ����������� ������������
AVRefCounter& AVRefCounter::operator=(const AVRefCounter&)
{
	return *this;
}

void AVRefCounter::AddRef() const
{
	m_ref_count.ref();
};

void AVRefCounter::Release() const
{
	if( m_ref_count.deref() )
		return;

	{
		m_ref_count.ref();
		OnSelfZeroRef();
		m_ref_count.load();
		const_cast<AVRefCounter*>(this)->Uninit();
		if( m_ref_count.deref() )
			return;
	}

	SelfDelete();
};

void AVRefCounter::SelfDelete() const
{
	// ��� ����� ���� AddRef/Release ��������� � �����������, �� ��������� � ���������� ��������
	m_ref_count.ref();

	// HEAP[]: Invalid Address specified to RtlValidateHeap
	// �������� ������ ��� ������ �� ����� new (�������� � ����� ��� �������� ������)
	// �� ��� ���� ��� ������� � ��������� ������� ������ �������� ��� �������.
	// �� �����������, � ����� ��������� ������ �������� ������ ������� �������
	// ��������� ����� new/delete ��� ��� ����� ��������� ������ ��� ����
	// ����� �������������� ����� ������ ��� ����������.
	//
	// ������ � ���, ��� ����� ������ ����� � ����� ���������, � �� � ��� ���
	// ����� ��������� �������� ��� �������.
	delete this;
}

int AVRefCounter::GetRefCount() const
{
	return m_ref_count.load();
}


void AVRefCounter::AfterAssignAddRefRelease(const AVRefCounter* addref, const AVRefCounter* release)
{
	// � ������ ���������� ������ ����, ��������� �� ������ �����������. ������
	// ������� ����������� ����� ���������, � ������ ����� ���������� ������
	if( addref )
		addref->AddRef();
	if( release )
		release->Release();
}

