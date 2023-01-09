#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

VectorXd optimize_portfolio(const MatrixXd& covariance_matrix, const VectorXd& expected_returns) {
    int num_assets = expected_returns.size();

    // define the optimization function
    auto optimize_portfolio_inner = [&](const VectorXd& weights) {
        double portfolio_return = weights.dot(expected_returns);
        double portfolio_variance = weights.dot(covariance_matrix * weights);
        return -portfolio_return / std::sqrt(portfolio_variance);
    };

    // initialize the optimization
    VectorXd x0 = VectorXd::Ones(num_assets) / num_assets;
    VectorXd lower_bounds = VectorXd::Zero(num_assets);
    VectorXd upper_bounds = VectorXd::Ones(num_assets);

    // define the constraints
    auto sum_to_one = [&](const VectorXd& weights) {
        return weights.sum() - 1.0;
    };

    std::vector<std::pair<std::function<double(const VectorXd&)>, double>> constraints;
    constraints.emplace_back(sum_to_one, 0.0);

    // minimize the optimization function
    auto result = minimize_box_constrained(optimize_portfolio_inner, x0, lower_bounds, upper_bounds, constraints);
    return result.x;
}

int main() {
    VectorXd expected_returns(3);
    expected_returns << 0.1, 0.2, 0.15;

    MatrixXd covariance_matrix(3, 3);
    covariance_matrix << 0.05, 0.03, 0.02,
            0.03, 0.06, 0.04,
            0.02, 0.04, 0.09;

    VectorXd optimal_weights = optimize_portfolio(covariance_matrix, expected_returns);
    std::cout << optimal_weights << std::endl;
    return 0;
}

