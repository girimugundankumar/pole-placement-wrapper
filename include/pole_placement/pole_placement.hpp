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
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INT_internal_::ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File:        pole_placement.hpp
 * Author:      Giri Mugundan Kumar
 * Date:        September 30, 2024
 * For info:    Andrea L'Afflitto (a.lafflitto@vt.edu)
 *              Giri Mugundan Kumar (girimugundan@vt.edu)
 * 
 * Description: Close-loop pole placement using state feedback. Computes a state-feedback matrix K such that the 
 *              eigen values of A - B * K are those specified by the user. No eigenvalue should have a multiplicity 
 *              greater than the number of inputs.
 *              
 * 
 * GitHub:   https://github.com/girimugundankumar/pole-placement-wrapper.git
 **********************************************************************************************************************/

#ifndef POLE_MODULE_HPP_
#define POLE_MODULE_HPP_

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <string>

// Specify namespaces for boost python
namespace p = boost::python;
namespace np = boost::python::numpy;

namespace _pole_placement_wrapper_{

namespace _internal_{

    // Helper function to convert Eigen::MatrixXd to numpy array
    np::ndarray eigen_to_numpy(const Eigen::MatrixXd& matrix) {
        p::tuple shape = p::make_tuple(matrix.rows(), matrix.cols());
        np::dtype dtype = np::dtype::get_builtin<double>();
        np::ndarray array = np::zeros(shape, dtype);
        
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.cols(); ++j) {
                array[i][j] = matrix(i, j);
            }
        }
        return array;
    }

    // Helper function to convert Eigen::VectorXcd to numpy array
    np::ndarray eigen_to_numpy(const Eigen::VectorXcd& vector) {
        p::tuple shape = p::make_tuple(vector.size());
        np::dtype dtype = np::dtype::get_builtin<std::complex<double>>();
        np::ndarray array = np::zeros(shape, dtype);
        
        for (int i = 0; i < vector.size(); ++i) {
            array[i] = vector(i);
        }
        return array;
    }

    // Helper function to convert Eigen::VectorXd to numpy array
    np::ndarray eigen_to_numpy(const Eigen::VectorXd& vector) {
        p::tuple shape = p::make_tuple(vector.size());
        np::dtype dtype = np::dtype::get_builtin<double>();
        np::ndarray array = np::zeros(shape, dtype);
        
        for (int i = 0; i < vector.size(); ++i) {
            array[i] = vector(i);
        }
        return array;
    }

    // Helper function to convert numpy.ndarray to Eigen::MatrixXd
    Eigen::MatrixXd numpy_to_eigen(const p::object& array) {
        // Ensure the object is a numpy ndarray
        if (p::str(array.attr("__class__").attr("__name__")) != "ndarray") {
            throw std::runtime_error("Provided object is not a numpy ndarray.");
        }

        int rows = p::extract<int>(array.attr("shape")[0]);
        int cols = p::extract<int>(array.attr("shape")[1]);
        Eigen::MatrixXd mat(rows, cols);
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat(i, j) = p::extract<double>(array[i][j]);
            }
        }
        return mat;
    }

    // Helper function to convert numpy.ndarray to Eigen::VectorXcd
    Eigen::VectorXcd numpy_to_eigen_vector(const p::object& array) {
        // Ensure the object is a numpy ndarray
        if (p::str(array.attr("__class__").attr("__name__")) != "ndarray") {
            throw std::runtime_error("Provided object is not a numpy ndarray.");
        }

        int size = p::extract<int>(array.attr("shape")[0]);
        Eigen::VectorXcd vec(size);
        
        for (int i = 0; i < size; ++i) {
            vec(i) = p::extract<std::complex<double>>(array[i]);
        }
        return vec;
    }

}   // namespace _internal_

class PolePlacementWrapper {

    public:
        // Default Constructor
        PolePlacementWrapper()
        {
            // Python Initialization
            Py_Initialize();
            np::initialize();

            // Append the directory containing the Python module to sys.path
            p::object sys = p::import("sys");
            sys.attr("path").attr("append")("../include/pole_placement/");
        }

        // Destructor
        ~PolePlacementWrapper()
        {
            // Close the API instance
            Py_Finalize();
        } 

    public:
        // Function to calculate the gains matrix
        std::tuple<Eigen::MatrixXd, Eigen::VectorXcd> calculate_gain_matrix(
        const Eigen::MatrixXd& A,
        const Eigen::MatrixXd& B,
        const Eigen::VectorXcd& P,
        const std::string& method = "YT",    // Default method
        double rtol = 1e-3,                  // Default tolerance
        int maxiter = 30)                    // Default maximum iterations
        {
            try 
            {
                // Import the Python module
                p::object pole_placement_module = p::import("pole_placement");

                // Convert Eigen matrices to numpy arrays
                np::ndarray np_A = _internal_::eigen_to_numpy(A);
                np::ndarray np_B = _internal_::eigen_to_numpy(B);
                np::ndarray np_P = _internal_::eigen_to_numpy(P);

                // Convert additional arguments
                p::str py_method(method);                       // Convert C++ string to Python string
                p::object py_rtol = p::object(rtol);            // Convert C++ double to Python object
                p::object py_maxiter  = p::object(maxiter);     // Convert C++ int to Python object

                // Call the Python function with additional arguments
                p::object result = pole_placement_module.attr("calculate_gain_matrix")(np_A, np_B, np_P, 
                                                                                       py_method, py_rtol, py_maxiter);

                // Extract the gain matrix and placed poles
                p::object gain_matrix_py = result[0];
                p::object placed_poles_py = result[1];

                // Convert the results back to Eigen types
                Eigen::MatrixXd gain_matrix = _internal_::numpy_to_eigen(gain_matrix_py);
                Eigen::VectorXcd placed_poles = _internal_::numpy_to_eigen_vector(placed_poles_py);  

                return std::make_tuple(gain_matrix, placed_poles);              
            }
            catch (const p::error_already_set& e)
            {
                PyErr_Print();
                throw std::runtime_error("Error calling Python function");
            }
        }
};

// Exposing the function to Python
BOOST_PYTHON_MODULE(pole_module) {
    using namespace boost::python;
    class_<PolePlacementWrapper>("PolePlacementWrapper", init<>())
        .def("calculate_gain_matrix", &PolePlacementWrapper::calculate_gain_matrix);
}


}   // namespace _pole_placement_wrapper_

#endif // POLE_MODULE_HPP_