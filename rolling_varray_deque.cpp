#include <cstdlib.h>

#include "rolling_varray_deque.h"

template <typename T>
rolling_varray_deque<T>::rolling_varray_deque()
{	
	frontTable = backTable = nullptr;
	frontArray = backArray = nullptr;
	
	frontTableSize = backTableSize = 0;
	frontSize      = backSize      = 0;
	frontCapacity  = backCapacity  = 0;

	frontIndex     = backIndex     = -1;
}

template <typename T>
rolling_varray_deque<T>::~rolling_varray_deque()
{	
	for(size_t i = 0; i < frontTableSize; ++i) //FIXME: this won't work in the future
		free(frontTable[i]);

	for(size_t i = 0; i < backTableSize; ++i) //FIXME: this won't work in the future
		free(backTable[i]);
	
	free(frontTable);
	free(backTable);
}
/*
template <typename T>
T& rolling_varray_deque<T>::at(size_t i)
{
	size_t superindex = superindex(i);
	return lookupTable[superindex][subindex(i,superindex)];
}

template <typename T>
T* rolling_varray_deque<T>::at(size_t i)
{	
	size_t superindex = superindex(i);
	return &lookupTable[superindex][subindex(i,superindex)];
}

template <typename T>
T rolling_varray_deque<T>::at(size_t superindex, size_t subindex)
{	
	return lookupTable[superindex][subindex];
}

template <typename T>
T* rolling_varray_deque<T>::at(size_t superindex, size_t subindex)
{	
	return &lookupTable[superindex][subindex];
}

template <typename T>
void rolling_varray_deque<T>::push_back(T data)
{	
	if(quickIndex == endIndex)
	{
		if(size == capacity)
		{
			lookupTable = (T**) realloc(lookupTable, tableSize*sizeof(T*));
			lookupTable[tableSize] = (T*) malloc(capacity*sizeof(T));
			++tableSize;
			capacity *= 2;
		}

		farArray = lookupTable[maxBit+2];
		++maxBit;
		quickIndex = 0;
	}

	farArray[quickIndex++] = std::move(data);
}

template <typename T>
T rolling_varray_deque<T>::pop_back()
{	
	if(!empty())
	{
		if(quickIndex == 0)
		{
			if(size <= capacity/4)
			{
				--tableSize;
				free lookupTable[maxBit];
				lookupTable = (T**) realloc(lookupTable, (tableSize-1)*sizeof(T*));
				capacity /= 2;
			}
			farArray = lookupTable[maxBit+1];
			quickIndex = 0;
			--tableSize;
			--maxBit;
		}
		farArray[quickIndex--];

		return data;
	}
	return null;
}
*/

template <typename T>
size_t rolling_varray_deque<T>::size()
{
	return frontSize + backSize;
}

/**
 * deceivingly O(1) avg: iterating until finding an element is (in the average case): sum ( 1*(n/2) + 2*(n/4) + 3*(n/8) + ... + i*(n*2^-i) )/n, so 2
 */
template <typename T>
size_t rolling_varray_deque<T>::superindexOf(size_t i)
{
	size_t real_i = (i+chunkSize)/chunkSize;
	ssize_t iter = maxBit;
	while(iter > 0)
	{
		if(real_i >> iter) return iter;
	}
	return real_i;
}

template <typename T>
size_t rolling_varray_deque<T>::subindexOf(size_t i)
{
	return subindexOf(i, superindexOf(i));
}

template <typename T>
size_t rolling_varray_deque<T>::subindexOf(size_t i, size_t superindex)
{
	return i - (chunkSize << superindex);
}