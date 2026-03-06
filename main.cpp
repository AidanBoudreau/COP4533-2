#include <iostream>
using namespace std;
#include <vector>

int main()
{
    int k = 2;
    int m=9;
    vector<int> r{1,2,3,3,2,1,2,1,3};

    if (k < 1){
        std::cout << "k needs to be greater than or equal to 1" << std:: endl;
        return -1;
    }

    cout << "k: " << k << endl;
    cout << "m: " << m << endl;
    cout << "r: ";
    for (int i = 0; i < r.size(); i++) {
        cout << r[i] << " ";
    }
}