#include<cmath>
#include"eigen3/Eigen/Core"
#include"eigen3/Eigen/Dense"
#include<iostream>

using namespace std;

int main() {
    Eigen::Vector3d p(2, 1, 1);
    int theta = 45;
    Eigen::Matrix3d rotate, translate;
    rotate << cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1;
    p = rotate * p;
    cout << p << endl;
    translate << 1, 0, 1, 0, 1, 2, 0, 0, 1;
    p = translate * p;
    cout << p;
    return 0;
}