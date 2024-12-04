# Tests

These tests use the source code of this repo.

Therefore the paths are `"EIPScanner/..."` rather than `<EIPScanner/...>`
* The source files are being linked directly rather than through the EIPScanner `/usr/local/lib` shared object file 


## Requirements

The GMock Library: `sudo apt install libgmock-dev`

## Building the tester

```shell
# in EIPScanner root directory
mkdir build && cd build
cmake -DTEST_ENABLED=ON ..
cmake --build .
```

# Testing the Data 

Can use: `./test/test_eipscanner --gtest_filter=TestIOInputData.*:TestEncoderInputData.*`
* And add to it with future classes