from pathlib import Path
import random
import shutil
import torch
from ultralytics import YOLO

# =========================
# 기본 경로 설정
# =========================
BASE_DIR = Path(__file__).resolve().parent
DATASET_DIR = BASE_DIR / "dataset_detect_parts"

IMAGES_ALL_DIR = DATASET_DIR / "images_all"
LABELS_ALL_DIR = DATASET_DIR / "labels_all"

# 자동 생성될 YOLO용 분할 데이터셋
PREPARED_DIR = DATASET_DIR / "_prepared"
DATA_YAML = PREPARED_DIR / "data.yaml"

PROJECT_DIR = BASE_DIR / "runs_detect"

# =========================
# 설정
# =========================
MODEL_NAME = "yolo11n.pt" # 학습 데이터 활용하려면 이 부분 수정
# MODEL_NAME = str(BASE_DIR / "runs_detect" / "all_detect" / "weights" / "best.pt")
EPOCHS = 50
IMGSZ = 640
BATCH = 64
RUN_NAME = "all_detect"

VAL_RATIO = 0.2
RANDOM_SEED = 42
REBUILD_SPLIT = True  # True면 매번 train/val 다시 생성

ALLOWED_EXTS = {".jpg", ".jpeg", ".png", ".bmp"}

def collect_images(images_dir: Path):
    if not images_dir.exists():
        raise FileNotFoundError(f"이미지 폴더가 없습니다: {images_dir.resolve()}")

    image_list = sorted(
        [p for p in images_dir.iterdir() if p.is_file() and p.suffix.lower() in ALLOWED_EXTS]
    )

    if not image_list:
        raise ValueError(f"이미지 폴더에 이미지가 없습니다: {images_dir.resolve()}")

    return image_list


def check_all_in_one_dataset(images_dir: Path, labels_dir: Path):
    if not labels_dir.exists():
        raise FileNotFoundError(f"라벨 폴더가 없습니다: {labels_dir.resolve()}")

    image_list = collect_images(images_dir)

    missing_labels = []
    for img_path in image_list:
        label_path = labels_dir / f"{img_path.stem}.txt"
        if not label_path.exists():
            missing_labels.append(label_path.name)

    if missing_labels:
        preview = "\n".join(missing_labels[:10])
        raise FileNotFoundError(
            f"라벨 없는 이미지가 있습니다. 예시:\n{preview}\n"
            f"(총 {len(missing_labels)}개 누락)"
        )

    print(f"전체 이미지 수: {len(image_list)}장")
    print("all-in-one 데이터셋 확인 완료")
    return image_list


def make_prepared_dirs(prepared_dir: Path):
    if prepared_dir.exists():
        shutil.rmtree(prepared_dir)

    for p in [
        prepared_dir / "images" / "train",
        prepared_dir / "images" / "val",
        prepared_dir / "labels" / "train",
        prepared_dir / "labels" / "val",
    ]:
        p.mkdir(parents=True, exist_ok=True)


def split_dataset(image_list, val_ratio=0.2, seed=42):
    image_list = image_list[:]
    random.seed(seed)
    random.shuffle(image_list)

    val_count = max(1, int(len(image_list) * val_ratio))
    train_count = len(image_list) - val_count

    if train_count < 1:
        raise ValueError("train 데이터가 1장도 안 남습니다. 데이터 수를 늘리거나 val_ratio를 줄이세요.")

    train_images = image_list[:train_count]
    val_images = image_list[train_count:]

    return train_images, val_images


def copy_split_files(train_images, val_images, labels_dir: Path, prepared_dir: Path):
    split_info = [
        ("train", train_images),
        ("val", val_images),
    ]

    for split_name, image_list in split_info:
        img_dst_dir = prepared_dir / "images" / split_name
        lbl_dst_dir = prepared_dir / "labels" / split_name

        for img_path in image_list:
            label_path = labels_dir / f"{img_path.stem}.txt"

            shutil.copy2(img_path, img_dst_dir / img_path.name)
            shutil.copy2(label_path, lbl_dst_dir / label_path.name)

# yaml 잘 확인하기
def write_data_yaml(yaml_path: Path, prepared_dir: Path):
    yaml_text = f"""path: {prepared_dir.as_posix()}
train: images/train
val: images/val

names:
  0: base_case
  1: fan_case
  2: board
  3: upper_casecar
  4: height_plate
  5: spring_plate
  6: base_plate
  7: field1
  8: field2
  9: field3
  10: field4
  11: goal_net_back
  12: goal_net_side
  13: goalside 1
  14: goalside 2
  15: lateral1
  16: lateral2
  17: player2_rod
  18: player3_rod
  19: rod_cover
  20: knobb
"""
    yaml_path.write_text(yaml_text, encoding="utf-8")


def prepare_dataset():
    image_list = check_all_in_one_dataset(IMAGES_ALL_DIR, LABELS_ALL_DIR)

    if REBUILD_SPLIT or not PREPARED_DIR.exists():
        make_prepared_dirs(PREPARED_DIR)

        train_images, val_images = split_dataset(
            image_list,
            val_ratio=VAL_RATIO,
            seed=RANDOM_SEED
        )

        copy_split_files(train_images, val_images, LABELS_ALL_DIR, PREPARED_DIR)
        write_data_yaml(DATA_YAML, PREPARED_DIR)

        print(f"train images: {len(train_images)}장")
        print(f"val images  : {len(val_images)}장")
        print("자동 train/val 분할 완료")
    else:
        print("기존 분할 데이터셋 사용")

    if not DATA_YAML.exists():
        raise FileNotFoundError(f"data.yaml 파일이 없습니다: {DATA_YAML.resolve()}")


def main():
    prepare_dataset()

    device = 0 if torch.cuda.is_available() else "cpu"

    print("\n학습 시작")
    print(f"BASE_DIR    : {BASE_DIR.resolve()}")
    print(f"DATA_YAML   : {DATA_YAML.resolve()}")
    print(f"PROJECT_DIR : {PROJECT_DIR.resolve()}")
    print(f"device      : {device}")

    model = YOLO(MODEL_NAME)

    model.train(
        data=str(DATA_YAML),
        epochs=EPOCHS,
        imgsz=IMGSZ,
        batch=BATCH,
        device=device,
        project=str(PROJECT_DIR),
        name=RUN_NAME,
        pretrained=True,
        verbose=True,
        patience=10,
        plots=True
    )

    best_path = PROJECT_DIR / RUN_NAME / "weights" / "best.pt"
    print("\n학습 완료")
    print(f"best model: {best_path.resolve()}")


if __name__ == "__main__":
    main()