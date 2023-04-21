from cs50 import get_float
from math import floor

owed = -1

while owed < 0:
  owed = get_float("Change owed: ")

quarters = round(owed/0.25, 2)
dimes = round((owed - 0.25*floor(quarters))/0.1, 2)
nickels = round((owed - 0.25*floor(quarters) - 0.1*floor(dimes))/0.05, 2)
pennies = round((owed - 0.25*floor(quarters) - 0.1*floor(dimes) - 0.05*floor(nickels))/0.01, 2)

print(floor(quarters) + floor(dimes) + floor(nickels) + floor(pennies))