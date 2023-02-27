#include <iostream>
#include "libxl.h"
#include <vector>
#include <cmath>

using namespace libxl;

double discounted_cash_flow(double cash_flow[], double discount_rate[], int n)
{
    double present_value = 0;
    for (int i = 0; i < n; i++)
    {
        present_value += cash_flow[i] / pow(1 + discount_rate[i], i + 1);
    }
    return present_value;
}

int main() {
    Book* book = xlCreateBook();
    if(book) {
        if(book->load("example.xls")) { // replace "example.xls" with the path to your Excel file
            Sheet* sheet = book->getSheet(0); // get the first sheet of the Excel file
            if(sheet) {
                int rows = sheet->lastRow();
                int cols = sheet->lastCol();
                std::vector<double> cash_flow;
                std::vector<double> discount_rate;
                for(int row = 0; row < rows; ++row) {
                    double cash_flow_val = sheet->readNum(row+1, 1); // read the value of the cash flow column
                    double discount_rate_val = sheet->readNum(row+1, 2); // read the value of the discount rate column
                    cash_flow.push_back(cash_flow_val); // store the cash flow value in a dynamic array
                    discount_rate.push_back(discount_rate_val); // store the discount rate value in a dynamic array
                }
                int n = cash_flow.size(); // get the size of the dynamic arrays
                double* cash_flow_arr = &cash_flow[0]; // convert the cash flow dynamic array to a C-style array
                double* discount_rate_arr = &discount_rate[0]; // convert the discount rate dynamic array to a C-style array
                double present_value = discounted_cash_flow(cash_flow_arr, discount_rate_arr, n); // perform discounted cash flow on the arrays
                std::cout << "Present Value: " << present_value << std::endl; // print the result to the console
            }
        }
        book->release();
    }
    return 0;
}
