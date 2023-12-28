"""This function detect user mood depending on what the share"""
def detect_mood(user_input):
    """
    Detects the user's mood based on their response.

    Parameters:
    - user_input (str): The user's input.

    Returns:
    - str: A response indicating the detected mood.
    """

    # Define positive and negative keywords
    positive_keywords = ["happy", "joyful", "excited", "good"]
    negative_keywords = ["sad", "angry", "frustrated", "bad"]

    # Check for positive keywords
    for word in positive_keywords:
        if word in user_input:
            return "It sounds like you're in a positive mood! 😊"

    # Check for negative keywords
    for word in negative_keywords:
        if word in user_input:
            return "I'm sorry to hear that. Is there anything I can do to help?"

    # Default response for neutral mood
    return "Seems like a neutral mood. How can I assist you today?"
