SELECT * FROM EMPLOYEES;

SELECT * FROM DEPARTMENTS d;

SELECT employee_id, first_name, last_name from employees;

SELECT * from employees;

SELECT first_name, 
       phone_number, 
       hire_date, 
       salary 
from employees;

--사원의 이름(first_name)과 성(last_name), 급여, 전화번호, 이메일, 입사일을 출력하세요
SELECT first_name "이름",
       last_name "성",
       salary "급여",
       phone_number "전화번호", 
       email "이메일",
       hire_date "입사일"        
from employees;

select first_name || ' hire date is ' || hire_date
from employees;


select first_name, salary, salary*12, (salary+300)*12
from employees;

select concat(concat(first_name, '-'), last_name) "성명",
        salary "급여",
        salary*12 "연봉",
        salary*12 + 5000 "연봉2", phone_number "전화번호"
from employees;


select first_name, salary, salary*12
from employees
where salary >= 15000;


select first_name, hire_date from employees where hire_date >= '07/01/01';

select to_char(hire_date, 'yy/mm/dd')
from employees;

SELECT salary*12 FROM EMPLOYEES 
WHERE FIRST_NAME = 'Lex';

select first_name, salary*12
from employees
where salary <= 14000 
or salary >= 17000;


select first_name, hire_date 
from employees 
where hire_date >= '04/01/01' and hire_date <= '05/12/31';

select first_name, salary
from employees
where salary between 14000 and 17000;

select first_name, salary
from employees
where salary >= 14000 
and salary <= 17000;

select first_name, last_name, salary
from employees
where first_name in ('Neena', 'Lex', 'John');

select first_name, last_name, salary
from employees
where first_name in ('Neena', 'Lex', 'John');

select first_name, last_name, salary
from employees
where first_name like 'L%';

select first_name, last_name, salary*12
from employees
where first_name like '_a%';

select first_name, salary, commission_pct
from employees
where commission_pct is null;

select first_name, salary, commission_pct
from employees
where commission_pct is NOT null;

select first_name
from employees
where manager_id is null;

select * from employees;

select first_name, salary
from employees
order by salary;

select DEPARTMENT_ID, salary, first_name || ' ' || last_name
from employees
order by DEPARTMENT_ID asc;

select first_name || ' ' || last_name, salary 
from employees
where salary >= 5000
order by 1 desc;

select DEPARTMENT_ID, salary, first_name || ' ' || last_name 
from employees
order by DEPARTMENT_ID asc, salary desc;

select email, initcap(email), department_id
from employees
where department_id = 100;

select INITCAP('apple') from dual;
select LOWER('APPLE') from dual;
select UPPER('apple') from dual;

select first_name, 
lpad(first_name, 10,'*'), 
rpad(first_name,4,'*')
from employees;


SELECT sysdate FROM dual;

select months_between(sysdate, hire_date) 
from employees
where department_id = 110;

select first_name, to_char(salary*12, '$999,999.99') "SAL"
from employees
where department_id =110;

select sysdate, to_char(sysdate, 'YYYY--MM-DD HH24:MI:SS')
from dual;

select sysdate, to_char(sysdate, 'YYYY"년" MM"월" DD"일" HH24"시" MI"분" SS"초"')
from dual;


--문제
--1
select first_name || ' ' || last_name "이름", salary "월급", phone_number "전화번호", hire_date "입사일"
from employees
order by hire_date;

--2
select job_id, salary
from employees
order by salary DESC;

--3
select first_name || ' ' || last_name "이름",
        manager_id "매니저 아이디", commission_pct "커미션 비율", salary "월급"
from employees
where manager_id is not null and salary > 3000;

--4
select job_title, max_salary
from jobs
order by max_salary DESC;

--5
select first_name || ' ' || last_name "이름", salary, nvl(commission_pct,0)
from employees
where salary < 14000 and salary >= 10000
order by salary DESC;


--6
select first_name || ' ' || last_name "이름", salary, 
to_char(hire_date, 'YYYY-MM'), department_id from employees
where department_id = 10 or department_id = 90 or department_id = 100;

--7
--select first_name, salary from employees where first_name like '%S%' or first_name like  '%s%';
select first_name, salary from employees where UPPER(first_name) like '%S%'; --시간을 단축할 수 있음

--8
select department_name from departments order by length(department_name) desc;

--9
--select UPPER(country_name) from countries; 
select distinct location_id from departments; --distinct를 통해 중복제거. 자주쓰임
select *from locations where location_id in(1800, 2400, 1400, 2500, 1700, 2700, 1500);

select UPPER(country_name) from countries 
where country_id in ('US', 'CA', 'DE', 'UK')
order by 1;

--10
--select first_name, salary, to_char(phone_number, '999-999-9999'), hire_date 
-- 이거는 그냥 숫자가 아니라서 사용할 수 X. 010.2222.1213 같이 이미 문자열이지 숫자가 아님
--from employees  where hire_date < '03/12/31';

select first_name, salary, replace(phone_number, '.', '-'), hire_date 
from employees  where hire_date < '03/12/31';

--숫자는 잘 되는지 확인해보기
select first_name, to_char(salary,'999,999,999'), hire_date 
from employees  where hire_date < '03/12/31';
--잘 됨!!

select * from employees;
select * from departments;
select * from countries;
