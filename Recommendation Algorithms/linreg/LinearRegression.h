#pragma once
#include <functional>
#include <vector>

namespace LR {
class linear_regression {
   public:
    linear_regression(std::vector<std::vector<double> > dat, std::vector<double> resp) : b(0),
                                                                                         weights(dat[0].size()),
                                                                                         gradient(dat[0].size() + 1),
                                                                                         fitted(resp.size()) {
        data = std::move(dat);
        response = std::move(resp);
        sampleSize = response.size();
        numFeatures = data[0].size();
    }

    void perform_LR(double alpha, size_t repeat) {
        if (data.size() != response.size()) {
            throw std::invalid_argument("sizes do not match");
        }
        optimize(alpha, repeat);
    }

   private:
    // set sample size, calculate fitted values
    double dcdw_i(size_t j) {
        double total = 0;
        for (size_t i = 0; i < sampleSize; ++i) {
            total += 2 * (fitted[i] - response[i]) * data[i][j];
        }
        return total;
    }

    double dcdb() {
        double total = 0;
        for (size_t i = 0; i < sampleSize; ++i) {
            total += 2 * sampleSize * (fitted[i] - response[i]);
        }
        return total;
    }

    void update_gradient() {
        for (int i = 0; i < weights.size(); ++i) {
            gradient[i] = dcdw_i(i);
        }
        gradient.back() = dcdb();
    }

    void update_params(double alpha) {
        for (size_t i = 0; i < numFeatures; ++i) {
            weights[i] -= alpha * gradient[i];
        }
        b -= alpha * gradient.back();
    }

    void optimize(double alpha, size_t repeat) {
        for (size_t i = 0; i < repeat; ++i) {
            update_gradient();
            update_params(alpha);
            update_fitted();
            auto err = std::move(error());
            double cost = Residual_sum_squares(err);
        }
    }

    std::vector<double> error() {
        std::vector<double> err;
        err.reserve(response.size());
        for (size_t i = 0; i < data.size(); i++) {
            err.push_back(fitted[i] - response[i]);
        }
        return err;
    }

    void update_fitted() {
        size_t index = 0;
        for (auto& row : data) {
            double sum = 0;
            for (size_t i = 0; i < data[0].size(); ++i) {
                sum += weights[i] * row[i];
            }
            sum += b;
            fitted[index++] = sum;
        }
    }

    double Residual_sum_squares(std::vector<double>& err) {
        double total = 0;
        for (size_t i = 0; i < err.size(); i++) {
            total += err[i] * err[i];
        }
        return total;
    }

    // variables
   private:
    std::vector<std::vector<double> > data;
    std::vector<double> response;
    std::vector<double> fitted;
    std::vector<double> weights;
    std::vector<double> gradient;
    double b;

    size_t sampleSize;
    size_t numFeatures;
};

}