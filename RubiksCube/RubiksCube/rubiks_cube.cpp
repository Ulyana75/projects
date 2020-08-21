//
// Created by user on 09.05.2020.
//

#include "rubiks_cube.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

bool RubiksCube::check_correct_state() {
    int u = U_[0][0], d = D_[0][0], r = R_[0][0], l = L_[0][0], f = F_[0][0], b = B_[0][0];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if((U_[i][j] != u) || (D_[i][j] != d) || (R_[i][j] != r) || (L_[i][j] != l) || (F_[i][j] != f) || (B_[i][j] != b))
                return false;
    return true;
}

void RubiksCube::generate_state() {
    srand(time(0));
    write_solution_ = true;
    for(int i = 0; i < 25; i++) {
        int a = rand() % 12;
        switch (a) {
            case 0:
                U();
                break;
            case 1:
                Uc();
                break;
            case 2:
                D();
                break;
            case 3:
                Dc();
                break;
            case 4:
                R();
                break;
            case 5:
                Rc();
                break;
            case 6:
                L();
                break;
            case 7:
                Lc();
                break;
            case 8:
                F();
                break;
            case 9:
                Fc();
                break;
            case 10:
                B();
                break;
            default:
                Bc();
        }
    }
    write_solution_ = false;
}

void RubiksCube::read_state(std::istream &stream) {
    std::cout << "facets input sequence: yellow, red, green, orange, blue, white\n";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> U_[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> L_[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> F_[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> R_[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> B_[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            stream >> D_[i][j];
}

void RubiksCube::write_solution(const std::string& str) {
    if(write_solution_)
        std::cout << str << " ";
}

void RubiksCube::solve() {
    Solution s(*this);
    if(!check_correct_state()) {
        std::cout << "Incorrect state of cube. Impossible to solve\n";
    }
}

void CFacet::clock_wise() {
    int tmp[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tmp[i][j] = facet[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            facet[i][j] = tmp[2 - j][i];
}

void CFacet::counter_clock_wise() {
    int tmp[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tmp[i][j] = facet[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            facet[i][j] = tmp[j][2 - i];
}

void RubiksCube::scramble(std::istream &stream) {
    std::string str;
    while(stream >> str) {
        if(str[0] == 'R') {
            if (str.size() == 1)
                R();
            else if (str[1] == '2')
                R2();
            else
                Rc();
        }
        else if(str[0] == 'L') {
            if (str.size() == 1)
                L();
            else if (str[1] == '2')
                L2();
            else
                Lc();
        }
        else if(str[0] == 'U') {
            if (str.size() == 1)
                U();
            else if (str[1] == '2')
                U2();
            else
                Uc();
        }
        else if(str[0] == 'D') {
            if (str.size() == 1)
                D();
            else if (str[1] == '2')
                D2();
            else
                Dc();
        }
        else if(str[0] == 'F') {
            if (str.size() == 1)
                F();
            else if (str[1] == '2')
                F2();
            else
                Fc();
        }
        else if(str[0] == 'B') {
            if (str.size() == 1)
                B();
            else if (str[1] == '2')
                B2();
            else
                Bc();
        }
        else
            throw RubiksCubeException("Wrong command");
    }
}

void RubiksCube::print(std::ostream &stream) {
    stream << '\n';
    for(int i = 0; i < 3; i++) {
        stream << "       ";
        for(int j = 0; j < 3; j++)
            stream << U_[i][j] << ' ';
        stream << '\n';
    }
    for(int i = 0; i < 3; i++) {
        stream << L_[i][0] << " " << L_[i][1] << " " << L_[i][2] << "  ";
        stream << F_[i][0] << " " << F_[i][1] << " " << F_[i][2] << "  ";
        stream << R_[i][0] << " " << R_[i][1] << " " << R_[i][2] << "  ";
        stream << B_[i][0] << " " << B_[i][1] << " " << B_[i][2] << "  ";
        stream << '\n';
    }
    for(int i = 0; i < 3; i++) {
        stream << "       ";
        for(int j = 0; j < 3; j++)
            stream << D_[i][j] << ' ';
        stream << '\n';
    }
}

void RubiksCube::R() {
	if(use_queue)
		rotations.push("R");
    write_solution("R");
    R_.clock_wise();
    int tmp[3] = {F_[0][2], F_[1][2], F_[2][2]};
    for(int i = 0; i < 3; i++) {
        F_[i][2] = D_[i][2];
        D_[i][2] = B_[2 - i][0];
        B_[2 - i][0] = U_[i][2];
        U_[i][2] = tmp[i];
    }
}

void RubiksCube::Rc() {
	if (use_queue)
		rotations.push("R'");
    write_solution("R'");
    R_.counter_clock_wise();
    int tmp[3] = {F_[0][2], F_[1][2], F_[2][2]};
    for(int i = 0; i < 3; i++) {
        F_[i][2] = U_[i][2];
        U_[i][2] = B_[2 - i][0];
        B_[2 - i][0] = D_[i][2];
        D_[i][2] = tmp[i];
    }
}

void RubiksCube::L() {
	if (use_queue)
		rotations.push("L");
    write_solution("L");
    L_.clock_wise();
    int tmp[3] = {F_[0][0], F_[1][0], F_[2][0]};
    for(int i = 0; i < 3; i++) {
        F_[i][0] = U_[i][0];
        U_[i][0] = B_[2 - i][2];
        B_[2 - i][2] = D_[i][0];
        D_[i][0] = tmp[i];
    }
}

void RubiksCube::Lc() {
	if (use_queue)
		rotations.push("L'");
    write_solution("L'");
    L_.counter_clock_wise();
    int tmp[3] = {F_[0][0], F_[1][0], F_[2][0]};
    for(int i = 0; i < 3; i++) {
        F_[i][0] = D_[i][0];
        D_[i][0] = B_[2 - i][2];
        B_[2 - i][2] = U_[i][0];
        U_[i][0] = tmp[i];
    }
}

void RubiksCube::U() {
	if (use_queue)
		rotations.push("U");
    write_solution("U");
    U_.clock_wise();
    int tmp[3] = {F_[0][0], F_[0][1], F_[0][2]};
    for(int i = 0; i < 3; i++) {
        F_[0][i] = R_[0][i];
        R_[0][i] = B_[0][i];
        B_[0][i] = L_[0][i];
        L_[0][i] = tmp[i];
    }
}

void RubiksCube::Uc() {
	if (use_queue)
		rotations.push("U'");
    write_solution("U'");
    U_.counter_clock_wise();
    int tmp[3] = {F_[0][0], F_[0][1], F_[0][2]};
    for(int i = 0; i < 3; i++) {
        F_[0][i] = L_[0][i];
        L_[0][i] = B_[0][i];
        B_[0][i] = R_[0][i];
        R_[0][i] = tmp[i];
    }
}

void RubiksCube::D() {
	if (use_queue)
		rotations.push("D");
    write_solution("D");
    D_.clock_wise();
    int tmp[3] = {F_[2][0], F_[2][1], F_[2][2]};
    for(int i = 0; i < 3; i++) {
        F_[2][i] = L_[2][i];
        L_[2][i] = B_[2][i];
        B_[2][i] = R_[2][i];
        R_[2][i] = tmp[i];
    }
}

void RubiksCube::Dc() {
	if (use_queue)
		rotations.push("D'");
    write_solution("D'");
    D_.counter_clock_wise();
    int tmp[3] = {F_[2][0], F_[2][1], F_[2][2]};
    for(int i = 0; i < 3; i++) {
        F_[2][i] = R_[2][i];
        R_[2][i] = B_[2][i];
        B_[2][i] = L_[2][i];
        L_[2][i] = tmp[i];
    }
}

void RubiksCube::F() {
	if (use_queue)
		rotations.push("F");
    write_solution("F");
    F_.clock_wise();
    int tmp[3] = {L_[0][2], L_[1][2], L_[2][2]};
    for(int i = 0; i < 3; i++) {
        L_[i][2] = D_[0][i];
        D_[0][i] = R_[2 - i][0];
        R_[2 - i][0] = U_[2][2 - i];
        U_[2][2 - i] = tmp[i];
    }
}

void RubiksCube::Fc() {
	if (use_queue)
		rotations.push("F'");
    write_solution("F'");
    F_.counter_clock_wise();
    int tmp[3] = {L_[0][2], L_[1][2], L_[2][2]};
    for(int i = 0; i < 3; i++) {
        L_[i][2] = U_[2][2 - i];
        U_[2][2 - i] = R_[2 - i][0];
        R_[2 - i][0] = D_[0][i];
        D_[0][i] = tmp[i];
    }
}

void RubiksCube::B() {
	if (use_queue)
		rotations.push("B");
    write_solution("B");
    B_.clock_wise();
    int tmp[3] = {L_[0][0], L_[1][0], L_[2][0]};
    for(int i = 0; i < 3; i++) {
        L_[i][0] = U_[0][2 - i];
        U_[0][2 - i] = R_[2 - i][2];
        R_[2 - i][2] = D_[2][i];
        D_[2][i] = tmp[i];
    }
}

void RubiksCube::Bc() {
	if (use_queue)
		rotations.push("B'");
    write_solution("B'");
    B_.counter_clock_wise();
    int tmp[3] = {L_[0][0], L_[1][0], L_[2][0]};
    for(int i = 0; i < 3; i++) {
        L_[i][0] = D_[2][i];
        D_[2][i] = R_[2 - i][2];
        R_[2 - i][2] = U_[0][2 - i];
        U_[0][2 - i] = tmp[i];
    }
}

void RubiksCube::y() {
	if (use_queue)
		rotations.push("y");
    write_solution("y");
    U_.clock_wise();
    D_.counter_clock_wise();
    CFacet tmp = F_;
    F_ = R_;
    R_ = B_;
    B_ = L_;
    L_ = tmp;
}
