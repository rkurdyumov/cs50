SELECT title FROM
movies JOIN ratings on movies.id = ratings.movie_id JOIN
stars on stars.movie_id = movies.id
WHERE person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman")
ORDER BY ratings.rating DESC
LIMIT 5;
