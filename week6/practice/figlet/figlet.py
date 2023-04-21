import sys, random
from pyfiglet import Figlet

figlet = Figlet()
fonts = figlet.getFonts()

try:
  if len(sys.argv) == 1:
    str = input("Input: ")
    f = random.choice(fonts)
    figlet.setFont(font = f)
    print(f"Output:\n{figlet.renderText(str)}")
  elif sys.argv[1] in ["-f", "--font"] and len(sys.argv) == 3 and sys.argv[2] in fonts:
    str = input("Input: ")
    fig = figlet.setFont(font = sys.argv[2])
    print(f"Output:\n{figlet.renderText(str)}")
  else:
    sys.exit('Invalid usage')
except:
  sys.exit('Invalid usage')