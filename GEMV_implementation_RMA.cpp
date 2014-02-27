//HPCII-Ex01
//(c) 2014 Rocio Molina Atienza, ETH Zurich

#include"GEMV_serial_RMA.hpp"
#include"GEMV_threads_RMA.hpp"
#include<random>
#include<vector>
#include<iostream>
#include<chrono>
#include"utils/ArgumentParser.h"



int main(int argc, char *argv[])
{
	ArgumentParser parser(argc, argv);
	int nthreads  = parser("-nthreads").asInt(0);	// number of steps, default 10
	const int invecsize = parser("-matsize").asInt(1000);	// number of steps, default 10

//Set up random number genarator. 
 
unsigned seed = 1992;
std::mt19937 generator (seed); 
std::uniform_real_distribution<double> distribution(0.0,1.0);


//Declare variables
//int nthreads = 0;
double alpha = 1.0;
double beta  = 1.0;
std::vector<double> x;
std::vector<double> y;
std::vector<std::vector<double>> A;

//unsigned invecsize = 1000;
unsigned matrows = invecsize;

x.resize(invecsize);//gives a size to vector x. Avoids memory allocation issues
y.resize(matrows);//
A.resize(matrows);//

//Control # threds
    if(nthreads == 0){
        nthreads = std::thread::hardware_concurrency();
    }

std::cout<<"the number of threads is " << nthreads << std :: endl;

//Fill in matrix & vectors

for (unsigned int i=0; i < matrows ;i++)
	{
	 y[i] = distribution(generator);		
		A[i].resize(invecsize);	
				
			for (unsigned int j=0; j < invecsize ; j++)

			{
				x[j] = distribution(generator);
				A[i][j] = distribution(generator);
									
			}		
	}



//Calculate matrix  vector product

//------------------------Serial---------------------------------------

std::chrono::high_resolution_clock::time_point s_start, s_end;
s_start = std::chrono::high_resolution_clock::now();

GEMV(0,matrows,A,x,y,alpha,beta);

s_end = std::chrono::high_resolution_clock::now();
  
std::chrono::duration<double> elapsed_seconds= std::chrono::duration_cast
	<std::chrono::duration<double>>  (s_end-s_start);
  
std::cout << "elapsed time serial : " << elapsed_seconds.count() << "s\n";
//---------------------------------------------------------------------


//-----------------------Parallel----------------------------------
s_start = std::chrono::high_resolution_clock::now();

GEMV_parallel(A,x,y,alpha,beta,nthreads);

s_end = std::chrono::high_resolution_clock::now();
  
elapsed_seconds= std::chrono::duration_cast
	<std::chrono::duration<double>>  (s_end-s_start);
  
std::cout << "elapsed time parallel: " << elapsed_seconds.count() << "s\n";
//------------------------------------------------------------------

/*for (unsigned int n=0; n<matrows; n++)
{
	std::cout<<y[n]<<std::endl;

}*/

return 0;
}

