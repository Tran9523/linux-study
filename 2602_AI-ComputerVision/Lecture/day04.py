from flask import Flask, render_template, request
# 전체를 불러오면 너무 무거워짐
# render_template: flask server가 run되는 "위치"와 동일한
# 위치에 있는 "templates" 폴더 내 html 문서를 load
# request: 요청 관련 처리 라이브러리
app = Flask(__name__)
@app.route("/")
def index():
    return render_template("index.html")
# 여기에 코드를 담게 되면 접속하는 순간 모두 다 실행이 됨
@app.route("/cal", methods=["GET"]) # get 방식으로 명령이란 명시
def cal():
    # get방식으로 data가 넘어온다
    # key값은 num1, num2다
    if request.method == "GET":
        # args -> GET방식
        # form -> POST방식
        # file -> POST(FILE) 방식
        num1 = request.args["num1"]
        num2 = request.args["num2"]
        result = int(num1) + int(num2)
    return f"{num1} + {num2} = {result}"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)