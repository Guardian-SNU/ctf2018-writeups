import os
from pathlib import Path
from flask import Flask
from flask import request
from flask import render_template, send_from_directory, redirect, render_template_string
app = Flask(__name__)
root_path = Path(app.root_path)

diaries = [
    ('세번째 일기장', '2018/10/20', 'mythirdwebsite.txt'),
    ('좋아하는 시', '2018/10/23', 'poem.txt'),
    ('좋아하는 시2', '2018/10/24', 'poem2.txt'),
    ('좋은 구절', '2018/10/24', 'phrase1.txt'),
    ('멋진 구절', '2018/10/25', 'phrase2.txt'),
]


@app.route('/')
def index():
    return render_template('search.html', all_diaries=diaries)


@app.route('/search')
def search():
    title = request.args.get('title', None)
    if not title:
        return redirect('/')

    if 'flag' in title.lower():
        return "GO AWAY HACKER!"

    results = []
    for t in diaries:
        if title in t[0]:
            results.append(t)

    template = (root_path / 'templates' / 'search_result.html').read_text(encoding='utf-8')
    return render_template_string(template % title, results=results)


@app.route('/diary', methods=['GET'])
def diary():
    path = request.args.get('path', None)
    if not path:
        return redirect('/')

    if '/' in path or '\\' in path or '..' in path:
        return "NO HACK!!!   " * 100

    if 'flag' in path.lower():
        return "GO AWAY HACKER!"

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
