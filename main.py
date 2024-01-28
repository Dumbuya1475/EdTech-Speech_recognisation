"""Importing function from my function file"""
import calendar
import random
import re
from engine import say
from date_time_cal import calculate, date_response, time_response, weather_response
from extra_function import funny, joke_response, local_language
from extra_function import medical_response, president_response, wake_up
from lists import CHANGE_NAME_INPUT
from lists import MEDICATION_RECEIVE, NAME_RECEIVE
from teach_function import get_educational_info, listen_and_recognize, teach_me
from updates import ai_update, change_name, name_respond_output, user_credential
# from teach_function import get_educational_info
from detect_user_mood import detect_mood

def handle_teach_me():
    """
    The function which interact with American wise say.
    """
    say("Sure, let's get started.")
    say("This are few things I can teach you.")
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
        print("=================================================================")
    elif "joke" in user_input:
        print(joke_response())
        say(joke_response())
    else:
        say("Sorry, I didn't understand, please try again.")

def get_random_joke():
    """Return joke if user mood is not good"""
    jokes = [
        "Why don't scientists trust atoms? Because they make up everything!",
        "Did you hear about the mathematician who's afraid of negative numbers? He will stop at nothing to avoid them!",
        "Parallel lines have so much in common. It's a shame they'll never meet.",
        "Why did the scarecrow win an award? Because he was outstanding in his field!",
        "What do you call fake spaghetti? An impasta!"
    ]
    return random.choice(jokes)

def main():
    """
    Initialize all the functions
    """
    print("Hello! I am your assistant.")
    say("Hello! I am your assistant.")

    while True:
        # Listen for the user's input
        user_input = listen_and_recognize()

        # Check if speech recognition failed
        if user_input is None:
            print("Sorry, I couldn't understand the question. Please try again.")
            say("Sorry, I couldn't understand the question. Please try again.")
            continue

        # Detect the user's mood
        mood_response = detect_mood(user_input)
        print("AI:", mood_response)
        say(mood_response)

        # Check for the specific command "teach me"
        if user_input == "teach me":
            # Handle the "teach me" command
            handle_teach_me()
        else:
            # Proceed with the rest of the logic based on user input
            if "fun" in user_input:
                funny()
            elif "time" in user_input:
                print(time_response())
                say(time_response())
            elif "date" in user_input:
                print(date_response())
                say(date_response())
            elif re.match(r'^[\d+\-*/. ]+$', user_input):
                result = calculate(user_input)
                print(user_input + " = " + result)
                say(user_input + " = " + result)
            else:
                # Extract the last word as the topic
                topic = user_input.split()[-1].lower()
                response = get_educational_info(topic)
                print("AI:", response)
                say(response)

                # If mood is negative, share a random joke
                if "negative" in mood_response.lower():
                    joke = get_random_joke()
                    print("AI:", joke)
                    say(f"Here's a joke for you: {joke} Hope this makes you smile!")

if __name__ == "__main__":
    main()
