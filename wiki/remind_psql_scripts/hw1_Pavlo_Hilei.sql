-- 1 create database
create database university
	WITH 
	ENCODING = 'UTF8';

-- 2 create tables
create table student (
	sid integer 	  primary key,
	fname varchar(25) not null,
	lname varchar(25) not null,
	phone char(13)    unique not null,
	iq integer,
	birth_date date
);

create table migration (
	mid integer 	primary key,
	who integer 	not null,
	from_ integer 	not null, 	-- from - reserved keyword
	to_ integer 	not null, 	-- to - reserved keyword
	when_ date, 				-- when - reserved keyword
	student_sid integer, 		-- foreigner key
	university_cid integer 		-- foreigner key
);

create table university (
	uid integer 		primary key,
	name_ varchar(100) 	not null,	 -- not 45 - some names are way too long
	founded_in date,
	rating integer
);

select * from student;
select * from migration;
select * from university;

-- 3 add about to university
alter table university add column about text;

-- 4 add gender to student
alter table student add column gender boolean; -- true if male, false if female

-- 5 populate db. 
-- Usen dataset: https://www.kaggle.com/c/titanic 
insert into student(sid,fname,lname,phone,iq,birth_date,gender) VALUES 
(0,'Owen','Harris','+380926717386',124,'2002-02-21',true),
(1,'Briggs','Thayer','+380014004689',130,'2003-06-11',false),
(2,'Miss','Laina','+380145439101',118,'2001-12-11',false),
(3,'May','Peel','+380851832164',109,'2002-03-04',false),
(4,'William','Henry','+380298381686',123,'2002-02-15',true),
(5,'Moran','James','+380759221166',108,'2004-03-31',true),
(6,'Timothy','J','+380845763778',98,'2002-07-27',true),
(7,'Gosta','Leonard','+380074270930',121,'2002-12-26',true),
(8,'Vilhelmina','Berg','+380608116050',120,'2000-04-20',false),
(9,'Adele','Achem','+380044329431',129,'2003-11-13',false),
(10,'Marguerite','Rut','+380562566272',119,'2004-11-16',false),
(11,'Miss','Elizabeth','+380232756676',110,'2001-06-20',false),
(12,'William','Henry','+380739060312',102,'2003-01-29',true),
(13,'Anders','Johan','+380239491845',93,'2003-08-13',true),
(14,'Amanda','Adolfina','+380088697747',119,'2001-06-01',false),
(15,'D','Kingcome','+380400025040',111,'2000-07-29',false),
(16,'Master','Eugene','+380639683735',94,'2000-02-24',true),
(17,'Charles','Eugene','+380155875408',128,'1999-07-01',true),
(18,'Maria','Vandemoortele','+380513853344',102,'2002-07-02',false),
(19,'Masselmani','Fatima','+380647530481',123,'1999-02-07',false),
(20,'Joseph','J','+380770677711',119,'1999-11-30',true),
(21,'Beesley','Lawrence','+380126379168',105,'2003-06-04',true),
(22,'Anna','Annie','+380237324556',92,'2000-03-15',false),
(23,'William','Thompson','+380498347897',125,'2001-12-05',true),
(24,'Torborg','Danira','+380301912633',107,'2002-03-11',false),
(25,'Emilia','Johansson','+380886016419',90,'2003-01-10',false),
(26,'Farred','Chehab','+380843318453',104,'2003-03-09',true),
(27,'Charles','Alexander','+380749220885',130,'2003-02-12',true),
(28,'Ellen','Nellie','+380026228123',127,'2004-07-27',false),
(29,'Todoroff','Lalio','+380332365992',126,'2004-08-03',true),
(30,'Manuel','E','+380908957740',96,'2001-06-20',true),
(31,'Marie','Eugenie','+380277851429',125,'2003-07-04',false),
(32,'Mary','Agatha','+380546030535',102,'2003-12-13',false),
(33,'Edward','H','+380452405980',104,'2000-09-11',true),
(34,'Edgar','Joseph','+380070030035',112,'1999-09-30',true),
(35,'Alexander','Oskar','+380562376254',93,'2000-12-25',true),
(36,'Mamee','Hanna','+380660648870',111,'2000-05-17',true),
(37,'Ernest','Charles','+380620829821',116,'2002-09-13',true),
(38,'Augusta','Maria','+380230282169',105,'2000-02-29',false),
(39,'Miss','Jamila','+380729904560',129,'1999-05-29',false);

