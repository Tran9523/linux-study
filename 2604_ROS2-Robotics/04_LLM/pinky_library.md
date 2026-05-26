
# Pinky Library Documentation (Full)

> 본 문서는 Pinky 전용 파이썬 라이브러리의 API 레퍼런스입니다. 모듈별로 대표 클래스와 메서드를 설명하며, 예제 코드는 최소 실행 단위로 정리되어 있습니다.

## Ultrasonic

### `get_dist()`

* **Description**
  Pinky의 초음파 센서로 거리를 측정한 값을 반환한다.
* **Syntax**
  `get_dist()`
* **Parameters**
  None
* **Returns**
  `int distance` : 초음파센서로부터 받은 거리 (단위: cm 가정)
* **Example Code**

```python
from pinkylib import Ultrasonic
import time

pinky = Ultrasonic()

try:
    while True:
        dist = pinky.get_dist()
        print(f"{dist:.2f} cm")
        time.sleep(1)
finally:
    pinky.close()
```

---

## Buzzer

### `buzzer_start()`

* **Description**
  Pinky의 부저 핀에 대한 PWM 신호를 시작한다.
* **Syntax**
  `buzzer_start()`
* **Parameters**
  None
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Buzzer

pinky = Buzzer()
try:
    pinky.buzzer_start()
finally:
    pinky.clean()
```

### `set_buzzer_duty(duty)`

* **Description**
  부저 PWM의 듀티사이클(DutyCycle)을 설정해 소리 크기를 조절한다.
* **Syntax**
  `set_buzzer_duty(50)`
* **Parameters**
  `int duty` : PWM DutyCycle
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Buzzer
import time

pinky = Buzzer()
try:
    pinky.buzzer_start()
    pinky.set_buzzer_duty(50)
    time.sleep(1)
    pinky.set_buzzer_duty(0)
    pinky.buzzer_stop()
finally:
    pinky.clean()
```

### `set_buzzer_freq(freq)`

* **Description**
  부저 PWM의 주파수(Frequency)를 설정해 음의 높낮이를 조절한다.
* **Syntax**
  `set_buzzer_freq(261)`
* **Parameters**
  `int freq` : PWM frequency(Hz)
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Buzzer
import time

pinky = Buzzer()
try:
    pinky.buzzer_start()
    pinky.set_buzzer_duty(50)
    pinky.set_buzzer_freq(261)  # 도
    time.sleep(1)
    pinky.set_buzzer_freq(293)  # 레
    time.sleep(1)
    pinky.set_buzzer_duty(0)
    pinky.buzzer_stop()
finally:
    pinky.clean()
```

### `buzzer(cnt=1)`

* **Description**
  부저를 입력된 횟수만큼 울린다. 기본값은 1회.
* **Syntax**
  `buzzer()`
  `buzzer(3)`
* **Parameters**
  `int cnt` : 부저를 울릴 횟수
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Buzzer

pinky = Buzzer()
try:
    pinky.buzzer_start()
    pinky.buzzer(3)
    pinky.buzzer_stop()
finally:
    pinky.clean()
```

### `buzzer_stop()`

* **Description**
  부저의 PWM을 종료한다.
* **Syntax**
  `buzzer_stop()`
* **Parameters**
  None
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Buzzer

pinky = Buzzer()
try:
    pinky.buzzer_start()
    pinky.buzzer(3)
    pinky.buzzer_stop()
finally:
    pinky.clean()
```

---

## IR

### `read_ir()`

* **Description**
  Pinky의 IR 센서 값을 읽어온다.
* **Syntax**
  `read_ir()`
* **Parameters**
  None
* **Returns**
  `int ir_1, int ir_2, int ir_3` : IR 센서값
* **Example Code**

```python
from pinkylib import IR
import time

pinky = IR()
try:
    while True:
        ir_1, ir_2, ir_3 = pinky.read_ir()
        print(f"ir_1: {ir_1}, ir_2: {ir_2}, ir_3: {ir_3}")
        time.sleep(0.1)
finally:
    pinky.close()
```

---

## IMU

### `read_imu_data()`

* **Description**
  Pinky의 IMU 센서 값을 읽어온다.
* **Syntax**
  `read_imu_data()`
* **Parameters**
  None
* **Returns**
  `dict data` : IMU 센서 측정값

  * `'acceleration'`: `(x, y, z)` 각 축의 가속도, 단위 m/s²
  * `'gyro'`: `(x, y, z)` 각 축의 각속도, 단위 deg/s
  * `'quaternion'`: `(w, x, y, z)` 센서 자세 쿼터니언
* **Example Code**

```python
from pinkylib import IMU
import time

