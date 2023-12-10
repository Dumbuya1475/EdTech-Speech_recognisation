"""
Importing function from my function file
"""
import calendar
import re
from ENGINE import say
from my_asistant_date_time_cal import calculate, date_response, time_response, weather_response
from my_asistant_extra_function import funny, joke_response, medical_response, president_response
from my_asistant_list import CHANGE_NAME_INPUT
from my_asistant_list import MEDICATION_RECEIVE, NAME_RECEIVE
from my_asistant_teach_function import learning, listen_and_recognize, read_day
from my_asistant_teach_function import read_months, spell_days, wake_up
from my_asistant_update import ai_update, change_name, name_respond_output, user_credential


def main():
    """
    entry point
    """
    say("Hello! I am your asiatant.")

    user_input = listen_and_recognize()

    if user_input == "teach me":
        learning()
        while True:
            # say("What can I teach you?")

            user_input = listen_and_recognize()

            if "read the month of the year" in user_input or user_input == "1":
                read_months()

            elif "read the days of the week" in user_input or user_input == "2":
                read_day()

            elif "spell the days of the week" in user_input or user_input == "3":
                spell_days()

            elif "user" in user_input:
                user_credential()
            else:
                say("Sorry, I didn't understand your choice. Please try again.")

    elif "Hey super" in user_input:
        wake_up()

    elif "update" in user_input:
        ai_update()

    elif "weather" in user_input:
        print(weather_response())
        say(weather_response())

    elif "user" in user_input:
        user_credential()

    elif user_input in MEDICATION_RECEIVE:
        medical_response()

    elif user_input in CHANGE_NAME_INPUT:
        change_name()

    elif user_input in NAME_RECEIVE:
        name_respond_output()

    elif "president" in user_input:
        print(president_response())
        say(president_response())

    elif "fun" in user_input:
        funny()

    # elif "teach" in user_input:
        # teach_me()

    elif "time" in user_input:
        print(time_response())
        say(time_response())

    elif "date" in user_input:
        print(date_response())
        say(date_response())

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

if __name__ == "__main__":
    main()
