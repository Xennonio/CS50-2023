import csv
import requests

def main():
  # Read NYTimes Covid Database
  download = requests.get("https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv")
  decoded_content = download.content.decode("utf-8")
  file = decoded_content.splitlines()
  reader = csv.DictReader(file)

  cases = []

  for row in reader:
    cases.append(row)

  # Construct 14 day lists of new cases for each states
  new_cases = calculate(cases)

  # Create a list to store selected states
  states = []
  print("Choose one or more states to view average COVID cases.")
  print("Press enter when done.\n")

  while True:
    state = input("State: ")
    if state in new_cases:
      states.append(state)
    if len(state) == 0:
      break

  print(f"\nSeven-Day Averages")

  # Print out 7-day averages for this week vs last week
  comparative_averages(new_cases, states)

# Create a dictionary to store 14 most recent days of new cases by state
def calculate(cases):
  difstates = []
  new_dict = {}
  for case in cases[::-1]:
    if case['name'] not in difstates:
      difstates.append(case['name'])

  for state in difstates:
    i = 0
    for item in reversed(cases):
      if item['state'] == state:
        new_dict[item['state']] = item['date']
        i += 1
      if i == 14:
        break

  return difstates

# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
  ...

main()