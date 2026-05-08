# 🤖 ROS 2 Robotics Study & Project

![Ubuntu](https://img.shields.io/badge/Ubuntu-24.04-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)
![ROS 2](https://img.shields.io/badge/ROS_2-Jazzy-22314E?style=for-the-badge&logo=ros&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

이 폴더는 ROS 2(Robot Operating System 2)를 기반으로 한 로봇 제어, 시뮬레이션, SLAM 및 내비게이션 실습과 프로젝트 코드를 관리하는 공간입니다. 

## 📢 Repository 관리 정책
본 레포지토리는 용량 최적화 및 효율적인 버전 관리를 위해 **실습에 사용된 모든 원본 패키지 코드를 업로드하지 않습니다.** - 📦 **기본 로봇 패키지:** 하단의 [모듈별 Clone 가이드](#-모듈별-워크스페이스-구성-및-clone-가이드)를 참고하여 공식/강의 레포지토리를 직접 클론(`git clone`)하여 사용하시기 바랍니다.
- 🗺️ **본 저장소 포함 내역:** 실습 중 **직접 제작한 커스텀 맵(Map) 데이터(`.yaml`, `.pgm`)**와, 기본 패키지를 응용하여 **직접 작성/수정한 핵심 노드 코드들만 선별하여 업로드**되어 있습니다.

---

## 🛠️ 모듈별 워크스페이스 구성 및 Clone 가이드

원활한 실습을 위해 각 챕터별로 워크스페이스(Workspace)의 `src` 폴더로 이동한 뒤, 아래의 명령어들을 통해 필요한 패키지들을 구성하세요.

### 00_Simulation (가상 환경 실습)
가제보(Gazebo) 시뮬레이션 환경에서 Pinky 로봇을 구동하기 위한 패키지입니다.
```bash
# 워크스페이스 src 폴더로 이동 (예시)
cd ~/ros2_ws/src

# Pinky Pro 패키지 클론
git clone [https://github.com/pinklab-art/pinky_pro.git](https://github.com/pinklab-art/pinky_pro.git)
```
---

### 01_Turtlebot3_ws (TurtleBot3 실습)
터틀봇3의 SLAM 및 Navigation 실습을 위한 공식 ROS 2 Jazzy 버전 패키지입니다.
```bash
# 워크스페이스 src 폴더로 이동 (예시)
cd ~/turtlebot3_ws/src

# 다이나믹셀 SDK 및 터틀봇3 관련 패키지 클론 (Jazzy 브랜치)
git clone -b jazzy [https://github.com/ROBOTIS-GIT/DynamixelSDK.git](https://github.com/ROBOTIS-GIT/DynamixelSDK.git)
git clone -b jazzy [https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git](https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git)
git clone -b jazzy [https://github.com/ROBOTIS-GIT/turtlebot3.git](https://github.com/ROBOTIS-GIT/turtlebot3.git)
git clone -b jazzy [https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git](https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git)
```

---

### 02_PinkyPro (실물 로봇 구동)
실제 Pinky 로봇 하드웨어에 탑재되거나, 로봇을 원격으로 제어하기 위한 패키지입니다.
```bash
# 워크스페이스 src 폴더로 이동
cd ~/pinky_ws/src

# 실물 제어용 Pinky Pro 패키지 클론
git clone [https://github.com/pinklab-art/pinky_pro.git](https://github.com/pinklab-art/pinky_pro.git)
```
---

### 03_vicpinky (VicPinky 로봇 구동 및 모니터링)
VicPinky 로봇 구동 및 모니터링 환경 구성을 위한 패키지입니다.
```bash
# 워크스페이스 src 폴더로 이동
cd ~/vicpinky_ws/src

# vic_pinky 패키지 클론 (monitor 브랜치 지정)
git clone [https://github.com/pinklab-art/vic_pinky.git](https://github.com/pinklab-art/vic_pinky.git) -b monitor
```

---

### 빌드 및 실행 방법(공통)

1. 의존성 설치 (필요시)
```bash
cd ~/워크스페이스_경로
rosdep install --from-paths src --ignore-src -r -y
```
2. 워크스페이스 빌드
```bash
colcon build --symlink-install
```

3. 환경 변수 소싱 (필수)
```bash
source install/setup.bash
```



