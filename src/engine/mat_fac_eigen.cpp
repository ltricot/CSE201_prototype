#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

class mat_factorization
{
  public:
    // Data Members
    int lat_feat;
    int users, brands;
    double alpha, beta;
    int num_iterations, samples_count;

    // Matrices
    Eigen::MatrixXd matrix;
    Eigen::MatrixXd P;
    Eigen::MatrixXd Q;

    // Bias
    double global_bias;

  // Constructor
  mat_factorization(Eigen::MatrixXd R, int K, double a, double b, int num_iter)
  {
      lat_feat = K;

      users = R.rows();
      brands = R.cols();
      matrix.resize(users, brands);
      P.resize(users, lat_feat);
      Q.resize(lat_feat, brands);

      double sum = 0;
      int tot = 0;
      for (int i = 0; i < users; i++)
      {
          for(int j = 0; j < brands; j++)
          {
            if (R(i,j) != 0){
                matrix(i, j) = R(i, j);
                sum += R(i, j);
                tot += 1;
            }
          }

        }
      std::cout<< matrix <<std::endl;


      global_bias = sum/(tot);
      alpha = a;
      beta = b;
      num_iterations = num_iter;

    }

  double error()
  {
    double e = 0;
    for(int i = 0; i < users; i++)
              {
                for (int j = 0; j < brands; j++)
                {
                  if (matrix(i, j) > 0)
                  {
                    double sum = 0;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      sum += P(i, k)*Q(k, j);
                    }

                    e += std::pow(matrix(i, j) - sum, 2);

                    for(int k = 0; k < lat_feat; k++)
                    {
                      e += (beta/2) * ( std::pow(P(i, k), 2) + std::pow(Q(k, j), 2) );
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
       P = Eigen::MatrixXd::Random(users, lat_feat);
       Q = Eigen::MatrixXd::Random(lat_feat, brands);

        double error_trial = 0;
        for(int count = 0; count < num_iterations; count++)
        {

              for(int i = 0; i < users; i++)
              {
                for (int j = 0; j < brands; j++)
                {
                  if (matrix(i, j) > 0)
                  {

                    // Compute the error
                    double sum = 0;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      sum += P(i, k)*Q(k, j);
                    }

                    double eij = matrix(i, j) - sum;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      P(i, k) += alpha * (2 * eij * Q(k, j) - beta * P(i, k));
                      Q(k, j) += alpha * ( 2 * eij * P(i, k) - beta * Q(k, j));
                    }

                  }
                }
              }

              error_trial = error();
              if (error_trial < 0.000001){
                break;
              }

        }


    // Once the matrices have been updated we just compute the product of PQ^t
    // And print it
    Eigen::MatrixXd result(users, brands);

    // Next we want to do matrix multiplication

    result = P*Q;
    std::cout<< "Answer" << std::endl;

    std::cout<< result << std::endl;

    std::cout << "Error = " << error_trial << std::endl;
      }

};

int main(){

 Eigen::MatrixXd mat(5,4);
   mat(0, 0) = 5;
   mat(0, 1) = 3;
   mat(0, 3) = 1;

   mat(1, 0) = 4;
   mat(1, 3) = 1;

   mat(2, 0) = 1;
   mat(2, 1) = 1;
   mat(2, 3) = 5;

   mat(3, 0) = 1;
   mat(3, 3) = 4;

   mat(4, 1) = 1;
   mat(4, 2) = 5;
   mat(4, 3) = 4;

  int lat_feat = 3;
  double alpha = 0.0002;
  double beta = 0.02;
  int num_iter = 50000;
  mat_factorization classifier(mat, lat_feat, alpha, beta, num_iter);
  classifier.train();


  return 0;
}
