//Array.h

#ifndef _ARRAY_H
#define _ARRAY_H

template <typename T>
class Array {
	public :
		Array(int capacity = 100);
		Array(const Array& source);
		Array& operator =(const Array& source);

		~Array();

		int Store(int index, T object);
		int AppendFromFront(T object);
		int AppendFromRear(T object);
		int Insert(int index, T object);
		int Modify(int index, T object);

		int LinearSearchUnique(void *key, int (*compare)(void *, void *));
		void LinearSearchDuplicate(void *key, int* (*indexes), int *count, int (*compare)(void *, void *));
		int BinarySearchUnique(void *key, int (*compare)(void *, void *));
		void BinarySearchDuplicate(void *key, int* (*indexes), int *count, int (*compare)(void *, void *));

		int Delete(int index);
		int DeleteFromFront();
		int DeleteFromRear();
		void DeleteAll();

		void SelectionSort(int (*compare)(void *, void *));
		void InsertionSort(int (*compare)(void *, void *));
		void MergeSort(const Array& one, const Array& other, int (*compare)(void *, void *));

		T& operator [](int index);
		T* operator +(int index);		// 포인터 산술 연산자
		T& GetAt(int index);

		int& GetCapacity() const;
		int& GetLength() const;

	private :
		T (*front);
		int capacity;
		int length;
};

template <typename T>
inline int& Array<T>::GetLength() const {

	return const_cast<int&>(this->length);
}

template <typename T>
inline int& Array<T>::GetCapacity() const {

	return const_cast<int&>(this->capacity);
}

