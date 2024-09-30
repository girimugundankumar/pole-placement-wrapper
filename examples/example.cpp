/*************************************************************************************************************************
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
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INT_internal_::ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************************************************************************************/

/*************************************************************************************************************************
 * File:        example.cpp
 * Author:      Giri Mugundan Kumar
 * Date:        September 30, 2024
 * For info:    Andrea L'Afflitto (a.lafflitto@vt.edu)
 *              Giri Mugundan Kumar (girimugundan@vt.edu)
 * 
 * Description: Example file on instructions to use the wrapper class
 * 
 * GitHub:   https://github.com/girimugundankumar/pole-placement-wrapper.git
 ************************************************************************************************************************/

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

    P << std::complex<double>(-25, 0), 
         std::complex<double>(-24, 0),
         std::complex<double>(-18, 0);

    /* Compute the gains with the default YT method and the rtol and iteration values
    If you need KNV0 you can pass a string "KNV0" after the P value.
    Likewise you can change the tolerance and the maximum number of iterations respectively. 
    Look to pole_placement.hpp for more information. */
    
    // Initialize the pole placement object
    PolePlacementWrapper ppw;

    // Compute the gains
    auto result = ppw.calculate_gain_matrix(A,B,P);

    // Get the gains
    auto gains = std::get<0>(result);
    std::cout << "Gain Matrix: \n" << gains << std::endl;

    // Get the placed poles
    auto placed_poled = std::get<1>(result);
    std::cout << "Placed Poles: \n" << placed_poled << std::endl;

    return 0;
}
