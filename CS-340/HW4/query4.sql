-- Find the actor_id, first_name and last_name of all actors who have never been in a Sci-Fi film.
-- Order by the actor_id in ascending order.
-- Put your query for Q4 here
SELECT at.actor_id, at.first_name, at.last_name FROM actor at
	INNER JOIN film_actor fa ON at.actor_id = fa.actor_id
	INNER JOIN film f ON fa.actor_id = f.film_id
	INNER JOIN film_category fcat ON f.film_id = fcat.film_id
	INNER JOIN category ct ON fcat.category_id = ct.category_id
WHERE at.actor_id NOT IN
(SELECT at.actor_id FROM actor at
        INNER JOIN film_actor fa ON at.actor_id=fa.actor_id
        INNER JOIN film f ON fa.film_id=f.film_id
        INNER JOIN film_category fcat ON f.film_id=fcat.film_id
        INNER JOIN category ct ON fcat.category_id=ct.category_id
		WHERE ct.name='Sci-Fi'
       GROUP BY at.actor_id)
GROUP BY at.actor_id;
