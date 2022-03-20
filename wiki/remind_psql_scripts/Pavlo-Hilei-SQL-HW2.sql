-- 1. From the Terminal, create a database called encyclopedia and connect to it via the the psql console.

-- createdb -U postgres -w encyclopedia
-- psql -U postgres -w -d encyclopedia

-- 2. Create a table called countries. 
create table countries (
	id serial primary key,
	name varchar(25) unique not null,
	capital varchar(50) not null,
	population integer
);

-- 3.  Create a table called famous_people.

create table famous_people (
	id serial primary key,
	name varchar(100) not null,
	occupation varchar(150),
	date_of_birth varchar(50),
	deceased bool default false
);

-- 4. Create a table called animals that could contain the sample data below:

create table animals (
	id serial primary key,
	name varchar(100) not null,
	binomial_name varchar(100) not null,
	max_weight_kg numeric(32, 16) CHECK (max_weight_kg >= 0.01 AND max_weight_kg <= 40000),
	max_age_years integer,
	conservation_status character(2)
);

-- 5. List all of the tables in the encyclopedia database.

-- \dt

-- 6. Display the schema for the animals table.

-- \d+ animals

-- 7. Rename the famous_people table to celebrities.

alter table famous_people rename to celebreties; 

-- 8. Change the name of the name column in the celebrities table to first_name, and change its data type to varchar(80).
-- The order in which you execute the statements isn't important.

alter table celebreties rename column name to first_name;
alter table celebreties 
	alter column first_name type varchar(80);

-- 9. Create a new column in the celebrities table called last_name.

alter table celebreties add column last_name varchar(100) not null;

-- 10. Change the celebrities table so that the date_of_birth column uses a data type that holds
-- an actual date value rather than a string. Also ensure that this column must hold a value.

alter table celebreties 
	alter column date_of_birth type date using date_of_birth::date;  -- explicit casting

alter table celebreties 
	alter column date_of_birth set not null;

-- 11. Change the animals table so that the binomial_name column cannot contain duplicate values.

alter table animals 
	add constraint unique_bin_name unique(binomial_name);

-- 12. Add the following data to the countries table:

insert into countries(name, capital, population) values 
	('France', 'Paris', 67158000); 

-- check if inserted correctly
select * from countries;

-- 13. Now add the following additional data to the countries table:

insert into countries(name, capital, population) values 
	('USA',     'Washington D.C.', 325365189),
	('Germany', 'Berlin',          82349400),
	('Japan',   'Tokyo',           126672000);


-- 14. Add an entry to the celebrities table for the singer and songwriter
-- Bruce Springsteen, who was born on September 23rd 1949 and is still alive.

insert into celebreties(first_name, last_name, date_of_birth, occupation, deceased) values
	('Bruce', 'Springsteen', '1949-09-23', 'singer and songwrite', false);
	
-- 15.  Add an entry for the actress
-- Scarlett Johansson, who was born on November 22nd 1984.
-- Use the default value for the deceased column.

insert into celebreties(first_name, last_name, date_of_birth, occupation) values
	('Scarlett', 'Johansson', '1984-11-22', 'actress');

-- 16. Add the following two entries to the celebrities table with a single INSERT statement.
--      For Frank Sinatra set true as the value for the deceased column.
--      For Tom Cruise, don't set an explicit value for the deceased column, but use the default value.

-- |first_name 	|last_name 	|occupation 	|date_of_birth
-- ------------------------------------------------------------
-- |Frank 	    |Sinatra 	|Singer, Actor 	|December 12, 1915
-- |Tom 	    |Cruise 	|Actor 	        |July 03, 1962

insert into celebreties(first_name, last_name, date_of_birth, occupation, deceased) values
	('Frank', 'Sinatra', '1915-12-12', 'Singer, Actor', true),
	('Tom', 'Cruise', '1962-07-03', 'Actor',DEFAULT);
			
-- 17.  Look at the schema of the celebrities table.
--      What do you think will happen if we try to insert the following data?
--      |first_name 	|last_name 	|occupation 	                     |date_of_birth  |deceased
-- ---------------------------------------------------------------------------------------------------
--      |Madonna 		|           |Singer, Actress 	                 |'08/16/1958' 	|false
--      |Prince 		|           |Singer, Songwriter, Musician, Actor |'06/07/1958' 	|true

-- Since last_name is not null, insert those values should be impossibe

insert into celebreties(first_name, date_of_birth, occupation, deceased) values
	('Madonna', '08/16/1958', 'Singer, Actress ', false),
	('Prince', '06/07/1958', 'Singer, Songwriter, Musician, Actor',true);
	
-- 18. Update the last_name column of the celebrities table so that the data in the previous question can be entered, and then add the data to the table.

