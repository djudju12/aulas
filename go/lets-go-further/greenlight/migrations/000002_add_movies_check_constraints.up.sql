ALTER TABLE movies ADD CONSTRAINT filterMetadata CHECK (runtime >= 0);

ALTER TABLE movies ADD CONSTRAINT filterMetadata CHECK (year BETWEEN 1888 AND date_part('year', now()));

ALTER TABLE movies ADD CONSTRAINT filterMetadata CHECK (array_length(genres, 1) BETWEEN 1 AND 5);