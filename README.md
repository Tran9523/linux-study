# 🤖 kcci_study: Robotics & Embedded SW Roadmap

이 저장소는 임베디드 및 로봇 소프트웨어 엔지니어로 성장하기 위한 기술적 여정을 기록하는 공간입니다. 저수준 언어 기초부터 시스템 프로그래밍, 비전 AI, 그리고 하드웨어 제어와 로봇 운영체제(ROS2) 통합까지의 단계별 학습 과정을 담고 있습니다.

## 🛠 Tech Stacks

- **Languages:** C, Python
- **OS & Environment:** Ubuntu (Linux), Shell Scripting, Makefile, Git
- **Frameworks:** ROS2 (Jazzy), OpenCV
- **Embedded & AI:** STM32 (Cortex-M), YOLO11 (Vision AI), Raspberry Pi
- **Expertise:** Image Sensor ISP Tuning, Real-time System Control

---

## 📅 Learning Roadmap (Timeline)

### 1. 펀더멘탈 (2025.11 ~ 2026.01)
- **`2511_baekjoon`**: C 언어 기초 문법 숙달 및 효율적인 알고리즘 설계를 위한 문제 풀이 (Problem Solving)
- **`2512_Linux_C-programming`**: 리눅스 환경에서의 C 프로그래밍 심화 실습 및 알고리즘 역량 강화
  - 심화교재(`skill_book`) 내 다양한 예제 구현을 통한 포인터, 구조체, 메모리 관리 등 핵심 문법 최적화
  - 챕터별 실습을 통한 논리적 사고 및 소스 코드 구조화 능력 배양
  - `Makefile`을 활용한 빌드 자동화 및 리눅스 개발 환경 숙달

### 2. 인지 및 하드웨어 제어 (2026.02 ~ 2026.03)
- **`2602_AI-ComputerVision`**: 시각 지능 구현 및 실시간 객체 인식 응용
  - **Featured Project:** [Realtime Assembly Guide](https://github.com/Tran9523/Realtime_Assembly_Guide.git)
  - YOLO11과 Raspberry Pi를 활용한 실시간 조립 오류 방지 시스템 개발
- **`2603_Embedded-CortexM`**: ARM Cortex-M 기반 마이크로컨트롤러 제어 역량 확보
  - **Featured Project:** [STM32 SmartFarm System](https://github.com/Tran9523/STM32_SmartFarm_System.git)
  - STM32 아키텍처 이해 및 센서 데이터를 활용한 스마트팜 제어 로직 설계

### 3. 시스템 통합 (2026.04 ~ Present)
- **`2604_ROS2-Robotics`**: 로봇 소프트웨어 프레임워크 기반 시스템 통합
  - ROS2 통신 메커니즘(Topic, Service, Action) 설계 및 패키지 개발
  - 사용자 정의 인터페이스를 통한 분산 제어 시스템 구축

---

## 🚀 Key Competencies

- **Full-Stack Engineering:** 펌웨어 제어부터 상위 비전 AI 알고리즘까지 아우르는 통합 기술 스택 보유
- **Professional Workflow:** Makefile, CMake 기반의 빌드 시스템 관리 및 Git을 활용한 형상 관리 숙달
- **Real-time Optimization:** ISP 튜닝 및 임베디드 시스템 경험을 바탕으로 한 데이터 처리 최적화

---

## 📂 Directory Structure

```text
.
├── 2511_baekjoon               # C 알고리즘 실습
├── 2512_Linux_C-programming    # 시스템 프로그래밍 & IPC
├── 2602_AI-ComputerVision      # Vision AI (YOLO11 Project)
├── 2603_Embedded-CortexM       # STM32 기반 하드웨어 제어
└── 2604_ROS2-Robotics          # ROS2 기반 로봇 소프트웨어
```