from googlesearch import search

# Your predefined list of answers
predefined_answers = {
    "hello": "Hi there!",
    "how are you": "I'm just a computer program, but I'm doing well. Thanks for asking!",
    # Add more predefined answers as needed
}

def get_user_input():
    return input("Ask me something: ")

def get_answer(user_input):
    # Check if the user input is in the predefined answers
    if user_input.lower() in predefined_answers:
        return predefined_answers[user_input.lower()]
    else:
        # If not in the list, search the web for an answer
        return search_web(user_input)

def search_web(query):
    # Use the googlesearch library to perform a web search
    try:
        search_results = search(query, num=1, stop=1)
        for result in search_results:
            return f"I found this on the web: {result}"
    except Exception as e:
        return f"An error occurred: {e}"

# Main program loop
while True:
    user_input = get_user_input()
    if user_input.lower() == 'exit':
        print("Goodbye!")
        break

    answer = get_answer(user_input)
    print(answer)
