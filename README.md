EdTech-Speech_recognisation

This program is a simple personal assistant that interacts with the user through voice commands. It includes various functions such as providing the current time and date, calculating mathematical expressions, responding to weather queries, telling jokes, and more.

## Functions

- handle_teach_me(): Interacts with the American wise say function to teach the user.
- handle_user_input(user_input): Handles various user commands and responses.
- get_random_joke(): Returns a random joke to be shared when the user's mood is negative.
- engine(): Initalize the text to speech libary
- listen_and_recognize(): This recognize user speech using the speech recognization package
- main(): The main loop of the assistant, listening to user input, detecting mood, and responding accordingly.

## Imported Modules

- calendar: Provides functionality to work with calendars.
- random: Generates random numbers for joke selection.
- re: Provides regular expression matching.
- engine: Custom module for text-to-speech functionality.
- date_time_cal: Custom module for date, time, and weather responses.
- extra_function: Custom module containing additional functions such as funny responses and local language support.
- lists: Custom module containing predefined lists of inputs and output.
- teach_function: Custom module for educational information and voice recognition.
- updates: Custom module for handling updates and user credentials.
- detect_user_mood: Custom module for detecting the user's mood based on their input.

## Features

1. **Teach month of the year**
2. **Teach days of the week**
3. **Ask user for to take a quiz by calling the days or month and user should spell them correctly**
4. **User friendly**
5. **Providing the current date and time**
6. **Answer user question** **Eg. If user ask what is a noun**
7. **Calculate mathematical expresion**

   ```bash
      git clone https://github.com/your-username/EdTech-Speech_recognisation.git
         cd EdTech-Speech_recognisation
