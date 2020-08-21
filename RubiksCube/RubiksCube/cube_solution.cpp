//
// Created by user on 10.05.2020.
//

#include "cube_solution.h"

void Solution::solve() {
	if (cube.check_correct_state())
		return;
	cross();
	down_corners();
	down_edges();
	cross_up();
	orient_edges();
	place_up_corners();
	orient_corners();
}

bool is_ready(CFacet u) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(u[i][j] != 0)
                return false;
    return true;
}

void Solution::place_right() {
    while(cube.U_[2][2] == 0)
        cube.U();
}

void Solution::orient_corners() {
    while(!is_ready(cube.U_)) {
        place_right();
        while(cube.U_[2][2] != 0)
            algorithm_for_orient();
    }
    while(cube.F_[1][1] != cube.F_[0][1])
        cube.U();
}

void Solution::algorithm_for_orient() {
    cube.R();
    cube.Fc();
    cube.Rc();
    cube.F();
}

bool is_corner(CFacet f, CFacet s, CFacet t, int col1, int col2, int col3, int i1, int i2, int i3, int i4, int i5, int i6) {
    if((f[i1][i2] == col1) || (f[i1][i2] == col2) || (f[i1][i2] == col3))
        if((s[i3][i4] == col1) || (s[i3][i4] == col2) || (s[i3][i4] == col3))
            if((t[i5][i6] == col1) || (t[i5][i6] == col2) || (t[i5][i6] == col3))
                return true;
    return false;
}

int Solution::count_corners() {
    int res = 0;
    if(is_corner(cube.F_, cube.R_, cube.U_, cube.F_[1][1], cube.R_[1][1], 0, 0, 2, 0, 0, 2, 2)) res++;
    if(is_corner(cube.R_, cube.B_, cube.U_, cube.R_[1][1], cube.B_[1][1], 0, 0, 2, 0, 0, 0, 2)) res++;
    if(is_corner(cube.B_, cube.L_, cube.U_, cube.B_[1][1], cube.L_[1][1], 0, 0, 2, 0, 0, 0, 0)) res++;
    if(is_corner(cube.F_, cube.L_, cube.U_, cube.F_[1][1], cube.L_[1][1], 0, 0, 0, 0, 2, 2, 0)) res++;
    return res;
}

void Solution::place_up_corners() {
    if(count_corners() == 4)
        return;
    if(count_corners() == 1)
        while(!is_corner(cube.F_, cube.R_, cube.U_, cube.F_[1][1], cube.R_[1][1], 0, 0, 2, 0, 0, 2, 2))
            cube.y();
    algorithm_for_corners();
    place_up_corners();
}

void Solution::algorithm_for_corners() {
    cube.Lc();
    cube.U();
    cube.R();
    cube.Uc();
    cube.L();
    cube.U();
    cube.Rc();
    cube.Uc();
}

void Solution::algorithm_for_edges() {
    cube.Lc();
    cube.U2();
    cube.L();
    cube.U();
    cube.Lc();
    cube.U();
    cube.L();
}

int Solution::count_rights() {
    int res = 0;
    if(cube.F_[0][1] == cube.F_[1][1]) res++;
    if(cube.R_[0][1] == cube.R_[1][1]) res++;
    if(cube.L_[0][1] == cube.L_[1][1]) res++;
    if(cube.B_[0][1] == cube.B_[1][1]) res++;
    return res;
}

void Solution::orient_edges() {
    if(count_rights() == 4)
        return;
    if(find_position())
        while(cube.F_[0][1] != cube.F_[1][1])
            cube.y();
    algorithm_for_edges();
    orient_edges();
}

bool Solution::find_position() {
    if(count_rights() == 1)
        return true;
    cube.U();
    if(count_rights() == 1)
        return true;
    cube.U();
    if(count_rights() == 1)
        return true;
    cube.U();
    return count_rights() == 1;
}