insert into migration(mid, who, from_, to_, when_,student_sid,university_cid) VALUES
(0,24,141,205,'1983-04-04',37,0),
(1,26,122,36,'1982-01-23',26,3),
(2,2,113,205,'1982-02-14',37,20),
(3,16,221,139,'1989-03-18',17,6),
(4,32,133,114,'1982-02-03',28,19),
(5,31,66,23,'1980-05-15',31,18),
(6,25,15,20,'1986-11-14',22,3),
(7,19,206,81,'1987-05-13',5,12),
(8,30,140,224,'1982-12-01',20,2),
(9,22,3,130,'1985-05-05',39,11),
(10,37,23,125,'1980-10-09',7,3),
(11,13,184,27,'1981-01-02',31,1),
(12,32,215,77,'1987-08-12',37,19),
(13,8,102,141,'1988-06-30',40,0),
(14,18,181,74,'1981-06-17',21,6),
(15,8,211,180,'1989-10-31',12,5),
(16,6,200,31,'1981-09-04',15,22),
(17,39,171,140,'1980-06-07',1,3),
(18,16,160,85,'1989-06-12',17,15),
(19,34,0,208,'1980-11-24',7,6),
(20,38,156,138,'1987-11-04',14,23),
(21,9,126,52,'1989-04-20',23,1),
(22,19,211,204,'1986-01-23',10,21),
(23,6,222,154,'1987-08-31',21,0),
(24,4,85,140,'1984-05-21',27,17),
(25,21,62,150,'1989-05-24',3,13),
(26,30,186,73,'1987-11-28',6,19),
(27,35,83,113,'1985-11-18',9,3),
(28,6,180,23,'1983-02-02',14,8),
(29,22,222,152,'1985-11-07',2,2),
(30,27,16,204,'1989-02-06',36,7),
(31,20,48,98,'1982-08-22',40,2),
(32,39,145,81,'1989-07-11',34,20),
(33,40,56,147,'1982-05-31',38,9),
(34,13,61,61,'1987-08-15',4,11);

-- Usen dateset: https://www.kaggle.com/mylesoneill/world-university-rankings?select=cwurData.csv
insert into university(uid,name_,founded_in,rating,about) VALUES
(0,'Ukrainian Catholic University','1929-10-06',0,'The best of the best'),
(1,'Harvard University','1616-12-07',1,'Very interesting and nice university - Harvard University'),
(2,'Massachusetts Institute of Technology','1691-01-17',2,'Very interesting and nice university - Massachusetts Institute of Technology'),
(3,'Stanford University','1720-08-01',3,'Very interesting and nice university - Stanford University'),
(4,'University of Cambridge','1608-03-01',4,'Very interesting and nice university - University of Cambridge'),
(5,'California Institute of Technology','1897-08-01',5,'Very interesting and nice university - California Institute of Technology'),
(6,'Princeton University','1637-07-10',6,'Very interesting and nice university - Princeton University'),
(7,'University of Oxford','1637-08-29',7,'Very interesting and nice university - University of Oxford'),
(8,'Yale University','1739-10-24',8,'Very interesting and nice university - Yale University'),
(9,'Columbia University','1782-09-26',9,'Very interesting and nice university - Columbia University'),
(10,'University of California, Berkeley','1870-09-24',10,'Very interesting and nice university - University of California, Berkeley'),
(11,'University of Chicago','1628-07-25',11,'Very interesting and nice university - University of Chicago'),
(12,'Cornell University','1725-12-21',12,'Very interesting and nice university - Cornell University'),
(13,'University of Pennsylvania','1741-01-24',13,'Very interesting and nice university - University of Pennsylvania'),
(14,'University of Tokyo','1656-12-31',14,'Very interesting and nice university - University of Tokyo'),
(15,'Johns Hopkins University','1678-08-13',15,'Very interesting and nice university - Johns Hopkins University'),
(16,'Swiss Federal Institute of Technology in Zurich','1669-06-02',16,'Good university - Swiss Federal Institute of Technology in Zurich'),
(17,'Kyoto University','1725-08-18',17,'Very interesting and nice university - Kyoto University'),
(18,'Weizmann Institute of Science','1651-03-30',18,'Very interesting and nice university - Weizmann Institute of Science'),
(19,'University of California, Los Angeles','1678-08-12',19,'Very interesting and nice university - University of California, Los Angeles'),
(20,'University of California, San Diego','1704-01-31',20,'Very interesting and nice university - University of California, San Diego'),
(21,'Rockefeller University','1635-04-06',21,'Very interesting and nice university - Rockefeller University'),
(22,'Hebrew University of Jerusalem','1767-02-12',22,'Very interesting and nice university - Hebrew University of Jerusalem'),
(23,'New York University','1793-08-06',23,'Very interesting and nice university - New York University'),
(24,'University of California, San Francisco','1631-09-27',24,'Very interesting university - University of California, San Francisco');

-- 6 update phones for 3 students
select * from student;
update student 
set phone='+380961233212'
where sid=3;

update student 
set phone='+380969009900'
where fname='Timothy';

update student 
set phone='+380960000000'
where phone='+380926717386';

-- 7 select all girls
select * from student where gender=false;

-- 8 older then 18
select * from student
where extract(year from age(birth_date)) > 18;

-- 9 first 10 ordered by lname and fname
select * from student 
order by lname, fname
limit 10;

-- 10 delete all records
truncate table student;
truncate table migration;
truncate table university;

-- 11 delete all tables
drop table if exists student;
drop table if exists migration;
drop table if exists university;

-- 12 delete database
drop database if exists university;