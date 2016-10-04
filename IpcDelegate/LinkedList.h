#pragma once

//-------------------------------------------------------

class LinkedListElement;


template<class TElement>
class LinkedListIterator
{
public:

	LinkedListIterator(TElement* current)
		:m_current(current)
	{
	}

	TElement* operator*()
	{
		return_x_if_equal(m_current,NULL,NULL);
		return m_current;
	}

	LinkedListIterator operator++(int)
	{
		LinkedListIterator tmp = *this;
		if(m_current!=NULL)
			m_current=static_cast<TElement*>(m_current->m_next);
		return (tmp);
	}

	bool IsCurrentEqual(const LinkedListElement* val) const
	{
		return (val == m_current);
	}

	bool operator==(const LinkedListIterator& val)
	{
		return m_current==val.m_current;
	}

	bool operator!=(const LinkedListIterator& val)
	{
		return m_current!=val.m_current;
	}

private:

	TElement* m_current;
};

//-------------------------------------------------------

class LinkedListElement
{
public:

	LinkedListElement()
		:m_next(this)
		,m_prev(this)
	{
// 		// Это нужно для элементов которые добавляются в лист потом, а не при создании
// 		if(parent!=NULL)
// 			parent->Add(this);
	}

	~LinkedListElement(void)
	{
		RemoveFromList();
	}

	void RemoveFromList()
	{
		if( IsEmpty() )
			return;

		m_prev->m_next = m_next;
		m_next->m_prev = m_prev;

		m_next = this;
		m_prev = this;
	}

	void AddAfter(LinkedListElement* element_to_add)
	{
		return_if_not_equal(element_to_add->IsEmpty(), true);

		element_to_add->m_prev = this;
		element_to_add->m_next = this->m_next;
		this->m_next->m_prev = element_to_add;
		this->m_next = element_to_add;
	}

	void AddBefore(LinkedListElement* element_to_add)
	{
		return_if_not_equal(element_to_add->IsEmpty(), true);

		element_to_add->m_next = this;
		element_to_add->m_prev = this->m_prev;
		this->m_prev->m_next = element_to_add;
		this->m_prev = element_to_add;
	}

private:

	bool IsEmpty() const
	{
		return m_next==this;
	}

	LinkedListElement(const LinkedListElement&);
	LinkedListElement& operator=(const LinkedListElement&);

private:

	template<class TElement>
	friend class LinkedListIterator;

	template<class TData>
	friend class LinkedList;

	LinkedListElement*	m_next;
	LinkedListElement*	m_prev;
};

//-------------------------------------------------------

template<class TData>
class LinkedList
{
public:

	LinkedList(void)
	{
	}

	~LinkedList(void)
	{
		while( !m_first.IsEmpty() )
			m_first.m_next->RemoveFromList();
	}

	TData* Front() const
	{
		if( m_first.IsEmpty() )
			return NULL;
		return const_cast<TData*>(static_cast<const TData*>(m_first.m_next));
	}

// 	TData* Back() const
// 	{
// 		if( m_first.IsEmpty() )
// 			return NULL;
// 		return const_cast<TData*>(static_cast<const TData*>(m_first.m_prev));
// 	}


// 	LinkedListIterator<TData> Begin() const
// 	{
// 		TData* tmp=const_cast<TData*>(static_cast<const TData*>(m_first.m_next));
// 		return LinkedListIterator<TData>(tmp);
// 	}
// 
// 	LinkedListIterator<TData> End() const
// 	{
// 		return LinkedListIterator<TData>(NULL);
// 	}

	void PushBack(LinkedListElement* element)
	{
		m_first.AddBefore(element);
	}

// 	void PushFront(LinkedListElement* element)
// 	{
// 		m_first.AddAfterThis(element);
// 	}


// 	LinkedListIterator<TData> Remove(LinkedListIterator<TData> removed)
// 	{
// 		LinkedListIterator<TData> res(removed);
// 		res++;
// 		(*removed)->RemoveFromList();
// 		return res;
// 
// 		// Не возвращать предыдущий - это непривычное и неочевидно поведение 
// 		// около первого и последнего элементов породило баг при обходе листа
// 		//
// 		// const LinkedListElement* old_prev=(*removed)->m_prev;
// 		// 
// 		// (*removed)->RemoveFromList();
// 		// 
// 		// LinkedListIterator<TData> res(NULL);
// 		// if(old_prev==&m_first)
// 		// 	res=Begin();
// 		// else
// 		// 	res=LinkedListIterator<TData>(const_cast<TData*>(static_cast<const TData*>(old_prev)));
// 		// 
// 		// // Возвращать предыдущий. 
// 		// // Для упрощения реализвции удаления текущего элемента 
// 		// // в процессе обхода листа, 
// 		// return res;
// 	}

	void MoveToList(LinkedList* other)
	{	
		if( !m_first.IsEmpty() )
		{
			other->m_first.m_next = m_first.m_next;
			other->m_first.m_prev = m_first.m_prev;

			m_first.m_next->m_prev = &other->m_first;
			m_first.m_prev->m_next = &other->m_first;
			m_first.m_next = &m_first;
			m_first.m_prev = &m_first;
		}
	}



	size_t Size()
	{
		size_t count = 0;
		for( LinkedListIterator<TData> it = Front(); !IsEnd(it); it++ )
			count++;
		return count;
	}

	TData* At(size_t index)
	{
		size_t count = 0;
		for( LinkedListIterator<TData> it = Front(); !IsEnd(it); it++ )
		{
			if( count == index )
				return (*it);
			count++;
		}
		return NULL;
	}

private:

	bool IsEnd(const LinkedListIterator<TData>& element) const
	{
		if( element.IsCurrentEqual(NULL) )
			return true;
		return element.IsCurrentEqual(&m_first);
	}


private:

	// Этот класс неперемещаем т.к. содержит указатель на собственный член
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);


private:
	LinkedListElement m_first;
};

