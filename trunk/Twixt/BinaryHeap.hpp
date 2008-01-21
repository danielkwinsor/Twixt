

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

template <class T>
class HEAP
{
public:
	int	key;
	T	data;

	HEAP<T>(void){return;};
	HEAP<T>(T data, int key) {HEAP::data = data; HEAP::key = key; return;};

	bool operator==(HEAP<T> &compare) {
		if (this->key == compare.key && this->data == compare.data) return true;
		else return false;
	}
};

template <class T>
class CBinaryHeap
{
	/*
	CBinaryHeap					();
	CBinaryHeap					(int size);
	~CBinaryHeap				();

	HEAP<T>		popTopHeap		();
	HEAP<T>		popTopHeap		(int& returnSize);
	HEAP<T>		peekTopHeap		() const;
	HEAP<T>		peekElement		(int index) const;
	int			size			() const;
	int			getMaxSize		() const;
	int			insertElement	(const T data, const int key);
	HEAP<T>		removeElement	(const T data, const int key);
	HEAP<T>		removeElement	(const T data);
	bool		editElement		(const T oldData, const T newData,
								const int oldKey, const int newKey);
	bool		editElement		(const T data, const int key);
	int			findData		(const T data) const;
	int			findData		(const T data, const int key) const;
	void		clear			(){heapCount = 1; return;};

private:
	int			moveUp			(int index, int newKey);
	int			moveDown		(int index, int newKey);

	int			heapCount;
	int			maxSize;
	HEAP<T>*	BinaryHeap;
*/


public:
	void clear ()
	{
		heapCount = 1;
		return;
	}

	CBinaryHeap(int size)
	{
		if (size <= 0) {
			size = 1023;
		}
		//size must be maxSize + 1, because 1 element is unused.
		BinaryHeap = new HEAP<T>[size+1];
		maxSize = size;
		heapCount = 1;
		return;
	}

	CBinaryHeap()
	{
		//size must be maxSize + 1, because 1 element is unused.
		BinaryHeap = new HEAP<T>[1024];
		maxSize = 1023;
		heapCount = 1;
		return;
	}

	~CBinaryHeap()
	{
		delete BinaryHeap;
	}

	HEAP<T> removeElement(const T data)
	{
		HEAP<T> returnHeap;
		int index = findData(data);
		if (index) {
			returnHeap = BinaryHeap[index];
			--heapCount;
			BinaryHeap[moveDown(index, BinaryHeap[heapCount].key)] = BinaryHeap[heapCount];
		}
		return (returnHeap);
	}

	HEAP<T> removeElement(const T data, const int key)
	{
		HEAP<T> returnHeap;
		int index = findData(data, key);
		if (index) {
			returnHeap = BinaryHeap[index];
			--heapCount;
			BinaryHeap[moveDown(index, BinaryHeap[heapCount].key)] = BinaryHeap[heapCount];
		}
		return (returnHeap);
	}

	int moveUp(register int index, int newKey)
	{
		while (index > 1) {
			int current2 = index>>1;//divided by 2
			if (BinaryHeap[current2].key > newKey) {
				//move parent down
				BinaryHeap[index] = BinaryHeap[current2];
				index = current2;
			}
			else {
				break;
			}
		}
		return (index);
	}

	int moveDown(int index, int currentKey)
	{
		register int current2 = index+index;
			while (current2 < heapCount) {
			if (current2+1 < heapCount) {
				current2 += (BinaryHeap[current2].key > BinaryHeap[current2+1].key);
				//choose child to possibly move
				if (currentKey > BinaryHeap[current2].key) {
					//move child up
					BinaryHeap[index] = BinaryHeap[current2];
					index = current2;
					current2 += current2;//times 2
				}
				else {
					return index;
				}
			}
			else {
				if (currentKey > BinaryHeap[current2].key) {
					BinaryHeap[index] = BinaryHeap[current2];
					index =  current2;
				}
				return index;
			}
		}
		return index;
	}

	bool editElement(const T oldData, const T newData, const int oldKey, const int newKey)
	{
		int index = findData(oldData, oldKey);
		if (index) {
			if (oldKey < newKey) {
				index = moveDown(index, newKey);
				BinaryHeap[index].key = newKey;
			}
			else if (oldKey > newKey) {
				index = moveUp(index, newKey);
				BinaryHeap[index].key = newKey;
			}
			BinaryHeap[index].data = newData;
			return true;
		}
		return false;
	}