alter table celebreties
	alter column last_name drop not null; 
	
insert into celebreties(first_name, date_of_birth, occupation, deceased) values
	('Madonna', '08/16/1958', 'Singer, Actress ', false),
	('Prince', '06/07/1958', 'Singer, Songwriter, Musician, Actor',true);

-- 19. Check the schema of the celebrities table.
-- What would happen if we specify a NULL value for deceased column, such as with the data below?

-- \d celebreties

-- |first_name 	|last_name 	|occupation 	            |date_of_birth  |deceased
-- ---------------------------------------------------------------------------------------
-- |Elvis 	    |Presley 	|Singer, Musician, Actor 	|'01/08/1935' 	|NULL

-- should work good, since we didn't spcify not null to deceased column before
	insert into celebreties(first_name, last_name, date_of_birth, occupation, deceased) values
		('Elvis', 'Presley', '01/08/1935', 'Singer, Musician, Actor', null);

	select * from celebreties;

-- 20. Check the schema of the animals table.

-- \d animals

-- What would happen if we tried to insert the following data to the table?
-- Identify the problem and alter the table so that the data can be entered as shown, and then insert the data.

-- Hint: we need to remove this contraint before adding the data.
-- |name 	         |binomial_name 	        |max_weight_kg 	    |max_age_years 	    |conservation_status
-- -----------------------------------------------------------------------------------------------------------
-- |Dove 	         |Columbidae Columbiformes 	|2 	            	|15                 |LC
-- |Golden Eagle 	 |Aquila Chrysaetos 	    |6.35 	            |24 	            |LC
-- |Peregrine Falcon |Falco Peregrinus 	    	|1.5 	            |15 	            |LC
-- |Pigeon 	         |Columbidae Columbiformes 	|2 	            	|15 	            |LC
-- |Kakapo 	         |Strigops habroptila 	    |4 	            	|60 	            |CR

-- since binomial_name is unique, we cannot add this data
-- remove uniqueness:
alter table animals drop constraint unique_bin_name; 

insert into animals(name, binomial_name, max_weight_kg, max_age_years, conservation_status) values
	('Dove', 		 	 'Columbidae Columbiformes', 2,    15, 'LC'),
	('Golden Eagle', 	 'Aquila Chrysaetos', 		 6.35, 24, 'LC'),
	('Peregrine Falcon', 'Falco Peregrinus', 		 1.5,  15, 'LC'),
	('Pigeon', 			 'Columbidae Columbiformes', 2,    15, 'LC'),
	('Kakapo', 			 'Strigops habroptila', 	 4,    60, 'CR');

-- 21.Create database ls_burger.

-- createdb -U postgres -w burger

-- 22. Connect to ls_burger.

-- psql -U postgres -w -d burger

-- 23. Create a table in the ls_burger database called orders. The table should have the following columns:

create table orders (
	id serial primary key,
	customer_name varchar(100) not null,
	burger varchar(50),
	side varchar(50),
	drink varchar(50),
	order_total numeric(4,2) not null check (order_total >= 0) 
);

-- 24. Add the following columns to the orders table:
--     A column called customer_email; it should hold strings of up to 50 characters.
--     A column called customer_loyalty_points that should hold integer values. If no value is specified for this column, then a value of 0 should be applied.

alter table orders 
	add column customer_email varchar(50),
	add column customer_loyalty_points integer default 0;

-- 25. Add three columns to the orders table called burger_cost, side_cost, and drink_cost to hold monetary values in dollars and cents (assume that all values will be less than $100).
-- If no value is entered for these columns, a value of 0 dollars should be used.

alter table orders
	add column burger_cost numeric(4,2) default 0,
	add column side_cost numeric(4,2) default 0,
	add column drink_cost numeric(4,2) default 0;
	
-- 26. Remove the order_total column from the orders table.

alter table orders
	drop column order_total;

-- 27. Based on the table schema and following information, write and execute an INSERT statement to add the appropriate data to the orders table.

insert into orders(customer_name, burger, side, drink, customer_email, customer_loyalty_points, burger_cost, side_cost, drink_cost) values
	('James Bergman', 'LS Chicken Burger', 'Fries', 'Cola', 'james1998@email.com', 28, 4.5, 0.99, 1.5),
	(E'Natasha O\'Shea', 'LS Cheeseburger', 'Fries', null, 'natasha@osheafamily.com', 18, 3.5, 0.99, DEFAULT),
	(E'Natasha O\'Shea', 'LS Double Deluxe Burge', 'Onion Rings', 'Chocolate Shake', 'natasha@osheafamily.com', 42, 6.0, 1.5, 2.0),
	('Aaron Muller', 'LS Burger', null, null, null, 10, 3.0, DEFAULT, DEFAULT);

select * from orders;
	
