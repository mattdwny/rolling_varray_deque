/**
 * The rolling varray deque...
 *
 * @author Matthew Russell Downey (MattDwny)
 */

template <typename T>
class rolling_varray_deque
{
private:
	T** frontTable;//an array of pointers to contiguous arrays of object T. The array sizes are 1, 1, 2, 4, 8...
	T** backTable;
	
	T*  frontArray; //retrieval optimization for pop/push_front
	T*  backArray;
		
	size_t frontTableSize;
	size_t backTableSize;

	size_t frontSize;
	size_t backSize;
	
	size_t frontCapacity;
	size_t backCapacity;

	size_t frontIndex; //- if inside of back
	size_t backIndex; //- if inside of front

	size_t superindexOf(size_t i);
	size_t subindexOf(size_t i);

public:
	/**
	 * constructors
	 */
	rolling_varray_deque();

	/**
	 * destructors
	 */
	~rolling_varray_deque();

	/**
	 *  element access
	 */
	T at(size_t i);
	T operator[](/*???*/);
	T front();
	T back();

	/**
	 * iterators
	 */
	iterator begin();
	const_iterator cbegin();

	iterator end();
	const_iterator cend();

	iterator rbegin();
	const_iterator crbegin();

	iterator rend();
	const_iterator crend();

	/**
	 * capacity
	 */
	size_t size();
	bool empty();
	size_t max_size();
	void reserve();
	size_t capacity();
	//void shrink_to_fit(); //will need to implement
	//void arrayify();

	/**
	 * modifiers
	 */
	void clear();
	void push_back(T& obj);
	void pop_back();
	void push_front(T& obj);
	void pop_back();
	void insert(iterator pos, T& obj);
	void erase(iterator pos);
}