#define DEBUG 1
#include <cmath>
#include <iomanip>

template<class T>
class TupleData
{
	private:
		//TupleData variables
		T* things; //T array 
		int _size; //size of the array
		int pointingAt; //number of things pointing at this Tuple
	public: 
		//TupleData constructors
		TupleData(int l); 
		TupleData(const TupleData<T> &other);
		TupleData(const T *a, int l);
		~TupleData() { if(things) delete [] things;}

		//TupleData operators
		T& operator[](int i) {return things[i];} 
		const T& operator[](int i) const {return things[i];}
		
		//setters/getters for TupleData
		int size() const {return _size;}
		void incrementPointingAt() {pointingAt++;}
		void decrementPointingAt();
		int useCount() const {return pointingAt;}

		const TupleData<T>& operator=(const T x)
		{
			TupleData<T>* newT = new TupleData<T>[things->size()];
			for(int i = 0; i < things->size(); i++)
				newT[i] = things[i];
			things = newT;
			
			delete newT;
		}
};
//----------------------------------------------------------------------
//----------------------All TupleData functions-------------------------
//----------------------------------------------------------------------
template<class T>
TupleData<T>::TupleData(int l)
{
	_size = l;
	pointingAt = 0;
	things = new T[_size];
	for(int i = 0; i < _size; i++)
		things[i] = 0;
}
template<class T>
TupleData<T>::TupleData(const TupleData<T>& other)
{
	pointingAt = other.pointingAt+1;
	things = other.things;
	_size = other.size();
}
template<class T>
TupleData<T>::TupleData(const T* a, int l)
{
	_size = l;
	pointingAt = 0;
	things = new T[_size];
	for(int i = 0; i < _size; i++)
		things[i] = a[i];
}
template<class T>
void TupleData<T>::decrementPointingAt() 
{
	pointingAt--; 
	if(pointingAt <= 0) 
		delete this;
}
template<class T>
class Tuple
{
	//tuple variables
	private:
		TupleData<T>* data; //pointer to the Tuple's tupledata
		static T ret; ///static t to return 0
	public:
		//Tuple constructors
		Tuple(int n): data(new TupleData<T>(n)) { data->incrementPointingAt(); }
		Tuple(const T* p, int n): data(new TupleData<T>(p, n)) { data->incrementPointingAt(); }
		Tuple(const Tuple<T>& other) : data(other.data) { data->incrementPointingAt(); }
		~Tuple() {data->decrementPointingAt();}

		//Tuple operator overloads
		T& operator[](int i);
		const T& operator[](int i) const;
	
		const Tuple& operator=(const Tuple<T>& other);
		bool operator==(const Tuple<T>& other) const;
		bool operator!=(const Tuple<T>& other) const { return !((*this)==other);}

		//Tuple getters
		int size() const { return data->size(); }
		T magnitude() const { return sqrt((*this) * (*this)); }
		int useCount() { return data->useCount(); }
		
		#ifdef DEBUG
			TupleData<T>& implementation() const {return *data; }
		#endif
};
//Math operator overloads
template<class T> 
Tuple<T> operator+(const Tuple<T>& first, const Tuple<T>& second); //A+B

template<class T> 
const Tuple<T>& operator+=(Tuple<T>& first, const Tuple<T>& second); //A += B

template<class T> 
T operator*(const Tuple<T>& first, const Tuple<T>& second);  // A*B

template<class T> 
Tuple<T> operator*(const Tuple<T>& tup, const T& x); // A*x

template<class T> 
Tuple<T> operator*(const T& x, const Tuple<T>& tup); // x*A

template<class T> 
const Tuple<T>& operator*=(Tuple<T>& tup, const T& x); // A *= x

//------------------------------------------------------------------
//----------------------All Tuple functions-------------------------
//------------------------------------------------------------------
template<class T>
T Tuple<T>::ret = 0;
template<class T>
const T& Tuple<T>::operator[](int i) const //returns the item in the location of i
{
	if(i < 0 || i > data->size())
	{
		ret = 0;
		return ret;
	}
	return (*data)[i];
}
template<class T>
T& Tuple<T>::operator[](int i) //returns the address of the object at i for reassigning
{
	if(i < 0 || i >= data->size())
		return ret;
	if(data->useCount() > 1)
	{
		data->decrementPointingAt();
		TupleData<T>* temp = new TupleData<T>(data->size());
		for(int j = 0; j < data->size(); j++)
			(*temp)[j] = (*data)[j];
		data = temp;
		data->incrementPointingAt();
	}
	return (*data)[i];
}
template<class T>
const Tuple<T>& Tuple<T>::operator=(const Tuple<T>& other) //sets one Tuple equal to another
{
	if(this != &other)
	{
		data->decrementPointingAt();
		data = other.data;
		data->incrementPointingAt();
	}
	return (*this);
}
template<class T>
bool Tuple<T>::operator==(const Tuple<T>& other) const //determines if a Tuple is == to another
{
	if(this->size() != other.size())
		return false;
	for(int i = 0; i < other.size(); i++)
	{
		if((*this)[i] != other[i])
			return false;
	}
	return true;
}
//----------------------------------------------------------------------
//-------------------Overloaded operator Methods------------------------
//----------------------------------------------------------------------
//A and B are Tuples for this whole section and x is a T
template<class T>
Tuple<T> operator+(const Tuple<T>& first, const Tuple<T>& second) // overloads A + B
{
	int largerSize = (first.size() > second.size() ? first.size() : second.size());
	Tuple<T> final(largerSize);

	for(int i = 0; i < largerSize; i++)
		final[i] = first[i] + second[i];

	return final;
}
template<class T> 
const Tuple<T>& operator+=(Tuple<T>& first, const Tuple<T>& second) // overloads A += B
{
	return first = (first + second);
}
template<class T>
T operator*(const Tuple<T>& first, const Tuple<T>& second)  // overloads A * B
{
	int smaller = (first.size() < second.size() ? first.size() : second.size());

	T sum = 0;
	for(int i = 0; i < smaller; i++)
		sum += first[i] * second[i];
	return sum;
}
template<class T>
Tuple<T> operator*(const Tuple<T>& tup, const T& x) // overloads A * x
{
	Tuple<T> newT(tup.size());
	for(int i = 0; i < newT.size(); i++)
		newT[i] = (tup[i] * x);
	return newT;
}
template<class T>
Tuple<T> operator*(const T& x, const Tuple<T>& tup) // overloads x * A
{
	return tup * x;
}
template<class T>
const Tuple<T>& operator*=(Tuple<T>& tup, const T& x) // overloads A *= x
{
	for(int i = 0; i < tup.size(); i++)
	{
		tup[i] *= x;
	}
	return tup;
}