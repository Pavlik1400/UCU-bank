-- 1. Вивести імена замовників в лексикографічному порядку(без повторів).

select distinct concat(first_name, ' ', last_name) as name 
	from customer
	order by name;

-- 2. Вивести імена акторів, які знімалися у фільмах, назва яких починається на літеру "A" (case insensitive).

select distinct concat(first_name, ' ', last_name) full_name, title as film_name 
	from film_actor fa left join actor a 
	on (fa.actor_id = a.actor_id)
	left join film f 
	on (fa.film_id = fa.film_id)
	where (title ilike 'a%')
	
-- 3. Вивести імена замовників(first_name), які повторюються(ті, що зустрічаються в тадлиці більше 1 разу)та відповідні кількості повторів(repeat).

select first_name, count(first_name) repeat
	from customer
	group by first_name
	having count(first_name) > 1;

-- 4. Вивести назви(city_name) 5-ти міст та кількості магазинів в цих містах(num_stores), впорядковані за спаданням кількісті магазинів.
-- 	  (Якщо кількість магазинів в містах однакова, то ці міста мають бути в оберненому до лексикографічного порядку). 
-- 	  (Вважайте що поле city унікально визначає рядочок в таблиці)
-- 	  Чи вийде отримати 5 міст? так

select city city_name, count(address_id)
	from address a left join city c 
	on (a.city_id = c.city_id)
	group by city_name
	order by count(address_id) desc, city_name desc
	limit 5;

-- 5. Вивести 10 найнепопулярніших назв категорій фільмів(name), та кількості фільмів(num_films), знятих в цих категоріях в порядку зростання кількості фільмів(num_films).
--    (якщо є дві категорії з однаковою тількістю фільмів, то вони мають бути впорядковані за лексикографічним порядком)
--	  (Важайте що назва категорії name є унікальною)

select name, count(film_id) num_films
	from category c left join film_category fc 
	on (c.category_id = fc.category_id)
	group by name
	order by count(film_id), name;
	
-- 6. Знайти 3 мови(name), такі, що фільми, озвучені цими мовами, орендуються найчастіше.
--   (Вважайте що назва мови name є унікальною)
--    Чи вийде отримати 3 мови? ні, всі фільми англійською:
select distinct language_id from film;

select l.name, count(f.film_id) 
	from rental r
	left join inventory i 
	on (r.inventory_id = i.inventory_id)
	left join film f 
	on (f.film_id = i.film_id)
	left join language l
	on (l.language_id = f.language_id)
	group by l.name
	order by count(f.film_id)
	limit 3;

-- 7. Створити предствавлення(actor_num_film) яке містить наступні колонки: 
--    * actor_id - унікальний ідентифікатор актора, 
--    * num_films - кількість фільмів у яких він знявся.
--   (представлення = view)

create view actor_num_film as
	select actor_id, count(film_id) num_films
		from film_actor
		group by actor_id;

-- select * from actor_num_film;
-- drop view if exists actor_num_film;

-- 8. Вивести інформацію(full_name) про 10 найбільш популярних акторів(ті, хто знялися в найбільшій кількості фільмів) 
--    та відповідні кількості фільмів(num_films) використовуючи представлення actor_num_film.
--	  (full_name = first_name + ' ' + last_name).

select concat(first_name, ' ', last_name) full_name, num_films
	from actor_num_film anf left join actor a
	on (anf.actor_id = a.actor_id)
	order by num_films desc
	limit 10;

-- 9. Створити представлення(film_num_rental ), яке міститиме наступні колонки:
-- 	* film_id - унікальний ідентифікатор фільму,
-- 	* num_rental - кількість оренд відповідного фільму.

create view film_num_rental as
	select f.film_id, count(f.film_id) num_rental
		from rental r
		left join inventory i 
		on (r.inventory_id = i.inventory_id)
		left join film f 
		on (f.film_id = i.film_id)
		group by f.film_id;
		
-- select * from film_num_rental;
-- drop view if exists film_num_rental;


