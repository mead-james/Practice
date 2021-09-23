## Overview

CRUD application allows user to add, view, modify, and remove students, instructors, and courses in a basic school information system. Creates and manipulates its own database with sample data preloaded.

### Features

User can:
    - View student info
    - View instructor info
    - View course info
    - Add/modify/remove student
    - Add/modify/remove instructor
    - Add/modify/remove course
    - Enroll/modify/remove student in course

## Purpose

Application created to practice SQLite, database design, Java, OOP, and GUI programming.

## Files Overview

App.java is used to trigger the application.

DBManager.java connects to the database and runs SQL queries.

UserGUI.java allows the user to interact with the database through a GUI.

Utils.java stores helper methods.
    - .sql file reader (splits .sql into multiple queries to run)
    - GPA calculator (converts matrix of grades/credit hrs into GPA)

## Dependencies

Application uses sqlite-jdbc-3.36.0.3 to connect to its SQLite database ("StudentSQLite_Practice.db").