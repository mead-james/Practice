-- SQLite syntax
CREATE TABLE user(
    user_id INT PRIMARY KEY,
    student_id INT,
    instructor_id INT,
    first_name VARCHAR(30) NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    gender CHAR(1) NOT NULL,
    birth_date CHAR(10) NOT NULL,
    email VARCHAR(30)
);

CREATE TABLE student(
    student_id INT PRIMARY KEY,
    enrolled_date CHAR(10) NOT NULL,
    gpa DECIMAL(3,2),
    CONSTRAINT fk_student_user
        FOREIGN KEY (student_id) REFERENCES user(student_id)
        ON DELETE CASCADE
);

CREATE TABLE instructor(
    instructor_id INT PRIMARY KEY,
    hire_date CHAR(10) NOT NULL,
    salary INT,
    CONSTRAINT fk_instructor_user
        FOREIGN KEY (instructor_id) REFERENCES user(instructor_id)
        ON DELETE CASCADE
);

CREATE TABLE course(
    crn INT PRIMARY KEY,
    course_id INT NOT NULL,
    dept VARCHAR(30) NOT NULL,
    course_name VARCHAR(30) NOT NULL,
    instructor_id INT,
    credit_hrs DECIMAL(3,1) NOT NULL,
    CONSTRAINT fk_course_instructor
        FOREIGN KEY (instructor_id) REFERENCES instructor(instructor_id)
        ON DELETE SET NULL
);

CREATE TABLE student_enrollment(
    student_id INT,
    crn INT,
    start_date CHAR(10) NOT NULL,
    end_date CHAR(10) NOT NULL,
    course_grade VARCHAR(2) NOT NULL,
    counts_toward_gpa BOOLEAN NOT NULL DEFAULT 1,
    PRIMARY KEY(student_id, crn),
    CONSTRAINT fk_student_enrollment_student
        FOREIGN KEY (student_id) REFERENCES student(student_id)
        ON DELETE CASCADE,
    CONSTRAINT fk_student_enrollment_course
        FOREIGN KEY (crn) REFERENCES course(crn)
        ON DELETE CASCADE
);