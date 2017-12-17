/*Program to Sequentially estimate the mean and variance from the data given from the univariate gaussian data generator*/
/*Author: Siffi Singh */
/*Dated: 27/10/2017 */

/* standard Header */
#include <bits/stdc++.h>
#include <random>
#include <cmath>
using namespace std;
# define two_pi 2.0*3.14159265358979323846
/*Generating guassian distributed data*/
double guassian(double mu, double sigma) {
        double z0, z1;
        double epsilon = std::numeric_limits < double > ::min();
        bool generate;
        generate = !generate;
        if (!generate)
            return z1 * sigma + mu;
        double u1, u2;
        do {
            u1 = rand() * (1.0 / RAND_MAX);
            u2 = rand() * (1.0 / RAND_MAX);
        } while (u1 <= epsilon);
        z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
        z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
        return z0 * sigma + mu;
    }
    /*Driver Function*/
int main() {
    double mu, sigma;
    cout << "Enter Mean: ";
    cin >> mu;
    cout << "Enter Variance: ";
    cin >> sigma;
    int data;
    cout << "Enter number of data points you want to generate: ";
    cin >> data;
    /*Variable Declarations*/
    double ans;
    int count[10000] = {
        0
    };
    double val[10000];
    int freq[10000] = {
        0
    };
    double p[10000];
    for (int i = 0; i <= data; i++) {
        ans = guassian(mu, sigma);
        int a = (int) floor(ans);
        count[a]++; //calculating frequency of data generated
        val[i] = ans;
        freq[i] = count[a];
    }
    for (int i = 0; i < data - 1; i++) {
        for (int j = 0; j < data - i - 1; j++) {
            if (val[j] > val[j] + 1) {
                swap(val[j], val[j + 1]);
                swap(freq[j], freq[j + 1]);
            }
        }
    }
    /*Printing guassian distribution*/
    for (int i = 0; i < data; i++) {
        cout << val[i] << " ";
        p[i] = (double) freq[i] / data; //calculating probability values
        for (int j = 0; j < freq[i]; j++)
            cout << "*";
        cout << endl;
    }
    double mu_cal = 0;
    for (int i = 0; i < data; i++) {
        mu_cal += p[i] * val[i];
        //cout<<p[i]<<" "<<val[i]<<endl;
        cout << "Mean in " << i + 1 << "th iteration is: " << mu_cal << endl; //mean in each iteration printed until convergence
        if (floor(mu_cal) == floor(mu))
            break;
    }
    double sigma_cal = 0;
    for (int i = 0; i < data; i++) {
        sigma_cal += (p[i] * pow((val[i] - mu_cal), 2));
        //cout<<p[i]<<" "<<(val[i]-mu_cal)<<endl;
        cout << "variance in " << i + 1 << "th iteration is: " << sigma_cal << endl; //variance in each iteration printed until convergence
        if (floor(sigma_cal) == floor(sigma))
            break;
    }
    return 0;
}



