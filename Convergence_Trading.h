#include <iostream>
#include <cmath>

const double threshold = 0.01; // convergence threshold

int main() {
    double stock1_price = 100.0; // current price of stock 1
    double stock2_price = 105.0; // current price of stock 2
    double position = 0.0; // current position (long or short)

    while (true) {
        double diff = stock1_price - stock2_price; // price difference

        if (diff > threshold && position <= 0) { // buy stock 1, sell stock 2
            position = 1.0;
            std::cout << "Buying stock 1, selling stock 2" << std::endl;
        } else if (diff < -threshold && position >= 0) { // sell stock 1, buy stock 2
            position = -1.0;
            std::cout << "Selling stock 1, buying stock 2" << std::endl;
        }

        // update stock prices
        stock1_price = get_new_price(stock1_price);
        stock2_price = get_new_price(stock2_price);
    }

    return 0;
}