pinky = IMU()
try:
    while True:
        data = pinky.read_imu_data()
        print(data)
        time.sleep(0.1)
finally:
    pinky.close()
```

---

## Battery

### `get_voltage()`

* **Description**
  Pinky의 배터리 전압을 반환한다.
* **Syntax**
  `get_voltage()`
* **Parameters**
  None
* **Returns**
  `float voltage` : 배터리 전압 (V)
* **Example Code**

```python
from pinkylib import Battery

battery = Battery()
try:
    print(f"{battery.get_voltage():.2f} V")
finally:
    battery.close()
```

### `battery_percentage()`

* **Description**
  Pinky의 배터리 남은 잔량(%)을 반환한다.
* **Syntax**
  `battery_percentage()`
* **Parameters**
  None
* **Returns**
  `int percent` : 배터리 남은 잔량(%)
* **Example Code**

```python
from pinkylib import Battery

battery = Battery()
try:
    print(f"{battery.battery_percentage()} %")
finally:
    battery.close()
```

---

## Motor

### `enable_motor()`

* **Description**
  모터를 활성화한다.
* **Syntax**
  `enable_motor()`
* **Parameters**
  None
* **Returns**
  None

### `disable_motor()`

* **Description**
  모터를 비활성화한다.
* **Syntax**
  `disable_motor()`
* **Parameters**
  None
* **Returns**
  None

### `move(L, R)`

* **Description**
  입력 속도로 좌·우 모터를 구동한다.
  음수는 후진, 0은 정지를 의미한다.
* **Syntax**
  `move(25, -25)`
* **Parameters**

  * `int L` : 왼쪽 모터 속도 (-100 ~ 100)
  * `int R` : 오른쪽 모터 속도 (-100 ~ 100)
* **Returns**
  None

### `stop()`

* **Description**
  주행 중 정지한다.
* **Syntax**
  `stop()`
* **Parameters**
  None
* **Returns**
  None

### `close()`

* **Description**
  모터 사용을 종료한다.

* **Syntax**
  `close()`

* **Parameters**
  None

* **Returns**
  None

* **Example Code (종합)**

```python
from pinkylib import Motor
import time

pinky = Motor()
try:
    pinky.enable_motor()
    pinky.move(25, -25)
    time.sleep(1)
    pinky.stop()
    pinky.disable_motor()
finally:
    pinky.close()
```

---

## Camera

### `start(width=640, height=480)`

* **Description**
  Pinky의 카메라를 활성화한다.
* **Syntax**
  `start()`
  `start(width=640, height=480)`
* **Parameters**

  * `int width`  : 영상 가로 해상도
  * `int height` : 영상 세로 해상도
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()  # 또는 cam.start(width=640, height=480)
```

### `get_frame()`

* **Description**
  카메라 프레임을 읽어온다.
* **Syntax**
  `get_frame()`
* **Parameters**
  None
* **Returns**
  `np.ndarray frame` : 카메라 프레임 데이터
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()

frame = cam.get_frame()
print(type(frame), frame.shape)

cam.close()
```

### `display_jupyter(frame)`

* **Description**
  주피터 노트북에 이미지를 출력한다.
* **Syntax**
  `display_jupyter(frame)`
* **Parameters**
  `np.ndarray frame` : 출력할 이미지 데이터
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()

frame = cam.get_frame()
cam.display_jupyter(frame)

cam.close()
```

### `play_jupyter(cnt=None)`

* **Description**
  설정된 시간 동안 카메라 프레임을 주피터에 계속 출력한다.
* **Syntax**
  `play_jupyter()`
  `play_jupyter(cnt)`
* **Parameters**
  `float cnt` : 출력할 시간(초). 미지정 시 라이브 보기로 동작할 수 있음(구현에 따름).
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()
cam.play_jupyter(5)  # 5초간 재생
cam.close()
```

### `calibration_camera(img_path, checkerboard_size=(8, 6), square_size=25)`

* **Description**
  체커보드 이미지들을 불러와 카메라 캘리브레이션을 수행하고 결과를 현재 위치에 `.npz`로 저장한다.
* **Syntax**
  `calibration_camera(img_path)`
  `calibration_camera(img_path, checkerboard_size=(8, 6), square_size=25)`
* **Parameters**

  * `str img_path` : 체커보드 이미지 디렉터리 경로
  * `tuple checkerboard_size` : 내부 코너점 개수 `(cols, rows)`
  * `float square_size` : 체커보드 한 칸의 실제 변 길이(mm)
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.calibration_camera("./calib_img", checkerboard_size=(8, 6), square_size=25)
```

