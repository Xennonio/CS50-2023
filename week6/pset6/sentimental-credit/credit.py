def amex(n, ct):
  k = len(n)
  return k == 15 and n[0:2] in ["34", "37"] and ct % 10 == 0

def macard(n, ct):
  k = len(n)
  return k == 16 and n[0:2] in ["51", "52", "53", "54", "55"] and ct % 10 == 0

def visa(n, ct):
  k = len(n)
  return (k == 13 or k == 16) and n[0:1] == "4" and ct % 10 == 0

cnumb = input("Número: ")

cardtest = 0

for i in range(len(cnumb)):
  x = int(cnumb[i])*(((i + len(cnumb) + 1) % 2) + 1)
  if len(str(x)) > 1:
    x = ((x - 1) % 9) + 1
  cardtest += x

if amex(cnumb, cardtest):
  print("AMEX\n")
elif macard(cnumb, cardtest):
  print("MASTERCARD\n")
elif visa(cnumb, cardtest):
  print("VISA\n")
else:
  print("INVALID\n")