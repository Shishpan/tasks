/**
 * @file: task/list_impl.h 
 * Solution implementation of the programming task 1
 */

namespace Task
{
// ---- DList::Unit class implementation ----

    // This is how template class members are defined outside of the template class
	template <class T>  DList<T>::Unit::Unit()
	{
		content = static_cast<T>(NULL);
		nextptr = NULL;
		prevptr = NULL;
	}

	template <class T>  DList<T>::Unit::~Unit()
	{	}

    template <class T> typename DList<T>::Unit *   
    DList<T>::Unit::next()      
    {
        return nextptr;
    }

    template <class T> typename DList<T>::Unit * 
    DList<T>::Unit::prev()      
    {
        return prevptr;
    }

	template <class T> T&
    DList<T>::Unit::val()      
    {
        return content;
    }

	template <class T> DList<T>::DList()
	{
		firstptr = NULL;
		lastptr = NULL;
		sizevalue = 0;
	}

	template <class T> DList<T>::~DList()
	{

	}

	template <class T> void DList<T>::push_front(const T& val)
	{
		if (firstptr == NULL && lastptr == NULL)
		{
			firstptr = new Unit;
			lastptr = firstptr;
			firstptr->content = val;
			sizevalue = 1;
		}
		else
		{
			firstptr->prevptr = new Unit;
			firstptr->prevptr->nextptr = firstptr;
			firstptr = firstptr->prevptr;
			firstptr->content = val;
			sizevalue++;
		}
	}
	template <class T> void DList<T>::push_back(const T& val)
	{
		if (firstptr == NULL && lastptr == NULL)
		{
			firstptr = new Unit;
			lastptr = firstptr;
			firstptr->content = val;
			sizevalue = 1;
		}
		else
		{
			lastptr->nextptr = new Unit;
			lastptr->nextptr->prevptr = lastptr;
			lastptr = lastptr->nextptr;
			lastptr->content = val;
			sizevalue++;
		}
	}
	template <class T> void DList<T>::pop_front()
	{
		if (firstptr != NULL)
		{
			firstptr = firstptr->nextptr;
			delete firstptr->prevptr;
			sizevalue--;
		}
	}
	template <class T> void DList<T>::pop_back()
	{
		if (lastptr != NULL)
		{
			Unit* tmp = lastptr;
			lastptr = lastptr->prevptr;
			delete tmp;
			sizevalue--;
		}
		if (sizevalue == 0)
			firstptr = NULL;
	}
	template <class T> typename DList<T>::Unit *
		DList<T>::insert(Unit* u, const T& val)
		{
			u->prevptr->nextptr = new Unit;
			u->prevptr->nextptr->content = val;
			u->prevptr->nextptr->prevptr = u->prevptr;
			u->prevptr->nextptr->nextptr = u;
			u->prevptr = u->prevptr->nextptr;
			sizevalue++;
			return u->prevptr;
		}
	template <class T> typename DList<T>::Unit *
		DList<T>::first()
		{
			return firstptr;
		}
	template <class T> typename DList<T>::Unit *
		DList<T>::last()
		{
			return lastptr;
		}
	template <class T> typename DList<T>::Unit *
		DList<T>::erase(Unit* u)
		{
			Unit* tmptoreturn = NULL;
			if (u->prevptr == NULL && u->nextptr == NULL)
			{
				delete u;
				firstptr = NULL;
				lastptr = NULL;
			}
			else
				if (u->prevptr != NULL && u->nextptr != NULL)
				{
					u->prevptr->nextptr = u->nextptr;
					u->nextptr->prevptr = u->prevptr;
					tmptoreturn = u->nextptr;
					delete u;
				}
				else
					if (u->prevptr == NULL)
					{
						tmptoreturn = u->nextptr;
						tmptoreturn->prevptr = NULL;
						firstptr = tmptoreturn;
						delete u;
					}
					else
						{
							u->prevptr->nextptr = NULL;
							tmptoreturn = NULL;
							lastptr = tmptoreturn;
							delete u;
						}
			sizevalue--;
			return tmptoreturn;
		}
	template <class T> void DList<T>::clear()
	{
		Unit* tmpptr = firstptr;
	/*	while (tmpptr != NULL)
		{
			tmpptr = erase(firstptr);
		}
	*/
		int j = size();
		for (int i = 0; i < j; i++)
		{
			pop_back();
		}
	}
	template <class T> bool DList<T>::empty()
	{
		bool tmp = sizevalue ? false : true;
		return tmp;
	}
	template <class T> unsigned DList<T>::size()
	{
		return sizevalue;
	}
	template <class T> void DList<T>::reverse()
	{
		Unit* tmp = firstptr;
		Unit* tmp1 = NULL;
		do
		{
			tmp1 = tmp->nextptr;
			tmp->nextptr = tmp->prevptr;
			tmp->prevptr = tmp1;
			tmp = tmp1;
		} while (tmp != NULL && tmp->prevptr != NULL);
		tmp1 = lastptr;
		lastptr = firstptr;
		firstptr = tmp1;
	}
// ---- End of DList::Unit class implementation ----

// ---- DList template class implementation ----

    //One more example of template class members definition
	

// ---- End of DList template class implementation ----
};
