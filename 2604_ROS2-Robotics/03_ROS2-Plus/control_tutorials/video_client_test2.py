import cv2
import requests
import numpy as np
from ultralytics import YOLO

def run_yolo_client():
    # 1. YOLO11n Segmentation 모델 로드 (최초 실행 시 자동 다운로드 됨)
    model = YOLO("yolo11n-seg.pt") 
    
    # 2. 터틀봇 서버 주소 (★ 회원님의 터틀봇 IP로 반드시 변경하세요!)
    url = 'http://10.10.14.11:5000/video_feed'
    
    # 스트리밍 요청
    response = requests.get(url, stream=True)
    bytes_data = b''
    
    # OpenCV 전용 고속 디스플레이 창 생성
    cv2.namedWindow('TurtleBot Vision - YOLO11', cv2.WINDOW_NORMAL)

    print("스트리밍 및 YOLO 추론을 시작합니다. (종료하려면 화면 클릭 후 'q'를 누르세요)")

    for chunk in response.iter_content(chunk_size=1024):
        bytes_data += chunk
        
        # JPG 이미지의 시작(ff d8)과 끝(ff d9) 찾기
        start = bytes_data.find(b'\xff\xd8')
        end = bytes_data.find(b'\xff\xd9')
        
        if start != -1 and end != -1:
            jpg = bytes_data[start:end+2]
            bytes_data = bytes_data[end+2:]
            
            # 바이너리 데이터를 OpenCV 프레임으로 디코딩
            frame = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
            
            if frame is not None:
                # 3. YOLO 추론 실행 (verbose=False로 터미널 로그 지저분한 것 방지)
                results = model(frame, verbose=False)
                
                # 4. 결과(바운딩 박스 + 마스크)가 그려진 프레임 가져오기
                annotated_frame = results[0].plot()
                
                # 5. 고속 화면 출력
                cv2.imshow('TurtleBot Vision - YOLO11', annotated_frame)
                
            # 'q' 키를 누르면 종료
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    cv2.destroyAllWindows()

if __name__ == '__main__':
    run_yolo_client()