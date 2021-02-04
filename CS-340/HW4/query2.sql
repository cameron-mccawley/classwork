-- We want to find out how many of each category of film ED CHASE has starred in.

-- So return a table with "category_name" and the count of the "number_of_films" that ED was in that category.

-- Your query should return every category even if ED has been in no films in that category

-- Order by the category name in ascending order.

SELECT ct.name AS category_name, COUNT(act.actor_id) AS number_of_films FROM category ct
LEFT JOIN film_category AS fcat ON ct.category_id=fcat.category_id
LEFT JOIN film AS f ON fcat.film_id=f.film_id
LEFT JOIN film_actor AS a ON f.film_id=a.film_id
LEFT JOIN actor AS act ON
(a.actor_id=act.actor_id) AND (act.first_name='ED' AND act.last_name='CHASE')
GROUP BY ct.category_id ORDER BY ct.name;
