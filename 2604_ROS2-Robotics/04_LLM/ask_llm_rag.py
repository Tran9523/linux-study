import os
import requests
import chromadb
from chromadb.utils import embedding_functions
from langchain_text_splitters import RecursiveCharacterTextSplitter

# ==========================================
# [설정] 모델 및 파일 경로 설정
# ==========================================
MODEL_NAME = "hf.co/rippertnt/HyperCLOVAX-SEED-Text-Instruct-1.5B-Q4_K_M-GGUF:Q4_K_M"
EMBED_MODEL = "mxbai-embed-large"
MD_FILE_PATH = "pinky_library.md"
DB_PATH = "./pinky_rag_db"

# ==========================================
# 1) ChromaDB 및 임베딩 초기화
# ==========================================
# 로컬 디스크에 데이터를 영구 저장하는 ChromaDB 클라이언트 생성
chroma = chromadb.PersistentClient(path=DB_PATH)

# Ollama의 임베딩 API를 사용하기 위한 설정
# (텍스트 -> 숫자 벡터 변환 담당)

embed_fn = embedding_functions.OllamaEmbeddingFunction(
    model_name=EMBED_MODEL,
    url="http://localhost:11434/api/embeddings"
)
# 컬렉션 가져오기 또는 생성 (기존 DB 유지)
collection = chroma.get_or_create_collection(
    name="pinky_docs",
    embedding_function=embed_fn
)

# ==========================================
# 2) 문서 로딩 및 청킹 (DB가 비어있을 때만)
# ==========================================
# 컬렉션에 데이터가 없으면 문서를 로딩하고 저장합니다.
if collection.count() == 0:
    if os.path.exists(MD_FILE_PATH):
        print("문서 로딩 및 청킹 중...")
        # 마크다운 파일 읽기
        with open(MD_FILE_PATH, "r", encoding="utf-8") as f:
            docs = f.read()
        # 문서를 작은 조각(Chunk)으로 자르기 위한 객체 생성
        # chunk_size: 한 조각당 약 500자
        # chunk_overlap: 문맥이 끊기지 않도록 앞뒤 내용을 50자씩 겹치게 함
        splitter = RecursiveCharacterTextSplitter(
            chunk_size=500,
            chunk_overlap=50
        )

        # 텍스트 분할 수행
        chunks = splitter.split_text(docs)
        # ==========================================
        # 3) 벡터 에 데이터 삽입
        # ==========================================
        print(f"{len(chunks)}개 청크 DB 저장 중...")
        for i, chunk in enumerate(chunks):
            # ChromaDB에 데이터 추가 (텍스트는 자동으로 임베딩됨)
            collection.add(
                ids=[f"id_{i}"],    # 각 문서 조각의 고유 ID
                documents=[chunk]   # 실제 텍스트 내용
            )
        print("문서 저장 완료!")
    else:
        print("경고: MD 파일이 없습니다.")
else:
    print("기존 DB를 로드했습니다.")
# ==========================================
# 4) 검색 및 호출 함수 정의
# ==========================================
def search(query, top_k=3):
    """
    사용자 질문(Query)과 가장 유사한 문서 조각을 검색합니다.
    top_k: 검색할 문서 개수 (기본 3개)
    """ 
    result = collection.query(
        query_texts=[query],
        n_results=top_k
    )
    # 검색 결과가 있으면 문서 리스트 반환
    if result["documents"]:
        return result["documents"][0]
    return []



def ask_ollama(model, prompt):
    resp = requests.post(
        "http://localhost:11434/api/chat",
        json={"model": model, "messages": [{"role": "user", "content": prompt}], "stream": False}
    )
    return resp.json()["message"]["content"]


# ==========================================
# 5) 메인 챗봇 루프 (Chat Loop)
# ==========================================
def chat():
    print(f"Model: {MODEL_NAME}")
    print("종료하려면 'exit' 입력")
    while True:
        # 사용자 입력 받기
        user_input = input("\n질문: ").strip()
        
        # 종료 조건 처리
        if user_input.lower() in ["exit", "quit"]:
            print("종료합니다.")
            break
        if not user_input: continue
        # 1. 문서 검색 (Retrieval)
        retrieved_docs = search(user_input, top_k=3)
        # 검색된 문서 조각들을 하나의 문자열로 합침
        context = "\n\n".join(retrieved_docs)

        # 2. 프롬프트 구성 (Augmentation)
        # 검색된 컨텍스트(Context)를 질문과 함께 모델에게 전달
        final_prompt = f"""
다음 문서를 참고해서 질문에 답해줘.

[Context]
{context}

[Question]
{user_input}
"""
        # 3. 답변 생성 (Generation)
        print("답변 생성 중...")
        answer = ask_ollama(MODEL_NAME, final_prompt)
        print(f"답변: {answer}")

if __name__ == "__main__":
    chat()