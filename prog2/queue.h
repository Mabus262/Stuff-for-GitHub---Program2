#if !defined QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class ElementType>
class Queue
{
public:
	Queue(int s = 10);
	Queue(const Queue & orig);
	virtual ~Queue();
	
	Queue & operator=(const Queue & right);
	
	bool enqueue(const ElementType & a);
	ElementType peekFront() const;
	bool dequeue();
	bool isEmpty() const;
	int length() const;

	void Display(ostream & out) const;  // for testing only
	void Dump(ostream & out) const;  // REALLY for testing only
private:
	class Node
	{
	public:
		ElementType data;
		Node * next;

		//Node();
		//Node(const ElementType & val, Node * link = 0); //:data(val), next(link)
	};
	Node * front;
	Node * back;
};


//***********
//Name: Enqueue
//Purpose: appends new data to the end of the queue
//Parameters: ElementType a passed by reference - this is the data to be appended
//Operation: This function creates a new node containing the data, a, and then traverses the queue in order to leave it as the last node in the queue
//
//***********

template <class ElementType>
bool Queue<ElementType>::enqueue(const ElementType & a)
{
	Node * q = new Node;
	assert(q != 0);
	q->data = a;
	q->next = 0;

	if (front == 0)
	{
		front = q;
		back = q;
	}
	else
	{
		back->next = q;
		back = q;
	}
	return true;
}

//***********
//Name: peekFront
//Purpose: outputs the value located at the front of the queue
//Parameters: None
//Operation: The function checks for a queue with data, then creates a variable to house the data we want to view.
//If data is found, it is copied into the temporary variable which is output to the screen
//If no data is found, it outputs a message stating such and returns garbage
//
//***********

template <class ElementType>
ElementType Queue<ElementType>::peekFront() const
{
	//cout << "p1" << endl;
	ElementType e;
	if (front != 0)
	{
		e = front->data;
		//cout << "p2.1" << endl;                                                                  //test
	}
	else
	{
		cout << "No front, returning garbage" << endl;
		//cout << "p2.2" << endl;                                                                  //test
	}
	return e;
}

//***********
//Name: Dequeue
//Purpose: Removes a value from the front of the queue
//Parameters: None
//Operation: If it finds data, it changes the front node to the following node, then deletes the old front which is being located by a new node pointer
//
//***********

template <class ElementType>
bool Queue<ElementType>::dequeue()
{
	if (front == 0)
	{
		cout << "Queue is empty ... nothing to pop" << endl;
		return false;
	}
	else
	if (front->next!=0)
	{
		Node * p = front;
		front = front->next;
		delete p;
	}
	else
	if (front->next == 0)
	{
		Node * p = front;
		front = 0;
		back = 0;
		delete p;
	}
	return true;
}

//***********
//Name: Length
//Purpose: counts the number of nodes in the queue
//Parameters: None
//Operation: This function, provided there is data in the queue, traverses the queue to the end while incrementing a counter at each node.
//
//***********

template <class ElementType>
int Queue<ElementType>::length() const
{
	int l = 0;
	if (front != 0){
		Node * p = front;
		l++;
		while (p->next != 0)
		{
			p = p->next;
			l++;
		}
	}
	return l;
}

//***********
//Name: isEmpty
//Purpose: Checks if there is data in the queue
//Parameters: None
//Operation: This simply returns a boolean value checking if the root pointer is pointing to data
//
//***********

template <class ElementType>
bool Queue<ElementType>::isEmpty() const
{
	return (front == 0);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//***********
//Name: Queue - constructor
//Purpose: constructs a default queue
//Parameters: Int passed by value, with a default of 10. This value is irrelevent to all operations.
//Operation: This function creates a queue without data, marking the front and back pointers as empty
//
//***********

template <class ElementType>
Queue<ElementType>::Queue(int s=10)
{
	front = 0;
	back = 0;
}

//***********
//Name: Queue - copy constructor
//Purpose: Creates a new queue that is a copy of an existing one
//Parameters: Queue passed by reference
//Operation: This Function copies an existing queue into a new queue by first creating a new node which the front of the new quue is directed towards
//a while loop occurs within which new nodes are created and are given the data from a pointer traversing the existing queue
//the back pointer is given the location of each new node and the last node is finally given a "next" value of zero
//
//***********

template <class ElementType>
Queue<ElementType>::Queue(const Queue<ElementType> & orig)
{
	Node * p = orig.front;
	Node * q = new Node;
	assert(q != 0);
	front = q;
	while (p != 0)
	{
		q->next = new Node;
		assert(q->next != 0);
		q = q->next;
		q->data = p->data;
		p = p->next;
		back = q;
	}
	back->next = 0;
}
	
//***********
//Name: assignment operator
//Purpose: Allows existing queues to copy other queues
//Parameters: Queue passed by reference
//Operation: The function the queue to be copied for data, if there is no data the current queue. IF there is no data, the newly emptied queue receiving the copy is left empty
//with data in the copied queue, a new node is created, then a while loop occurs within which new nodes are created and are given the data from a pointer traversing the existing queue
//the back pointer is given the location of each new node and the last node is finally given a "next" value of zero
//
//***********

template <class ElementType>
Queue<ElementType> & Queue<ElementType>::operator=(const Queue<ElementType>  & right)
{
	if (&right == &*this)
		return *this;
	Node * p = right.front;
	while (front != 0)
	{
		dequeue();
	}
	if (right.front == 0)
	{
		front = 0;
		back = 0;
	}
	else
	{
		//cout << "=1" << endl;
		//cout << "=2" << endl;
		Node * q = new Node;
		assert(q != 0);
		front = q;
		while (p != 0)
		{
			q->next = new Node;
			assert(q->next != 0);
			q = q->next;
			q->data = p->data;
			p = p->next;
			back = q;
		}
		back->next = 0;
	}
		return *this;
	
}

//***********
//Name: Destructor
//Purpose: deletes nodes and returns memory
//Parameters: None
//Operation: This function creates a new node pointer which it uses to traverse the queue from a while loop. in this loop, the pointer is given what is housed in front.
//Front then moves to its next node and the new pointer's node is deleted
//
//***********

template <class ElementType>
Queue<ElementType>::~Queue()
{
	Node*q;
	while (front != 0)
	{
		q= front->next;
		delete front;
		front = q;
	}
}

//***********
//Name: Display
//Purpose: Outputs the contents of the queue
//Parameters: ostream & out
//Operation: This function outputs the contents of thr queue, provided there are any, in a single line to either the screen or a file
//
//***********

template <class ElementType>
void Queue<ElementType>::Display(ostream & out) const
{
	out << "Contents of the queue ... " << endl;
	if (front == 0)
		out << "The queue is empty .. nothing to display" << endl;
	else
	{
		//cout << "else" << endl;
		Node * p = front;
		while (p != 0)
		{
			out << p->data << ' ';
			p = p->next;
			//cout << "one cycle" << endl;
		}
		out << endl;
	}
	out << "***********************" << endl;
}

//***********
//Name: Dump
//Purpose: Outputs the contents of the queue
//Parameters: ostream & out
//Operation: This function operates nearly identically to the Display function, even calling said function witht he addition of the pointer information to both front and back
//
//***********

template <class ElementType>
void Queue<ElementType>::Dump(ostream & out) const
{
	out << endl << "Queue Dump follows ..... " << endl;
	out << "front: " << front << endl;
	out << "back: " << back << endl;
	this.Display;
	out << "End of Queue Dump ..... " << endl << endl;
}
#endif