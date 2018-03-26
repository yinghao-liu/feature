#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex mtx;
condition_variable cv;
int flag=0;

void print_id(int id)
{
	unique_lock<mutex> lock(mtx, defer_lock);
	while (1){
		lock.lock();
		while (flag != id){
			cv.wait(lock);
		}
		//cout<<id;
		//cout<<pthread_self()<<" ";
		cout<<this_thread::get_id()<<" ";
		flag++;
		if (flag > 3){
			flag = 1;
			cout<<endl;
			sleep(1);
		}
		cv.notify_all();
		lock.unlock();
	}
}

int main(void)
{
	thread threads[3];
	flag=1;
	for (int i=0; i<3; i++){
		threads[i] = thread(print_id, i+1);
	}
		
	for (auto &a : threads){
		a.join();
	}
	return 0;
}
