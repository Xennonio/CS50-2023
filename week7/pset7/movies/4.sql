SELECT COUNT(*) AS rate_10_movies FROM movies WHERE id IN
  (SELECT movie_id FROM ratings WHERE rating = 10);