SELECT *
FROM EMPLOYEES e
WHERE DEPARTMENT_ID = 50;

CREATE OR REPLACE VIEW emp_v1 AS
SELECT *
FROM EMPLOYEES e
WHERE DEPARTMENT_ID = 50;

SELECT *
FROM emp_v1;

SELECT * FROM emp_v1
WHERE salary > 2500;


CREATE OR REPLACE VIEW emp_v2 AS
SELECT e.EMPLOYEE_ID, e.FIRST_NAME, e.LAST_NAME, e.SALARY
FROM EMPLOYEES e
WHERE DEPARTMENT_ID = 10
UNION
SELECT e.EMPLOYEE_ID, e.FIRST_NAME, e.LAST_NAME, e.SALARY
FROM EMPLOYEES e
WHERE DEPARTMENT_ID = 20;

SELECT * FROM emp_v2;

SELECT * FROM EMPLOYEES e WHERE e.DEPARTMENT_ID IN (10,20);

SELECT * from employees;

------------------------------

SELECT a.employee_id, a.first_name, b.department_name
FROM employees a, departments b
WHERE a.department_id = b.department_id;

SELECT * 
from employees
where department_id is null;

SELECT * 
from employees
where employee_id = 178;

SELECT *
FROM EMPLOYEES e, DEPARTMENTS d, LOCATIONS l
WHERE e.DEPARTMENT_ID = d.DEPARTMENT_ID
AND d.LOCATION_ID = l.LOCATION_ID;

SELECT * 
from employees
where department_id is null;

SELECT * 
from employees
where department_id is null;

SELECT e.employee_id, e.first_name, d.department_name 
FROM employees e, departments d
where e.department_id = d.department_id;

SELECT /*+ use_merge(e,d) */
    e.employee_id, e.first_name, d.department_name 
FROM employees e, departments d
where e.department_id = d.department_id;

