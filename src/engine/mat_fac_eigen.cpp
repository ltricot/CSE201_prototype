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
      P = (Eigen::MatrixXd::Random(users, lat_feat) + Eigen::MatrixXd::Constant(users, lat_feat, 1.))*0.5;
      Q = (Eigen::MatrixXd::Random(lat_feat, brands) + Eigen::MatrixXd::Constant(lat_feat, brands, 1.))*0.5;

    }

    void multiplicative_update()
  {
    Q = Q.cwiseProduct((P.transpose()*matrix).cwiseQuotient(P.transpose()*P*Q));
    P = P.cwiseProduct((matrix*Q.transpose()).cwiseQuotient(P*Q*Q.transpose()));
  }

    void kullback_leibler()
    {
     Eigen::MatrixXd one = Eigen::MatrixXd::Constant(users, brands, 1.);
     Q = Q.cwiseProduct((P.transpose()*(matrix.cwiseQuotient(P*Q))).cwiseQuotient(P.transpose()*one));
     P = P.cwiseProduct(((matrix.cwiseQuotient(P*Q)*Q.transpose())).cwiseQuotient(one*Q.transpose()));
    }

  void itakura_saito()
  {
    Eigen::MatrixXd PQ = P*Q;
    Eigen::MatrixXd PQ_square = PQ.cwiseProduct(PQ);
    Eigen::MatrixXd one = Eigen::MatrixXd::Constant(users, brands, 1.);

    Q = Q.cwiseProduct(P.transpose()*(matrix.cwiseQuotient(PQ_square)));
    P = P.cwiseProduct(((matrix.cwiseQuotient(PQ_square))*Q.transpose()).cwiseQuotient((one.cwiseQuotient(P*Q)*Q.transpose())));
  }


  void train_2(std::string update_rule)
  { double error_trial = 0;
      if (update_rule.compare("mu"))
      {

      for (int count = 0;count < num_iterations; count ++)
        {
            multiplicative_update();
            error_trial = (matrix-P*Q).squaredNorm();
            if (error_trial < 0.001)
                {
                    break;
                }
        }
      }
      else if (update_rule.compare("klb"))
      {

      for (int count = 0;count < num_iterations; count ++)
        {
            kullback_leibler();
            error_trial = (matrix-P*Q).squaredNorm();
            if (error_trial < 0.001)
                {
                    break;
                }
        }
      }
      else if (update_rule.compare("ita"))
      {
         for (int count = 0;count < num_iterations; count ++)
        {
            itakura_saito();
            error_trial = (matrix-P*Q).squaredNorm();
            if (error_trial < 0.001)
                {
                    break;
                }
        }
      }

    Eigen::MatrixXd result(users, brands);

    // Next we want to do matrix multiplication

    result = P*Q;
    std::cout<< "Answer" << std::endl;

    std::cout<< result << std::endl;

    std::cout << "Error = " << error_trial << std::endl;

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
                      double dot = 0;
                    for(int k = 0; k < lat_feat; k++)
                    {
                      dot += P(i, k)*Q(k, j);
                    }

                    e += std::pow(matrix(i, j) - dot, 2);

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

      // R = PQ^t
        // Initialize the matrix P with dimension user*lat_feat


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
              if (error_trial < 0.001){
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
 mat << 5,0,0,3,
       4,0,0,1,
       1,0,0,5,
       1,0,0,4,
       0,1,0,4;

  int lat_feat = 2;
  double alpha = 0.002;
  double beta = 0.02;
  int num_iter = 50000;
  mat_factorization classifier(mat, lat_feat, alpha, beta, num_iter);
  classifier.train_2("ita");
  classifier.train();



  return 0;
}
