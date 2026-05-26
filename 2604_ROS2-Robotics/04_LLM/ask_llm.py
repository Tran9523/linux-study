import requests

MODEL_NAME = "hf.co/rippertnt/HyperCLOVAX-SEED-Text-Instruct-1.5B-Q4_K_M-GGUF:Q4_K_M"
def ask_ollama(model, prompt):
    resp = requests.post(
        "http://localhost:11434/api/chat",
        json={"model": model, "messages": [{"role": "user", "content": prompt}], "stream": False}
    )
    return resp.json()["message"]["content"]

def chat():
    print(f"Model: {MODEL_NAME}")
    print("exit or quit to end")
    while True:
        user_input = input("\nQuestion: ").strip()
        if user_input.lower() in ["exit", "quit"]:
            break
        if not user_input:
            continue
        answer = ask_ollama(MODEL_NAME, user_input)
        print(f"Answer: {answer}")

if __name__ == "__main__":
    chat()