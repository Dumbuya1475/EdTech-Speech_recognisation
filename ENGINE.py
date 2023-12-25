"""Text to speech engine"""
import pyttsx3

ENGINE = pyttsx3.init()

def set_voice_properties(pitch=2.5, rate=150):
    """set voice property"""
    # Adjust the voice pitch (0.5 is lower pitch, 1.0 is the default, 2.0 is higher pitch)
    ENGINE.setProperty('pitch', pitch)

    # Adjust the voice rate (words per minute)
    ENGINE.setProperty('rate', rate)

def say(text):
    """Engine to speek text"""
    ENGINE.say(text)
    ENGINE.runAndWait()
