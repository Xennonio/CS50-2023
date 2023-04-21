menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

x = 0

while True:
  try:
    item = input("Item: ")
    if item.title() in menu:
      x += menu[item.title()]
      print("Total: ${:.2f}".format(x))
  except EOFError:
    print("")
    break