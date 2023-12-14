"""
Importing function from my function file
"""
import calendar
import re
from ENGINE import say
from my_asistant_date_time_cal import calculate, date_response, time_response, weather_response
from my_asistant_extra_function import funny, joke_response, local_language
from my_asistant_extra_function import medical_response, president_response, wake_up
from my_asistant_list import CHANGE_NAME_INPUT
from my_asistant_list import MEDICATION_RECEIVE, NAME_RECEIVE
from my_asistant_teach_function import listen_and_recognize, teach_me
from my_asistant_update import ai_update, change_name, name_respond_output, user_credential


def handle_teach_me():
    """
    The function which interact with American wise say.
    """
    say("Sure, let's get started.")
    teach_me()


def handle_user_input(user_input):
    """
    Function handle all user input.
    """
    if "user" in user_input:
        user_credential()
    elif "Hey super" in user_input:
        wake_up()
    elif "update" in user_input:
        ai_update()
    elif "weather" in user_input:
        print(weather_response())
        say(weather_response())
    elif "krio" in user_input:
        local_language()
    elif user_input in MEDICATION_RECEIVE:
        medical_response()
    elif user_input in CHANGE_NAME_INPUT:
        change_name()
    elif user_input in NAME_RECEIVE:
        name_respond_output()
    elif "president" in user_input:
        print(president_response())
        say(president_response())
    elif "cal" in user_input:
        print("Current year calendar::::")
        print(calendar)
        print("=============================================================================")
    elif "joke" in user_input:
        print(joke_response())
        say(joke_response())
    elif re.match(r'^[\d+\-*/. ]+$', user_input):
        result = calculate(user_input)
        print(user_input + " = " + result)
        say(user_input + " = " + result)
    else:
        say("Sorry, I didn't understand your choice. Please try again.")


def main():
    """
    Inicialize all the functions
    """
    say("Hello! I am your assistant.")

    while True:
        user_input = listen_and_recognize()

        if user_input == "teach me":
            handle_teach_me()
        elif "fun" in user_input:
            funny()
        elif "time" in user_input:
            print(time_response())
            say(time_response())
        elif "date" in user_input:
            print(date_response())
            say(date_response())
        else:
            handle_user_input(user_input)

if __name__ == "__main__":
    main()
