height = -1

while height <= 0 or height > 8:
  try:
    height = int(input("Height: "))
  except:
    pass

for i in range(height):
  print(" "*(height - i - 1) + "#"*(i + 1) + "  " + "#"*(i + 1))