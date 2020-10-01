import sys
import logging
import csv
import re
import sqlite3


def main():

    # Setup logging level
    logging.basicConfig(level=logging.INFO)

    # Chech program parameters
    if len(sys.argv) != 2:
        print('Usage: python import.py characters.csv')
    # Check for csv file as a parameter
    elif (not bool(re.search(".csv$", str(sys.argv[1])))):
        print(f"Problem: Use csv file instead of {sys.argv[1]}")

    # Open the csv file
    try:
        with open(sys.argv[1], newline='') as csvfile:
            peopleDictReader = csv.DictReader(csvfile, delimiter=',')
            logging.debug(f"Fieldnames of file {sys.argv[1]}: {peopleDictReader.fieldnames}")

            # Chech for correct fieldnames
            if (not(peopleDictReader.fieldnames[0] == 'name' and
                    peopleDictReader.fieldnames[1] == 'house' and
                    peopleDictReader.fieldnames[2] == 'birth')):
                print(f"Problem: Incorrect structure in csvfile {sys.argv[1]}. Must be: 'name', 'house', 'birth'")
                sys.exit(1)

            # Fill the list with peolpe
            people = list()
            for row in peopleDictReader:
                fullName = str(row['name']).split(' ')
                logging.debug(f"---FILL---> FullName: {fullName}")
                newPeople = {'firstName': fullName[0], 'middleName': None,
                            'lastName': None, 'house': row['house'], 'birth': row['birth']}
                if len(fullName) == 3:
                    newPeople['middleName'] = fullName[1]
                    newPeople['lastName'] = fullName[2]
                else:
                    newPeople['lastName'] = fullName[1]
                logging.debug(f"---FILL---> newPeople: {newPeople}")
                people.append(newPeople)

    except EnvironmentError:
        print(f"Problem: Can`t process file {sys.argv[1]}")

    # Open DB and insert values
    studentsConnection = sqlite3.connect("students.db")
    studentsCursor = studentsConnection.cursor()

    for row in people:
        studentsCursor.execute("INSERT into STUDENTS (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);",
                                (row['firstName'],
                                row['middleName'],
                                row['lastName'],
                                row['house'],
                                row['birth']))

    studentsConnection.commit()
    studentsConnection.close()


main()
