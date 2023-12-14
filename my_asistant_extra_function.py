"""
"""
import speech_recognition
import random
from ENGINE import say
from my_asistant_list import HEAD_MEDICATION_RESPONSE

def medical_response():
    """
    _summary_
    """
    print("Describe how you feeling now and i will help you out")
    say("Describe how you are feeling now so can help you out")

    user_input = input(">>> ")

    if "head" in user_input or "sleeping" in user_input:
        say(random.choice(HEAD_MEDICATION_RESPONSE))

    elif "sleepless" in user_input or "dizzy" in user_input:
        say(random.choice(HEAD_MEDICATION_RESPONSE))

    else:
        print("sorry i did not understand")
        say("sorry i did not understand")
        medical_response()

def president_response():
    """
    Provide information about the current president of Sierra Leone.
    """
    return "The current President Soerra Leone is Julius Madda Beo."

def joke_response():
    """
    Provide a random joke.
    """
    jokes = [
        "U mut day smell",
        "cus nor fine",
        "ok o",
        # "spell for me. Psycology",
        # "spell for me. love,",
        # "spell for me. KAdiatu",
        # "spell for me. cow",
        # "spell for me. man",
        # "spell for me. y",
        "spell for me. house",
        "hawanatu U mut day smell",
        # "You na piss are badie",
        "Na who fat so",
        "Are wan eat",
        "unar go sleep",
        "go wass u mut",
        "Ibrahim. u kin spy",
        "Exam dae nah d coner o",
        "you back",
        "banoo eye o",
        "oo salone",
        "beans",
        "he shuck you",
    ]
    return random.choice(jokes)

def funny():
    """
    hjkakjdh
    """
    fun = [
        "unar day talk too mush",
        "me are done tire",
        "aaaaaaaaaaaaaa me",
        "dis country sweet oooo",
        "hawanatu",
        "memunatu"
        "u lek man",
        "you fool"
    ]
    say(random.choice(fun))

def local_language():
    """
    Responding in local language (krio)
    """
    local = [
        "Okey lae we tock am",
        "me are nor sabie tock am fine o",
        "hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
    ]
    say(random.choice(local))

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
