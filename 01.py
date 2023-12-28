import vosk

# Specify the correct path to the folder containing the Vosk model files
model_path = r"c:\Users\Suber\AppData\Local\Packages\PythonSoftwareFoundation.Python.3.11_qbz5n2kfra8p0\LocalCache\local-packages\Python311\Scripts"
# model_path = r"C:\Users\Suber\Downloads\vosk-model-small-en-us-0.15\ivector"

try:
    vosk_model = vosk.Model(model_path)
except Exception as e:
    print(f"Error: {e}")
    vosk_model = None

if vosk_model:
    # Continue with your speech recognition code using vosk_model
    recognizer = vosk.KaldiRecognizer(vosk_model, 16000)
    # ... rest of your code ...
else:
    print("Failed to create a Vosk model.")
# c:\Users\Suber\AppData\Local\Packages\PythonSoftwareFoundation.Python.3.11_qbz5n2kfra8p0\LocalCache\local-packages\Python311\Scripts