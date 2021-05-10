# rm-2021-Code-Framework
- **GCUROBOT-WOLF-TEAM RoboMaster-2021 Visual &amp; Algorithm Group Code Framework**

### 硬件配置

| drvices    | name                     |
|:----------:|:------------------------:|
|    PC      | Intel NUC8i5BEK4         |
|  Camera    | MindVision MV-SUA134GC-T |
| SerialPort | Normal USB to TTL        |
|||

### 软件配置

| name           |        version                 |
|:--------------:|:------------------------------:|
| System         | Ubuntu 18.04.05 LTS            |
| OpenCV         | [`4.4.0`](https://github.com/opencv/opencv/releases/tag/4.4.0)                               |
| OpenCV-Contrib | [`4.4.0`](https://github.com/opencv/opencv_contrib/releases/tag/4.4.0)                |
| Cmake          | [`3.10.2`](https://cmake.org/) |
|||


## 文件目录
``` shell
├── base/
├── common/
│   ├── camera_param/
│   └── yolo/
│       ├── classes/
│       ├── model/
│       └── weights/
├── drvices/
│   ├── camera/
│   │   ├── RM_VideoCapture.cpp
│   │   └── RM_VideoCapture.h
│   └── serial/
│       ├── RM_SerialPort.cpp
│       └── RM_SerialPort.h
├── module/
│   ├── angle_solve
│   │   ├── RM_SolvePNP.cpp
│   │   └── RM_SolvePNP.h
│   ├── armor/
│   │   ├── RM_ArmorDetection.cpp
│   │   └── RM_ArmorDetection.h
│   ├── buff/
│   │   ├── RM_BuffDetection.cpp
│   │   └── RM_BuffDetection.h
│   ├── filter/
│   │   ├── RM_KalmanFilter.cpp
│   │   └── RM_KalmanFilter.h
│   ├── object_detection/
│   │   ├── RM_ObjectDetection.cpp
│   │   └── RM_ObjectDetection.h
│   └── roi/
│       ├── RM_ROI.cpp
│       └── RM_ROI.h
└── ...
```

