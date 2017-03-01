#ifndef A3_TESTS_HPP
#define A3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>

#include "a3_priority_queue.hpp"

typedef PriorityQueue::DataType DataType;

DataType arrayMax( DataType* array, int n )
{
    DataType max = array[0];
    for( int i = 1; i < n; i++ )
        if( array[i] > max )
            max = array[i];
    return max;
}

bool enqueue( int n, PriorityQueue &q, int cap, DataType* in, int &nin, DataType* out, int &nout )
{
    for( int i = 0; i < n; i++ )
    {
        bool full0 = nin == cap;
        ASSERT_TRUE( q.size() == nin );
        ASSERT_TRUE( q.full() == full0 );
        ASSERT_TRUE( q.empty() == (nin == 0) );

        ASSERT_TRUE( q.enqueue( out[nout-1] ) != full0 );
        if( !full0 )
            in[nin++] = out[--nout];

        ASSERT_TRUE( q.size() == nin );
        ASSERT_TRUE( q.full() == (nin == cap) );
        ASSERT_TRUE( !q.empty() );

        ASSERT_TRUE( q.max() == arrayMax( in, nin ) );
    }
    return true;
}

bool dequeue( int n, PriorityQueue &q, int cap, DataType* in, int &nin, DataType* out, int &nout )
{
    sort( in, in+nin );
    for( int i = 0; i < n; i++ )
    {
        bool empty0 = nin == 0;
        ASSERT_TRUE( q.size() == nin );
        ASSERT_TRUE( q.full() == (nin == cap) );
        ASSERT_TRUE( q.empty() == empty0 );

        ASSERT_TRUE( q.dequeue() != empty0 );
        if( !empty0 ) {
            nin--;
            // cout << "dequeued " << in[nin] << endl;
        }

        ASSERT_TRUE( q.size() == nin );
        ASSERT_TRUE( !q.full() );
        ASSERT_TRUE( q.empty() == (nin == 0) );

        if( nin > 0 )
            ASSERT_TRUE( q.max() == arrayMax( in, nin ) );
    }
    return true;
}

class PriorityQueueTest {
public:
	// New queue is valid
  bool test1()
  {
    PriorityQueue q(16);
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

	// Enqueue one item and then dequeue it
  bool test2()
  {
    PriorityQueue q(2);
    ASSERT_TRUE( q.enqueue(10) );
    ASSERT_TRUE( !q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 1 );
    ASSERT_TRUE( q.max() == 10 );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

	// Enqueue too many
  bool test3()
  {
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(5) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(3) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(4) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(7) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );
    return true;
  }
  
  // Enqueue too many then dequeue too many
bool test4()
{
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(5) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(3) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(4) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(7) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.max() == 4 );
    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.max() == 3 );
    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );

    ASSERT_TRUE( !q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    return true;
}

	// dequeue 5, enqueue 10, with repeat
bool test5()
{
    const int cap = 15;
    const int nout1 = 10;
    int nout = nout1;
    int out[nout1] = {9,5,23,1,3,15,14,1,5,3};
    int nin = 0;
    int in[nout1];

    PriorityQueue q(cap);
    ASSERT_TRUE( dequeue( 5, q, cap, in, nin, out, nout ) );
    ASSERT_TRUE( enqueue( 10, q, cap, in, nin, out, nout ) );
    
    return true;
}

	// enqueue 50, dequeue 30, enqueue max, dequeue max, enqueue 25
bool test6()
{
    const int cap = 64;
    const int nout1 = 150;
    int nin = 0;
    int in[nout1];
    int nout = nout1;
    int out[nout1];
    for( int i = 0; i < nout1; i++ ) out[i] = (i % 75) - 25;
    random_shuffle( out, out+nout );

    PriorityQueue q(cap);
    ASSERT_TRUE( enqueue( 50, q, cap, in, nin, out, nout ) );
    
    ASSERT_TRUE( dequeue( 30, q, cap, in, nin, out, nout ) );
    ASSERT_TRUE( enqueue( 10, q, cap, in, nin, out, nout ) );    
    
    ASSERT_TRUE( enqueue( 40, q, cap, in, nin, out, nout ) );
    ASSERT_TRUE( dequeue( 70, q, cap, in, nin, out, nout ) );    
    ASSERT_TRUE( enqueue( 25, q, cap, in, nin, out, nout ) );    
    return true;
}
};

#endif