### `calibration(save_path="./", num_images=10, checkerboard_size=(8, 6), square_size=25)`

* **Description**
  카메라로 1초 간격으로 지정 횟수만큼 체커보드 이미지를 촬영하고, 이어서 캘리브레이션을 수행한다.
* **Syntax**
  `calibration()`
  `calibration(save_path="./", num_images=10, checkerboard_size=(8, 6), square_size=25)`
* **Parameters**

  * `str save_path` : 체커보드 이미지를 저장할 디렉터리
  * `int num_images` : 촬영 횟수
  * `tuple checkerboard_size` : 내부 코너점 개수 `(cols, rows)`
  * `float square_size` : 체커보드 한 칸 실제 변 길이(mm)
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()
cam.calibration(save_path="./", num_images=10, checkerboard_size=(8, 6), square_size=25)
cam.close()
```

### `set_calibration(file_path="camera_calibration.npz")`

* **Description**
  저장된 캘리브레이션 파일을 읽어 카메라 내부 파라미터를 설정한다.
* **Syntax**
  `set_calibration()`
  `set_calibration(file_path="camera_calibration.npz")`
* **Parameters**
  `str file_path` : 캘리브레이션 정보(npz)의 경로
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.set_calibration("camera_calibration.npz")
```

### `detect_aruco(frame, aruco_dict_type=cv2.aruco.DICT_5X5_250, marker_size=0.02)`

* **Description**
  카메라 프레임에서 ArUco 마커를 인식하고 감지 결과 프레임과 자세(위치) 리스트를 반환한다.
* **Syntax**
  `detect_aruco(frame)`
  `detect_aruco(frame, aruco_dict_type=cv2.aruco.DICT_5X5_250, marker_size=0.02)`
* **Parameters**

  * `np.ndarray frame` : 입력 이미지
  * `int aruco_dict_type` : 탐지할 ArUco 딕셔너리 종류
  * `float marker_size` : 마커 한 변의 실제 길이(미터)
* **Returns**

  * `np.ndarray output_frame` : 검출 오버레이가 그려진 프레임
  * `list[list[int|float]] pose` : `[[id, x, y, z], ...]` 형태의 위치 값
* **Example Code**

```python
from pinkylib import Camera
import cv2

cam = Camera()
cam.set_calibration("camera_calibration.npz")
cam.start()

frame = cam.get_frame()
output_frame, pose = cam.detect_aruco(frame, marker_size=0.036)
print("pose:", pose)
cam.display_jupyter(output_frame)

cam.close()
```

### `detect_aruco_target(frame, target_id, aruco_dict_type=cv2.aruco.DICT_5X5_250, marker_size=0.02)`

* **Description**
  ArUco 마커를 인식 후, 지정한 `target_id`에 해당하는 마커만 골라 반환한다.
* **Syntax**
  `detect_aruco_target(frame, target_id)`
  `detect_aruco_target(frame, target_id, aruco_dict_type=cv2.aruco.DICT_5X5_250, marker_size=0.02)`
* **Parameters**

  * `np.ndarray frame` : 입력 이미지
  * `int target_id` : 목표 마커 ID
  * `int aruco_dict_type` : 탐지할 ArUco 딕셔너리 종류
  * `float marker_size` : 마커 한 변의 실제 길이(미터)
* **Returns**

  * `np.ndarray output_frame` : 검출 오버레이 프레임
  * `list[list[int|float]] pose` : 목표 마커의 위치 값 (없으면 빈 리스트)
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.set_calibration("camera_calibration.npz")
cam.start()

frame = cam.get_frame()
output_frame, pose = cam.detect_aruco_target(frame, target_id=1, marker_size=0.036)
print("target pose:", pose)
cam.display_jupyter(output_frame)

cam.close()
```

### `close()`

* **Description**
  카메라 사용을 종료한다.
* **Syntax**
  `close()`
* **Parameters**
  None
* **Returns**
  None
* **Example Code**

```python
from pinkylib import Camera

