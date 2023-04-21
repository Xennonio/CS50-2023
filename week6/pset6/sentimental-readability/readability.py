import string

text = input("Text: ").split()

words = len(text)
sentences = 0
letters = 0
for word in text:
  i = 0
  for punc in string.punctuation:
    if punc in word:
      i += 1
  letters += len(word) - i
  sentences += ('.' in word or '!' in word or '?' in word)

index = round(0.0588*(100*letters/words) - 0.296*(100*sentences/words) - 15.8)

if index >= 16:
  print("Grade 16+")
elif index < 1:
  print("Before Grade 1")
else:
  print("Grade", index)