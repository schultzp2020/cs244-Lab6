#include "Collection.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"
#include "ListNode.h"
#include "MutableLinkedListIterator.h"
#include "OrderedLinkedList.h"
#include <functional>
#include <random>
#include <iostream>
#include <cassert>

using namespace std;

double sum(const Collection<double>& values);

int main() 
{
	ArrayList<double> arrayList(10);
	LinkedList<double> linkedList;
	double total{ 0 };

	const double lower_bound = 0;
	const double upper_bound = 10000;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	default_random_engine re;

	for (size_t i = 0; i < 10; i++)
	{
		double a_random_double = unif(re);

		total += a_random_double;
		arrayList.add(a_random_double);
		linkedList.addLast(a_random_double);
	}

	cout << "Array List Elements: " << arrayList << endl;
	cout << "Linked List Elements: " << linkedList << endl;

	cout << endl;

	cout << "Testing Part 1" << endl;

	cout << endl;

	cout << "Testing ArrayList sum" << endl;
	Collection<double> &c(arrayList);

	assert(sum(c) - total < 0.001);
	cout << "Passed!" << endl;

	cout << endl;

	cout << "Testing LinkedList sum" << endl;
	c = linkedList;

	assert(sum(c) - total < 0.001);
	cout << "Passed!" << endl;

	cout << endl;

	cout << "Part 1 complete!" << endl;
	
	cout << endl;

	cout << "Testing Part 2" << endl;

	cout << endl;

	cout << "Testing OrderedList remove" << endl;
	OrderedLinkedList<double,
		std::function<bool(const double&, const double&)>> orderedList
	{ 
		[](const double& x, const double& y) -> bool 
		{ 
			return x < y; 
		}
	};

	for (size_t i = 0; i < 10; i++)
	{
		orderedList.add(i + 1);
	}

	cout << "Ordered List elements: " << orderedList << endl;

	assert(orderedList.remove(1));
	assert(orderedList.remove(5));
	assert(!orderedList.remove(0));
	assert(!orderedList.remove(11));

	cout << "Ordered List elements: " << orderedList << endl;

	cout << "Passed!" << endl;

	cout << endl;

	cout << "Part 2 complete!" << endl;
	
}

double sum(const Collection<double>& values)
{
	double sum;

	values.forEach([&sum](double value)
	{
		sum += value;
	});

	return sum;
}