void Solution::cross_up() {
    if((cube.U_[1][0] == 0) && (cube.U_[1][2] == 0) && (cube.U_[0][1] == 0) && (cube.U_[2][1] == 0))
        return;
    if((cube.U_[1][0] != 0) && (cube.U_[1][2] != 0) && (cube.U_[0][1] != 0) && (cube.U_[2][1] != 0))
        make_cross_up_case1();
    while(cube.U_[1][0] != 0)
        cube.U();
    if(cube.U_[1][2] == 0) {
        make_cross_up_case1();
        return;
    }
    while((cube.U_[1][0] != 0) || (cube.U_[0][1] != 0))
        cube.U();
    make_cross_up_case2();
}

void Solution::make_cross_up_case1() {
    cube.F();
    cube.R();
    cube.U();
    cube.Rc();
    cube.Uc();
    cube.Fc();
}

void Solution::make_cross_up_case2() {
    cube.F();
    cube.U();
    cube.R();
    cube.Uc();
    cube.Rc();
    cube.Fc();
}

void Solution::down_edges() {
    for(int i = 0; i < 4; i++) {
        find_edge(cube.F_[1][1], cube.R_[1][1]);
        while(((cube.F_[0][1] != cube.F_[1][1]) || (cube.U_[2][1] != cube.R_[1][1]))
            && ((cube.R_[0][1] != cube.R_[1][1]) || (cube.U_[1][2] != cube.F_[1][1])))
            cube.U();
        if((cube.F_[0][1] == cube.F_[1][1]) && (cube.U_[2][1] == cube.R_[1][1]))
            place_edge_case1();
        else
            place_edge_case2();
        if(i != 3)
            cube.y();
    }
}

bool is_edge(CFacet f, CFacet s, int col1, int col2, int i1, int i2, int i3, int i4) {
    if((f[i1][i2] == col1) || (f[i1][i2] == col2))
        if((s[i3][i4] == col1) || (s[i3][i4] == col2))
            return true;
    return false;
}

void Solution::find_edge(int a, int b) {
    if(is_edge(cube.F_, cube.R_, a, b, 1, 2, 1, 0))
        place_edge_case1();
    if(is_edge(cube.F_, cube.L_, a, b, 1, 0, 1, 2)) {
        cube.F(); cube.Uc(); cube.Fc(); cube.Uc(); cube.Lc(); cube.U(); cube.L();
    }
    if(is_edge(cube.L_, cube.B_, a, b, 1, 0, 1, 2)) {
        cube.L(); cube.Uc(); cube.Lc(); cube.Uc(); cube.Bc(); cube.U(); cube.B();
    }
    if(is_edge(cube.R_, cube.B_, a, b, 1, 2, 1, 0)) {
        cube.B(); cube.Uc(); cube.Bc(); cube.Uc(); cube.Rc(); cube.U(); cube.R();
    }
}


void Solution::place_edge_case1() {
    cube.U();
    cube.R();
    cube.Uc();
    cube.Rc();
    cube.Uc();
    cube.Fc();
    cube.U();
    cube.F();
}

void Solution::place_edge_case2() {
    cube.Uc();
    cube.Fc();
    cube.U();
    cube.F();
    cube.U();
    cube.R();
    cube.Uc();
    cube.Rc();
}

void Solution::down_corners() {
    for(int i = 0; i < 4; i++) {
        find_corner(cube.F_[1][1], cube.R_[1][1]);
        place_corner();
        if(i != 3)
            cube.y();
    }
}

