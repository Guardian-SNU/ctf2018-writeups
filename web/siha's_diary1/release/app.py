import os
from pathlib import Path
from flask import Flask
from flask import request
from flask import render_template, send_from_directory, redirect
app = Flask(__name__)
root_path = Path(app.root_path)
FLAG = "GuardianCTF{y0u_5h0uld_f1l73r_u53r_1npu7}"


@app.route('/')
def index():
    return render_template('list.html')


@app.route('/diary', methods=['GET'])
def diary():
    path = request.args.get('path', None)
    if not path:
        return redirect('/')

    diary_path = root_path / 'diaries' / path
    if not diary_path.is_file():
        return redirect('/')

    diary_data = diary_path.read_text(encoding='utf=8')
    return render_template('diary.html', text=diary_data.split('\n'))


@app.route('/favicon.ico')
def favicon():
    return send_from_directory(str(root_path / 'static/images'),
                               'favicon.ico', mimetype='image/vnd.microsoft.icon')


if __name__ == '__main__':
    app.run()
