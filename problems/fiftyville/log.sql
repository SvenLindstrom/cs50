-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the crime scene repot for more crime information
SELECT * FROM crime_scene_reports WHERE street LIKE "humphrey street";

-- check the 3 interviews from the crime scene for lead
SELECT * FROM interviews WHERE year = 2021 and month = 7 and day =28;

-- check bakery security for people that left the bakery ten min afther crime
SELECT *
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute < 25);

-- check atm for people that made withdraw money
SELECT *
    FROM people
    WHERE id IN
        (SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                    FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location LIKE "leggett street"
                    AND transaction_type = "withdraw");

-- check people that had a phone call on the day of the crime
SELECT *
    FROM people
    WHERE phone_number IN (
        SELECT caller
            FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28);

-- cheack for the air port id of the local air port
SELECT * FROM airports WHERE name LIKE "%Fiftyville%";

-- cheack people that
SELECT *
    FROM people
    WHERE passport_number IN
        (SELECT passport_number
            FROM passengers
            WHERE flight_id IN
                (SELECT id FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    AND origin_airport_id = 8));

-- combine previouse queries to determin suspects
SELECT *
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute < 25)
    AND id IN
        (SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                    FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location LIKE "leggett street"
                    AND transaction_type = "withdraw"))
    AND phone_number IN (
        SELECT caller
            FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60)
    AND passport_number IN
        (SELECT passport_number
            FROM passengers
            WHERE flight_id IN
                (SELECT id FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    AND origin_airport_id = 8));

-- cheak which flights the suspects where on to see who took the earlier one
SELECT *, name
    FROM flights, passengers, people
    WHERE flights.id = passengers.flight_id
    AND passengers.passport_number = people.passport_number
    AND people.name IN ("Diana","Bruce")
    AND flights.day = 29
    AND flights.origin_airport_id = 8;

-- since bruce took the earlier flight. he is the thief. so we check the city where the flight is heading
SELECT * FROM airports WHERE id = 4;

-- ceack the phone records of bruce to find his ACCOMPLICE
SELECT *
    FROM people
    WHERE phone_number IN (
        SELECT receiver
            FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND caller IN(
                SELECT phone_number
                FROM people
                WHERE name LIKE "bruce")
            AND duration < 60);
-- the ACCOMPLICE is Robin