cam = Camera()
cam.start()
_ = cam.get_frame()
cam.close()
```

---

## LCD

> LCD 모듈은 `pinky_lcd` 패키지를 사용합니다.

### `set_backlight(value)`

* **Description**
  LCD 밝기를 설정한다.
* **Syntax**
  `set_backlight(value)`
* **Parameters**
  `int value` : 밝기(0 ~ 255)
* **Returns**
  None
* **Example Code**

```python
from pinky_lcd import LCD

lcd = LCD()
lcd.set_backlight(50)
```

### `img_show(img)`

* **Description**
  LCD에 이미지를 출력한다.
* **Syntax**
  `img_show(img)`
* **Parameters**
  `np.ndarray or PIL.Image.Image img` : 출력할 이미지 데이터
* **Returns**
  None
* **Example Code**

```python
from pinky_lcd import LCD
from PIL import Image
import time

lcd = LCD()

img_width, img_height = 320, 240
background_color = (0, 255, 0)

img = Image.new('RGB', (img_width, img_height), color=background_color)
lcd.img_show(img)

time.sleep(3)
lcd.clear()
```

### `clear()`

* **Description**
  LCD를 검은 빈 화면으로 초기화한다.
* **Syntax**
  `clear()`
* **Parameters**
  None
* **Returns**
  None
* **Example Code**

```python
from pinky_lcd import LCD
from PIL import Image
import time

lcd = LCD()

img = Image.new('RGB', (320, 240), color=(0, 255, 0))
lcd.img_show(img)

time.sleep(3)
lcd.clear()
```

---

## LED

### 공통 상수 예시

```python
RED    = (255,   0,   0)
ORANGE = (255, 127,   0)
YELLOW = (255, 255,   0)
GREEN  = (  0, 255,   0)
BLUE   = (  0,   0, 255)
INDIGO = ( 75,   0, 130)
VIOLET = (148,   0, 211)
WHITE  = (255, 255, 255)
```

### `fill(color)`

* **Description**
  LED 전체를 지정한 색으로 채운다.
* **Syntax**
  `fill(color)`
* **Parameters**
  `tuple color` : `(R, G, B)`
* **Returns**
  None
* **Example Code**

```python
from pinkylib import LED

led = LED()
led.fill((0, 0, 255))  # BLUE
led.show()
```

### `set_pixel(index, color)`

* **Description**
  특정 인덱스의 LED 색을 설정한다. 색 설정 후 `show()`를 호출해야 반영된다.
* **Syntax**
  `set_pixel(index, color)`
* **Parameters**

  * `int index` : LED 인덱스 (0 ~ 7)
  * `tuple color` : `(R, G, B)`
* **Returns**
  None
* **Example Code**

```python
from pinkylib import LED

led = LED()

led.set_pixel(0, (255, 0, 0))   # RED
led.set_pixel(1, (255, 127, 0)) # ORANGE
led.set_pixel(2, (255, 255, 0)) # YELLOW
led.set_pixel(3, (0, 255, 0))   # GREEN
led.set_pixel(4, (0, 0, 255))   # BLUE
led.set_pixel(5, (75, 0, 130))  # INDIGO
led.set_pixel(6, (148, 0, 211)) # VIOLET
led.set_pixel(7, (255, 255, 255)) # WHITE

led.show()
```

### `show()`

* **Description**
  `set_pixel()` 등으로 설정한 색을 실제 LED에 적용한다.
* **Syntax**
  `show()`
* **Parameters**
  None
* **Returns**
  None
* **Example Code**

```python
from pinkylib import LED

led = LED()
led.fill((0, 0, 255))  # BLUE
led.set_pixel(4, (255, 0, 0))  # RED
led.set_pixel(5, (255, 0, 0))
led.set_pixel(6, (255, 0, 0))
led.set_pixel(7, (255, 0, 0))
led.show()
```

### `color_wipe(color, wait_ms=50)`

* **Description**
  LED를 0 → 7 인덱스 순서로 지정 색으로 순차 점등한다.
* **Syntax**
  `color_wipe(color, wait_ms=50)`
* **Parameters**

  * `tuple color` : `(R, G, B)`
  * `int wait_ms` : 다음 인덱스로 넘어가기 전 대기 시간(ms)
* **Returns**
  None
* **Example Code**

```python
from pinkylib import LED

led = LED()
RED = (255, 0, 0)
led.color_wipe(RED, wait_ms=100)
```

### `theater_chase(color, wait_ms=50, iterations=10)`

* **Description**
  지정한 색으로 연속 깜박임 효과를 낸다.
* **Syntax**
  `theater_chase(color, wait_ms=50, iterations=10)`
* **Parameters**

  * `tuple color` :
