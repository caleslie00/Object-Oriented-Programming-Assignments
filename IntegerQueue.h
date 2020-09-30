#include <iostream>

class IntegerQueue
{
	private:
		int* data;	// array of values
   		int space;	// space(size) of data array
    	int head;	// index from which the next value will be read (on Pop)
    	int tail;   // end of array
    public:
    	IntegerQueue(); //constructor
    	void push(int n); //pushes n to the end of the queue
    	int pop(); //pops from the head of the loop
    	bool empty() const; //returns t/f depending on if the queue is empty or not
    	int size() const; //returns the size of the queue
        const IntegerQueue& operator=(const IntegerQueue& q); //handles setting a queue equal to another
        IntegerQueue(const IntegerQueue& q); //constucts a new queue equal to q
        int getData(int index) const; //gets the integer from index of array data
        ~IntegerQueue(); //deconstructor
};

std::ostream& operator<<(std::ostream& out, const IntegerQueue& q); //outputs a IntegerQueue