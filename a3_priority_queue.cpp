#include <iostream>
#include "a3_priority_queue.hpp"

using namespace std;

typedef PriorityQueue::DataType DataType;

PriorityQueue::PriorityQueue(unsigned int capacity){

	heap_= new DataType [capacity + 1];
	size_ = 0;
	capacity_ = capacity;
}


PriorityQueue::~PriorityQueue(){
	
	delete heap_;
}
  
// Returns the number of elements in the priority queue.
unsigned int PriorityQueue::size() const{

return size_;
}
// Returns true if the priority queue is empty, and false otherwise.
bool PriorityQueue::empty() const{

return size_==0;
}
// Returns true if the priority queue is full, and false otherwise.
bool PriorityQueue::full() const{

return size_ == capacity_;
}
// Prints the contents of the priority queue.
void PriorityQueue::print() const{
	cout<<"zero ";
	for(int i = 1; i <= size_; i++){
		cout<< heap_[i]<<" ";
	}
	cout<< endl;
}
// Returns the max element of the priority queue, but does not remove it.
DataType PriorityQueue::max() const{
	return (empty() ? -1:heap_[1]);
}


// Inserts value into the priority queue. Returns true if successful, and 
// false otherwise. Assume no duplicate entries will be entered.
bool PriorityQueue::enqueue(DataType val){
	
	if(full()){
		return false;
	}
	
	heap_[size_+1] = val;
	size_++;
	
	int cur=size_;
	
	while (cur!=1 && heap_[cur/2]<heap_[cur]){
		DataType temp = heap_[cur];
		heap_[cur]=heap_[cur/2];
		heap_[cur/2]=temp;
		cur/=2;
	}
	return true;
}
// Removes the top element with the maximum value (priority) and rearranges 
// the resulting heap. Returns true if successful, and false otherwise.
bool PriorityQueue::dequeue(){
	if (empty()){
		return false;
	}
	
	heap_[1]=heap_[size_];
	size_--;
	int cur=1;
	if (size_<=1){
		return true;
	}
	
	while ((heap_[cur]<heap_[cur*2] || heap_[cur]<heap_[cur*2+1]) && cur>=size_/2){
		if (size_<3){
			if (heap_[cur*2]>heap_[cur]){
				DataType temp = heap_[cur];
				heap_[cur]=heap_[cur*2];
				heap_[cur*2]=temp;
				cur*=2;
			}
		}
		else{
			if (heap_[cur*2]>heap_[cur*2+1]){
				DataType temp = heap_[cur];
				heap_[cur]=heap_[cur*2];
				heap_[cur*2]=temp;
				cur*=2;
			} else {
				DataType temp = heap_[cur];
				heap_[cur]=heap_[cur*2+1];
				heap_[cur*2+1]=temp;
				cur*=2;
				cur++;
			}
		}
	}
	return true;	
}
