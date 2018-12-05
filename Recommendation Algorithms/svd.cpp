#include <iostream>
#include <cstdlib>
#include <stdlib.h>  
#include <random>
#include <algorithm>
#include <vector> 
#include <cmath>


class mat_factorization
{
  public:
    // Data Members
    int lat_feat;
    int users, brands;
    double alpha, beta;
    int num_iterations, samples_count;
    
    // Matrices
    std::vector< std::vector <double> > matrix;
    std::vector< std::vector <double> > P;
    std::vector< std::vector <double> > Q;
    std::vector< std::vector <double> > samples;
  
    // Bias 
    std::vector<double> b_u;
    std::vector<double> b_i;
    double global_bias;

  // Constructor
  mat_factorization(std::vector<std::vector<double>> R, int K, double a, double b, int num_iter)
  {
      lat_feat = K; 

      users = R.size(); 
      brands = R[0].size();
      double sum = 0;
      int tot = 0;
      for (int i = 0; i < users; i++)
      { 
          std::vector<double> temp; 
          for(int j = 0; j < brands; j++)
          {
            if (R[i][j] != 0){
                
                sum += R[i][j];
                tot += 1;
            }
            
            temp.push_back(R[i][j]);
          }

        matrix.push_back(temp);
        }
      std::cout<< "Input Matrix"<<std::endl;
      print_matrix(matrix);

      global_bias = sum/(tot);
      alpha = a;
      beta = b;
      num_iterations = num_iter;
     
      /*
      std::cout<< "Initial values of P" << std::endl;
      print_matrix(P);
      std::cout<< "Initial values of Q" << std::endl;
      print_matrix(Q);
      */
      for(int i = 0;i < users; i++){
        b_u.push_back(0);
      }
      for(int i = 0; i < brands; i++ ){
        b_i.push_back(0);
      }
      /*
      std::cout<< "Initial values of b_u" << std::endl;
      print_vector(b_u);
      std::cout<< "Initial values of b_i" << std::endl;
      print_vector(b_i);
      */
      
    }

  void print_vector(std::vector<double> vec)
  {
    int n = vec.size();
    for(int i = 0; i< n; i++){
      std::cout<< vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------"<< std::endl;
  }

  void print_matrix(std::vector<std::vector<double>> mat)
  {
    int row = mat.size();
    int col = mat[0].size();

    for(int i = 0;i < row; ++i){
      for (int j = 0; j< col; ++j){
        std::cout << mat[i][j] << " ";
      }
      std::cout << std::endl; 
    }
    std::cout << " ---------------------------------------"<< std::endl;
  }

  double error(int i, int j){
    double sum = 0;
    for (int k = 0; k < lat_feat; k++){
      sum+= P[i][k]*Q[k][j];
    }
    double error = std::pow(std::pow(matrix[i][j] - sum, 2), 0.5);
    return error;
  }


  double error()
  {
    double e = 0;
    for(int i = 0; i < users; i++)
              {
                for (int j = 0; j < brands; j++)
                {
                  if (matrix[i][j] > 0)
                  {
                    double sum = 0;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      sum += P[i][k]*Q[k][j];
                    }

                    e += std::pow(matrix[i][j] - sum, 2);

                    for(int k = 0; k < lat_feat; k++)
                    {
                      e += (beta/2) * ( std::pow(P[i][k], 2) + std::pow(Q[k][j], 2) );
                    }
                  }
                }
              }
    return e;
  }
  
  void train()
      {

      std::default_random_engine generator;
      std::uniform_real_distribution<double> distribution(0.0,1.0);

      // R = PQ^t
        // Initialize the matrix P with dimension user*lat_feat
        for(int i = 0; i < users; ++i)
        {
           std::vector<double> temp; 
           for (int j = 0; j < lat_feat; ++j){

             double r = distribution(generator);
             temp.push_back(r); 
           }
           P.push_back(temp);
        }
        // Initialize the matrix Q with dimension brands*lat_feat
        // We set Q = Q^t
        for(int i = 0; i < lat_feat; ++i)
        {
           std::vector<double> temp; 
           for (int j = 0; j < brands; j++){
             double r = distribution(generator);
             temp.push_back(r); 
           }
           Q.push_back(temp);
        }

        double error_trial = 0;
        for(int count = 0; count < num_iterations; count++)
        {
             
              for(int i = 0; i < users; i++)
              {
                for (int j = 0; j < brands; j++)
                {
                  if (matrix[i][j] > 0)
                  {

                    // Compute the error 
                    double sum = 0;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      sum += P[i][k]*Q[k][j];
                    }

                    double eij = matrix[i][j] - sum;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      P[i][k] = P[i][k] + alpha * (2 * eij * Q[k][j] - beta * P[i][k]);
                      Q[k][j] = Q[k][j] + alpha * ( 2 * eij * P[i][k] - beta * Q[k][j]);
                    }

                  }
                }
              }

              double error_trial = error();
              if (error_trial < 0.0001){
                break;
              }

        }


    // Once the matrices have been updated we just compute the product of PQ^t
    // And print it
    std::vector<std::vector<double>> result;

    // Initialize the result
    for(int i = 0; i < users; ++i){
      std::vector<double> temp;
      for(int j = 0; j < brands; ++j){
        temp.push_back(0);
      }
      result.push_back(temp);
    }

    // Next we want to do matrix multiplication


    for (int i = 0; i < users; ++i)
    {
        for (int j = 0; j < brands; ++j)
        {
            for (int k = 0; k < lat_feat ; ++k)
            {
                result[i][j] += P[i][k] * Q[k][j];
            }

            //result[i][j] += global_bias + b_u[i] + b_i[j];
        }
    }
    std::cout<< "Approximate Matrix after Factorization" << std::endl;
    print_matrix(result);
      }

};

int main(){
std::vector<std::vector<double> > test_matrix{ 
    {5, 3, 0, 1},
    {4, 0, 0, 1},
    {1, 1, 0, 5},
    {1, 0, 0, 4},
    {0, 1, 5, 4},
  };
  int lat_feat = 2;
  double alpha = 0.0002; 
  double beta = 0.02;
  int num_iter = 5000;
  mat_factorization classifier(test_matrix, lat_feat, alpha, beta, num_iter);
  classifier.train();
  return 0;
}
