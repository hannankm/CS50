--1
SELECT title FROM movies
WHERE year = 2008;

--2 
SELECT birth from people
WHERE name = 'Emma Stone';

--3
SELECT title from movies
WHERE year > 2018 OR year = 2018
ORDER BY title;

--4
SELECT COUNT(DISTINCT(movie_id)) FROM ratings
WHERE rating = 10.0;

--5
SELECT title, year FROM movies
WHERE title like "Harry Potter%"
ORDER BY year;

--6
SELECT AVG(ratings.rating) FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;

--7
SELECT movies.title, ratings.rating from movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title

--8
SELECT people.name from stars
JOIN people ON people.id = stars.person_id
JOIN movies on movies.id = stars.movie_id
WHERE movies.title = 'Toy Story'

--9
SELECT people.name from stars
JOIN movies ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE movies.year = 2004
ORDER BY people.birth;

--10
SELECT DISTINCT(people.name) FROM directors
JOIN movies ON movies.id = directors.movie_id
JOIN people ON directors.person_id  = people.id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0

--11
SELECT movies.title FROM stars
JOIN movies ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
JOIN ratings ON ratings.movie_id = stars.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5

--12 
SELECT movies.title from movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN people p1 ON p1.id = s1.person_id
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON p2.id = s2.person_id
WHERE p1.name = 'Jennifer Lawrence' AND p2.name = 'Bradley Cooper';

--13
SELECT name FROM people
WHERE id IN (SELECT stars.person_id FROM stars WHERE stars.movie_id IN
(SELECT stars.movie_id FROM stars
WHERE person_id =
(SELECT id FROM people where name ='Kevin Bacon' AND birth = 1958))) AND name != 'Kevin Bacon';
