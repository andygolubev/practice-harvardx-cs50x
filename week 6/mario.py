def main():
    while True:
        # chech for non-integer values
        try:
            height = int(input("Height (1-8): "))
            if height >= 1 and height <= 8:
                    break
        except ValueError:
            continue

    printPyramids(height + 1)
    return True

# Print pyramids
def printPyramids(height_input):
    for raw in range(1, height_input):
        print(" " * (height_input - raw - 1) + "#" * raw + "  " + "#" * raw)
    return True

main()
