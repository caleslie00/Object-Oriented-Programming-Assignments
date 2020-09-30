#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "IntegerQueue2.h"

using namespace std;

//initializes a new Integer queue
IntegerQueue::IntegerQueue()
{
    queue = new int[10];
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
            temp[tempSpot] = queue[i];
            tempSpot++;
        }
        delete [] queue;
        queue = temp;
        tail = tempSpot;
        head = 0;
        space *= 2;
        temp = NULL;
    }
    queue[tail] = n;
    tail++;
}
//pops and returns the value at the front of the list
int IntegerQueue::pop()
{
    return queue[head++];
}
//returns true if the queue is empty, false if not
bool IntegerQueue::empty()
{
    return head == tail;
}
//returns the size of the queue
int IntegerQueue::size()
{
    return tail-head;
}
IntegerQueue::~IntegerQueue()
{
    delete [] queue;
    queue = NULL;
}
//handles using the equals operator to set an IntgerQueue equal to
//another since that is not implicitly defined
const IntegerQueue& IntegerQueue::operator=(const IntegerQueue& q)
{
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
const IntegerQueue& IntegerQueue::IntegerQueue(const IntegerQueue& q)
{
    return this = q;
}
//correctly formats the output like an array according to the prompt
ostream& IntegerQueue::operator<<(ostream& out, const IntegerQueue& q)
{
    out << "{" << q[head];
    for(int i = 1; i < tail; i++)
        out << "," << q[head+i];
    out << "}";
    return out;
}

//BUILT IN TESTING 
IntegerQueue IntegerQueue::dup(IntegerQueue a)
{
    IntegerQueue result;
    while (!a.empty()) {
        int x = a.pop();
        result.push(x);
        result.push(x);
    }
    return result;
}

void IntegerQueue::print(IntegerQueue *a,int n)
{
    for (int i=0; i<n; i++)
        cout << a[i] << endl;
}

int main()
{ 
    IntegerQueue q;
    for (int i=0; i<10; i++)
        q.push(i);

    IntegerQueue r = q;
    IntegerQueue s(q);
    IntegerQueue t;
    t = q;

    IntegerQueue a[10];
 
    for (int i=0; i<10; i++)
        for (int j=0; j<i; j++)
            a[i].push(j);
 
    s = dup(a[9]);
    t = dup(a[4]);
    a[7] = IntegerQueue();
 
    IntegerQueue b[8] = {q,r,s,t,a[1],a[3],dup(a[5])};
 
    cout << "q = " << q << endl;
    cout << "r = " << r << endl;
    cout << "s = " << s << endl;
    cout << "t = " << t << endl;
 
    print(a,10);
    print(b,8);
}