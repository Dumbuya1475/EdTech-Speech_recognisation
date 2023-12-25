"""speech recognisation libeary"""
import speech_recognition as sr
from ENGINE import say

def listen_and_recognize():
    """
    Function that Recognizes the speech with the speech recognition package and
    returns none
    """

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
