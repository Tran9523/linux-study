import sys
from pathlib import Path
from collections import Counter
import cv2
import time


from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QVBoxLayout,
    QHBoxLayout, QStackedWidget, QFrame, QScrollArea,
    QGraphicsDropShadowEffect, QSizePolicy
)
from PyQt5.QtGui import QPixmap, QImage, QFont, QColor
from PyQt5.QtCore import Qt, QTimer

from ultralytics import YOLO



# 기본 설정
BASE_DIR = Path(__file__).resolve().parent

PARTS_DET_CONF_THRESHOLD = 0.85       # 부품 확인용 detect
HOME_DET_CONF_THRESHOLD = 0.85        # 홈 화면 자동 제품 인식용 detect

STEP_JUMP_CONF_THRESHOLD = 0.90       # "인식된 단계로 이동" 버튼 표시용
STEP_AUTO_ADVANCE_CONF_THRESHOLD = 0.90   # 자동 다음 단계 진행용

REQUIRED_CONSECUTIVE_MATCHES = 20       # 조립 인식에 필요한 frame count <- 빨리 넘어가면 수정 (하단 패널티 보충)
REQUIRED_PARTS_MATCH_TARGET = 10        # 가이드 첫번째 화면에서 부품 인식에 필요한 frame
STEP_SUCCESS_DELAY_MS = 1500   # 성공 문구 표시 후 다음 단계로 넘어가기까지 대기 시간(ms)

CAMERA_INDEX = 0
IMG_SIZE = 224

USE_CLASSIFICATION_MODEL = True
USE_DETECTION_MODEL = True

# 홈 화면 detection 모델 경로
HOME_DET_MODEL_PATH = BASE_DIR / "YOLO11_model" / "detect_all" / "weights" / "best.pt"


# 단계별 해야 할 일
STEP_TASK_MAP = {
    "raspberry_pi": {
        "step1": "빨간색 바닥 부품과 보드를 연결하세요. 전원 케이블 및 HDMI 단자의 위치를 보면 연결이 쉽습니다.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step2": "FAN이 있는 케이스를 FAN 케이블을 연결한 후 위로 덮어 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step3": "하얀색 덮개를 위치에 맞게 덮어 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step4": "조립이 완성되었습니다.\n잠시 후 홈 화면으로 이동합니다.",
    },

    "foosball": {
        "step1" : "바닥 부품 4개를 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step2" : "옆면 벽을 연결하여 벽 2개를 만드세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step3" : "골대 벽을 연결하여 골대 벽 2개를 만드세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step4" : "골대 부품들을 연결하여 골대 2개를 만드세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step5" : "옆면 벽과 골대 벽을 연결하여 전체 벽을 만드세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step6" : "전체 벽과 바닥을 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step7" : "벽 옆면에 선수봉 4개를 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step8" : "골대 벽에 골대를 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step9" : "조립이 완성되었습니다.\n잠시 후 홈 화면으로 이동합니다."    
        },
    
    "plates_tool": {
        "step1" : "받침대와 중심대를 서로 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step2" : "반대쪽 받침대에도 중심대를 연결하세요.\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step3" : "조절바 위치에 유의하여 스프링작용판이 있는 받침대에 높이조정대를 연결하세요\n\n\n바닥에 내려놓으면 인식이 잘됩니다.",
        "step4" : "조립이 완성되었습니다.\n잠시 후 홈 화면으로 이동합니다.",
        }
}


# 가이드 설정
# step마다 이미지 여러 장
GUIDE_CONFIG = {
    "raspberry_pi": {
        "title": "라즈베리 파이",
        "description": "라즈베리 파이 조립 가이드",
        "home_card_image": BASE_DIR / "assets" / "raspberry_pi" / "raspberry_pi.png",
        "model_path": BASE_DIR / "YOLO11_model" / "classify_raspberry" / "weights" / "best.pt",
        "precheck": [
            BASE_DIR / "assets" / "raspberry_pi" / "parts-1.jpg",
        ],
        "steps": [
            [
                BASE_DIR / "assets" / "raspberry_pi" / "step 1-1.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 1-2.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 1-3.jpg",
            ],
            [
                BASE_DIR / "assets" / "raspberry_pi" / "step 2-1.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 2-2.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 2-3.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 2-4.jpg",
            ],
            [
                BASE_DIR / "assets" / "raspberry_pi" / "step 3-1.jpg",
                BASE_DIR / "assets" / "raspberry_pi" / "step 3-2.jpg",
            ],
            [
                BASE_DIR / "assets" / "raspberry_pi" / "step 4-1.png",
            ]
        ]
    },

    "foosball": {
        "title": "축구 게임",
        "description": "축구 테이블 조립 가이드",
        "home_card_image": BASE_DIR / "assets" / "foosball" / "foosball.png",
        "model_path": BASE_DIR / "YOLO11_model" / "classify_foosball" / "weights" / "best.pt",
        "precheck": [
            BASE_DIR / "assets" / "foosball" / "parts-1.jpg",
            BASE_DIR / "assets" / "foosball" / "parts-2.jpg",
            BASE_DIR / "assets" / "foosball" / "parts-3.jpg",
        ],
        "steps": [
            [
                BASE_DIR / "assets" / "foosball" / "step 1-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 1-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 1-3.jpg"
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 2-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 2-2.jpg",
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 3-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 3-2.jpg",
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 4-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 4-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 4-3.jpg",
                BASE_DIR / "assets" / "foosball" / "step 4-4.jpg",
                BASE_DIR / "assets" / "foosball" / "step 4-5.jpg"
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 5-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 5-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 5-3.jpg",
                BASE_DIR / "assets" / "foosball" / "step 5-4.jpg"
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 6-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 6-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 6-3.jpg",
                BASE_DIR / "assets" / "foosball" / "step 6-4.jpg"
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 7-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-3.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-4.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-5.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-6.jpg",
                BASE_DIR / "assets" / "foosball" / "step 7-7.jpg"

            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 8-1.jpg",
                BASE_DIR / "assets" / "foosball" / "step 8-2.jpg",
                BASE_DIR / "assets" / "foosball" / "step 8-3.jpg",
                BASE_DIR / "assets" / "foosball" / "step 8-4.jpg"
            ],
            [
                BASE_DIR / "assets" / "foosball" / "step 9-1.png"
            ]
        ]
    },

    "plates_tool": {
        "title": "만능 기판받침대",
        "description": "만능 기판받침대 조립 가이드",
        "home_card_image": BASE_DIR / "assets" / "plates_tool" / "plates_tool.png",
        "model_path": BASE_DIR / "YOLO11_model" / "classify_plates" / "weights" / "best.pt",
        "precheck": [
            BASE_DIR / "assets" / "plates_tool" / "parts-1.jpg",
            BASE_DIR / "assets" / "plates_tool" / "parts-2.jpg",
        ],
        "steps": [
            [
                BASE_DIR / "assets" / "plates_tool" / "step 1-1.jpg",
                BASE_DIR / "assets" / "plates_tool" / "step 1-2.jpg",
            ],
            [
                BASE_DIR / "assets" / "plates_tool" / "step 2-1.jpg",
                BASE_DIR / "assets" / "plates_tool" / "step 2-2.jpg",
            ],
            [
                BASE_DIR / "assets" / "plates_tool" / "step 3-1.jpg",
                BASE_DIR / "assets" / "plates_tool" / "step 3-2.jpg",
                BASE_DIR / "assets" / "plates_tool" / "step 3-3.jpg",
            ],
            [
                BASE_DIR / "assets" / "plates_tool" / "step 4-1.png",
            ]
        ]
    }  
}

