#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>

class KinematicSolver {
private:
    std::vector<float> links;

public:
    void set_links(std::vector<float> new_links) { links = new_links; }

    std::vector<float> solve(float x, float y) {
        std::vector<float> joints;

        float b = sqrt(pow(x, 2) + pow(y, 2));
        float q1 = std::acos(x / b);
        float q2 = std::acos((pow(links[0], 2) - pow(links[1], 2) + pow(b, 2)) / (2 * b * links[0]));
        joints.push_back(q1 - q2);
        joints.push_back(M_PI - std::acos((pow(links[0], 2) + pow(links[1], 2) - pow(b, 2)) / (2 * links[0] * links[1])));

        return joints;
    }
};

int main()
{
    KinematicSolver solver;
    solver.set_links({ 4, 4 });
    std::vector<float> joints = solver.solve(5, 5);
    std::cout << joints[0] << ' ' << joints[1] << std::endl;
}