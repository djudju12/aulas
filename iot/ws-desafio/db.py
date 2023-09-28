#!/usr/bin/python3
import sqlite3
import json
import os
from dataclasses import dataclass 
from datetime import date, datetime

DB_NAME = "wheater.db"
PATH_DATA = "data.json"

INSERT_STMT = """
INSERT INTO weather 
VALUES
(:temperature, :humidity, :dewpoint, :pressure, :speed, :direction, :datetime)
"""

CREATE_TABLE_STMT = """
CREATE TABLE IF NOT EXISTS weather(
    temperature REAL NOT NULL, 
    humidity REAL NOT NULL, 
    dewpoint REAL NOT NULL, 
    pressure REAL NOT NULL, 
    speed REAL NOT NULL, 
    direction REAL NOT NULL, 
    datetime TEXT NOT NULL
);
"""

SELECT_ALL_STMT = "SELECT * FROM weather"

@dataclass
class Weather:
    temperature: float = 0
    humidty:     float = 0
    dewpoint:    float = 0
    pressure:    float = 0
    speed:       float = 0
    direction:   str   = ""
    datetime:    date  | None = None


class DB:
    conn: sqlite3.Connection 
    cur: sqlite3.Cursor

    def __init__(self, conn: sqlite3.Connection):
        self.conn = conn
        self.cur = conn.cursor()

    def insert_many(self, data: dict):
        try:
            print(INSERT_STMT)
            self.cur.executemany(INSERT_STMT, data["weather"])
        except sqlite3.OperationalError as e:
            print(f"ERROR: cannot execute sql: {INSERT_STMT}\nerr: {e}")
            raise e

    @staticmethod
    def _filter_from_args(args: dict[str, str]) -> str:
        result = " WHERE 1 = 1 "
        for k, v in args.items():
            result += " AND "
            if v.startswith("~eq~"):
                result+= f"{k} = {v[4:]}"
            elif v.startswith("~lt~"):
                result+= f"{k} < {v[4:]}"
            elif v.startswith("~gt~"):
                result+= f"{k} > {v[4:]}"
            else:
                result+= f"{k} LIKE {v}"
        
        return result

    def select_many(self, args: dict[str, str]) -> dict:
        filters = self._filter_from_args(args)
        stmt = SELECT_ALL_STMT + filters
        print(stmt)
        c = self.cur.execute(stmt)
        return {"weather": [Weather(*entry) for entry in c.fetchall()]}
    
    def select_one(self, args: dict[str, str]) -> Weather:
        filters = self._filter_from_args(args)
        stmt = SELECT_ALL_STMT + filters
        print(stmt)
        c = self.cur.execute(stmt)
        return Weather(*c.fetchone())
    
    def create(self, weather: Weather):
        c = self.cur.execute(INSERT_STMT, [Weather.temperature, 
                                           weather.humidty, 
                                           weather.dewpoint, 
                                           weather.pressure, 
                                           weather.speed, 
                                           weather.direction, 
                                           weather.datetime])
        self.conn.commit()
        return self.select_one(args={"rowid":f"~eq~{self.cur.lastrowid}"})

    def populate(self, data: dict):
        print(CREATE_TABLE_STMT)
        self.cur.execute(CREATE_TABLE_STMT)
        self.insert_many(data)
        self.conn.commit()



def init():
    if os.path.exists(DB_NAME):
        os.remove(DB_NAME)

    conn = sqlite3.connect(DB_NAME)
    db = DB(conn)
    data = read_data(PATH_DATA)
    db.populate(data)
    
        
def read_data(path: str) -> dict:
    data = {}
    try:
        with open(path, "r") as f:
            data = json.load(f)
    except OSError as e:
        print(f"ERROR: cannot read data file: {path}. {e.errno}: {e.strerror}")
    finally:
        return data 