template <typename T>
Array<T>::Array(int capacity) {

	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>
T& Array<T>::GetAt(int index) {

	return this->front[index];
}

template <typename T>
Array<T>::~Array() {

	DeleteAll();
}

template <typename T>
void Array<T>::DeleteAll()
{
	if (this->front != 0) {
		delete[] front;
		front = nullptr;
	}
}

template <typename T>
Array<T>::Array(const Array& source) {

	this->front = new T[source.capacity];
	
	for(int i = 0; i < source.length; i++) {
		this->front[i] = source.front[i];
		this->length++;
	}
	this->capacity = source.capacity;
}

template <typename T>
T& Array<T>::operator [](int index) {
	return this->front[index];
}

template <typename T>
T* Array<T>::operator +(int index) {
	return this->front + index;
}

template <typename T>
Array<T>& Array<T>::operator =(const Array& source) {

	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[source.capacity];
	
	for(int i = 0; i < source.length; i++) {
		this->front[i] = source.front[i];
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

template <typename T>
int Array<T>::Store(int index, T object) {

	this->front[index] = object;
	this->length++;
	return index;
}

template <typename T>
int Array<T>::AppendFromFront(T object) {

	T (*temp);
	int index = 0;

	temp = new T[this->capacity + 1];

	for(int i = 0; i < this->length; i++) {
		temp[i + 1] = this->front[i];
	}

	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
int Array<T>::AppendFromRear(T object) {

	T (*temp);
	int index;

	temp = new T[this->capacity + 1];

	for(int i = 0; i < this->length; i++) {
		temp[i] = this->front[i];
	}

	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;
	this->capacity++;
	index = this->capacity;
	this->front[index - 1] = object;
	this->length++;

	return index;
}

template <typename T>
int Array<T>::Insert(int index, T object) {

	T (*temp);
	int i;
	int index;

	temp = new T[this->capacity + 1];

	for(i = 0; i < index; i++) {
		temp[i] = this->front[i];
	}
	for(i = index; i <= this->length; i++) {
		temp[i + 1] = this->front[i];
	}

	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
int Array<T>::Delete(int index) {

	T (*temp);
	int i;

	if(this->capacity > 1) {
		temp = new T[this->capacity - 1];

		for(i = 0; i < index; i++) {
			temp[i] = this->front[i];
		}
		for(i = index + 1; i < this->capacity; i++) {
			temp[i - 1] = this->front[i];
		}

		if(this->front != 0) {
			delete[] this->front;
			this->front = 0;
		}
	}

	if(this->capacity > 1) {
		this->front = temp;
	}

	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template <typename T>
int Array<T>::DeleteFromFront() {

	T (*temp);
	int index = -1;

	if(this->capacity > 1) {
		temp = new T[this->capacity - 1];

		for(i = 1; i < this->length; i++) {
			temp[i - 1] = this->front[i];
		}
	}

	if(this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	
	if(this->capaicty > 1) {
		this->front = temp;
	}

	this->capacity--;
	this->length--;

	return index;
}

template <typename T>
int Array<T>::DeleteFromRear() {

	T (*temp);
	int index = -1;

	if(this->capacity > 1) {
		temp = new T[this->capacity - 1];

		for(i = 0; i < this->capacity - 1; i++) {
			temp[i - 1] = this->front[i];
		}
	}

	if(this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	
	if(this->capaicty > 1) {
		this->front = temp;
	}

	this->capacity--;
	this->length--;

	return index;
}

template <typename T>
int Array<T>::Modify(int index, T object) {
	
	this->front[index] = object;
	return index;
}

template <typename T>
int Array<T>::LinearSearchUnique(void *key, int (*compare)(void *, void *)) {
	
	int index = -1;
	int i = 0;

	while(i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if(i < this->length) {
		index = i;
	}
	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, int* (*indexes), int *count, int (*compare)(void *, void *)) {

	int j = 0;
	*indexes = new int[this->length];
	*count = 0;

	for(int i = 0; i < this->length; i++) {
		if(compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
	}
}

template <typename T>
int Array<T>::BinarySearchUnique(void *key, int (*compare)(void *, void *)) {

	int index = -1;
	int middle;
	int high = this->length - 1;
	int low = 0;

	middle = (low + high) / 2;

	while(low <= high && this->front[middle] != key) {
		if(this->front[middle] > key) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	if(low <= high) {
		index = middle;
	}
	return index;
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, int* (*indexes), int *count, int (*compare)(void *, void *)) {

	int middle;
	int low = 0;
	int high = this->length - 1;
	int i = 0;
	int j;

	middle = (low + high) / 2;
	*count = 0;

	while(low <= high && compare(this->front + middle, key) != 0) {
		if(compare(this->front + middle, key) == 0) {
			high = middle - 1;
		}
		else {
			low = middle + 1;
		}
		middle = (low + high) / 2;
	}
	if(low <= high) {
		*indexes = new T(this->length);
		j = middle - 1;

		while(j >= 0 && comapre(this->front + j, key) == 0) {
			j--;
		}
		j++;

		while(j < this->length && compare(this->front + j, key) == 0) {
			(*indexes)[i] = j;
			i++;
			(*count)++;
			j++;
		}
	}
}

template <typename T>
void Array<T>::SelectionSort(int (*compare)(void *, void *)) {

	T temp;

	for(int i = 0; i < this->length - 1; i++) {
		for(int j = i + 1; j < this->length; j++) {
			if(compare(this->front + i, this->front + j) > 0) {
				temp = this->front[i];
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
		}
	}
}

template <typename T>
void Array<T>::InsertionSort(int (*compare)(void *, void *)) {

	T temp;
	int i, index;
	int j = 0;

	for(i = 1; i < this->length; i++) {
		index = 0;

		while(index < i && compare(this->front + index, this->front + i) < 0) {
			index++;
		}

		if(index < i) {
			temp = this->front[i];
			j = i;
			
			while(j > index) {
				this->front[j] = this->front[j - 1];
				j--;
			}
			this->front[index] = temp;
		}
	}
}

template <typename T>
void Array<T>::MergeSort(const Array& one, const Array& other, int (*compare)(void *, void *)) {

	int i = 0;
	int j = 0;
	int k = 0;

	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[one.length + other.length];

	while(i < one.length && j < other.length) {
		if(compare(one.front + i, other.front + j) < 0) {
			this->front[k] = this->front[i];
			k++;
			i++;
		}
		else {
			this->front[k] = this->front[j];
			k++;
			j++;
		}
	}

	while(j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}

	while(i < one.length) {
		this->front[k] = other.front[i];
		k++;
		i++;
	}

	this->capacity = one.length + other.length;
	this->length = one.length + other.length;
}

#endif //_ARRAY_H