PRODUCT_PARTS_MAP = {
    "raspberry_pi": ["base_case", "fan_case", "board", "upper_casecar"],
    "plates_tool": ["height_plate", "spring_plate", "base_plate"],
    "foosball": [
        "field1", "field2", "field3", "field4",
        "goal_net_back", "goal_net_side",
        "goalside_1", "goalside_2",
        "lateral1", "lateral2",
        "player2_rod", "player3_rod",
        "rod_cover", "knobb"
    ],
}

PRODUCT_INFO = {
    "raspberry_pi": {
        "total_parts": 4,
        "auto_move_threshold": 3,
        "required_parts": {
            "base_case": 1,
            "fan_case": 1,
            "board": 1,
            "upper_casecar": 1,
        },
        "precheck_title": "부품 확인",
        "precheck_text": "라즈베리 파이 조립에 필요한 전체 부품을 모두 화면에 보여주세요.",
    },
    "plates_tool": {
        "total_parts": 4,
        "auto_move_threshold": 3,
        "required_parts": {
            "height_plate": 1,
            "spring_plate": 1,
            "base_plate": 2,
        },
        "precheck_title": "부품 확인",
        "precheck_text": "만능 기판받침대 조립에 필요한 전체 부품을 모두 화면에 보여주세요.",
    },
    "foosball": {
        "total_parts": 30,
        "auto_move_threshold": 6,
        "required_parts": {
            "field1": 1,
            "field2": 1,
            "field3": 1,
            "field4": 1,
            "goal_net_back": 2,
            "goal_net_side": 4,
            "goalside_1": 2,
            "goalside_2": 2,
            "lateral1": 2,
            "lateral2": 2,
            "player2_rod": 2,
            "player3_rod": 2,
            "rod_cover": 4,
            "knobb": 4,
        },
        "precheck_title": "부품 확인",
        "precheck_text": "축구 게임 조립에 필요한 전체 부품을 모두 화면에 보여주세요.",
    },
}

def apply_shadow(widget, blur=28, x=0, y=8, alpha=35):
    shadow = QGraphicsDropShadowEffect()
    shadow.setBlurRadius(blur)
    shadow.setXOffset(x)
    shadow.setYOffset(y)
    shadow.setColor(QColor(0, 0, 0, alpha))
    widget.setGraphicsEffect(shadow)

class ClickableHomeRow(QFrame):
    def __init__(self, title, image_path, on_click, pixmap_loader, parent=None):
        super().__init__(parent)
        self.on_click = on_click
        self.setObjectName("homeSelectRow")
        self.setCursor(Qt.PointingHandCursor)
        self.setFixedHeight(96)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(22, 12, 22, 12)
        layout.setSpacing(14)

        self.title_label = QLabel(title)
        self.title_label.setObjectName("homeSelectTitle")
        self.title_label.setAlignment(Qt.AlignVCenter | Qt.AlignLeft)
        self.title_label.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.title_label.setAttribute(Qt.WA_TransparentForMouseEvents, True)

        self.image_label = QLabel()
        self.image_label.setObjectName("homeInlineImage")
        self.image_label.setAlignment(Qt.AlignCenter)
        self.image_label.setFixedSize(128, 72)
        self.image_label.setAttribute(Qt.WA_TransparentForMouseEvents, True)

        pixmap = pixmap_loader(image_path, 128, 72)
        if pixmap is not None:
            self.image_label.setPixmap(pixmap)
        else:
            self.image_label.setText("이미지")

        layout.addWidget(self.title_label, 1)
        layout.addWidget(self.image_label, 0, Qt.AlignRight | Qt.AlignVCenter)

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton and callable(self.on_click):
            self.on_click()
        super().mousePressEvent(event)

