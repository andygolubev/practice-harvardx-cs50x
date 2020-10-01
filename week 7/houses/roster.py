import sys
import sqlite3


def main():

    # Chech program parameters
    if len(sys.argv) != 2:
        print('Usage: python roster.py [House name]')
        sys.exit(1)

    # Open DB and select data
    studentsConnection = sqlite3.connect("students.db")
    studentsCursor = studentsConnection.cursor()

    # make secure input https://docs.python.org/3/library/sqlite3.html
    t = (sys.argv[1],)

    # print the result
    for row in studentsCursor.execute("SELECT first, middle, last, birth FROM students WHERE house=? ORDER BY last, first;", t):
        print(row[0], ' ', '' if row[1] == None else row[1] + ' ', row[2], ', born ', row[3], sep='')

    studentsConnection.close()


main()
