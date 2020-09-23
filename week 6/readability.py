import logging


def main():

    # Config logging. All messages have logged by DEBUG level
    logging.basicConfig(level=logging.INFO)

    # Input text
    text = input("Text: ")

    logging.debug(f"TEXT -> {text}")

    # remove trash elements from string
    replacements = ('\'', '\"', '-', ',', ';')
    for r in replacements:
        text = text.replace(r, '')

    logging.debug(f"Text after replacement ('\'', '\"', '-', ',', ';') -> {text}")

    #
    # Work with sentences
    #
    replacements = ('!', '?')
    # replace end of sentence symbols with dots, then split sentences by dots
    for r in replacements:
        text = text.replace(r, '.')
    logging.debug(f"Text after replacement ('!', '?') -> {text}")
    sentences = text.split('.')

    logging.debug(f"Sentences -> {sentences}")
    # remove empty elements from the list
    sentences = removeEmptyElements(sentences)

    #
    # Work with words
    #
    # remove dots at all, then split words by spaces
    text = text.replace('.', '')
    logging.debug(f"Text after replacement ('.', '') -> {text}")
    words = text.split(' ')
    # remove empty elements from the list
    words = removeEmptyElements(words)
    logging.debug(f"Words -> {words}")

    #
    # Work with letters
    #

    # remove spaces at all. No need to split letters
    letters = text.replace(' ', '')
    logging.debug(f"Letters -> {letters}")

    # calculating grade by Coleman-Liau formula
    # 0.0588 * L - 0.296 * S - 15.8, where L is the average number of letters per 100 words in the text,
    # and S is the average number of sentences per 100 words in the text.
    grade = round(0.0588 * (len(letters) / len(words)) * 100 - 0.296 * (len(sentences) / len(words)) * 100 - 15.8)
    logging.debug(f"Letters -> {len(letters)}; Words -> {len(words)}; Sentences -> {len(sentences)}; Grade -> {grade}")

    # print result of the calculation
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

#
# Function for removing empty "" elements from list
#


def removeEmptyElements(textList):
    while("" in textList):
        textList.remove("")
    logging.debug(f"List after remove empty elements -> {textList}")
    return textList


main()