# 홈 화면
class HomePage(QWidget):
    def __init__(self, on_select):
        super().__init__()
        self.last_det_time = 0.0
        self.last_det_result = None
        self.current_detected_product = None
        self.show_home_detection_overlay = True

        self.on_select = on_select

        self.cap = None
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_frame)

        self.det_model = None
        self.auto_detect_running = False

        self.product_detect_start_time = None

        self.init_ui()
        self.load_detection_model_if_available()
        QTimer.singleShot(300, self.start_auto_detect)

    def init_ui(self):
        main_layout = QVBoxLayout()
        main_layout.setContentsMargins(32, 32, 32, 32)
        main_layout.setSpacing(20)

        title = QLabel("부품 조립 가이드")
        title.setObjectName("title")
        title.setAlignment(Qt.AlignCenter)

        subtitle = QLabel("수동으로 선택하거나 카메라로 자동 인식할 수 있습니다")
        subtitle.setObjectName("subtitle")
        subtitle.setAlignment(Qt.AlignCenter)

        main_layout.addWidget(title)
        main_layout.addWidget(subtitle)

        content_layout = QHBoxLayout()
        content_layout.setSpacing(20)

        # 왼쪽: 수동 선택
        left_frame = QFrame()
        left_frame.setObjectName("panel")
        apply_shadow(left_frame, blur=26, y=8, alpha=26)

        left_layout = QVBoxLayout()
        left_layout.setContentsMargins(20, 20, 20, 20)
        left_layout.setSpacing(18)

        manual_title = QLabel("직접 선택")
        manual_title.setObjectName("sectionTitle")

        button_layout = QVBoxLayout()
        button_layout.setSpacing(16)

        for key, cfg in GUIDE_CONFIG.items():
            card = QFrame()
            card.setObjectName("homeCard")

            card_layout = QVBoxLayout()
            card_layout.setContentsMargins(16, 12, 16, 16)
            card_layout.setSpacing(8)

            select_row = ClickableHomeRow(
                title=cfg["title"],
                image_path=cfg.get("home_card_image"),
                on_click=lambda k=key: self.on_select(k),
                pixmap_loader=self.create_home_card_pixmap
            )

            product_info = PRODUCT_INFO.get(key, {})
            total_parts = product_info.get("total_parts", "-")
            auto_threshold = product_info.get("auto_move_threshold", "-")

            desc_text = f"총 {total_parts}개 / {auto_threshold}개 이상 감지 시 자동 이동"

            desc = QLabel(desc_text)
            desc.setObjectName("homeCardDesc")
            desc.setAlignment(Qt.AlignCenter)
            desc.setWordWrap(True)

            card_layout.addWidget(select_row)
            card_layout.addWidget(desc)
            card.setLayout(card_layout)

            apply_shadow(card, blur=18, y=6, alpha=20)
            button_layout.addWidget(card)

        left_layout.addWidget(manual_title)
        left_layout.addLayout(button_layout)
        left_layout.addStretch()
        left_frame.setLayout(left_layout)

        # 오른쪽: 자동 인식
        right_frame = QFrame()
        right_frame.setObjectName("panel")
        apply_shadow(right_frame, blur=26, y=8, alpha=26)

        right_layout = QVBoxLayout()
        right_layout.setContentsMargins(20, 20, 20, 20)
        right_layout.setSpacing(14)

        auto_header_layout = QHBoxLayout()
        auto_header_layout.setSpacing(10)

        auto_title = QLabel("부품 자동 인식")
        auto_title.setObjectName("sectionTitle")

        self.home_overlay_toggle_btn = QPushButton("라벨 박스 ON")
        self.home_overlay_toggle_btn.setObjectName("topButton")
        self.home_overlay_toggle_btn.setCheckable(True)
        self.home_overlay_toggle_btn.setChecked(True)
        self.home_overlay_toggle_btn.clicked.connect(self.toggle_home_detection_overlay)

        auto_header_layout.addWidget(auto_title)
        auto_header_layout.addStretch()
        auto_header_layout.addWidget(self.home_overlay_toggle_btn)

        self.auto_status_label = QLabel("자동 인식 시작를 누르세요.")
        self.auto_status_label.setObjectName("miniStatusValue")
        self.auto_status_label.setWordWrap(True)

        self.home_camera_label = QLabel("Camera Preview")
        self.home_camera_label.setObjectName("guideImageLabel")
        self.home_camera_label.setAlignment(Qt.AlignCenter)
        self.home_camera_label.setMinimumSize(640, 460)
        self.home_camera_label.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_layout = QHBoxLayout()
        btn_layout.setSpacing(10)

        self.auto_start_btn = QPushButton("자동 인식 시작")
        self.auto_start_btn.setObjectName("primaryButton")
        self.auto_start_btn.clicked.connect(self.start_auto_detect)

        self.auto_stop_btn = QPushButton("정지")
        self.auto_stop_btn.setObjectName("topButton")
        self.auto_stop_btn.clicked.connect(self.stop_auto_detect)

        btn_layout.addWidget(self.auto_start_btn)
        btn_layout.addWidget(self.auto_stop_btn)

        right_layout.addLayout(auto_header_layout)
        right_layout.addWidget(self.auto_status_label)
        right_layout.addWidget(self.home_camera_label, 1)
        right_layout.addLayout(btn_layout)

        right_frame.setLayout(right_layout)

        content_layout.addWidget(left_frame, 2)
        content_layout.addWidget(right_frame, 4)

        main_layout.addLayout(content_layout)
        self.setLayout(main_layout)

    def load_detection_model_if_available(self):
        if not USE_DETECTION_MODEL:
            self.det_model = None
            return

        if not HOME_DET_MODEL_PATH.exists():
            self.det_model = None
            return

        try:
            self.det_model = YOLO(str(HOME_DET_MODEL_PATH))
        except Exception as e:
            print(f"[Home detection model load failed] {e}")
            self.det_model = None

    def create_home_card_pixmap(self, img_path, target_w=160, target_h=80):
        if img_path is None:
            return None

        img_path = Path(img_path)
        if not img_path.exists():
            return None
        
        pixmap = QPixmap(str(img_path))
        if pixmap.isNull():
            return None
        
        return pixmap.scaled(
            target_w,
            target_h,
            Qt.KeepAspectRatio,
            Qt.SmoothTransformation
        )

    def toggle_home_detection_overlay(self):
        self.show_home_detection_overlay = self.home_overlay_toggle_btn.isChecked()
        self.home_overlay_toggle_btn.setText(
            "라벨 박스 ON" if self.show_home_detection_overlay else "라벨 박스 OFF"
        )

    def start_auto_detect(self):
        self.stop_auto_detect()

        if self.cap is None or not self.cap.isOpened():
            self.cap = cv2.VideoCapture(CAMERA_INDEX)
            self.cap.set(cv2.CAP_PROP_BUFFERSIZE, 1) # default : 30


        if self.cap is None or not self.cap.isOpened():
            self.auto_status_label.setText("웹캠을 열 수 없습니다.")
            return

        self.auto_detect_running = True
        self.timer.start(80)

        self.show_home_detection_overlay = self.home_overlay_toggle_btn.isChecked()
        self.home_overlay_toggle_btn.setText(
            "라벨 박스 ON" if self.show_home_detection_overlay else "라벨 박스 OFF"
        )

        if USE_DETECTION_MODEL and self.det_model is not None:
            self.auto_status_label.setText("부품 인식 중입니다...")
        else:
            self.auto_status_label.setText("테스트 모드")

    def stop_auto_detect(self):
        self.timer.stop()
        self.auto_detect_running = False
        self.auto_start_btn.setText("자동 인식 시작")

        if self.cap is not None:
            if self.cap.isOpened():
                self.cap.release()
            self.cap = None

        self.home_camera_label.setPixmap(QPixmap())
        self.home_camera_label.setText("Camera Preview")
        self.auto_status_label.setText("자동 인식이 중지되었습니다.")

    def get_product_match_counts(self, detected_counts: dict):
        product_match_counts = {}

        for product_key, class_names in PRODUCT_PARTS_MAP.items():
            count = sum(detected_counts.get(name, 0) for name in class_names)
            product_match_counts[product_key] = count

        return product_match_counts

    def get_detected_product_keys(self, detected_counts: dict):
        detected_product_keys = []

        for product_key, class_names in PRODUCT_PARTS_MAP.items():
            count = sum(detected_counts.get(name, 0) for name in class_names)
            if count > 0:
                detected_product_keys.append(product_key)

        return detected_product_keys

    def find_best_product(self, product_match_counts: dict):
        if not product_match_counts:
            return None, 0

        best_product = max(product_match_counts, key=product_match_counts.get)
        best_count = product_match_counts[best_product]
        return best_product, best_count

    def update_frame(self):
        if self.cap is None or not self.cap.isOpened():
            return

        ret, frame = self.cap.read()
        if not ret:
            self.auto_status_label.setText("카메라 프레임을 읽을 수 없습니다.")
            return

        display_frame = frame.copy()

        if not self.auto_detect_running:
            rgb = cv2.cvtColor(display_frame, cv2.COLOR_BGR2RGB)
            h, w, ch = rgb.shape
            bytes_per_line = ch * w
            qimg = QImage(rgb.data, w, h, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qimg).scaled(
                self.home_camera_label.width(),
                self.home_camera_label.height(),
                Qt.KeepAspectRatio,
                Qt.SmoothTransformation
            )
            self.home_camera_label.setPixmap(pixmap)
            return

        if not USE_DETECTION_MODEL or self.det_model is None:
            rgb = cv2.cvtColor(display_frame, cv2.COLOR_BGR2RGB)
            h, w, ch = rgb.shape
            bytes_per_line = ch * w
            qimg = QImage(rgb.data, w, h, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qimg).scaled(
                self.home_camera_label.width(),
                self.home_camera_label.height(),
                Qt.KeepAspectRatio,
                Qt.SmoothTransformation
            )
            self.home_camera_label.setPixmap(pixmap)

            self.auto_status_label.setText("detection 모델이 없습니다.")
            return

        detected_counts = Counter()
        

        try:
            results = self.det_model.predict(
                source=frame,
                imgsz=640,
                conf=HOME_DET_CONF_THRESHOLD,
                verbose=False
            )
            result = results[0]

            if result is not None and result.boxes is not None and len(result.boxes) > 0:
                for box in result.boxes:
                    cls_id = int(box.cls[0].item())
                    cls_name = result.names[cls_id]
                    conf = float(box.conf[0].item())

                    # 신뢰도 설정 값 이상만 인정
                    if conf < HOME_DET_CONF_THRESHOLD:
                        continue

                    detected_counts[cls_name] += 1

                if self.show_home_detection_overlay:
                    display_frame = result.plot()
            else:
                display_frame = frame.copy()

        except Exception as e:
            self.auto_status_label.setText(f"detection 오류: {e}")
            return

        # 화면 표시
        rgb = cv2.cvtColor(display_frame, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb.shape
        bytes_per_line = ch * w
        qimg = QImage(rgb.data, w, h, bytes_per_line, QImage.Format_RGB888)
        pixmap = QPixmap.fromImage(qimg).scaled(
            self.home_camera_label.width(),
            self.home_camera_label.height(),
            Qt.KeepAspectRatio,
            Qt.SmoothTransformation
        )
        self.home_camera_label.setPixmap(pixmap)

        product_match_counts = self.get_product_match_counts(detected_counts)
        best_product, best_count = self.find_best_product(product_match_counts)

        if best_product is None or best_count == 0:
            self.product_detect_start_time = None
            self.current_detected_product = None
            self.auto_status_label.setText("부품 감지중...")
            return

        # 혼합 감지 여부를 먼저 판단
        detected_product_keys = self.get_detected_product_keys(detected_counts)

        if len(detected_product_keys) >= 2:
            self.product_detect_start_time = None
            self.current_detected_product = None

            mixed_titles = [GUIDE_CONFIG[key]["title"] for key in detected_product_keys]
            self.auto_status_label.setText(
                f"혼합 감지중입니다. ({', '.join(mixed_titles)})"
            )
            return

        required_count = PRODUCT_INFO.get(best_product, {}).get("auto_move_threshold", 1)
        best_title = GUIDE_CONFIG[best_product]["title"]

        if best_count < required_count:
            self.product_detect_start_time = None
            self.current_detected_product = None
            self.auto_status_label.setText(f"{best_title} 부품 {best_count}개 감지중...")
            return

        product_key = best_product
        matched_count = best_count

        # 다른 제품이 새로 감지되면 시간 초기화
        if self.current_detected_product != product_key:
            self.current_detected_product = product_key
            self.product_detect_start_time = time.time()

        if self.product_detect_start_time is None:
            self.product_detect_start_time = time.time()

        elapsed = time.time() - self.product_detect_start_time
        product_title = GUIDE_CONFIG[product_key]["title"]

        self.auto_status_label.setText(
            f"{product_title} 부품 {matched_count}개 감지 ({elapsed:.1f}s)"
        )

        # 2초 이상 유지되면 해당 가이드로 이동
        if elapsed >= 2.0:
            self.auto_status_label.setText(f"{product_title} 가이드로 이동합니다.")
            self.stop_auto_detect()
            QTimer.singleShot(500, lambda k=product_key: self.on_select(k))

    def closeEvent(self, event):
        self.stop_auto_detect()
        event.accept()


# 가이드 화면
class GuidePage(QWidget):
    def __init__(self, go_home):
        super().__init__()
        self.go_home = go_home

        self.last_det_time = 0.0
        self.last_det_result = None
        self.model = None
        self.parts_det_model = None

        self.cap = None
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_frame)

        self.image_timer = QTimer()
        self.image_timer.timeout.connect(self.change_image)
        self.auto_image_running = True
        self.current_guide_key = None

        # 내부 step index
        self.current_step_index = 0

        self.current_image_index = 0
        self.is_running = False
        self.match_count = 0
        self.detected_step_for_jump = None

        self.in_precheck_mode = True
        self.required_parts_status = {}
        self.required_parts_consecutive = 0
        self.required_parts_match_target = REQUIRED_PARTS_MATCH_TARGET

        self.success_pending = False
        # 설명란 하단에 따로 붙일 에러/안내 메시지
        self.extra_message = ""

        self.init_ui()

    def init_ui(self):
        main_layout = QVBoxLayout()
        main_layout.setContentsMargins(24, 24, 24, 24)
        main_layout.setSpacing(16)

        top_bar = QHBoxLayout()
        top_bar.setSpacing(12)

        self.home_btn = QPushButton("홈")
        self.home_btn.setObjectName("topButton")
        self.home_btn.clicked.connect(self.handle_home)

        self.title_label = QLabel("가이드")
        self.title_label.setObjectName("pageTitle")
        self.title_label.setAlignment(Qt.AlignCenter)

        left_container = QWidget()
        left_top_layout = QHBoxLayout(left_container)
        left_top_layout.setContentsMargins(0, 0, 0, 0)
        left_top_layout.addWidget(self.home_btn)
        left_top_layout.addStretch()

        center_container = QWidget()
        center_top_layout = QHBoxLayout(center_container)
        center_top_layout.setContentsMargins(0, 0, 0, 0)
        center_top_layout.addWidget(self.title_label, 0, Qt.AlignCenter)

        right_container = QWidget()
        right_top_layout = QHBoxLayout(right_container)
        right_top_layout.setContentsMargins(0, 0, 0, 0)
        right_top_layout.addStretch()

        top_bar.addWidget(left_container, 1)
        top_bar.addWidget(center_container, 2)
        top_bar.addWidget(right_container, 1)

        main_layout.addLayout(top_bar)

        content_layout = QHBoxLayout()
        content_layout.setSpacing(18)

        # 왼쪽 가이드 이미지
        left_frame = QFrame()
        left_frame.setObjectName("panel")
        apply_shadow(left_frame, blur=32, y=10, alpha=26)

        left_layout = QVBoxLayout()
        left_layout.setContentsMargins(10, 10, 10, 10)
        left_layout.setSpacing(8)

        guide_header = QLabel("가이드 이미지")
        guide_header.setObjectName("sectionTitle")
        guide_header.setAlignment(Qt.AlignCenter)

        image_nav_layout = QHBoxLayout()
        image_nav_layout.setSpacing(10)

        self.prev_img_btn = QPushButton("이전")
        self.prev_img_btn.setObjectName("topButton")
        self.prev_img_btn.clicked.connect(self.show_prev_image)

        self.toggle_auto_img_btn = QPushButton("자동 넘김 정지")
        self.toggle_auto_img_btn.setObjectName("topButton")
        self.toggle_auto_img_btn.clicked.connect(self.toggle_auto_image)

        self.next_img_btn = QPushButton("다음")
        self.next_img_btn.setObjectName("topButton")
        self.next_img_btn.clicked.connect(self.show_next_image)

        image_nav_layout.addStretch()
        image_nav_layout.addWidget(self.prev_img_btn)
        image_nav_layout.addWidget(self.toggle_auto_img_btn)
        image_nav_layout.addWidget(self.next_img_btn)
        image_nav_layout.addStretch()

        self.guide_image_label = QLabel("Guide Image")
        self.guide_image_label.setAlignment(Qt.AlignCenter)
        self.guide_image_label.setObjectName("guideImageLabel")
        self.guide_image_label.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        self.guide_image_label.setMinimumSize(700, 500)

        left_layout.addWidget(guide_header, 0, Qt.AlignTop)
        left_layout.addLayout(image_nav_layout)
        left_layout.addWidget(self.guide_image_label, 1)

        left_frame.setLayout(left_layout)

        # 오른쪽 정보
        right_frame = QFrame()
        right_frame.setObjectName("panel")
        apply_shadow(right_frame, blur=32, y=10, alpha=26)

        right_layout = QVBoxLayout()
        right_layout.setContentsMargins(18, 18, 18, 18)
        right_layout.setSpacing(14)

        info_title = QLabel("가이드 정보")
        info_title.setObjectName("sectionTitle")

        top_info_frame = QFrame()
        top_info_frame.setObjectName("miniInfoFrame")

        top_info_layout = QHBoxLayout()
        top_info_layout.setContentsMargins(6, 6, 6, 6)
        top_info_layout.setSpacing(6)

        step_card = QFrame()
        step_card.setObjectName("miniCard")
        step_card_layout = QVBoxLayout()
        step_card_layout.setContentsMargins(6, 4, 6, 4)
        step_card_layout.setSpacing(4)

        current_title = QLabel("현재 단계")
        current_title.setObjectName("miniCardTitle")

        self.step_label = QLabel("부품 확인")
        self.step_label.setObjectName("miniValue")

        step_card_layout.addWidget(current_title)
        step_card_layout.addWidget(self.step_label)
        step_card.setLayout(step_card_layout)

        conf_card = QFrame()
        conf_card.setObjectName("miniCard")
        conf_card_layout = QVBoxLayout()
        conf_card_layout.setContentsMargins(6, 4, 6, 4)
        conf_card_layout.setSpacing(4)

        self.conf_title_label = QLabel("신뢰도")
        self.conf_title_label.setObjectName("miniCardTitle")

        self.conf_label = QLabel("-")
        self.conf_label.setObjectName("miniValue")

        conf_card_layout.addWidget(self.conf_title_label)
        conf_card_layout.addWidget(self.conf_label)
        conf_card.setLayout(conf_card_layout)

        self.progress_label = QLabel(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

        top_info_layout.addWidget(step_card)
        top_info_layout.addWidget(conf_card)
        top_info_frame.setLayout(top_info_layout)

        task_frame = QFrame()
        task_frame.setObjectName("taskFrame")
        task_frame.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)

        task_layout = QVBoxLayout()
        task_layout.setContentsMargins(16, 10, 16, 12)
        task_layout.setSpacing(6)
        task_layout.setAlignment(Qt.AlignTop)

        task_title = QLabel("설명")
        task_title.setObjectName("cardTitle")

        self.task_label = QLabel("가이드 시작 버튼을 눌러 현재 단계 안내를 확인하세요.")
        self.task_label.setObjectName("taskValue")
        self.task_label.setWordWrap(True)
        self.task_label.setAlignment(Qt.AlignTop | Qt.AlignLeft)
        self.task_label.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)

        self.task_scroll = QScrollArea()
        self.task_scroll.setWidgetResizable(True)
        self.task_scroll.setFrameShape(QFrame.NoFrame)
        self.task_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.task_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.task_scroll.setObjectName("taskScrollArea")

        task_content = QWidget()
        task_content_layout = QVBoxLayout(task_content)
        task_content_layout.setContentsMargins(0, 0, 0, 0)
        task_content_layout.setSpacing(0)
        task_content_layout.addWidget(self.task_label)
        task_content_layout.addStretch()

        self.task_scroll.setWidget(task_content)

        task_layout.addWidget(task_title, 0, Qt.AlignTop)
        task_layout.addWidget(self.task_scroll, 1)
        task_frame.setLayout(task_layout)

        camera_title = QLabel("실시간 카메라")
        camera_title.setObjectName("cardTitle")

        self.camera_label = QLabel("카메라 미리보기")
        self.camera_label.setAlignment(Qt.AlignCenter)
        self.camera_label.setObjectName("cameraLabel")
        self.camera_label.setFixedSize(260, 180)

        self.jump_btn = QPushButton("인식된 단계로 이동")
        self.jump_btn.setObjectName("primaryButton")
        self.jump_btn.clicked.connect(self.jump_to_detected_step)
        self.jump_btn.hide()

        right_layout.addWidget(info_title)
        right_layout.addWidget(top_info_frame)
        right_layout.addWidget(task_frame, 1)
        right_layout.addWidget(self.jump_btn, 0)
        right_layout.addWidget(camera_title)
        right_layout.addWidget(self.camera_label, 0, Qt.AlignRight | Qt.AlignBottom)

        right_frame.setLayout(right_layout)

        content_layout.addWidget(left_frame, 4)
        content_layout.addWidget(right_frame, 2)

        main_layout.addLayout(content_layout)
        self.setLayout(main_layout)

        self.success_overlay = QLabel("성공!\n다음 단계로 넘어갑니다")
        self.success_overlay.setParent(self)
        self.success_overlay.setAlignment(Qt.AlignCenter)
        self.success_overlay.hide()
        self.success_overlay.setStyleSheet("""
            QLabel {
                background-color: rgba(0, 0, 0, 150);
                color: white;
                border-radius: 24px;
                font-size: 36px;
                font-weight: 700;
                padding: 30px 50px;
            }
        """)

    def set_extra_message(self, message):
        self.extra_message = message or ""
        self.refresh_task_text()

    def get_base_task_text(self):
        if self.current_guide_key is None:
            return "현재 단계 안내가 없습니다."

        if self.in_precheck_mode:
            return self.build_precheck_task_text()

        step_key = f"step{self.current_step_index}"
        return STEP_TASK_MAP.get(self.current_guide_key, {}).get(step_key, "현재 단계 안내가 없습니다.")

    def refresh_task_text(self):
        base_text = self.get_base_task_text()

        if self.extra_message:
            self.task_label.setText(f"{base_text}\n\n[안내]\n{self.extra_message}")
        else:
            self.task_label.setText(base_text)

        self.task_label.adjustSize()
        self.task_label.updateGeometry()

    def update_success_overlay_geometry(self):
        if not hasattr(self, "success_overlay"):
            return
        overlay_w = 520
        overlay_h = 180
        x = (self.width() - overlay_w) // 2
        y = (self.height() - overlay_h) // 2
        self.success_overlay.setGeometry(x, y, overlay_w, overlay_h)

    def toggle_auto_image(self):
        if self.auto_image_running:
            self.image_timer.stop()
            self.auto_image_running = False
            self.toggle_auto_img_btn.setText("자동 넘김 시작")
        else:
            self.image_timer.start(3000)
            self.auto_image_running = True
            self.toggle_auto_img_btn.setText("자동 넘김 정지")

    def load_model_for_guide(self, guide_key):
        self.model = None

        if not USE_CLASSIFICATION_MODEL:
            self.set_extra_message("classification 모델 없이 UI 테스트 모드입니다.")
            return

        if guide_key not in GUIDE_CONFIG:
            self.set_extra_message("가이드 설정을 찾을 수 없습니다.")
            return

        model_path = GUIDE_CONFIG[guide_key].get("model_path", None)

        if model_path is None:
            self.set_extra_message("모델 경로가 설정되지 않았습니다.")
            return

        if not model_path.exists():
            self.set_extra_message("classification 모델 파일이 없습니다.")
            return

        try:
            self.model = YOLO(str(model_path))
        except Exception as e:
            self.model = None
            self.set_extra_message(f"classification 모델 로드 오류: {e}")

    def load_parts_detection_model(self):
        self.parts_det_model = None

        if not USE_DETECTION_MODEL:
            self.set_extra_message("detection 모델 없이 부품 확인 단계는 UI만 표시됩니다.")
            return

        if not HOME_DET_MODEL_PATH.exists():
            self.set_extra_message("부품 확인용 detection 모델 파일이 없습니다.")
            return

        try:
            self.parts_det_model = YOLO(str(HOME_DET_MODEL_PATH))
        except Exception as e:
            self.parts_det_model = None
            self.set_extra_message(f"부품 detection 모델 로드 오류: {e}")

    def get_current_image_list(self):
        if self.current_guide_key is None:
            return []

        cfg = GUIDE_CONFIG.get(self.current_guide_key, {})

        if self.in_precheck_mode:
            return cfg.get("precheck", [])

        step_groups = cfg.get("steps", [])
        guide_step_index = self.current_step_index - 1

        if not (0 <= guide_step_index < len(step_groups)):
            return []

        return step_groups[guide_step_index]

    def set_guide(self, guide_key):
        self.stop_camera()

        self.current_guide_key = guide_key
        self.current_step_index = 0
        self.current_image_index = 0
        self.is_running = False
        self.match_count = 0
        self.detected_step_for_jump = None

        self.in_precheck_mode = True
        self.required_parts_consecutive = 0
        self.reset_required_parts_status()
        self.extra_message = ""

        cfg = GUIDE_CONFIG[guide_key]
        self.title_label.setText(cfg["title"])
        self.conf_title_label.setText("진행률" if self.in_precheck_mode else "신뢰도")
        self.conf_label.setText("0.0%" if self.in_precheck_mode else "-")
        self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

        self.load_model_for_guide(guide_key)
        self.load_parts_detection_model()

        self.refresh_step_display()
        self.show_step_image()
        self.refresh_task_text()

    def reset_required_parts_status(self):
        self.required_parts_status = {}

        if self.current_guide_key is None:
            return

        product_info = PRODUCT_INFO.get(self.current_guide_key, {})
        required_parts = product_info.get("required_parts", {})

        for part_name, required_count in required_parts.items():
            self.required_parts_status[part_name] = {
                "required": required_count,
                "detected": 0,
                "checked": False,
            }

    def get_precheck_progress_percent(self):
        if not self.required_parts_status:
            return 0.0

        total_items = len(self.required_parts_status)
        checked_items = sum(
            1 for info in self.required_parts_status.values()
            if info["checked"]
        )

        if total_items == 0:
            return 0.0

        return (checked_items / total_items) * 100.0
    
    def get_total_steps(self):
        if self.current_guide_key is None:
            return 0
        return len(GUIDE_CONFIG.get(self.current_guide_key, {}).get("steps", []))

    def get_completed_steps(self):
        if self.current_guide_key is None:
            return 0

        if self.in_precheck_mode:
            return 0

        total_steps = self.get_total_steps()
        return min(self.current_step_index, total_steps)

    def refresh_step_display(self):
        total_steps = self.get_total_steps()
        completed_steps = self.get_completed_steps()
        
        if self.in_precheck_mode:
            self.step_label.setText(f"부품 확인 ({completed_steps}/{total_steps})")
        else:
            self.step_label.setText(f"step{self.current_step_index} ({completed_steps}/{total_steps})")

    def show_precheck_page(self):
        self.show_step_image()

    def show_prev_image(self):
        if self.auto_image_running:
            self.toggle_auto_image()

        current_images = self.get_current_image_list()
        if len(current_images) <= 1:
            return

        self.current_image_index = (self.current_image_index - 1) % len(current_images)
        self.show_step_image()

    def show_next_image(self):
        if self.auto_image_running:
            self.toggle_auto_image()

        current_images = self.get_current_image_list()
        if len(current_images) <= 1:
            return

        self.current_image_index = (self.current_image_index + 1) % len(current_images)
        self.show_step_image()

    def show_step_image(self):
        if self.current_guide_key is None:
            return

        current_images = self.get_current_image_list()

        self.prev_img_btn.setEnabled(len(current_images) > 1)
        self.next_img_btn.setEnabled(len(current_images) > 1)

        if not current_images:
            self.guide_image_label.clear()
            self.guide_image_label.setText("이미지가 없습니다.")
            return

        if self.current_image_index >= len(current_images):
            self.current_image_index = 0

        img_path = current_images[self.current_image_index]

        if img_path.exists():
            pixmap = QPixmap(str(img_path))
            target_w = max(200, self.guide_image_label.width() - 20)
            target_h = max(200, self.guide_image_label.height() - 20)

            scaled = pixmap.scaled(
                target_w,
                target_h,
                Qt.KeepAspectRatio,
                Qt.SmoothTransformation
            )

            self.guide_image_label.setPixmap(scaled)
            self.guide_image_label.setText("")
        else:
            self.guide_image_label.clear()
            self.guide_image_label.setText(f"이미지를 찾을 수 없습니다.\n{img_path}")

    def show_success_message(self, message="성공!\n다음 단계로 넘어갑니다", callback=None):
        if self.success_pending:
            return

        self.success_pending = True
        self.success_overlay.setText(message)
        self.update_success_overlay_geometry()
        self.success_overlay.show()
        self.success_overlay.raise_()

        QTimer.singleShot(
            STEP_SUCCESS_DELAY_MS,
            lambda cb=callback: self.finish_step_transition(cb)
        )

    def finish_step_transition(self, callback=None):
        self.success_overlay.hide()
        self.success_pending = False

        if callable(callback):
            callback()

    def is_auto_home_step(self, step_index):
        if self.current_guide_key is None:
            return False

        step_key = f"step{step_index}"
        step_text = STEP_TASK_MAP.get(self.current_guide_key, {}).get(step_key, "")
        return "홈 화면으로 이동합니다" in step_text

    def enter_auto_home_step(self):
        step_key = f"step{self.current_step_index}"

        self.refresh_step_display()
        self.show_step_image()
        self.set_extra_message("")
        self.task_label.setText(
            STEP_TASK_MAP.get(self.current_guide_key, {}).get(
                step_key,
                "조립이 완성되었습니다. 잠시 후 홈 화면으로 이동합니다."
            )
        )

        self.detected_step_for_jump = None
        self.jump_btn.hide()
        self.match_count = 0
        self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

        self.is_running = False
        self.show_success_message("잠시 후\n홈 화면으로 이동합니다", self.complete_home_success)

    def complete_precheck_success(self):
        self.in_precheck_mode = False
        self.current_step_index = 1
        self.current_image_index = 0
        self.required_parts_consecutive = 0
        self.match_count = 0
        self.extra_message = ""

        self.refresh_step_display()
        self.show_step_image()
        self.conf_title_label.setText("신뢰도")
        self.conf_label.setText("-")
        self.refresh_task_text()

        if self.auto_image_running:
            self.image_timer.start(3000)
            self.toggle_auto_img_btn.setText("자동 넘김 정지")
        else:
            self.image_timer.stop()
            self.toggle_auto_img_btn.setText("자동 넘김 시작")

        self.is_running = True

    def complete_step_success(self):
        self.current_step_index += 1
        self.current_image_index = 0
        self.match_count = 0
        self.refresh_step_display()
        self.detected_step_for_jump = None
        self.jump_btn.hide()
        self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

        if self.is_auto_home_step(self.current_step_index):
            self.enter_auto_home_step()
            return

        total_steps = len(GUIDE_CONFIG[self.current_guide_key]["steps"])
        if self.current_step_index > total_steps:
            self.task_label.setText("모든 단계가 완료되었습니다.")
            self.stop_camera()
            QTimer.singleShot(1200, self.go_home)
            return

        self.show_step_image()
        self.refresh_task_text()
        self.is_running = True
    
    def complete_home_success(self):
        self.stop_camera()
        QTimer.singleShot(3000, self.go_home)

    def resizeEvent(self, event):
        super().resizeEvent(event)
        self.show_step_image()
        self.update_success_overlay_geometry()

    def jump_to_detected_step(self):
        if self.in_precheck_mode:
            return

        if self.detected_step_for_jump is None:
            return

        if not self.detected_step_for_jump.startswith("step"):
            return

        try:
            step_num = int(self.detected_step_for_jump.replace("step", ""))
        except ValueError:
            return

        step_groups = GUIDE_CONFIG[self.current_guide_key]["steps"]
        target_index = step_num

        if 1 <= target_index <= len(step_groups):
            self.current_step_index = target_index
            self.current_image_index = 0
            self.match_count = 0
            self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

            self.show_step_image()
            self.refresh_step_display()
            self.set_extra_message("")
            self.refresh_task_text()

            self.jump_btn.hide()
            self.detected_step_for_jump = None

    def start_guide(self):
        if self.current_guide_key is None:
            self.set_extra_message("먼저 홈 화면에서 가이드를 선택하세요.")
            return

        if self.cap is None or not self.cap.isOpened():
            self.cap = cv2.VideoCapture(CAMERA_INDEX)
            self.cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

        if self.cap is None or not self.cap.isOpened():
            self.set_extra_message("웹캠을 열 수 없습니다.")
            return

        self.is_running = True
        if self.in_precheck_mode:
            self.conf_title_label.setText("진행률")
            self.conf_label.setText("0.0%")
        else:
            self.conf_title_label.setText("신뢰도")
            self.conf_label.setText("-")
        self.match_count = 0
        self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")

        if self.auto_image_running:
            self.image_timer.start(3000)
            self.toggle_auto_img_btn.setText("자동 넘김 정지")
        else:
            self.image_timer.stop()
            self.toggle_auto_img_btn.setText("자동 넘김 시작")

        self.timer.start(80)

    def change_image(self):
        current_images = self.get_current_image_list()
        if len(current_images) <= 1:
            return

        self.current_image_index = (self.current_image_index + 1) % len(current_images)
        self.show_step_image()

    def stop_camera(self):
        self.image_timer.stop()
        self.timer.stop()
        self.auto_image_running = True
        self.toggle_auto_img_btn.setText("자동 넘김 정지")
        self.is_running = False
        self.match_count = 0
        self.success_pending = False
        self.success_overlay.hide()
        self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")
        self.required_parts_consecutive = 0

        if self.in_precheck_mode:
            self.conf_title_label.setText("진행률")
            self.conf_label.setText("0.0%")
        else:
            self.conf_title_label.setText("신뢰도")
            self.conf_label.setText("-")

        if self.cap is not None:
            if self.cap.isOpened():
                self.cap.release()
            self.cap = None

        self.camera_label.setPixmap(QPixmap())
        self.camera_label.setText("Camera Preview")

    def handle_home(self):
        self.stop_camera()
        self.go_home()

    def _predict_step(self, frame):
        if self.model is None:
            return None, 0.0

        results = self.model.predict(
            source=frame,
            imgsz=IMG_SIZE,
            verbose=False
        )

        result = results[0]
        if result.probs is None:
            return None, 0.0

        top1_idx = int(result.probs.top1)
        top1_conf = float(result.probs.top1conf)
        pred_name = result.names[top1_idx]
        return pred_name, top1_conf

    def detect_required_parts(self, frame):
        detected_counts = Counter()
        display_frame = frame.copy()

        if self.parts_det_model is None:
            return detected_counts, display_frame

        try:
            results = self.parts_det_model.predict(
                source=frame,
                imgsz=640,
                conf=PARTS_DET_CONF_THRESHOLD,
                verbose=False
            )
            result = results[0]

            if result is not None and result.boxes is not None and len(result.boxes) > 0:
                for box in result.boxes:
                    cls_id = int(box.cls[0].item())
                    cls_name = result.names[cls_id]
                    conf = float(box.conf[0].item())

                    if conf < PARTS_DET_CONF_THRESHOLD:
                        continue

                    detected_counts[cls_name] += 1


        except Exception as e:
            self.set_extra_message(f"부품 detection 오류: {e}")

        return detected_counts, display_frame

    def check_required_parts_completed(self, detected_counts):
        if self.current_guide_key is None:
            return False

        product_info = PRODUCT_INFO.get(self.current_guide_key, {})
        required_parts = product_info.get("required_parts", {})

        if not self.required_parts_status:
            self.reset_required_parts_status()

        for part_name, required_count in required_parts.items():
            current_count = detected_counts.get(part_name, 0)

            current_count = min(current_count, required_count)

            if current_count > self.required_parts_status[part_name]["detected"]:
                self.required_parts_status[part_name]["detected"] = min(current_count, required_count)

            if self.required_parts_status[part_name]["detected"] >= required_count:
                self.required_parts_status[part_name]["checked"] = True

        all_ok = all(info["checked"] for info in self.required_parts_status.values())
        return all_ok

    def build_precheck_task_text(self):
        product_info = PRODUCT_INFO.get(self.current_guide_key, {})
        precheck_text = product_info.get("precheck_text", "필요한 전체 부품을 화면에 보여주세요.")
        required_parts = product_info.get("required_parts", {})

        lines = [precheck_text, ""]

        for part_name, required_count in required_parts.items():
            detected_count = 0
            checked = False

            if part_name in self.required_parts_status:
                detected_count = self.required_parts_status[part_name]["detected"]
                checked = self.required_parts_status[part_name]["checked"]

            mark = "✅" if checked else "⬜"
            lines.append(f"{mark} {part_name}: {detected_count}/{required_count}")

        return "\n".join(lines)

    def update_frame(self):
        if self.cap is None or not self.cap.isOpened():
            return

        ret, frame = self.cap.read()
        if not ret:
            self.set_extra_message("카메라 프레임을 읽을 수 없습니다.")
            return

        # -------- 부품 확인 단계(detect) --------
        if self.in_precheck_mode:
            detected_counts, display_frame = self.detect_required_parts(frame)

            rgb = cv2.cvtColor(display_frame, cv2.COLOR_BGR2RGB)
            h, w, ch = rgb.shape
            bytes_per_line = ch * w
            qimg = QImage(rgb.data, w, h, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qimg).scaled(
                self.camera_label.width(),
                self.camera_label.height(),
                Qt.KeepAspectRatio,
                Qt.SmoothTransformation
            )
            self.camera_label.setPixmap(pixmap)

            if not self.is_running:
                return

            self.refresh_step_display()

            all_ok = self.check_required_parts_completed(detected_counts)

            self.conf_title_label.setText("진행률")
            self.conf_label.setText(f"{self.get_precheck_progress_percent():.1f}%")

            self.refresh_task_text()

            if all_ok:
                self.required_parts_consecutive += 1
            else:
                self.required_parts_consecutive = 0

            if self.required_parts_consecutive >= self.required_parts_match_target:
                self.is_running = False
                self.show_success_message("성공!\n다음 단계로 넘어갑니다", self.complete_precheck_success)
                return

            return

        # -------- classify 단계 --------
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb.shape
        bytes_per_line = ch * w
        qimg = QImage(rgb.data, w, h, bytes_per_line, QImage.Format_RGB888)
        pixmap = QPixmap.fromImage(qimg).scaled(
            self.camera_label.width(),
            self.camera_label.height(),
            Qt.KeepAspectRatio,
            Qt.SmoothTransformation
        )
        self.camera_label.setPixmap(pixmap)

        if not self.is_running:
            return

        pred_name, conf = self._predict_step(frame)

        if pred_name is None:
            self.step_label.setText("Unknown")
            self.conf_title_label.setText("신뢰도")
            self.conf_label.setText("-")
            self.set_extra_message("classification 예측 결과를 가져오지 못했습니다.")
            return

        self.refresh_step_display()
        self.conf_title_label.setText("신뢰도")

        expected_step = f"step{self.current_step_index}"

        if pred_name == expected_step:
            self.conf_label.setText(f"{conf * 100:.1f}%")
        else:
            self.conf_label.setText("-")

        self.refresh_task_text()

        if pred_name.startswith("step") and conf >= STEP_JUMP_CONF_THRESHOLD:
            try:
                pred_num = int(pred_name.replace("step", ""))

                if pred_num > self.current_step_index:
                    self.detected_step_for_jump = pred_name
                    self.jump_btn.setText(f"{pred_name}로 이동")
                    self.jump_btn.show()
                else:
                    self.detected_step_for_jump = None
                    self.jump_btn.hide()
            except ValueError:
                self.detected_step_for_jump = None
                self.jump_btn.hide()
        else:
            self.detected_step_for_jump = None
            self.jump_btn.hide()

        if pred_name == expected_step and conf >= STEP_AUTO_ADVANCE_CONF_THRESHOLD:
            self.match_count += 1
            self.progress_label.setText(f"{self.match_count} / {REQUIRED_CONSECUTIVE_MATCHES}")
            self.set_extra_message("")

            if self.match_count >= REQUIRED_CONSECUTIVE_MATCHES:
                self.is_running = False
                self.show_success_message("성공!\n다음 단계로 넘어갑니다", self.complete_step_success)
                return

        else:
            self.match_count = max(0, self.match_count - 2)  # 한번 놓쳤을 때 패널티 - REQUIRED_CONSECUTIVE_MATCHES
            self.progress_label.setText(f"0 / {REQUIRED_CONSECUTIVE_MATCHES}")
            self.set_extra_message("")

    def closeEvent(self, event):
        self.stop_camera()
        event.accept()

