#include <iostream>
#include <string>
using namespace std;

#include "a3_tests.hpp"

string get_status_str(bool status)
{
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main()
{

    PriorityQueueTest pqueue_test;

	string pqueue_test_descriptions[6] = {
      "Test1: New queue is valid",
      "Test2: Enqueue one item and then dequeue it",
      "Test3: Enqueue too many",
      "Test4: Enqueue too many then dequeue too many",
      "Test5: Dequeue 5, enqueue 10, with repeat",
      "Test6: Lots of enqueues and dequeues"
	};
	
	bool pqueue_test_results[6];
    pqueue_test_results[0] = pqueue_test.test1();
    pqueue_test_results[1] = pqueue_test.test2();
    pqueue_test_results[2] = pqueue_test.test3();
    pqueue_test_results[3] = pqueue_test.test4();
    pqueue_test_results[4] = pqueue_test.test5();
    pqueue_test_results[5] = pqueue_test.test6();

	cout << "PRIORITY QUEUE TESTING RESULTS \n";
	cout << "****************************** \n";
	for (int i = 0; i < 6; ++i) {
    	cout << pqueue_test_descriptions[i] << endl << get_status_str(pqueue_test_results[i]) << endl;
	}
	cout << endl;
    
    system("pause");
	return 0;
}
