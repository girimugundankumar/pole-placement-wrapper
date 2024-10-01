# Pole Placement C++ Wrapper

[![BSD License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](LICENSE.txt)

## 📚 Overview

This package is a C++ wrapper that provides an interface for performing **pole placement** using the `scipy.place` function from Python's SciPy library. The main purpose is to leverage the Python-based control system functionality from C++ code, as there aren't any open-source, easily available libraries for pole placement written natively in C++.

Pole placement is widely used for designing controllers, and this code was written for integration into the flightstack architecture at the **Advanced Control Systems Lab (ACSL)** for testing on UAVs:

- [ACSL Flightstack Winged](https://github.com/andrealaffly/ACSL-flightstack-winged)
- [ACSL Flightstack](https://github.com/andrealaffly/ACSL-flightstack)

## 🛠️ Dependencies

To successfully build and use this package, ensure the following dependencies are installed:

### 1. Python

Make sure Python is installed. Even if it's installed, run the following commands to ensure the required packages are available:

```bash
# Install Python3 development headers
sudo apt install python3-dev

# Install numpy and scipy
sudo pip3 install numpy scipy

# Upgrade them to the latest version
sudo pip3 install --upgrade scipy numpy
```

### 2. Boost.Python

Boost.Python ([Boost](https://www.boost.org/)) is required to provide a Python API from C++.

#### Installing Boost.Python from Source

Run the following commands (Linux instructions):

```bash
# Go to home directory
cd ~

# Clone Boost version 1.86
git clone https://github.com/boostorg/boost/tree/boost-1.86.0

# cd into boost root folder
cd ~/boost

# Compile Boost with Python
./bootstrap.sh --with-python

# Install Boost
sudo ./b2 --with-python
sudo ./b2 install

# Link Boost
sudo ldconfig

# Verify if Boost.Python is installed
ldconfig -p | grep boost_python
```

## 💻 How to Use the Repository

### 1. Clone the repository

```bash
# Clone wherever you need -- the recursive clones Eigen 3.40 too. If you already have it you can remove the tag to clone recursively
git clone --recursive https://github.com/girimugundankumar/pole-placement-wrapper.git

# cd into the package
cd pole-placement-wrapper

# Create build directory and cd into it
mkdir build && cd build

# Run cmake
cmake ..

# Compile
make
```

### 2. Run the example file

```bash
# Run the example executable from the build directory
./pole_placement_example
```

#### Example Output

When you run the example file, the output should be:

```bash
===== For Complex Poles ===== 
Gain Matrix: 
15.6   -0   -0
  -0 17.8   -1
  -0    1 23.8
Placed Poles: 
 (-24,0)
(-25,-1)
 (-25,1)

===== For Real Poles =====

Gain Matrix: 
 0.200714 -0.966658  0.240661 -0.102798
 0.505873  0.577791  0.517958 -0.419914
Placed Poles: 
(-8.6659,0)
(-5.0566,0)
   (-0.5,0)
   (-0.2,0)

```

If you see this output, the code works correctly.

## 📄 CMake Integration

The [CMakeLists.txt](https://github.com/girimugundankumar/pole-placement-wrapper/blob/main/CMakeLists.txt) file includes all the necessary library dependencies, so you can easily integrate this package into your project.

## 📝 License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](https://github.com/girimugundankumar/pole-placement-wrapper/blob/main/LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! If you’d like to improve this package, feel free to submit a pull request or open an issue.

