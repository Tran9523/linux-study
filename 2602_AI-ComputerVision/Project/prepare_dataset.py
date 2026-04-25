from pathlib import Path
import random
from PIL import Image, ImageEnhance

# =========================
# 기본 경로 설정
# =========================
BASE_DIR = Path(__file__).resolve().parent
SOURCE_DIR = BASE_DIR / "source"
OUTPUT_DIR = BASE_DIR / "dataset_ready"

TRAIN_DIR = OUTPUT_DIR / "train"
VAL_DIR = OUTPUT_DIR / "val"

# =========================
# 설정
# =========================
VAL_RATIO = 0.3          # 기존 0.2 -> 0.3
MIN_VAL_COUNT = 4        # 클래스당 최소 val 개수 보장
RANDOM_SEED = 42
IMG_SIZE = (224, 224)
AUG_PER_IMAGE = 2        # 기존 6 -> 2
ALLOWED_EXTS = {".jpg", ".jpeg", ".png", ".bmp"}

random.seed(RANDOM_SEED)


def clear_output_dirs():
    """dataset_ready 내부 파일 정리"""
    if OUTPUT_DIR.exists():
        for p in OUTPUT_DIR.rglob("*"):
            if p.is_file():
                p.unlink()

    TRAIN_DIR.mkdir(parents=True, exist_ok=True)
    VAL_DIR.mkdir(parents=True, exist_ok=True)


def get_class_dirs():
    """source 폴더 아래 클래스 폴더 목록"""
    if not SOURCE_DIR.exists():
        raise FileNotFoundError(f"source 폴더가 없습니다: {SOURCE_DIR.resolve()}")

    class_dirs = [p for p in SOURCE_DIR.iterdir() if p.is_dir()]
    if not class_dirs:
        raise ValueError("source 폴더 안에 클래스 폴더가 없습니다.")

    return sorted(class_dirs)


def list_images(class_dir: Path):
    return sorted([
        p for p in class_dir.iterdir()
        if p.is_file() and p.suffix.lower() in ALLOWED_EXTS
    ])


def safe_open_image(path: Path):
    try:
        return Image.open(path).convert("RGB")
    except Exception as e:
        print(f"[열기 실패] {path.name}: {e}")
        return None


def fit_to_canvas(img: Image.Image, canvas_size=(224, 224), bg_color=(255, 255, 255)):
    """
    비율을 유지한 채 이미지를 canvas 중앙에 배치
    - 큰 이미지는 축소
    - 작은 이미지는 확대하지 않음
    """
    canvas = Image.new("RGB", canvas_size, bg_color)
    img = img.copy()
    img.thumbnail(canvas_size, Image.Resampling.LANCZOS)

    x = (canvas_size[0] - img.width) // 2
    y = (canvas_size[1] - img.height) // 2
    canvas.paste(img, (x, y))
    return canvas


def augment_image(img: Image.Image):
    """과적합 완화를 위한 약한 증강"""
    img = img.copy()

    # 회전 범위 축소 (기존보다 약하게)
    angle_choices = [-10, -5, 0, 5, 10]
    angle = random.choice(angle_choices)
    img = img.rotate(
        angle,
        resample=Image.Resampling.BICUBIC,
        expand=True,
        fillcolor=(255, 255, 255)
    )

    # 크기 변화 범위도 약하게
    scale = random.uniform(0.95, 1.05)
    new_w = max(10, int(img.width * scale))
    new_h = max(10, int(img.height * scale))
    img = img.resize((new_w, new_h), Image.Resampling.LANCZOS)

    # 밝기 변화 약하게
    brightness = random.uniform(0.9, 1.1)
    img = ImageEnhance.Brightness(img).enhance(brightness)

    # 대비 변화 약하게
    contrast = random.uniform(0.9, 1.1)
    img = ImageEnhance.Contrast(img).enhance(contrast)

    # 최종 캔버스 정렬
    img = fit_to_canvas(img, IMG_SIZE)
    return img


def main():
    clear_output_dirs()

    class_dirs = get_class_dirs()
    print("클래스 목록:", [p.name for p in class_dirs])

    for class_dir in class_dirs:
        class_name = class_dir.name
        images = list_images(class_dir)

        if len(images) == 0:
            print(f"[건너뜀] {class_name}: 이미지 없음")
            continue

        train_class_dir = TRAIN_DIR / class_name
        val_class_dir = VAL_DIR / class_name
        train_class_dir.mkdir(parents=True, exist_ok=True)
        val_class_dir.mkdir(parents=True, exist_ok=True)

        random.shuffle(images)

        # val 개수 계산: 비율 + 최소 개수 보장
        if len(images) >= 2:
            val_count = max(MIN_VAL_COUNT, int(len(images) * VAL_RATIO))
            val_count = min(val_count, len(images) - 1)  # train이 최소 1장 남게
        else:
            val_count = 0

        val_images = set(images[:val_count])

        train_saved = 0
        val_saved = 0

        for img_path in images:
            img = safe_open_image(img_path)
            if img is None:
                continue

            base_img = fit_to_canvas(img, IMG_SIZE)

            if img_path in val_images:
                target_dir = val_class_dir
                save_name = f"{img_path.stem}_orig.png"
                base_img.save(target_dir / save_name)
                val_saved += 1
            else:
                target_dir = train_class_dir
                save_name = f"{img_path.stem}_orig.png"
                base_img.save(target_dir / save_name)
                train_saved += 1

                # train에만 증강 적용
                for i in range(AUG_PER_IMAGE):
                    aug_img = augment_image(img)
                    aug_name = f"{img_path.stem}_aug_{i:02d}.png"
                    aug_img.save(target_dir / aug_name)
                    train_saved += 1

        print(f"{class_name}: train {train_saved}장 / val {val_saved}장")

    print("\n데이터셋 준비 완료")
    print(f"source      : {SOURCE_DIR.resolve()}")
    print(f"train output: {TRAIN_DIR.resolve()}")
    print(f"val output  : {VAL_DIR.resolve()}")


if __name__ == "__main__":
    main()