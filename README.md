# SYCL examples

This repo contains a set of SYCL examples which illustrate to how to use SYCL
to program GPUs.

## Build this project

This project uses conda to manage dependencies (`CMake`, `clang-format`,
`clang-tidy` and other dependencies for documentation).

Dependencies can be installed by executing following commands after installing
[conda](https://docs.conda.io/en/latest/miniconda.html).
```sh
conda env create -f environment-dev.yml
conda activate sycl-examples-dev
```

Simply run `configure` to configure and `sycl-examples` script to build and
install the examples:
```sh
./configure -enable-docs
./sycl-examples -docs -install
```

Use `-help` to see all the options supported by the scripts:
```
./configure -help
./sycl-examples -help
```
