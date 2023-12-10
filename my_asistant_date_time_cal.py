"""
as
"""
from datetime import datetime
# import re

CURRENT_DATETIME = datetime.now() # Get the current date and time

CURRENT_DATE = CURRENT_DATETIME.date() # Extract the date components

CURRENT_TIME = CURRENT_DATETIME.time() # Extract the time components

FORMATTED_DATE = CURRENT_DATE.strftime("%d-%m-%Y") # Format the date as "YYYY-MM-DD"

FORMATTED_TIME = CURRENT_TIME.strftime("%H:%M") # Format the time as "HH:MM:SS"

def time_response():
    """
    Provide the current time.
    """
    return "The current time is " + FORMATTED_TIME

def date_response():
    """
    Provide the current date.
    """
    return "The current date is " + FORMATTED_DATE

def weather_response():
    """
    Display a string representing the current weather.
    """
    return "The weather today is sunny with a high of 75°F."


def calculate(expression):
    """
    Evaluate a mathematical expression.
    - try: look for any mathematical expression and return result
    - except: if no mathematical expression return Error
    """
    try:
        result = eval(expression)
        return f"{result}"
    except Exception  as e:
        return f"Error: {str(e)}"
