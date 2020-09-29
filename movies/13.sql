SELECT DISTINCT(people.name) FROM people
WHERE people.id IN (
    SELECT person_id FROM stars
    WHERE stars.movie_id in (SELECT movie_id FROM stars
        WHERE stars.person_id in (SELECT id FROM people
            WHERE people.name = "Kevin Bacon" AND birth = 1958)))
AND people.name <> "Kevin Bacon";
