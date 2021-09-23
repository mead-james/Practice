-- SQLite syntax

-- INSTRUCTORS
INSERT INTO user VALUES(000,NULL,200,"Pierre","Bezukhov",
    "M","1964-04-25","pierre.bezukhov@school.edu");
INSERT INTO instructor VALUES(200,"1998-01-27",82000);

INSERT INTO user VALUES(001,NULL,201,"Jane","Eyre",
    "F","1977-12-18","jane.eyre@school.edu");
INSERT INTO instructor VALUES(201,"1993-06-02",94000);

INSERT INTO user VALUES(002,NULL,202,"Victor","Frankenstein",
    "M","1972-03-13","victor.frankenstein@school.edu");
INSERT INTO instructor VALUES(202,"2003-11-23",52000);

INSERT INTO user VALUES(003,NULL,203,"Edmond","Dantes",
    "M","1981-07-08","edmond.dantes@school.edu");
INSERT INTO instructor VALUES(203,"2007-07-30",46000);

INSERT INTO user VALUES(004,NULL,204,"Jo","March",
    "F","1968-08-29","jo.march@school.edu");
INSERT INTO instructor VALUES(204,"2004-04-21",73000);

INSERT INTO user VALUES(005,NULL,205,"Elizabeth","Bennet",
    "F","1962-03-27","elizabeth.bennet@school.edu");
INSERT INTO instructor VALUES(205,"2011-07-14",57000);

INSERT INTO user VALUES(006,NULL,206,"Don","Quixote",
    "M","1953-02-14","don.quixote@school.edu");
INSERT INTO instructor VALUES(206,"1992-02-28",79000);

-- COURSES
INSERT INTO course VALUES(1000,100,"ENGL","Craft of Writing",206,3.0);
INSERT INTO course VALUES(1001,100,"ENGL","Craft of Writing",204,3.0);
INSERT INTO course VALUES(1010,101,"RUSS","Essential Russian",200,2.0);
INSERT INTO course VALUES(1020,102,"SOC","Research Methods",203,3.0);
INSERT INTO course VALUES(1030,103,"PHIL","Theory of Knowledge",201,3.0);
INSERT INTO course VALUES(1040,104,"ECON","Principles of Microeconomics",204,3.0);
INSERT INTO course VALUES(2050,205,"CSIT","Computer Science I",202,3.0);
INSERT INTO course VALUES(2060,206,"BIOL","Genetics",202,3.0);
INSERT INTO course VALUES(3070,307,"PHIL","Philosophy of Religion",206,3.0);
INSERT INTO course VALUES(4080,408,"GEO","Thesis Research",201,4.0);
INSERT INTO course VALUES(4090,409,"COMM","Communication Law and Ethics",204,3.0);

-- STUDENTS
INSERT INTO user VALUES(007,100,NULL,"Nikolai","Rostov",
    "M","1999-11-02","nikolai.rostov@school.edu");
INSERT INTO student VALUES(100,"2018-08-27", NULL);

INSERT INTO user VALUES(008,101,NULL,"Milo","Minderbender",
    "M","2001-03-07","milo.minderbender@school.edu");
INSERT INTO student VALUES(101,"2020-08-24", NULL);

INSERT INTO user VALUES(009,102,NULL,"Hester","Prynne",
    "F","2001-03-28","hester.prynne@school.edu");
INSERT INTO student VALUES(102,"2019-08-24", NULL);

INSERT INTO user VALUES(010,103,NULL,"Philip","Marlowe",
    "M","2000-06-17","philip.marlowe@school.edu");
INSERT INTO student VALUES(103,"2019-08-24", NULL);

INSERT INTO user VALUES(011,104,NULL,"Joseph","K",
    "M","1999-09-11","joseph.k@school.edu");
INSERT INTO student VALUES(104,"2018-08-27", NULL);

INSERT INTO user VALUES(012,105,NULL,"Esther","Greenwood",
    "F","2001-04-04","esther.greenwood@school.edu");
INSERT INTO student VALUES(105,"2019-08-24", NULL);

INSERT INTO user VALUES(013,106,NULL,"Alia","Atreides",
    "F","2000-10-19","alia.atreides@school.edu");
INSERT INTO student VALUES(106,"2018-08-27", NULL);

INSERT INTO user VALUES(014,107,NULL,"Scout","Finch",
    "F","2002-12-02","scout.finch@school.edu");
INSERT INTO student VALUES(107,"2021-09-02", NULL);

-- STUDENT ENROLLMENTS
INSERT INTO student_enrollment VALUES(100,1020,"2021-09-02","2021-12-17","B-",1);
INSERT INTO student_enrollment VALUES(100,2060,"2021-09-02","2021-12-17","A",1);
INSERT INTO student_enrollment VALUES(100,1040,"2021-09-02","2021-12-17","B",1);
INSERT INTO student_enrollment VALUES(101,3070,"2021-02-04","2021-06-21","A-",1);
INSERT INTO student_enrollment VALUES(101,4080,"2021-09-02","2021-12-17","C",1);
INSERT INTO student_enrollment VALUES(102,1020,"2021-09-02","2021-12-17","A",1);
INSERT INTO student_enrollment VALUES(102,2050,"2021-09-02","2021-12-17","C+",1);
INSERT INTO student_enrollment VALUES(103,3070,"2021-02-04","2021-06-21","P",0);
INSERT INTO student_enrollment VALUES(103,2050,"2021-09-02","2021-12-17","B-",1);
INSERT INTO student_enrollment VALUES(104,4090,"2021-02-04","2021-06-21","A",1);
INSERT INTO student_enrollment VALUES(105,2060,"2021-09-02","2021-12-17","B",1);
INSERT INTO student_enrollment VALUES(105,1000,"2021-02-04","2021-06-21","A-",1);
INSERT INTO student_enrollment VALUES(106,1000,"2021-09-02","2021-12-17","C-",1);
INSERT INTO student_enrollment VALUES(106,1030,"2021-02-04","2021-06-21","A",1);
INSERT INTO student_enrollment VALUES(107,1001,"2021-09-02","2021-12-17","B+",1);
INSERT INTO student_enrollment VALUES(107,1010,"2021-09-02","2021-12-17","A",1);
