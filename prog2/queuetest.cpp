#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

int main()
{
	//Queue<string> test1(1);
	//test1.Display(cout);
	//Queue<string> test2(1);
	//cout << "t1" << endl;
	//test2= test1;
	//cout << "t2" << endl;
	//test1.enqueue("str1");
	//cout << "t3" << endl;
	//test2 = test1;
	//cout << "t4" << endl;
	//test2.Display(cout);
	//test1.dequeue();
	//cout << "t5" << endl;
	//test1.Display(cout);
	//test1.dequeue();
	//cout << "t6" << endl;
	//test1.Display(cout);
	//test2.Display(cout);
	//cout << "peek: "<<test2.peekFront() << endl;
	//cout << "t7" << endl;
	//Queue<string> test3(test2);
	//cout << "t8" << endl;
	//test3.Display(cout);
	//if (test3.isEmpty())
	//	cout << "is empty" << endl;
	//else
	//	cout << "not empty" << endl;
	//cout << "t9" << endl;
	Queue<string> test3;
	test3.enqueue("str1");
	test3.enqueue("str2");
	test3.enqueue("str3");
	test3.enqueue("str4");
	test3.enqueue("str1");
	test3.enqueue("str1");
	test3.enqueue("str1");
	test3.enqueue("str1");
	test3.enqueue("str1");
	cout << test3.length() << endl;
	cout << "t10" << endl;
	test3 = test3;
	return 0;
}