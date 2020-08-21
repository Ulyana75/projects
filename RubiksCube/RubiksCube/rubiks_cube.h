//
// Created by user on 09.05.2020.
//

#ifndef LAB8_RUBIKS_CUBE_H
#define LAB8_RUBIKS_CUBE_H

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include "cube_solution.h"

class Solution;

class RubiksCubeException {
public:
    explicit RubiksCubeException(std::string error)
        :error_(error) {}
    std::string get_error() {
        return error_;
    }
private:
    std::string error_;
};



class CFacet {
public:
    CFacet() = default;

    CFacet(int color) {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                facet[i][j] = color;
    }

    CFacet(CFacet const &other) {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                facet[i][j] = other.facet[i][j];
    }

    void clock_wise();
    void counter_clock_wise();

     int* operator[] (int i) {
        return facet[i];
    }

private:
    int facet[3][3];
};



class RubiksCube {
    friend class Solution;
public:
	std::queue<std::string> rotations;
	bool use_queue;
    RubiksCube() {
        U_ = CFacet(0);
        D_ = CFacet(5);
        R_ = CFacet(4);
        L_ = CFacet(1);
        F_ = CFacet(3);
        B_ = CFacet(2);
        write_solution_ = false;
		use_queue = true;
    }

    void R();
    void Rc();
    void L();
    void Lc();
    void F();
    void Fc();
    void B();
    void Bc();
    void D();
    void Dc();
    void U();
    void Uc();
    void U2() {U(); U();}
    void D2() {D(); D();}
    void R2() {R(); R();}
    void L2() {L(); L();}
    void F2() {F(); F();}
    void B2() {B(); B();}

    void y();

    void print(std::ostream &stream);
    void scramble(std::istream &stream);

    void solve();

    void write_solution(const std::string& str);

    void read_state(std::istream &stream);

    void generate_state();

    bool check_correct_state();

    bool write_solution_;

private:
    CFacet U_, D_, L_, R_, F_, B_;
};

#endif //LAB8_RUBIKS_CUBE_H
