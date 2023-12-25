"""Add this folder to the PYTHONPATH so Python can find the modules below."""
import os
import time
from ENGINE import say
from listen_and_recognize import listen_and_recognize

listen_and_recognize()

def read_day():
    """
    This Function is to read out the day of the week to the user.
   ...
    Now we read it with the method "say" for the
    """
    days = [
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
    ]
    print("Repeat after me:")
    say("Repeat after me:")
    say("The days of the week are:")
    for day in days:
        print("{day}")
        say(f"{day}")

        user_input = listen_and_recognize()

        while user_input != day.lower():
            print(f"Try again.{day}")
            say(f"{day}")
            user_input = listen_and_recognize()

        say("Correct!")

    print("Seven days make one Week.")
    say("Seven days make one Week.")
    print("Do you want to try again? (Yes or No)")
    say("Do you want to try again? (Yes or No)")


def read_months():
    """handle user input to read month"""
    months = [
        ("Sunday", "S u n d a y"),
        # Add other months as needed
    ]
    print("Repeat after me:")
    say("Repeat after me:")
    say("The days of the week are:")

    for month, spelled_month in months:
        print(f"{month}" + f"{spelled_month}")
        say(f"{month}")

        user_input = listen_and_recognize()

        while user_input != month.lower():
            print(f"Try again.{month}")
            say(f"{month}")
            user_input = listen_and_recognize()

        say("Correct!")

    print("Seven days make one week.")
    say("Seven days make one week.")

    # Play short music using os.system
    music_file_path = r'C:\Users\Suber\Downloads\drop.mp3'
    os.system(f'start {music_file_path}')

    # Optional: Add a delay to let the music finish playing before the program exits
    time.sleep(5)

    print("Do you want to try again? (Yes or No)")
    say("Do you want to try again? (Yes or No)")

    user_input = listen_and_recognize()
    if user_input == "yes":
        read_months()


def spell_word(word):
    """
    Like spell study the user will be asked to spell a word
    knowing that the AI will also spell the word correctly
    """

    print(f"AI: {word}")
    say(word)
    user_input = listen_and_recognize()

    while user_input != word.lower():
        print(f"AI: {word}")
        say(word)
        user_input = listen_and_recognize()
        # print("Incorrect. Try again.")
        say("Incorrect. Try again.")

    say("Correct!")

def spell_days():
    """
    returns a list of tuples that have all the months
    """

    days = [
        ("Sunday", "S u n d a y"),
        ("Monday", "M o n d a y"),
        ("Tuesday", "T u e s d a y"),
        ("Wednesday", "W e d n e s d a y"),
        ("Thursday", "T h u r s d a y"),
        ("Friday", "F r i d a y"),
        ("Saturday", "S a t u r d a y"),
    ]

    say("We are going to learn how to spell the days of the week")
    say("The days of the week are:")

    for day, spelled_day in days:
        spell_word(day)
        spell_word(spelled_day)

    say("Great job! You've spelled all the days of the week.")

def spell_months():
    """
    returns a list of tuples that have all the months
    """
    months = [
        ("January" , "J a n u a r y"),
        ("February", "F e b r u a r y"),
        ("March", "M a r c h"),
        ("April", "A p r i l"),
        ("May", "M a y"),
        ("June", "J u n e"),
        ("July", "J u l y"),
        ("August", "A u g u s t"),
        ("September", "S e p t e m b e r"),
        ("October", "O c t o b e r"),
        ("November", "N o v e m b e r"),
        ("December", "D e c e m b e r")
    ]

    say("We are going to learn how to spell the month of the year")
    say("The month of the year are: ")

    for month, spelled_month in months:
        spell_word(month)
        spell_word(spelled_month)

    say("Great job! You've spelled all the month of the year.")

def learning():
    """
    Shows the user the available options
    """

    my_teachings = [
        "1. Learn to read the month of the year",
        "2. Learn to spell the month of the year",
        "3. Learn to read the days of the week",
        "4. Learn to spell the days of the week",
    ]
    for my_teaching in my_teachings:
        print(my_teaching)
        say(my_teaching)

def teach_me():
    """Handle user input to teach"""
    learning()
    while True:
        user_input = listen_and_recognize()
        print(f"DEBUG: User input is '{user_input}'")

        if "read the month of the year" in user_input or user_input == "1":
            read_months()

        elif "read the days of the week" in user_input or user_input == "2":
            read_day()

        elif "spell the days of the week" in user_input or user_input == "3":
            spell_days()

        else:
            print("DEBUG: Breaking out of the loop.")
            break
