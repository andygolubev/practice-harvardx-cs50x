import sys
import csv
import logging


def main():

    # Config logging. All messages have logged by DEBUG level
    logging.basicConfig(level=logging.INFO)

    #
    # Check programm input
    #
    if len(sys.argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')

    #
    # Open file and fill dictionary
    #
    people = list()
    with open(sys.argv[1], newline='') as csvfile:
        peopleDictReader = csv.DictReader(csvfile, delimiter=',')
        columnNames = peopleDictReader.fieldnames
        logging.debug(f"Column names -> {columnNames}")
        for row in peopleDictReader:
            people.append(row)

    #
    # Open file with sequence
    #
    dnalist = open(sys.argv[2]).readlines()
    tmp = dnalist[0]  # only one line sequence

    logging.debug(f"Sequence -> {tmp}")  # will print a message to the console

    #
    # FIND pattens in sequence
    #
    result = dict()
    for name in columnNames[1:]:
        positions_list = list()  # make an empty list for the pattern positions in the sequence
        current_search_position = 0  # start position
        res_temp = 0  # temp counter for current non-interupted sequence
        while True:
            # find position of the NAME pattern in the sequence from the N position
            current_search_position = tmp.find(name, current_search_position)
            logging.debug("NAME -> {name}: current_search_position:{current_search_position}")
            if current_search_position < 0:  # if return -1 then exit loop for NAME
                logging.debug(f"NAME -> {name}: BREAK")
                break
            positions_list.append(current_search_position)  # add position to the list
            current_search_position += len(name)
        logging.debug(f"EXIT WHILE for:{name} -> result {positions_list}")
        if (len(positions_list) == 0):  # No patterns in sequense. result = 0
            result.update({name: 0})
            logging.debug(f"THIS -> len(positions_list) == 0 TRUE")
        elif (len(positions_list) == 1):  # One pattern in sequense
            result.update({name: 1})
            logging.debug(f"THIS -> len(positions_list) == 1 TRUE")
        else:  # There are few patterns in sequence
            logging.debug(f"THIS -> len(positions_list) > 1 TRUE")
            restemp = list()
            restemp.append(0)
            # Go throu positions list and find sequences. Each of them record in list
            for number in range(1, len(positions_list)):
                item1 = positions_list[number - 1]
                item2 = positions_list[number]
                logging.debug(f"------------- NUMBER: {number} , item1: {item1} , item2: {item2}")

                if item2 - item1 == len(name):
                    res_temp += 1
                    restemp.append(res_temp)
                    logging.debug(
                        f"-------------======= if item2 - item1 == len(name) TRUE res_temp NUMBER: {number} , item1: {item1} , item2: {item2}")
                    if number == len(positions_list) - 1:  # the last element in list
                        result.update({name: max(restemp) + 1})
                        logging.debug(
                            f"-------------=======+++ result.update(name : max(restemp) + 1 -> {max(restemp) + 1}) AND BREAK")
                        break
                    if (positions_list[number + 1] - positions_list[number]) == len(name):  # look for next element in sequence
                        continue
                    else:  # break the sequence
                        res_temp = 0

                else:
                    if number == len(positions_list) - 1:  # the last element. write result
                        result.update({name: max(restemp) + 1})
                    res_temp = 0

    # Find the name
    resName = "No match"  # Is default value that will be overwrited if we found the name
    for human in people:
        logging.debug(f"Current human -> {human}")
        i = dict(human)
        tmpName = i["name"]
        del i["name"]  # delete column names

        for key, value in i.items():
            i[key] = int(value)  # convert to integer for correct comparison

        logging.debug(i)
        if i == result:
            resName = tmpName  # overwrite the name then we have found it. then break
            break
    logging.debug(result)
    print(resName)


main()
