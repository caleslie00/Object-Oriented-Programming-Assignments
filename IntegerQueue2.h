class IntegerQueue
{
	private:
		int* queue;	// array of values
   		int space;	// space(size) of data array
    	int head;	// index from which the next value will be read (on Pop)
    	int tail;
    public:
    	IntegerQueue();
    	void push(int n);
    	int pop();
    	bool empty();
    	int size();
    	~IntegerQueue();
        const IntegerQueue& operator=(const IntegerQueue& q);
        ostream& operator<<(ostream& out, const IntegerQueue& q);
        IntegerQueue dup(IntegerQueue a);
        void print(IntegerQueue *a,int n);
};