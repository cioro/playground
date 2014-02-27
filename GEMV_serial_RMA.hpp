//HPCII-Ex01
//(c) 2014 Rocio Molina Atienza, ETH Zurich
	
#ifndef GEMV_HPP
#define GEMV_HPP
#include <vector>


typedef std::vector<double> vec_t;
typedef std::vector<vec_t> mat_t;

void GEMV(const int& from, const unsigned int& to, const mat_t& A, const vec_t& x, vec_t& y, const double& alpha, const double& beta)
{

//Better practice-create tests for coherent vector and matrix size
	for (unsigned int i = from; i < to ;i++)
		{
			for (unsigned int j=0; j < A[0].size() ; j++)

			{
				y[i] = alpha*A[i][j]*x[j] + beta*y[i];
									
			}		
		}


}
#endif 
