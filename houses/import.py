import csv
import sqlite3
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python import.py file.csv")
        exit()
    conn = sqlite3.connect("students.db")
    with open(sys.argv[1], "r") as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            name = row["name"].split()
            middle = None if len(name) == 2 else name[1]
            birth = int(row["birth"])
            com = ("INSERT INTO students (first, middle, last, house, birth) "
                   "VALUES(?, ?, ?, ?, ?)")
            values = (name[0], middle, name[-1], row["house"], birth)
            conn.cursor().execute(com, values)
    conn.commit()
    conn.close()

main()
