import random
import speech_recognition as sr
from ENGINE import say
# from my_asistant_main import main

def listen_and_recognize():
    # recognizer = sr.Recognizer()

    # with sr.Microphone() as source:
    #     print("Say something:")
    #     recognizer.adjust_for_ambient_noise(source)
    #     audio = recognizer.listen(source)

    try:
        # user_input = recognizer.recognize_google(audio).lower()
        user_input = input("$ ").lower()
        print("You said:", user_input)
        return user_input
    except sr.UnknownValueError:
        print("Sorry, could not understand audio.")
        say("Sorry, could not understand audio.")
        return None
    except sr.RequestError as e:
        print(f"Error with the speech recognition service: {e}")
        return None

def read_day():
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
    months = [
        "Sunday",
        # "Monday",
        # "Tuesday",
        # "Wednesday",
        # "Thursday",
        # "Friday",
        # "Saturday",
    ]
    print("Repeat after me:")
    say("Repeat after me:")
    say("The month of the year are:")
    for month in months:
        print("{month}")
        say(f"{month}")

        user_input = listen_and_recognize()

        while user_input != month.lower():
            print(f"Try again.{month}")
            say(f"{month}")
            user_input = listen_and_recognize()

        say("Correct!")

    print("Twelve month make one year.")
    say("Twelve month make one year.")
    print("Do you want to try again? (Yes or No)")
    say("Do you want to try again? (Yes or No)")

    user_input = listen_and_recognize()
    if user_input == "yes":
        read_months()
    else:
        main()

def spell_word(word):
    print(f"AI: {word}")
    say(word)
    user_input = listen_and_recognize()

    while user_input != word.lower():
        print(f"AI: {word}")
        say(word)
        user_input = listen_and_recognize()
        # print("Incorrect. Try again.")
        # say("Incorrect. Try again.")

    say("Correct!")

def spell_days():
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
    months = [
        ("January" , "J a n u a r y"),
        ("February", "F e b r u a r y"),
        ("March", "M a r c h"),
        ("April", "A p r i l"),
        ("May", "M a y"),
        ("June", "J u n e"),
        ("July", "J u l y"),
    ]

    say("We are going to learn how to spell the month of the year")
    say("The days of the week are:")

    for month, spelled_month in months:
        spell_word(month)
        spell_word(spelled_month)

    say("Great job! You've spelled all the month of the year.")

def learning():
    my_teachings = [
        "1. Learn to read the month of the year",
        "2. Learn to spell the month of the year",
        "3. Learn to read the days of the week",
        "4. Learn to spell the days of the week",
    ]
    for my_teaching in my_teachings:
        print(my_teaching)
        say(my_teaching)
        # return my_teaching

def wake_up():
    response = random.choice(
        [
            "Hello, how can I help you today?",
            "I'm here to assist you with any questions.",
            "Ask me anything, and I'll do my best to provide an answer.",
            "How can I be of service to you?",
        ]
    )
    say(response)


