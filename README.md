## GCUROBOT-WOLF-TEAM RoboMaster-2021 Visual &amp; Algorithm Group Code Framework

### Hardware

| drvices    | name                     |
|:----------:|:------------------------:|
|    PC      | Intel NUC8i5BEK4         |
|  Camera    | MindVision MV-SUA134GC-T |
| SerialPort | CP2102N                  |
|||

### Software

| name           |        version                 |
|:--------------:|:------------------------------:|
| System         | Ubuntu 18.04.05 LTS            |
| OpenCV         | [`4.4.0`](https://github.com/opencv/opencv/releases/tag/4.4.0)                               |
| OpenCV_Contrib | [`4.4.0`](https://github.com/opencv/opencv_contrib/releases/tag/4.4.0)                |
| CMake          | [`3.10.2`](https://cmake.org/) |
| GCC            | [`7.5.0`](https://ftp.gnu.org/gnu/gcc/gcc-7.5.0/)      |
| GDB            | [`8.1.0`](https://www.gnu.org/software/gdb/download/)                           |
|||

### Contribute

#### Guide

Before start coding, please finish project configuration first:

```shell
sudo bash scripts/autoconfig.sh
```

#### Rules

- type: type of commit
- feat: new feature
- fix: modify the issue
- refactor: code refactoring
- docs: documentation changes
- style: code formatting changes, not css changes
- test: test case modifications
- chore: other changes, such as build process, dependency management
- scope: the scope of the commit, e.g. route, component, utils, build, etc.
- subject: overview of the commit

### License

`MIT, Copyright GCUROBOT-WOLF-TEAM 2021`
