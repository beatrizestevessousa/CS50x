-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the crime description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Find the transcripts and the witnesses of the interviews at the day of the crime
SELECT name, transcript
FROM interviews
WHERE transcript LIKE '%bakery%'
AND day = 28;

-- Get the license plate from the car the thief used to escape
SELECT license_plate
FROM bakery_security_logs
WHERE activity = 'exit' AND day = 28
AND month = 7 AND hour = 10
AND minute <= 25 AND minute >= 15;

-- Find the owners of the cars
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE activity = 'exit' AND day = 28
    AND month = 7 AND hour = 10
    AND minute <= 25 AND minute >= 15;
);

-- Check the count number of any transaction made in the ATM from Leggett Street on the day of the crime
SELECT account_number
FROM atm_transactions
WHERE day = 28 AND month = 7
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Identify who did withdraws on the day of the crime
SELECT name FROM people WHERE id IN (
    SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw';
    )
);

-- Identify who called for less than a minute on the crime day
SELECT name FROM people WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7 AND day = 28
    AND duration < 60 AND year = 2021
);

-- Find the destination city where the earliest flight for the day after the crime is not fiftyville
SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id FROM airports WHERE city LIKE 'FiftyVille'
    )
    AND month = 7 AND day = 29
    ORDER BY hour ASC
    LIMIT 1
);

-- The destination is New York City
-- Find the flights id and check the passengers
SELECT name FROM people WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE origin_airport_id IN (
            SELECT id FROM airports WHERE city LIKE 'FiftyVille'
        )
        AND month = 7 AND day = 29
        ORDER BY hour ASC
        LIMIT 1
    )
);

-- Bruce is the thief because he is in all four lists
-- Identify who receive a call from Bruce for less than a minute on the crime day
SELECT name FROM people WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE month = 7 AND day = 28
    AND duration < 60 AND year = 2021
    AND caller IN (
        SELECT phone_number FROM people WHERE name = 'Bruce'
    )
);

-- Bruce called Robin, so Robin is the accomplice
