import cv2
import time
import threading
from flask import Flask, Response, render_template

app = Flask(__name__)

# 1. 표준 OpenCV 방식으로 카메라 초기화 (0번은 기본 카메라)
cap = cv2.VideoCapture(0)

# 해상도 설정 (320x240)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

# 추가: 웹캠 자체의 프레임 속도를 10으로 제한 요청
cap.set(cv2.CAP_PROP_FPS, 10)

# 2. 최신 프레임을 저장할 전역 변수와 락 생성
global_frame = None
frame_lock = threading.Lock()

def capture_frames():
    """백그라운드 스레드에서 지속적으로 프레임을 캡처하여 global_frame 갱신"""
    global global_frame
    while True:
        # OpenCV로 프레임 읽기
        success, frame_data = cap.read()
        if not success:
            time.sleep(0.1)
            continue
            
        # 기존 libcamera의 transform(hflip=True, vflip=True)과 동일한 효과 (상하좌우 반전)
        # frame_data = cv2.flip(frame_data, -1)
        
        # 프레임을 JPEG로 인코딩
        ret, buffer = cv2.imencode('.jpg', frame_data)
        if not ret:
            continue
        frame = buffer.tobytes()
        
        # 스레드 안전하게 전역 변수 업데이트
        with frame_lock:
            global_frame = frame
        
        time.sleep(0.1)

# 3. 백그라운드 스레드 시작
capture_thread = threading.Thread(target=capture_frames)
capture_thread.daemon = True
capture_thread.start()

def gen_frames():
    """각 클라이언트의 요청마다 호출되어 global_frame을 스트리밍"""
    while True:
        with frame_lock:
            frame = global_frame
        if frame is None:
            continue
        yield ( b'--frame\r\n'
                b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
        time.sleep(0.1)

@app.route('/')
def index():
    # templates 폴더 안의 index.html을 렌더링
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    # 서버 실행 (모든 IP에서 접근 가능하도록 0.0.0.0 설정)
    app.run(host='0.0.0.0', port=5000, threaded=True)