# 홈 화면
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("부품 조립 가이드")
        self.resize(1450, 900)
        self.setMinimumSize(1450, 900)
        self.setMaximumSize(1450, 900)
        self.setAttribute(Qt.WA_StyledBackground, True)

        self.stack = QStackedWidget()

        self.home_page = HomePage(self.open_guide)
        self.guide_page = GuidePage(self.show_home)

        self.stack.addWidget(self.home_page)
        self.stack.addWidget(self.guide_page)

        layout = QVBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)
        layout.addWidget(self.stack)
        self.setLayout(layout)

        self.apply_styles()
        self.show_home()

    def apply_styles(self):
        self.setStyleSheet("""
            QWidget {
                background: #f5f5f7;
                color: #1d1d1f;
                font-family: "SF Pro Display", "Apple SD Gothic Neo", "Pretendard", "Noto Sans KR", Arial;
                font-size: 14px;
            }

            QLabel {
                background: transparent;
            }

            #title {
                font-size: 40px;
                font-weight: 700;
                color: #111111;
                margin-bottom: 2px;
            }

            #subtitle {
                font-size: 16px;
                color: #6e6e73;
                margin-bottom: 12px;
            }

            #homeCard {
                background: rgba(255, 255, 255, 0.92);
                border: 1px solid #ececf1;
                border-radius: 28px;
            }
            
            #homeCard:hover {
                background: rgba(255, 255, 255, 1.0);
                border: 1px solid #d9dce3;
            }               
            

            #homeCardDesc {
                font-size: 12px;
                color: #6e6e73;
                padding: 0 6px 6px 6px;
            }

            #guideButton {
                background: white;
                border: 1px solid #e5e5ea;
                border-radius: 18px;
                padding: 8px 14px;
                font-size: 17px;
                font-weight: 600;
                min-height: 96px;
                color: #1d1d1f;
                text-align: center;
            }

            #guideButton:hover {
                background: #fbfbfd;
                border: 1px solid #d2d2d7;
            }

            #guideButton:pressed {
                background: #f0f0f2;
            }
     
            #homeCard {
                background: rgba(255, 255, 255, 0.92);
                border: 1px solid #ececf1;
                border-radius: 28px;
            }

            #homeSelectRow {
                background: white;
                border: 1px solid #e5e5ea;
                border-radius: 20px;
            }
            
            #homeSelectRow:hover {
                background: #f7faff;
                border: 1px solid #bcd7ff;
            }

            #homeSelectTitle {
                font-size: 20px;
                font-weight: 600;
                color: #1d1d1f;
                padding-left: 6px;
            }
            #homeSelectRow:pressed {
                background: #eef5ff;
                border: 1px solid #9fc5ff;
            }

            #homeInlineImage {
                background: transparent;
                border: none;
            }

            #homeCardDesc {
                font-size: 12px;
                color: #6e6e73;
                padding: 0 6px 2px 6px;
            }
                                    
            #topButton {
                background: white;
                border: 1px solid #dcdce1;
                border-radius: 14px;
                padding: 12px 20px;
                font-size: 14px;
                font-weight: 600;
                color: #1d1d1f;
                min-width: 120px;
            }

            #topButton:hover {
                background: #fafafa;
            }

            #topButton:pressed {
                background: #ededf0;
            }

            #primaryButton {
                background: #0071e3;
                border: none;
                border-radius: 14px;
                padding: 12px 20px;
                font-size: 14px;
                font-weight: 600;
                color: white;
                min-width: 160px;
            }

            #primaryButton:hover {
                background: #0077ed;
            }

            #primaryButton:pressed {
                background: #0068d1;
            }

            #pageTitle {
                font-size: 28px;
                font-weight: 700;
                color: #111111;
                padding: 4px 0;
            }

            #panel {
                background: rgba(255, 255, 255, 0.94);
                border: 1px solid #ececf1;
                border-radius: 28px;
                padding: 12px;
            }

            #sectionTitle {
                font-size: 18px;
                font-weight: 700;
                color: #111111;
                padding: 2px 2px 6px 2px;
            }

            #guideImageLabel {
                background: #fbfbfd;
                border: 1px solid #e5e5ea;
                border-radius: 22px;
                font-size: 24px;
                color: #8e8e93;
            }

            #cameraLabel {
                background: #f2f2f7;
                border: 1px solid #e5e5ea;
                border-radius: 18px;
                font-size: 16px;
                color: #8e8e93;
            }

            #cardTitle {
                font-size: 15px;
                font-weight: 700;
                color: #8e8e93;
            }

            #miniInfoFrame {
                background: #f8f8fb;
                border: 1px solid #ececf1;
                border-radius: 18px;
            }

            #miniCardTitle {
                font-size: 11px;
                font-weight: 700;
                color: #8e8e93;
                margin-top: 2px;
            }

            #miniValue {
                font-size: 16px;
                font-weight: 600;
                color: #1d1d1f;
                margin-bottom: 4px;
            }

            #miniStatusValue {
                font-size: 14px;
                font-weight: 500;
                color: #4b5563;
            }

            #taskScrollArea {
                background: transparent;
                border: none;
            }

            #taskScrollArea > QWidget > QWidget {
                background: transparent;
            }
            #taskFrame {
                background: #ffffff;
                border: 1px solid #e5e5ea;
                border-radius: 22px;
            }

            #taskValue {
                font-size: 22px;
                font-weight: 600;
                color: #111111;
                line-height: 1.12;
            }
        """)

    def show_home(self):
        self.guide_page.stop_camera()
        self.stack.setCurrentWidget(self.home_page)
        QTimer.singleShot(500, self.home_page.start_auto_detect)

    def open_guide(self, guide_key):
        self.home_page.stop_auto_detect()
        self.guide_page.set_guide(guide_key)
        self.stack.setCurrentWidget(self.guide_page)
        QTimer.singleShot(500, self.guide_page.start_guide)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setFont(QFont("Arial", 10))

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())