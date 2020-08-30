import re

def get_string():
    while (True):
        try:
            text = input("Text: ")
            return text
        except:
            continue

def main():
    text = get_string()
    # Split on end marks; discard final match (after last end mark).
    sentences = re.split(r'[.!?]+', text)[:-1]
    words = [word for s in sentences for word in s.split()]
    letters = [c for word in words for c in word if c.isalpha()]
    L = len(letters) / len(words) * 100
    S = len(sentences) / len(words) * 100
    level = round(0.0588 * L - 0.296 * S - 15.8)
    if level < 1:
        print("Before Grade 1")
    elif level > 16:
        print("Grade 16+")
    else:
        print(f"Grade {level}")

main()
