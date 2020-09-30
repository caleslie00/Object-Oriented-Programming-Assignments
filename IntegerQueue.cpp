#include <iostream>
#include "IntegerQueue.h"

using namespace std;

//initializes a new Integer queue
IntegerQueue::IntegerQueue()
{
    data = new int[10];
    space = 10;
    head = 0;
    tail = 0;
}
//pushes n onto the end of the integer queue
void IntegerQueue::push(int n)
{
    //this if statement makes sure the queue isn't about to go beyond the array
    if(tail >= space)
    {
        int* temp = new int[space*2];
        int tempSpot = 0;
        for(int i = head; i < space; i++)
        {
            temp[tempSpot] = data[i];
            tempSpot++;
        }
        delete [] data;
        data = temp;
        tail = tempSpot;
        head = 0;
        space *= 2;
        temp = NULL;
    }
    data[tail] = n;
    tail++;
}
//pops and returns the value at the front of the list
int IntegerQueue::pop()
{
    return data[head++];
}
//returns true if the queue is empty, false if not
bool IntegerQueue::empty() const
{
    return head == tail;
}
//returns the size of the queue
int IntegerQueue::size() const
{
    return tail-head;
}
//this is a destructor which is implicit
IntegerQueue::~IntegerQueue()
{
    delete [] data;
    data = NULL;
}
//handles using the equals operator to set an IntgerQueue equal to
//another since that is not implicitly defined
const IntegerQueue& IntegerQueue::operator=(const IntegerQueue& q)
{
	if(data == q.data)
		return *this;
	delete [] data;
    head = q.head;
    tail = q.tail;
    space = q.space;
    data = new int[space];
    for(int i = head; i < tail; i++)
        data[i] = q.data[i];
    return *this;
}
//uses the equals operator that we just defined to do the same task
//only when passing it in a constructor
IntegerQueue::IntegerQueue(const IntegerQueue& q)
{
    head = q.head;
    tail = q.tail;
    space = q.space;
    data = new int[space];
    for(int i = head; i < tail; i++)
        data[i] = q.data[i];
}
//gets the data at index in the array since our operator<< can't
//get data directly from the class
int IntegerQueue::getData(int index) const
{
	return data[index];
}
//correctly formats the output like an array according to the prompt
ostream& operator<<(ostream& out, const IntegerQueue& q)
{
	if(q.empty())
	{
		out << "{}";
	}
	else
	{
	    out << "{" << q.getData(0);
	    for(int i = 1; i < q.size(); i++)
	        out << "," << q.getData(i);
	    out << "}";
	}
    return out;
}