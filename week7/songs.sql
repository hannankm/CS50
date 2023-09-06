--1
SELECT name from Songs;

--2
SELECT name from Songs ORDER BY tempo ;

--3
SELECT name from Songs ORDER BY duration_ms DESC LIMIT 5;

--4
SELECT name from Songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

--5
SELECT AVG(energy) AS avg_enegry FROM Songs;

--6
SELECT name from Songs WHERE artist_id = (SELECT id FROM Artists WHERE name = 'Post Malone');

--7
SELECT AVG(energy) AS avg_drake_enegry FROM (SELECT energy from Songs where artist_id = (SELECT id from artists where name = 'Drake'));

--8
SELECT songs.name from Songs
JOIN artists ON songs.artist_id = artists.id
WHERE songs.name LIKE '%feat.%';
