#!/usr/bin/python3
from flask import Flask, request, Response

from db import *
import sqlite3

app = Flask(__name__)

init()

@app.route("/ws/weather") # /ws/weather?pressure=~eq~20
def list_wheater():
    conn = sqlite3.connect(DB_NAME)
    database = DB(conn)
    d = database.select_many(request.args)
    return d

@app.route("/ws/weather", methods=["POST"])
def create_wheater():
    content_type = request.headers.get("Content-Type")
    if (content_type == 'application/json'):
        req = Weather(**request.json)
        conn = sqlite3.connect(DB_NAME)
        database = DB(conn)
        print(req)
        d = database.create(req)
        return Response(
            json.dumps(d.__dict__), status=201, mimetype="application/json")
    
    return ""
