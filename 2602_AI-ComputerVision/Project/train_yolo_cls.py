from pathlib import Path
import torch
from ultralytics import YOLO

# =========================
# 기본 경로 설정
# =========================
BASE_DIR = Path(__file__).resolve().parent
DATASET_DIR = BASE_DIR / "dataset_ready"
PROJECT_DIR = BASE_DIR / "runs_classify"

# =========================
# 설정
# =========================
MODEL_NAME = "yolo11n-cls.pt"
EPOCHS = 50
IMGSZ = 224
BATCH = 64
RUN_NAME = "football_steps" # 폴더 이름 설정

ALLOWED_EXTS = {".jpg", ".jpeg", ".png", ".bmp"}


def check_dataset_structure(dataset_dir: Path):
    train_path = dataset_dir / "train"
    val_path = dataset_dir / "val"

    if not train_path.exists():
        raise FileNotFoundError(f"train 폴더가 없습니다: {train_path.resolve()}")
    if not val_path.exists():
        raise FileNotFoundError(f"val 폴더가 없습니다: {val_path.resolve()}")

    train_classes = sorted([p.name for p in train_path.iterdir() if p.is_dir()])
    val_classes = sorted([p.name for p in val_path.iterdir() if p.is_dir()])

    if not train_classes:
        raise ValueError("train 폴더 안에 클래스 폴더가 없습니다.")
    if not val_classes:
        raise ValueError("val 폴더 안에 클래스 폴더가 없습니다.")
    if train_classes != val_classes:
        raise ValueError(
            f"train/val 클래스명이 다릅니다.\n"
            f"train: {train_classes}\n"
            f"val: {val_classes}"
        )

    for split_name, split_path in [("train", train_path), ("val", val_path)]:
        for class_dir in sorted([p for p in split_path.iterdir() if p.is_dir()]):
            images = [
                f for f in class_dir.iterdir()
                if f.is_file() and f.suffix.lower() in ALLOWED_EXTS
            ]
            if len(images) == 0:
                raise ValueError(f"{split_name}/{class_dir.name} 폴더에 이미지가 없습니다.")
            print(f"{split_name}/{class_dir.name}: {len(images)}장")

    print("데이터셋 확인 완료")


def main():
    check_dataset_structure(DATASET_DIR)

    device = 0 if torch.cuda.is_available() else "cpu"

    print("\n학습 시작")
    print(f"BASE_DIR   : {BASE_DIR.resolve()}")
    print(f"DATASET_DIR: {DATASET_DIR.resolve()}")
    print(f"PROJECT_DIR: {PROJECT_DIR.resolve()}")
    print(f"device     : {device}")

    model = YOLO(MODEL_NAME)

    model.train(
        data=str(DATASET_DIR),
        epochs=EPOCHS,
        imgsz=IMGSZ,
        batch=BATCH,
        device=device,
        project=str(PROJECT_DIR),
        name=RUN_NAME,
        pretrained=True,
        verbose=True
    )

    best_path = PROJECT_DIR / RUN_NAME / "weights" / "best.pt"
    print("\n학습 완료")
    print(f"best model: {best_path.resolve()}")


if __name__ == "__main__":
    main()