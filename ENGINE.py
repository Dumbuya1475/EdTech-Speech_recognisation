"""Text to speech libery"""
import pyttsx3

# Initialize the text-to-speech engine
ENGINE = pyttsx3.init()

def set_voice_properties(pitch=2.5, rate=150):
    """
    Set voice properties for the text-to-speech engine.

    Parameters:
    - pitch (float): Adjust the voice pitch (0.5 for lower pitch, 1.0 for default, 2.0 for higher pitch).
    - rate (int): Adjust the voice rate (words per minute).

    Returns:
    - None
    """
    # Adjust the voice pitch
    ENGINE.setProperty('pitch', pitch)

    # Adjust the voice rate
    ENGINE.setProperty('rate', rate)

def say(text):
    """
    Engine to speak the provided text.

    Parameters:
    - text (str): The text to be spoken.

    Returns:
    - None
    """
    ENGINE.say(text)
    ENGINE.runAndWait()
