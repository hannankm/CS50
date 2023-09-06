-- log file 
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Queries to understand the mystery
-- know description of the crime: 10:15 am 3 wintness interview bakery
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND
day = 28 AND
month = 7 AND
street = 'Humphrey Street';

-- interview transcripts
-- | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          | Ruth    |
-- | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 | Eugene  |
-- | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. | Raymond |
SELECT transcript, name from interviews
WHERE year = 2021 AND
month = 7 AND
day = 28;

-- atm transactions table to find account number: one of those account number is that of the thiefs
SELECT account_number, amount from atm_transactions
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
atm_location = 'Leggett Street' AND
transaction_type = 'withdraw';

-- phone calls to find who the callers are
SELECT caller, receiver from  phone_calls
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
duration < 60;

-- know  about bakery security logs :
SELECT activity, license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
hour = 10 AND
minute >= 5 OR
minute <= 25;



--QUEIRES to solve the query ANSWERS
-- figure out theif: Bruce, Diana, Kenny, Taylor
SELECT name from people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE bank_accounts.account_number IN
(SELECT account_number from atm_transactions
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
atm_location = 'Leggett Street' AND
transaction_type = 'withdraw') AND
people.license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
hour = 10 AND
activity = 'exit' AND
minute >= 5 AND
minute <= 25
)
AND
people.phone_number IN
(SELECT caller from  phone_calls
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
duration < 60
)
AND
people.passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id IN
(SELECT id FROM flights
WHERE
year = 2021 AND
month = 7 AND
day = 29 AND
origin_airport_id IN
(SELECT id from airports
WHERE city = 'Fiftyville')
ORDER BY hour, minute
LIMIT 1
)
)
;

--find city
SELECT city from airports
WHERE id IN
(SELECT destination_airport_id FROM flights
WHERE year = 2021 AND
year = 2021 AND
month = 7 AND
day = 29 AND
origin_airport_id IN
(SELECT id from airports
WHERE city = 'Fiftyville')
ORDER BY hour, minute
LIMIT 1
);

--find accomplice : Anna, Jack, Larry, Robin, Philip, Jacqueline
SELECT name from people
WHERE
people.phone_number IN
(SELECT receiver from  phone_calls
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
duration < 60 AND
caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
);