void Solution::find_corner(int a, int b) {
    if(is_corner(cube.F_, cube.R_, cube.D_, a, b, 5, 2, 2, 2, 0, 0, 2))
        return;
    if(is_corner(cube.F_, cube.L_, cube.D_, a, b, 5, 2, 0, 2, 2, 0, 0)) {
        cube.Lc();
        cube.Uc();
        cube.L();
    }
    if(is_corner(cube.L_, cube.B_, cube.D_, a, b, 5, 2, 0, 2, 2, 2, 0)) {
        cube.Bc();
        cube.Uc();
        cube.B();
    }
    if(is_corner(cube.R_, cube.B_, cube.D_, a, b, 5, 2, 2, 2, 0, 2, 2)) {
        cube.Rc();
        cube.Uc();
        cube.R();
    }
    if(is_corner(cube.U_, cube.F_, cube.R_, a, b, 5, 2, 2, 0, 2, 0, 0))
        return;
    if(is_corner(cube.U_, cube.L_, cube.F_, a, b, 5, 2, 0, 0, 2, 0, 0)) {
        cube.Uc();
        return;
    }
    if(is_corner(cube.U_, cube.B_, cube.L_, a, b, 5, 0, 0, 0, 2, 0, 0)) {
        cube.U2();
        return;
    }
    if(is_corner(cube.U_, cube.R_, cube.B_, a, b, 5, 0, 2, 0, 2, 0, 0)) {
        cube.U();
        return;
    }
}

void Solution::place_corner() {
    while((cube.D_[0][2] != 5) || (cube.F_[2][2] != cube.F_[1][1]) || (cube.R_[2][0] != cube.R_[1][1])) {
        cube.R();
        cube.U();
        cube.Rc();
        cube.Uc();
    }
}


void Solution::cross() {
	if ((cube.D_[0][1] == 5 && (cube.F_[2][1] == cube.F_[1][1]))
		&& (cube.D_[1][0] == 5 && (cube.L_[2][1] == cube.L_[1][1]))
		&& (cube.D_[1][2] == 5 && (cube.R_[2][1] == cube.R_[1][1]))
		&& (cube.D_[2][1] == 5 && (cube.B_[2][1] == cube.B_[1][1])))
		return;
    int k = 0;
    if(cube.U_[1][0] == 5) k++;
    if(cube.U_[1][2] == 5) k++;
    if(cube.U_[0][1] == 5) k++;
    if(cube.U_[2][1] == 5) k++;
    while(k != 4) {
        for(int i = 0; i < 2; i++) {
            check_down(k);
            check10(k);
            check12(k);
            check01(k);
            check21(k);
        }
        if(k != 4)
            cube.y();
    }
    while(cube.F_[0][1] != cube.F_[1][1])
        cube.U();
    cube.F2();

    while((cube.R_[0][1] != cube.R_[1][1]) || (cube.U_[1][2] != 5))
        cube.U();
    cube.R2();

    while((cube.L_[0][1] != cube.L_[1][1]) || (cube.U_[1][0] != 5))
        cube.U();
    cube.L2();

    while((cube.B_[0][1] != cube.B_[1][1]) || (cube.U_[0][1] != 5))
        cube.U();
    cube.B2();
}

void Solution::check01(int &k) {
    if(cube.F_[0][1] == 5) {
        cube.Fc();
        if(cube.U_[2][1] == 5)
            k++;
        check10(k);
    }
}

void Solution::check10(int &k) {
    if(cube.F_[1][0] == 5) {
        turn_up(1, 0);
        cube.Lc();
        k++;
        check10(k);
    }
}

void Solution::check21(int &k) {
    if(cube.F_[2][1] == 5) {
        turn_up(2, 1);
        cube.F();
        if(cube.U_[2][1] == 5)
            k++;
        check10(k);
    }
}

void Solution::check12(int &k) {
    if(cube.F_[1][2] == 5) {
        turn_up(1, 2);
        cube.R();
        k++;
        check12(k);
    }
}

void Solution::check_down(int &k) {
    if(cube.D_[0][1] == 5) {
        turn_up(2, 1);
        cube.F2();
        k++;
    }
}

void Solution::turn_up(int i, int j) {
    while(cube.U_[i][j] == 5)
        cube.U();
}