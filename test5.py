import requests
from bs4 import BeautifulSoup
import urllib.parse

def search_google(question):
    query = question.replace(" ", "+")  # Format for URL encoding
    url = f"https://www.google.com/search?q={query}"
    response = requests.get(url)
    soup = BeautifulSoup(response.text, "html.parser")

    # Extract text snippets from search results
    results = soup.find_all("span", class_="hgKElc")
    answers = [result.text.strip() for result in results]

    return answers

# Example usage within your AI code:
question = "What is a noun"
answers = search_google(question)

if answers:
    print("Google says:")
    for answer in answers:
        print(answer)
else:
    print("Sorry, I couldn't find an answer.")
