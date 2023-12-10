# import random
# import calendar
# from datetime import datetime

# AI_name = ["SuperBot (Default name)"]

# # CURRENT_YEAR and CURRENT_MONTH you want to display
# CURRENT_YEAR = 2023

# # Create a calendar object for the specified CURRENT_YEAR and CURRENT_MONTH
# cal = calendar.calendar(CURRENT_YEAR)
# # print(cal)




# # def calendar_response():
# #     return cal
#     # re

# change_name_input = [
#     "can i change your name",
#     "i want to change your name",
#     "cha",
#     ]

# change_name_responses = [
#     "AI: Yes. Enter the my new name",
#     "AI: Okey. What's my new name",
#     "AI: Sure. Tell me my new name",
#     ]

# greeting_receive = [
#     "hi",
#     "hello",
#     "sup",
#     "yo",
#     "help",
#     ]

# name_receive = [
#     "what is your name",
#     "your name",
#     "tell me your name",
#     "can i know your name",
#     "name",
#     ]

# illegal = [
#     "sex",
#     "fuck",
#     "xxx",
# ]

# # Get the current date and time
# current_datetime = datetime.now()

# # Extract the date and time components
# current_date = current_datetime.date()
# current_time = current_datetime.time()

# # Format the date as "YYYY-MM-DD"
# formatted_date = current_date.strftime("%d-%m-%Y")

# # Format the time as "HH:MM:SS"
# formatted_time = current_time.strftime("%H:%M")

# def simple_ai():
#     responses = [
#         "Hello, how can I help you today?",
#         "I'm here to assist you with any questions.",
#         "Ask me anything, and I'll do my best to provide an answer.",
#         "How can I be of service to you?",
#     ]
#     print(random.choice(responses))

# def calculate(expression):
#     try:
#         result = eval(expression)
#         return f"{result}"
#     except Exception as e:
#         return f"Error: {str(e)}"

# def weather_response():
#     return "The weather today is sunny with a high of 75°F."

# def president_response():
#     return "The current President Soerra Leone is Julius Madda Bio."

# def time_response():
#     return "The current time is " + formatted_time

# def date_response():
#     return "The current date is " + formatted_date

# def name_respond_output():
#     """
#     This function is used to respond to the user's name.
#     """
#     print(random.choice(name_receive))
#     if AI_name == []:
#         print("I dont have a name, would you like to give me one?")

#         action_input = input("Enter [Y/N]: ").lower()

#         if action_input in ("N", "n"):
#             print("I need an identity like you (name)")
#             say("I need an identity like you (name)")

#         elif action_input in ("Y", "y"):
#             action_input = input("Enter my name:... ")
#             while True:
#                 if action_input == "":
#                     print("Invalid")
#                     say("Invalid")
#                     action_input = input("Enter a valid name: ")
#                 else:
#                     AI_name.insert(0, action_input)
#                     for ai_name in AI_name:
#                         print("My new name is", ai_name)
#                     break
#     else:
#         for ai_name in AI_name:
#             print("My new name is", ai_name)

# def new_name():
#     AI_name.clear()
#     AI_name.insert(0, new_name_input)
#     for ai_name in AI_name:
#         print("My new name is", ai_name)

# def change_name():
#     print(random.choice(change_name_responses))

#     global new_name_input
#     new_name_input = input("$ ")

#     if new_name_input == "":
#         print("Sorry my name cant be blank")

#     if ("fuck" in new_name_input) or ("ass" in new_name_input) or ("pussy" in new_name_input):
#         print("Sorry due to terms and condition i connot accept this name")

#     if ("sex" in new_name_input) or ("bobs" in new_name_input) or ("pennis" in new_name_input):
#         print("Sorry due to terms and condition i connot accept this name")

#     else:
#         new_name()

# def ai_update():
#     print("UPDATE")
#     print("Now you can use short words to give commands")
#     print("Here are list of the short words you can use..")

#     my_update = [
#         "   cal - To display the calendar",
#         "   cha - To change my name",
#         "   name - To know my name",
#         "   joke - To outline joke",
#         "   file - To display file system",
#         "   game - To play game with me",
#         "   teach - To teach you",
#         "   riddle - To enter riddle mood",
#         "   user - To know current user status",
#     ]
#     for update in my_update:
#         print(update)

# def joke_response():
#     jokes = [
#         "Why did the scarecrow win an award? Because he was outstanding in his field!",
#         "Parallel lines have so much in common. It's a shame they'll never meet.",
#         "I used to play piano by ear, but now I use my hands.",
#     ]
#     return random.choice(jokes)

# def user_info():
#     global first_name
#     global last_name
#     print("AI: I need an instructor\n")
#     first_name = input("Enter your first name to continue\n$ ").capitalize()
#     last_name = input("AI: Enter last name to continue\n$ ").capitalize()
#     while True:
#         if first_name == "" and last_name == "":
#             print("Sorry this cant be blank")
#             name = input("$ ").capitalize()
#             print("AI: Hello " + last_name + " ask me anything.....")
#         else:
#             print("AI: Hello " + last_name + " ask me anything.....")
#         break

# def user_credential():
#     credentials =  ["Current user " + first_name + " " + last_name]
#     # return credential
#     for credental in credentials:
#         print(credental)
#     # print("This is me")