# simulation_user

cmake build system,tested on windows only

## Prerequisite
Build simulation_lib first

## Dependency
To successfully build simulation_user, you need install FIM_PACKAGE to ${CPACKAGE}/FIM.

## Build Commands
```shell
cd simulation_user
mkdir build
cd build
cmake ..
make
```

The last step produces `linear_network_simulation` executable. Running it generates the output file, which can be post-processed by script to plot numerical results.


