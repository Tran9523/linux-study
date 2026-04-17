# ROS 2 Jazzy 실습: Turtlesim 제어 및 고급 통신 인터페이스

[cite_start]이 저장소는 ROS 2(Jazzy)를 활용하여 로봇 통신의 핵심 메커니즘을 학습하고, Turtlesim 시뮬레이터를 정교하게 제어하는 실습 코드를 담고 있습니다. [cite: 1, 9]

## 🛠 개발 환경
- **OS**: Ubuntu 24.04 LTS (Noble)
- **ROS 2 Version**: Jazzy Jalisco
- **Language**: Python 3.12+

## 📂 패키지 구성
### 1. `my_first_package`
ROS 2의 주요 통신 방식을 구현한 메인 로직 패키지입니다.
- **Topic**: `my_publisher.py`, `my_subscriber.py`, `turtle_cmd_and_pose.py` (거북이 상태 모니터링 및 명령)
- **Service**: `my_service_server.py` (거북이 원형 배치 로직)
- [cite_start]**Action**: `dist_turtle_action_server.py` (목표 거리 이동 및 실시간 피드백) 
- **Multi-threading**: `my_multi_thread.py` (병렬 콜백 처리를 위한 MultiThreadedExecutor 적용)
- [cite_start]**Launch**: `launch/` 폴더 내 `.launch.py` 및 `.xml` 파일 (다중 노드 일괄 실행 및 파라미터 주입) 

### 2. `my_first_package_msgs`
실습에 필요한 커스텀 데이터 형식을 정의한 패키지입니다.
- **Message**: `CmdAndPoseVel.msg` (위치와 속도 통합 데이터)
- **Service**: `MultiSpawn.srv` (다중 소환 요청)
- **Action**: `DistTurtle.action` (거리 목표, 최종 위치 결과, 남은 거리 피드백)

## 🚀 주요 기능 및 특징
- [cite_start]**Dynamic Parameter Tuning**: `rqt`의 Dynamic Reconfigure를 통해 실행 중 거북이의 도달 기준치를 슬라이더로 실시간 조정 가능 
- **Advanced Action Control**: 유클리드 기하학 기반의 이동 거리 계산 알고리즘 적용 (`calc_position.ipynb` 참조)
- **Graceful Shutdown**: `KeyboardInterrupt` 예외 처리를 통해 `Ctrl+C` 종료 시 노드 자원을 안전하게 해제
- [cite_start]**Flexible Launching**: Python과 XML 두 가지 방식의 런치 파일을 지원하여 환경 설정의 유연성 확보 

## 📦 .bashrc - alias 설정
alias sb="source ~/.bashrc; echo \"bashrc is reloded\""
alias jazzy="source /opt/ros/jazzy/setup.bash; ros_domain; ros_venv; echo \"jazzy is activated.\"; cd ~/dev_ws/ros"
alias ros_domain="export ROS_DOMAIN_ID=26"
alias ros_venv="source ~/venv/ros/bin/activate"
alias ros_study="jazzy; source ~/dev_ws/ros/install/setup.bash; echo \"ros2_study workspace is activated.\""
alias rrros="sb; jazzy; source ~/dev_ws/ros/install/setup.bash; echo \"Reset!!\""
