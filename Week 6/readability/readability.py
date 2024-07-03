# TODO
text = input("Text: ")


# Counting the number of letters
def count_letters(text):
    count = 0
    for i in range(len(text)):
        # Check if it is a letter
        if text[i].isalpha():
            count += 1
    return count


# Counting the number of words
def count_words(text):
    # Making a list of the words
    t = text.split()
    count = len(t)
    return count


# Counting the number of sentences
def count_sentences(text):
    count = 0
    for i in range(len(text)):
        # Check if it is a punctuation signal
        if text[i] in ['.', '!', '?']:
            count += 1
    return count


letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

# Average of letter per 100 words
l = letters / words * 100

# Average of sentences per 100 words
s = sentences / words * 100

# Index grade
index = 0.0588 * l - 0.296 * s - 15.8

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
