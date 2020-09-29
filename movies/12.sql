SELECT title FROM
movies JOIN stars on movies.id = stars.movie_id JOIN
people on people.id = stars.person_id
WHERE people.name IN ("Johnny Depp", "Helena Bonham Carter")
GROUP BY movies.id HAVING COUNT(movies.id) = 2; 
