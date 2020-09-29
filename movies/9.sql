SELECT name FROM
people JOIN stars ON people.id = stars.person_id
WHERE movie_id IN (SELECT ID FROM movies WHERE year = 2004)
GROUP BY people.id
ORDER BY birth;
