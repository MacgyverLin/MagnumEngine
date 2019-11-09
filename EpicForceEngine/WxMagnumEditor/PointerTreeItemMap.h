#ifndef _PointerTreeItemMap_h_
#define _PointerTreeItemMap_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
#include "Vector3.h"
#include <map>
#include <MagnumEngine.h>
using namespace Magnum;

template<class T>
class PointerTreeItemMap
{
public:
	class ltstr1
	{
	public:
		bool operator()(T *ptr1, T *ptr2) const
		{
			return ptr1 < ptr2;
		}
	};

	class ltstr2
	{
	public:
		bool operator()(wxTreeItemId t1, wxTreeItemId t2) const
		{
			return t1.m_pItem < t2.m_pItem;
		}
	};

	PointerTreeItemMap()
	{
	}

	~PointerTreeItemMap()
	{
	}

	wxTreeItemId add(wxTreeItemId item, T *ptr)
	{
		std::map<T *, wxTreeItemId, ltstr1>::iterator itr1 = pointerTreeItemMap.find(ptr);
		std::map<wxTreeItemId, T *, ltstr2>::iterator itr2 = treeItemPointerMap.find(item);
		assert(itr1 == pointerTreeItemMap.end());
		assert(itr2 == treeItemPointerMap.end());

		pointerTreeItemMap.insert(std::pair<T *, wxTreeItemId>(ptr, item));
		treeItemPointerMap.insert(std::pair<wxTreeItemId, T *>(item, ptr));

		return item;
	}

	void remove(T *ptr)
	{
		std::map<T *, wxTreeItemId, ltstr1>::iterator itr1 = pointerTreeItemMap.find(ptr);
		std::map<wxTreeItemId, T *, ltstr2>::iterator itr2 = treeItemPointerMap.find(itr1->second);
		assert(itr1 != pointerTreeItemMap.end());
		assert(itr2 != treeItemPointerMap.end());

		pointerTreeItemMap.erase(itr1);
		treeItemPointerMap.erase(itr2);
	}

	void remove(wxTreeItemId item)
	{
		std::map<wxTreeItemId, T *, ltstr2>::iterator itr2 = treeItemPointerMap.find(item);
		std::map<T *, wxTreeItemId, ltstr1>::iterator itr1 = pointerTreeItemMap.find(itr2->second);
		assert(itr1 != pointerTreeItemMap.end());
		assert(itr2 != treeItemPointerMap.end());

		pointerTreeItemMap.erase(itr1);
		treeItemPointerMap.erase(itr2);
	}

	wxTreeItemId find(T *ptr)
	{
		wxTreeItemId item;

		std::map<T *, wxTreeItemId, ltstr1>::const_iterator itr = pointerTreeItemMap.find(ptr);
		if(itr==pointerTreeItemMap.end())
			return item;

		return itr->second;
	}

	T *find(wxTreeItemId item)
	{
		std::map<wxTreeItemId, T *, ltstr2>::const_iterator itr = treeItemPointerMap.find(item);
		if(itr==treeItemPointerMap.end())
			return 0;

		return itr->second;
	}

	void clear()
	{
		treeItemPointerMap.clear();
		pointerTreeItemMap.clear();
	}
private:
	std::map<T *, wxTreeItemId, ltstr1> pointerTreeItemMap;
	std::map<wxTreeItemId, T *, ltstr2> treeItemPointerMap;
};


#endif