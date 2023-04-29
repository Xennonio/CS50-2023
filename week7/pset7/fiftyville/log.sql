-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Pertinent Information: Robbery occurred on 7/28/2021 on Humphrey Street

-- Analyze the description of crime reports that occurred on the day and street of the theft
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 07 AND year = 2021 AND street = 'Humphrey Street';
/*
- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today
with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
*/

-- The theft occurred at 10:15am

-- Analyze the interview with the witnesses present on the day of the robbery, remembering that they all mention a bakery
SELECT transcript, name FROM interviews
WHERE day = 28 AND month = 07 AND year = 2021;
/*
Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you
have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard
the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on
the other end of the phone to purchase the flight ticket.
*/
-- Emma's bakery
-- In Leggett Street withdrawing some money
-- 10m of the theft, the thief get into a car
-- Take the earliest flight out of Fiftyville in 29/07/2021
-- They called someone who talked to them for less than a minute, saying to purchase the flight ticket

-- See if any witnesses are named Emma
SELECT transcript FROM interviews WHERE name LIKE '%Emma%';
-- But nothing relevant was found

-- Consult the possible types of transaction
SELECT DISTINCT transaction_type FROM atm_transactions;

-- Search for the transaction that occurred in the report
SELECT account_number, amount FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

/*
+----------------+--------+
| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |
+----------------+--------+
*/

-- Look for the information of the people with these bank accounts
SELECT person_id, creation_year FROM bank_accounts WHERE account_number IN
  (SELECT account_number FROM atm_transactions
  WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

SELECT name, phone_number, passport_number, license_plate FROM people WHERE id IN
  (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));

/*
+-----------+---------------+
| person_id | creation_year |
+-----------+---------------+
| 686048    | 2010          |
| 514354    | 2012          |
| 458378    | 2012          |
| 395717    | 2014          |
| 396669    | 2014          |
| 467400    | 2014          |
| 449774    | 2015          |
| 438727    | 2018          |
+-----------+---------------+

+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/

-- 10 min after the theft (10:25am) he left the bakery whose license plates in log are:
SELECT license_plate, minute FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute > 15 AND minute < 35 AND activity = 'exit';

/*
+---------------+--------+
| license_plate | minute |
+---------------+--------+
| 5P2BI95       | 16     |
| 94KL13X       | 18     |
| 6P58WS2       | 18     |
| 4328GD8       | 19     |
| G412CB7       | 20     |
| L93JTIZ       | 21     |
| 322W7JE       | 23     |
| 0NTHK55       | 23     |
+---------------+--------+
*/

-- Comparing with previous data the license plates that repeats are:
SELECT name, phone_number, passport_number FROM people WHERE license_plate IN
  (SELECT license_plate FROM bakery_security_logs
  WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute > 15 AND minute < 35 AND activity = 'exit'

  INTERSECT

  SELECT license_plate FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
      (SELECT account_number FROM atm_transactions
      WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')));

/*
One of these is the thief
+-------+----------------+-----------------+
| name  |  phone_number  | passport_number |
+-------+----------------+-----------------+
| Iman  | (829) 555-5269 | 7049073643      |
| Luca  | (389) 555-5198 | 8496433585      |
| Diana | (770) 555-1861 | 3592750733      |
| Bruce | (367) 555-5533 | 5773159633      |
+-------+----------------+-----------------+
*/

-- Look for calls made by that number during the event
SELECT receiver, caller, duration FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN
  (SELECT phone_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute > 15 AND minute < 35 AND activity = 'exit'

  INTERSECT

  SELECT license_plate FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
      (SELECT account_number FROM atm_transactions
      WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))));

/*
So the thief is either Bruce or Diana
+----------------+----------------+----------+
|    receiver    |     caller     | duration |
+----------------+----------------+----------+
| (375) 555-8161 | (367) 555-5533 | 45       |
| (725) 555-3243 | (770) 555-1861 | 49       |
+----------------+----------------+----------+
*/

-- Look for people with that phone number

SELECT name, passport_number FROM people WHERE phone_number = '(375) 555-8161' OR phone_number = '(725) 555-3243';

/*
Robin is probably the accomplice, since the passport does not match any of the thieves
+--------+-----------------+
|  name  | passport_number |
+--------+-----------------+
| Philip | 3391710505      |
| Robin  | NULL            |
+--------+-----------------+
*/

-- Check Fiftyville airports
SELECT id, abbreviation, full_name FROM airports WHERE city = 'Fiftyville';

/*
+----+--------------+-----------------------------+
| id | abbreviation |          full_name          |
+----+--------------+-----------------------------+
| 8  | CSF          | Fiftyville Regional Airport |
+----+--------------+-----------------------------+
*/

SELECT id, destination_airport_id, hour, minute FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = 8;

/*
The earliest flight is from id = 36
+----+------------------------+------+--------+
| id | destination_airport_id | hour | minute |
+----+------------------------+------+--------+
| 18 | 6                      | 16   | 0      |
| 23 | 11                     | 12   | 15     |
| 36 | 4                      | 8    | 20     |
| 43 | 1                      | 9    | 30     |
| 53 | 9                      | 15   | 20     |
+----+------------------------+------+--------+
*/

SELECT city FROM airports WHERE id = 4;

/*
So the city he fled to was NY
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/

SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN
  (SELECT passport_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute > 15 AND minute < 35 AND activity = 'exit'

    INTERSECT

    SELECT license_plate FROM people WHERE id IN
      (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))));

/*
The only one left to be the thief is Bruce
+-----------------+
| passport_number |
+-----------------+
| 5773159633      |
| 8496433585      |
+-----------------+
*/