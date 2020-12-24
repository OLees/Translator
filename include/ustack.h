#pragma once
#include <iostream>


const int MAX_SIZE = 1000;

template <class T>
class Vector {
protected:
	T* data;
	size_t Mem;  //выделенная память
	size_t Size;  //занимаемая память
public:
	Vector() {
		data = NULL;
		Mem = 0;
		Size = 0;
	}

	Vector(size_t s) {
		if ((s < 0) || (s > MAX_SIZE))
			throw "Negative or Too Big Size";
		Mem = size_t(1.5 * s) + 1;
		data = new T[Mem];
		Size = s;
		for (size_t i = 0; i < Mem; i++)
			data[i] = 0;
	}

	Vector(const Vector& v) {
		Mem = v.Mem;
		Size = v.Size;
		data = new T[Mem];
		for (size_t i = 0; i < Size; i++)
			this->data[i] = v.data[i];
		for (size_t i = Size; i < Mem; i++)
			data[i] = 0;
	}


	~Vector() {
		delete[] data;
		data = NULL;
		Mem = 0;
		Size = 0;
	}

	size_t GetSize() {
		return Size;
	}

	void push_back(T elem)
	{
		if (Size == MAX_SIZE)
			throw "Unable to push";
		if (Size + 1 >= Mem) {
			size_t NewMem = Mem * 1.5 + 3;
			Resize(NewMem);
		}
		data[Size] = elem;
		Size++;
	};

	void pop_back()
	{
		if (Size == 0)
			throw "Unable to pop";
		data[Size--] = 0;
		//Size--;
	};

	void Resize(size_t n)
	{
		if ((n <= 0) || (n > MAX_SIZE))
			throw "Unable to Resize";
		T* temp = new T[n];
		for (size_t i = 0; i < Size; i++)
			temp[i] = data[i];
		for (size_t i = Size; i < n; i++)
			temp[i] = 0;
		delete[] data;
		data = temp;
		Mem = n;
	}

	int empty()
	{
		return Size == 0;
	};

	int full()
	{
		return Size == Mem;
	};

	Vector& operator=(const Vector& v) const
	{
		size_t max = Size;
		if (max < v.Size)
			max = v.Size;
		delete[] data;
		data = new T[max];
		for (size_t i = 0; i < v.Size; i++)
			data[i] = v.data[i];
		for (size_t i = v.Size; i < max; i++)
			data[i] = 0;
	};

	T operator[](size_t i) const {
		if ((i > 0) && (i < MAX_SIZE))
			return data[i];
		else throw "Unable to get element";
	};
};


///-----------------------------///------------------------------////
///---------------------------///////------------------------------////


template <class T>
class Stack : public Vector <T> {
public:
	Stack() :Vector() {};
	Stack(const int n) :Vector(n) { Size = 0; };
	Stack(const Stack& s) :Vector(s) {};
	~Stack() {};

	T Top()
	{
		if (Size >= 1)
			return data[Size - 1];
		else
			throw "Stack is empty";
	}

	void push(T elem)
	{
		Vector<T>::push_back(elem);
	}

	void pop()
	{
		Vector<T>::pop_back();
	}

	int IsEmpty() const
	{
		return (Size == 0);
	}

	int IsFull() const
	{
		return Size == Mem - 1;
	}
};
