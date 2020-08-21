//
// Created by user on 10.05.2020.
//

#ifndef LAB8_CUBE_SOLUTION_H
#define LAB8_CUBE_SOLUTION_H

#include "rubiks_cube.h"

class RubiksCube;

class Solution {
public:
    explicit Solution(RubiksCube& cube_)
        : cube(cube_)
    {
        solve();
    }

	void solve();
private:

    void cross();
    void check10(int &k);
    void check12(int &k);
    void check01(int &k);
    void check21(int &k);
    void check_down(int &k);
    void turn_up(int i, int j);

    void down_corners();
    void find_corner(int a, int b);
    void place_corner();

    void down_edges();
    void find_edge(int a, int b);
    void place_edge_case1();
    void place_edge_case2();

    void cross_up();
    void make_cross_up_case1();
    void make_cross_up_case2();

    void orient_edges();
    void algorithm_for_edges();
    int count_rights();
    bool find_position();

    void place_up_corners();
    int count_corners();
    void algorithm_for_corners();

    void orient_corners();
    void algorithm_for_orient();
    void place_right();

    RubiksCube &cube;
};

#endif //LAB8_CUBE_SOLUTION_H
