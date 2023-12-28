from pocketsphinx import LiveSpeech

def offline_speech_recognition():
    speech = LiveSpeech()

    print("Listening for speech (Ctrl+C to exit):")
    for phrase in speech:
        print(phrase)

if __name__ == "__main__":
    offline_speech_recognition()
