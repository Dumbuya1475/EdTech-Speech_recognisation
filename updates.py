"""
w
"""
import random
from ENGINE import say
from lists import CHANGE_NAME_RESPONSES, ILLEGAL


NEW_NAME_INPUT = ""  # Initialize the variable at the module level
FIRST_NAME = "" # Initialize the variable at the module level
LAST_NAME = "" # Initialize the variable at the module level

AI_NAME = [] # AI name stored (list)

def change_name():
    """
    Change the AI's name based on user input.
    Parameters:
    - None.
    """
    say(random.choice(CHANGE_NAME_RESPONSES))

    global NEW_NAME_INPUT
    NEW_NAME_INPUT = input("$ ")

    if NEW_NAME_INPUT == "":
        print("Sorry, my name can't be blank")
        say("Sorry, my name can't be blank")

    elif any(illegal_word in NEW_NAME_INPUT for illegal_word in ILLEGAL):
        print("Sorry due to terms and conditions, I cannot accept this name")
        say("Sorry due to terms and conditions, I cannot accept this name")

    else:
        new_name()


def name_respond_output():
    """
    Respond with the AI's name.
    """
    if not AI_NAME:
        print("Sorry I don't have a name, would you like to give me one?")
        say("Sorry I don't have a name, would you like to give me one?")
        say("yes or no")

        action_input = input(">>> ").lower()

        if action_input in ("No", "no"):
            print("I need an identity like you (name)")
            say("I need an identity like you")

        elif action_input in ("Yes", "yes"):
            say("Enter the name")
            action_input = input(">>> ")
            while True:
                if action_input == "":
                    print("Invalid")
                    say("Invalid")
                    say("Enter a valid name: ")
                    action_input = input(">>> ")
                else:
                    AI_NAME.insert(0, action_input)
                    for ai_name in AI_NAME:
                        print("My new name is " + ai_name)
                        say("My new name is " + ai_name)
                    break
    else:
        for ai_name in AI_NAME:
            print("My new name is ", ai_name)
            say("My new name is " + ai_name)

def new_name():
    """
    Set a new name for the AI.
    """
    AI_NAME.clear()
    AI_NAME.insert(0, NEW_NAME_INPUT)
    for ai_name in AI_NAME:
        print("My new name is " + ai_name)
        say("My new name is " + ai_name)

def ai_update():
    """
    Provide an update on AI features.
    """
    print("UPDATE")
    print("Now you can use short words to give commands")
    print("Here are the lists of the short words you can use..")
    say("Now you can use short words to give commands")
    say("Here are the lists of the short words you can use.......")

    my_update = [
        "   cal - To display the calendar",
        "   cha - To change my name",
        "   name - To know my name",
        "   joke - To outline a joke",
        "   file - To display the file system",
        "   game - To play a game with me",
        "   teach - To teach you",
        # "   riddle - To enter riddle mood",
        "   user - To know the current user status",
    ]
    for update in my_update:
        print(update)
        say(update)

def user_credential():
    """
    This function is responsible for handling user credentials.

    Returns:
    - (bool): True if the provided credentials are valid, False otherwise.
    """
    credentials = ["Current user " + FIRST_NAME + " " + LAST_NAME]
    for credental in credentials:
        print(credental)
        # return(credental)

def user_info():
    """
    Collect user information.
    """
    global FIRST_NAME
    global LAST_NAME
    print(" I need an instructor\n")
    say(" I need an instructor\n")
    say("Enter your first name to continue")
    FIRST_NAME = input("\n$ ").capitalize()
    say("Enter last name to continue\n")
    LAST_NAME = input("\n$ ").capitalize()
    while True:
        if FIRST_NAME == "" and LAST_NAME == "":
            print("Sorry this can't be blank")
            say("Sorry this can't be blank")
            # name = input("$ ").capitalize()
            print(" Hello " + LAST_NAME + " ask me anything.....")
            say(" Hello " + LAST_NAME + " ask me anything.....")
        else:
            say(" Hello " + LAST_NAME + " ask me anything.....")
        break
