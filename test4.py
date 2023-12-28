def get_educational_info(topic):
    # In a real scenario, you might use an educational API or a knowledge base
    knowledge_base = {
        "noun": "A noun is a word that represents a person, place, thing, or idea.",
        "is water": "",
        "P H E": "Physical health"
    }
    return knowledge_base.get(topic, "I don't have information on that topic.")

# Example usage
# user_input = input("User: ")
# topic = user_input.split()[-1].lower()  # Extract the last word as the topic
# response = get_educational_info(topic)
# print("AI:", response)
