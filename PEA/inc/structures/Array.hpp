#pragma once

#include <iostream>

namespace SDIZO
{
	template<typename T> class Array;

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Array<T>& dt);

	template<typename T>
	class Array
	{
	public:
		Array();
		Array(const Array<T>& origin);
		~Array();

		virtual void addFront(const T& data);
		virtual void addBack(const T& data);
		virtual bool addAt(size_t index, const T& data);
		virtual bool search(const T& data);
		virtual bool removeFront();
		virtual bool removeBack();
		virtual bool removeAt(const size_t index);
		virtual void print();
		virtual size_t getSize();
		virtual T get(const size_t index);
		virtual void set(const size_t index, const T& data);
		virtual void swap(size_t first, size_t second);
		virtual void reverse(size_t first, size_t second);
		virtual void clear();
		virtual T* begin();
		virtual T* end();
		virtual bool contains(const T& element);

		Array<T>& operator=(const Array<T> other);
		bool operator==(const Array<T>& other);
		bool operator!=(const Array<T>& other);
		friend std::ostream& operator<< <>(std::ostream& os, const Array<T>& array);

	private:
		T* head;
		size_t size;
	};
}