	bool editElement(const T data, const int key)
	{
		int index = findData(data);
		if (index) {
			int oldKey = BinaryHeap[index].key;
			if (oldKey < key) {
				index = moveDown(index, key);
				BinaryHeap[index].data = data;
				BinaryHeap[index].key = key;
			}
			else if (oldKey > key) {
				index = moveUp(index, key);
				BinaryHeap[index].data = data;
				BinaryHeap[index].key = key;
			}
			return true;
		}
		return false;
	}

	int insertElement(const T data, const int key)
	{
		if (heapCount > maxSize) {
			return 0;
		}
		int index = heapCount;
		while (index > 1) {
			int current2 = index>>1;//divided by 2
			if (BinaryHeap[current2].key > key) {
				//move parent down
				BinaryHeap[index] = BinaryHeap[current2];
				index = current2;
			}
			else {
				break;
			}
		}
		BinaryHeap[index].data = data;
		BinaryHeap[index].key = key;
		return (heapCount++);
		
		/*
		if (heapCount > maxSize) {
			return 0;
		}
	__asm {
		mov		ecx, [this]
		mov		eax, [ecx]CBinaryHeap.heapCount
		mov		ecx, [ecx]CBinaryHeap.BinaryHeap
		mov     edx, key
		cmp     eax, 1
		jle     short insert

moveParentDown:
		mov		esi, eax
		sar     esi, 1
		cmp     [ecx+esi*8], edx
		jle     short insert//if parent key is higher, insert at current index
		cmp     esi, 1
		mov     ebx, [ecx+esi*8]
		mov     [ecx+eax*8], ebx
		mov     ebx, [ecx+esi*8+4]
		mov     [ecx+eax*8+4], ebx
		mov		eax, esi
		jg      short moveParentDown

insert:
		mov     esi, data
		mov     [ecx+eax*8+4], esi
		mov     [ecx+eax*8], edx
		mov		ecx, [this]
		mov     eax, [ecx]CBinaryHeap.heapCount//++heapCount
		mov		edx, eax
		inc		edx
		mov     [ecx]CBinaryHeap.heapCount, edx//BinaryHeap.heapCount = heapCount
	}*/
	}

	HEAP<T> popTopHeap(int& returnSize)
	{
		returnSize = heapCount-1;
		if (heapCount != 1) {
			return (popTopHeap());
		}
		return (BinaryHeap[0]);
	}

	HEAP<T> popTopHeap()
	{
		HEAP<T> returnHeap;
		if (heapCount != 1) {
			returnHeap = BinaryHeap[1];
			--heapCount;
			int currentKey = BinaryHeap[heapCount].key;
			int current2 = 2;
			int index = 1;
			while (current2 < heapCount) {
				if (current2+1 < heapCount) {
					current2 += (BinaryHeap[current2].key > BinaryHeap[current2+1].key);
					//choose child to possibly move
					if (currentKey > BinaryHeap[current2].key) {
						//move child up
						BinaryHeap[index] = BinaryHeap[current2];
						index = current2;
						current2 += current2;//times 2
					}
					else {
						break;
					}
				}
				else {
					if (currentKey > BinaryHeap[current2].key) {
						BinaryHeap[index] = BinaryHeap[current2];
						index =  current2;
					}
					break;
				}
			}
			BinaryHeap[index] = BinaryHeap[heapCount];
		}
		return (returnHeap);
	}

	HEAP<T> peekTopHeap() const
	{
		return (BinaryHeap[(heapCount != 1)]);
	}

	HEAP<T> peekElement(int index) const
	{
		if (index < heapCount) {
			return (BinaryHeap[index]);
		}
		else {
			return (BinaryHeap[0]);
		}
	}

	int size() const
	{
		return (heapCount-1);
	}

	int getMaxSize() const
	{
		return (maxSize);
	}

	int findData(const T data) const
	{
		register int current;
		for (current = heapCount-1; current > 0; --current) {
			if (BinaryHeap[current].data == data) {
				break;
			}
		}
		return current;
	}

	int findData(const T data, const int key) const
	{
		register int current;
		if ((BinaryHeap[1].key + BinaryHeap[heapCount-1].key)>>1 > key) {
			for (current = 1; current <= heapCount-1; ++current) {
				if (BinaryHeap[current].data == data && BinaryHeap[current].key == key) {
					return current;
				}
			}
		}
		for (current = heapCount-1; current > 0; --current) {
			if (BinaryHeap[current].data == data && BinaryHeap[current].key == key) {
				break;
			}
		}
		return current;
	}

private:
	int			heapCount;
	int			maxSize;
	HEAP<T>*	BinaryHeap;
};

#endif