-- 10. Вивести інформацію про 15 фільмів(title), які орендують найчастіше і опис(description) яких містить слово "amazing" (case sensitive), та відповідні кількості оренд(num_rental).
--    (якщо фільми мають однакову кількість оренд, впорядкуйте їх лексикографіно за назвою). Використовуйте представлення film_num_rental.

-- outputs nothing, because of case sensitivity (everywhere where amazing occures, its Amazing)
select f.title, f.description, num_rental 
	from film f left join film_num_rental fnr
	on (f.film_id = fnr.film_id)
	where f.description like '%amazing%'
	order by num_rental desc, f.title asc;
	


-- 11. Забезпечити видалення відповідних даних з таблиці film_actor у разі видалення фільму або актора.

-- actor
alter table film_actor
	drop constraint film_actor_actor_id_fkey,
	add constraint film_actor_actor_id_fkey 
	foreign key (actor_id) references actor(actor_id) on delete cascade;

-- check constraint
select * from film_actor;
select * from actor;

delete from actor
	where actor_id = 1;

-- film
alter table film_actor
	drop constraint film_actor_film_id_fkey,
	add constraint film_actor_film_id_fkey
	foreign key (film_id) references film(film_id) 
	on delete cascade;

-- change all other fk constraints
alter table film_category
	drop constraint film_category_film_id_fkey,
	add constraint film_category_film_id_fkey
	foreign key (film_id) references film(film_id) 
	on delete cascade;
	
alter table inventory
	drop constraint inventory_film_id_fkey,
	add constraint inventory_film_id_fkey
	foreign key (film_id) references film(film_id) 
	on delete cascade;
	
alter table rental
	drop constraint rental_inventory_id_fkey,
	add constraint rental_inventory_id_fkey
	foreign key (inventory_id) references inventory(inventory_id) 
	on delete cascade;
	
alter table payment
	alter column rental_id drop not null;

-- check constraint
select * from film;
delete from film
	where film_id = 133;

select * from film_actor where film_id = 133;
	
	
-- 12. Якщо ідентифікатор країни зміниться, забезпечити автоматичне оновлення записів таблиці city.

alter table city
	drop constraint fk_city,
	add constraint fk_city
	foreign key (country_id) references country(country_id) on update cascade;

-- check constraint
select * from city where country_id = 103;

update country
	set country_id = 200
	where country = 'United States'

select * from city where country_id = 200;

	

-- 13. Створити/видалити індекс для поля title таблиці film (написати 2 запити).

drop index if exists idx_title;
create index idx_title
	on film(title);

-- check if works
select * from film where title = 'Grosse Wonderful';
explain select * from film where title = 'Grosse Wonderful'; -- uses index

select * from film where title ilike 'a%'
explain select * from film where title ilike 'a%'			 -- doesn't use index

select * from film where title >'l'; 
explain select * from film where title > 'l'; 				 -- uses index

select * from film where title >'c'; 
explain select * from film where title > 'c';				 -- doesn't use index

-- 14. Створити/видалити індекс для комбінації полів first_name, last_name таблиці actor.

drop index if exists idx_actor_full_name
create index idx_actor_full_name 
	on actor(first_name, last_name);

-- 15. Забезпечити неможливість внесення двох країн з однаковою назвою.

alter table country
	add constraint unique_name unique(country);
select * from country where country = 'Algeria';

-- check constraint
insert into country(country_id, country, last_update) VALUES
	(200, 'Algeria', now());

-- 16. Додати таблицю genre з полями id, name. До таблиці film додати поле genre_id яке буде посилатись (foreign key) на поле id з таблиці genre. 

create table genre (
	id serial primary key,
	name varchar(30) not null
);

insert into genre(name) values
	('sport'),
	('horror'),
	('comedy');
	
select * from genre;

alter table film
	add column genre_id integer default null;
alter table film
	add constraint 
	genre_fkey foreign key (genre_id) 
	references genre(id) 
	on delete set null on update cascade;
	
update film
	set genre_id = 1
	where film_id = 3;
	
select * from film where genre_id = 1;

update genre
	set id = 4 
	where id = 1;
select * from film where genre_id = 1;


-- 17. Видалити поле genre_id. Видалити таблицю genre.

alter table film 
	drop column genre_id;

drop table if exists genre;


