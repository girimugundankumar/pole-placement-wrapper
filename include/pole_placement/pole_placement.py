# ***********************************************************************************************************************
# * Copyright (c) 2024 Giri M. Kumar, Mattia Gramuglia, Andrea L'Afflitto. All rights reserved.
# * 
# * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
# * following conditions are met:
# * 
# * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
# *    disclaimer.
# * 
# * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
# *    following disclaimer in the documentation and/or other materials provided with the distribution.
# * 
# * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
# *    products derived from this software without specific prior written permission.
# * 
# * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES,
# * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INT_internal_::ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
# * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
# * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# **********************************************************************************************************************/

# **********************************************************************************************************************  
# * Part of the code in this file leverages the following material.
# *
# * Referenced: https://github.com/scipy/scipy/blob/v1.14.1/scipy/signal/_ltisys.py#L2864
# *             
# *           Copyright (c) 2001-2002 Enthought, Inc. 2003-2024, SciPy Developers. All rights reserved.
# * 
# *                   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# *                   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# *                   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# *                   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# *                   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# *                   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# *                   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# *                   DATA, OR PROFITS; OR BUSINESS INT_internal_::ERRUPTION) HOWEVER CAUSED AND ON ANY
# *                   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# *                   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# *                   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# * 
# **********************************************************************************************************************/

# ***********************************************************************************************************************
# * File:        pole_placement.py
# * Author:      Giri Mugundan Kumar
# * Date:        September 30, 2024
# * For info:    Andrea L'Afflitto (a.lafflitto@vt.edu)
# *              Giri Mugundan Kumar (girimugundan@vt.edu)
# * 
# * Description: Close-loop pole placement using state feedback. Computes a state-feedback matrix K such that the 
# *              eigen values of A - B * K are those specified by the user. No eigenvalue should have a multiplicity 
# *              greater than the number of inputs.
# *              
# * 
# * GitHub:    https://github.com/girimugundankumar/pole-placement-wrapper.git
# **********************************************************************************************************************/

# pole_placement.py
import numpy as np
from scipy.signal import place_poles

def calculate_gain_matrix(A, B, P, method="YT", rtol=1e-3, maxiter=30):
    """
    Calculate the feedback gain matrix K using pole placement.

    Parameters:
    A : numpy.ndarray
        The system state matrix (real).
    B : numpy.ndarray
        The input matrix (real).
    P : numpy.ndarray
        The desired poles (complex). 
        Note: For real poles, set imaginary parts to zero.
    method : str, optional
        The method used for pole placement. Default is "YT".
    rtol : float, optional
        The relative tolerance for convergence. Default is 1e-3.
    maxiter : int, optional
        The maximum number of iterations for convergence. Default is 30.

    Returns:
    K : numpy.ndarray
        The calculated gain matrix.
    placed_poles : numpy.ndarray
        The computed poles.
    """

    # Use place_poles to calculate the feedback gain matrix K
    result = place_poles(A, B, P, method, rtol, maxiter)

    # The gain matrix K
    K = result.gain_matrix

    # Placed poles
    placed_poles = result.computed_poles

    # Return the gain matrix and the placed poles
    return K, placed_poles
