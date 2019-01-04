#pragma once

template <class Key, class Entry>
struct Record
{
	Key key;
	Entry data;
	operator Key() const
	{
		return key;
	}
};