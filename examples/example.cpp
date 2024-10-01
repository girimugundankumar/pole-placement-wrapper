/***********************************************************************************************************************
 * Copyright (c) 2024 Giri M. Kumar, Mattia Gramuglia, Andrea L'Afflitto. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *    following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File:        example.cpp
 * Author:      Giri Mugundan Kumar
 * Date:        September 30, 2024
 * For info:    Andrea L'Afflitto (a.lafflitto@vt.edu)
 *              Giri Mugundan Kumar (girimugundan@vt.edu)
 * 
 * Description: Example file on instructions to use the wrapper class
 * 
 * GitHub:   https://github.com/girimugundankumar/pole-placement-wrapper.git
 **********************************************************************************************************************/

#include "pole_placement.hpp"

using namespace _pole_placement_wrapper_;

int main() {

    // Define A, B matrices and desired poles P
    Eigen::MatrixXd A(3, 3);
    Eigen::MatrixXd B(3, 3);
    Eigen::VectorXcd P(3);

    A <<  -8.4,    0,    0,
             0, -7.2,    0,
             0,    0, -1.2;

    B << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    // Complex poles should always have conjugate pairs
    P << std::complex<double>(-25, -1), 
         std::complex<double>(-24, 0),
         std::complex<double>(-25, 1);

    
    
    // Initialize the pole placement object
    PolePlacementWrapper ppw;

    // Compute the gains and placed poles
    // If you only want the gains - ignore the second output like so
    // auto [gains, _] = ppw.calculate_gain_matrix(A,B,P);
    // Please note that the gains are odered according to the rearranged Poles P (acending order), 
    // print out the placed_poles to double check your result.
    auto [gains, placed_poles] = ppw.calculate_gain_matrix(A,B,P);

    std::cout << "===== For Complex Poles ===== \n" << std::endl;
    std::cout << "Gain Matrix: \n" << gains << std::endl;
    std::cout << "Placed Poles: \n" << placed_poles << std::endl;


    // Define AA, BB matrices and desired poles PP
    Eigen::MatrixXd AA(4, 4);
    Eigen::MatrixXd BB(4, 2);
    Eigen::VectorXd PP(4);

    AA << 1.380,  -0.2077,  6.715, -5.676,
         -0.5814, -4.290,   0,      0.6750,
         1.067,   4.273,  -6.654,  5.893,
         0.0480,  4.273,   1.343, -2.104;

    BB << 0,      5.679 ,
        1.136,    1.136,
         0,        0,
        -3.146,  0;

    PP << -0.2, -0.5, -5.0566, -8.6659;

    // Compute the gains with the default YT method and the rtol and iteration values
    // If you need KNV0 you can pass a string "KNV0" after the P value. Note that KNV0 only works with real poles
    // Likewise you can change the tolerance and the maximum number of iterations respectively. 
    // Look to pole_placement.hpp for more information.

    // Initialize the pole placement object
    // PolePlacementWrapper ppw;

    auto [gains2, placed_poles2] = ppw.calculate_gain_matrix(AA,BB,PP, "KNV0");

    std::cout << "\n===== For Real Poles =====\n" << std::endl;
    std::cout << "Gain Matrix: \n" << gains2 << std::endl;
    std::cout << "Placed Poles: \n" << placed_poles2 << std::endl;

    return 0;
}
