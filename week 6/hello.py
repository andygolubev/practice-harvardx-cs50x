
def main():
    name = get_name()
    print(f"hello, {name}")


def get_name():
    tmpName = input("What is your name?\n")
    return tmpName

main()
