SELECT title FROM movies, stars, people, ratings WHERE movies.id = stars.movie_id AND movies.id = ratings.movie_id AND stars.person_id = people.id AND people.name LIKE "chadwick boseman" ORDER BY ratings.rating DESC LIMIT 5



--WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name LIKE "chadwick boseman")) ORDER BY  LIMIT 5;
