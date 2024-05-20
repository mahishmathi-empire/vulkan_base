# vulkan base

## OS

- [x] Ubuntu - 22.04
- [ ] MacOS -
- [ ] Windows -

## Setup

0. Install the packages and dependecies followin the instructions in the [Vulkan Tutorials](https://docs.vulkan.org/tutorial/latest/02_Development_environment.html) page.

1. Create a workspace directory and change to it.
  
    ```bash
    mkdir -p ~/me_ws/src/ ~/me_ws/build/ ~/me_ws/install/

    cd ~/me_ws/src/
    ```

2. Clone the repository.
  
    ```bash
    [~/me_ws/src] $ git clone https://github.com/mahishmathi-empire/daagudumoothalu.git
    ```

3. Build the package.
  
    ```bash
    [~/me_ws/src] $ ./daagudumoothalu/build.sh -p daagudumoothalu -c -i -- -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=OFF
    ```

    - `-p` specifies the package name.
    - `-c` cleans the build directory.
    - `-i` installs the package.
    - `--` passes the arguments to `cmake`.
    -  `-DCMAKE_BUILD_TYPE=Debug` specifies the build type.
    -  `-DENABLE_TESTS=ON` enables the tests.

4. Build the tests.
  
    ```bash
    [~/me_ws/src] $ ./daagudumoothalu/build.sh -p daagudumoothalu -c -i -- -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=ON
    ```

## Test

1. Change to bin directory.
  
    ```bash
    cd ~/me_ws/install/bin/
    ```

2. Run the executable.
  
    ```bash
    [~/me_ws/src] $ ./test
    ```

## TODO

- [ ] Create a struct to hold Vulkan objects.
