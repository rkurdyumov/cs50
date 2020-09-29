import csv
import sqlite3
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python roster.py house")
        exit()
    conn = sqlite3.connect("students.db")
    conn.row_factory = sqlite3.Row
    command = "SELECT * FROM students WHERE house = ? ORDER BY last,first;"
    values = (sys.argv[1], )
    rows = conn.cursor().execute(command, values).fetchall()
    for row in rows:
        row = dict(zip(row.keys(), row))
        name = [x for x in [row["first"], row["middle"], row["last"]] if x]
        print(" ".join(name) + ", born " + str(row["birth"]))
    conn.close()

main()

