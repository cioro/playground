//HPCII-Ex01
//(c) 2014 Rocio Molina Atienza, ETH Zurich
//This 
//
//
//
	
#ifndef GEMV_threads_RMA_HPP
#define GEMV_threads_RMA_HPP
#include <vector>
#include"GEMV_serial_RMA.hpp"
#include<thread>


typedef std::vector<double> vec_t;
typedef std::vector<vec_t> mat_t;

void GEMV_parallel(const mat_t& A, const vec_t& x, vec_t& y, const double& alpha, const double& beta, const int& nthreads)
{
//declare a vector of threads 
std::vector<std::thread> all_threads(nthreads);


//find size into which divide matrix rows
int chunk = y.size() / nthreads;

//threads loop.
for (int i=0; i < nthreads; i++)
{

int to = i == nthreads-1 ? y.size(): (i+1)*chunk;//determines where the thread ends. Last threads finishes at last row, otherwise ends at next chunk.


all_threads[i] = std::thread(GEMV,i*chunk,to,std::ref(A),std::ref(x),std::ref(y),alpha,beta);//each thread executes the multiplication of some rows with vector x;

}

	// Join threads
	for(std::thread &t : all_threads)
		t.join();



}
#endif 
