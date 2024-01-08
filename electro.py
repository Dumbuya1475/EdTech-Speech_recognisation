"""function to check for voltage (V)"""
def find_voltage():
    """This function find the voltage of an electronic component"""
    val1 = int(input("Enter value for Current(I) "))
    val2 = int(input("Enter value for Resistance (R) "))

    calculate = val1 * val2
    print(f"I = {val1} amp\nR = {val2} ohms\nV = ?\n")
    print("Find voltage")
    print("V = I X R")
    print(f"V = {val1} X {val2}")
    print(f"V = {calculate} volts")

def find_current():
    """This function find the current running in a circuit"""
    val2 = int(input("Enter value for voltage (V) "))
    val1 = int(input("Enter value for resistance (R) "))

    calculate = val2 / val1

    print(f"V = {val1}\nR = {val2}\nI = ?\n")
    print("Find I")
    print("I = V / R")
    print(f"I = {val1} / {val2}")
    print(f"I = {calculate} amps")

def find_resistance():
    """This function look for resistance in a circuit"""
    val2 = int(input("Enter value for voltage (V) "))
    val1 = int(input("Enter value for Current (I) "))

    calculate = val2 / val1
    try:
        print(f"V = {val1}\nI = {val2}\nR = ?\n")
        print("Find R")
        print("R = V / I")
        print(f"R = {val1} / {val2}")
        print(f"R = {calculate} ohms")

    except float:
        if val1 

def main():
    """- Main call all the function"""
    while True:
        print("This is a simple calculator for ohms law")

        tax = [
            "Press",
            "1. To check for voltsge (V)",
            "2. To check for current (I)",
            "3. To check for Resistance (R)"
        ]

        for my_tax in tax:
            print(my_tax)

        user_input = input("$ ")

        if user_input == "1":
            print("====================================")
            find_voltage()
            print("====================================\n")
        elif user_input == "2":
            print("====================================")
            find_current()
            print("====================================\n")
        elif user_input == "3":
            print("====================================")
            find_resistance()
            print("====================================\n")
        else:
            print("\nInvalid input.........\n")

if __name__ == "__main__":
    main()
