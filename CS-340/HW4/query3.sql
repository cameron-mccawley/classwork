-- Find the actor_id first_name, last_name and total_combined_film_length 
-- of Sci-Fi films for every actor.
-- That is the result should list the actor ids, names of all of the actors(even if an actor has not been in any Sci-Fi films) 
-- and the total length of Sci-Fi films they have been in.
-- Look at the category table to figure out how to filter data for Sci-Fi films.
-- Order your results by the actor_id in descending order.
-- Put query for Q3 her

SELECT act.actor_id, act.first_name,act.last_name,CASE WHEN sci_fi.sum IS NULL THEN 0 ELSE sci_fi.sum END as total_combined_film_length
FROM actor act
LEFT JOIN
(SELECT act.actor_id AS actor_id, SUM(f.length) AS sum FROM actor act
INNER JOIN film_actor fa ON act.actor_id=fa.actor_id
INNER JOIN film f ON fa.film_id=f.film_id
INNER JOIN film_category fc ON f.film_id=fc.film_id
INNER JOIN category cate ON fc.category_id=cate.category_id
WHERE cate.name='Sci-Fi'
GROUP BY act.actor_id
ORDER BY sum ASC) AS sci_fi ON act.actor_id=sci_fi.actor_id
ORDER BY act.actor_id DESC;
