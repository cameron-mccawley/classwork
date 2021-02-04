-- Find the film_title of all films which feature both KIRSTEN PALTROW and WARREN NOLTE
-- Order the results by film_title in descending order.
(SELECT f.title as film_title FROM film f
    INNER JOIN film_actor f2 ON f.film_id=f2.film_id
    INNER JOIN actor a2 ON f2.actor_id=a2.actor_id
    INNER JOIN film_actor f1 ON f.film_id=f1.film_id
    INNER JOIN actor a1 ON f1.actor_id=a1.actor_id
WHERE (a1.first_name='WARREN' AND a1.last_name='NOLTE')
    AND (a2.first_name='KIRSTEN' AND a2.last_name='PALTROW'))
ORDER BY f.title DESC;
