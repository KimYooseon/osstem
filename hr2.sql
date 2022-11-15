select count(*), count(commission_pct)
from employees;

select count(commission_pct)
from employees;

select count(*)
from employees
where salary > 16000;

select count(*), sum(salary)
from employees;

select count(*), sum(salary), avg(salary)
from employees;

select count(*), sum(salary), avg(nvl(salary,0))
from employees;

select department_id, avg(salary)
from employees
group by department_id
order by department_id;

select department_id, count(*), sum(salary)
from employees
group by department_id;

--Group by에 참여한 컬럼이나 그룹함수만 올 수 있다.
--select department_id, job_id, count(*), sum(salary)
--from employees
--group by department_id;

select department_id, job_id, count(*), sum(salary)
from employees
group by department_id, job_id
order by 1;

--연봉(salary)의 합계가 20000 이상인 부서의 부서 번호와 , 인원수, 급여합계를 출력하세요
select department_id, count(*), sum(salary)
from employees
--where sum(salary) > 20000 =>where절은 group by 절 이전에 올 수 X. having절로 표현해야함
group by department_id
having sum(salary) > 20000;

select department_id, count(*), sum(salary)
from employees
group by department_id
having sum(salary) > 20000
and department_id = 100;

--1
select max(salary)-min(salary) "최고임금 - 최저임금" from employees;

--2
select max(to_char(hire_date, 'YYYY"년"MM"월"DD"일"')) from employees;

--3
select  department_id,
        avg(nvl(salary, 0)), 
        max(salary), 
        min(salary) 
from employees 
group by department_id
order by department_id desc;

--4
select job_id, avg(salary), max(salary), min(salary) 
from employees 
group by job_id 
order by job_id desc;

--5
select to_char(min(hire_date), 'YYYY"년" MM"월" DD"일"')
from employees;

--6
select department_id , nvl(avg(salary), 0), min(salary), nvl(avg(salary), 0)-min(salary)
from employees
group by department_id
having avg(salary)-min(salary)<2000
order by avg(salary)-min(salary) desc;

--7
select job_id, max(salary), min(salary), max(salary)-min(salary)
from employees
group by job_id
order by max(salary)-min(salary) desc;

-------
SELECT employee_id,
        salary,
        CASE WHEN job_id = 'AC_ACOOUNT' THEN salary + salary * 0.1
             WHEN job_id = 'AC_MGR' THEN salary + salary * 0.2
             ELSE salary
        END job_id
FROM employees;


--직원의 이름, 부서, 팀을 출력하세요
--팀은 부서코드로 결정하며 부서코드가 10~50 이면 ‘A-TEAM’
--60~100이면 ‘B-TEAM’ 110~150이면 ‘C-TEAM’ 나머지는 ‘팀없음’ 으로 출력하세요
select * from departments;
select * from employees;

-- 팀은 부서코드로 결정하며 
-- 부서코드가 10~50 이면 ‘A-TEAM’
-- 60~100이면 ‘B-TEAM’  
-- 110~150이면 ‘C-TEAM’ 
-- 나머지는 ‘팀없음’ 으로 출력하세요
select first_name, department_id,
    case when department_id >= 10 and department_id<=50 then 'A-TEAM'
        when department_id >= 60 and department_id<=100 then 'B-TEAM'
        when department_id >= 110 and department_id<=150 then 'C-TEAM'
        else '팀 없음'
END "팀"
from employees;
     

select count(*) from employees, departments;


select * from employees;
select * from jobs;
select * from departments;


select e.first_name, j.job_id, j.job_title
from employees e, jobs j
where e.job_id = j.job_id;

--모든 직원이름, 부서이름, 업무명 을 출력하세요
select e.first_name, d.department_name, j.job_title
from employees e, departments d, jobs j
where e.job_id = j.job_id and e.department_id = d.department_id;

select emp.first_name, mgr.first_name, emp.manager_id, mgr.employee_id
from employees emp, employees mgr
where emp.manager_id = mgr.employee_id;

--NULL도 포함하게 만들고 싶을 때는 NULL이 올 수 있는 쪽 조건에 (+)를 붙인다
select e.first_name, d.department_name, j.job_title
from employees e, departments d, jobs j
where e.job_id = j.job_id and e.department_id = d.department_id (+);

select e.department_id, e.first_name, d.department_name
from employees e left outer join departments d
on e.department_id = d.department_id ; 

select e.department_id, e.first_name, d.department_name
from employees e, departments d
where e.department_id = d.department_id(+) ; 


select *
from DEPARTMENTS d;

select e.department_id, e.first_name, d.department_name 
from employees e right outer join departments d
on e.department_id = d.department_id;

select e.department_id, e.first_name, d.department_name
from employees e full outer join departments d
on e.department_id = d.department_id ; 

select * from employees;

--1.각 사원(employee)에 대해서 사번(employee_id), 이름(first_name), 부서명(department_name), 매니저(manager)의 이름(first_name)을 조회하세요.
select emp.employee_id, emp.first_name, dep.department_name, mgr.first_name
from employees emp, employees mgr, departments dep
where emp.manager_id = mgr.employee_id and emp.department_id = dep.department_id;

SELECT
   e.EMPLOYEE_ID "사번",
   e.FIRST_NAME "이름",
   d.DEPARTMENT_NAME "부서명",
   m.FIRST_NAME "매니저 이름"
FROM
   EMPLOYEES e ,
   DEPARTMENTS d ,
   EMPLOYEES m
WHERE
   e.DEPARTMENT_ID = d.DEPARTMENT_ID
   AND e.MANAGER_ID = m.EMPLOYEE_ID ;
   
--2.지역(regions)에 속한 나라들을 지역이름(region_name), 나라이름(country_name)으로 출력하되 지역이름, 나라이름 순서대로 내림차순으로 정렬하세요.
SELECT * FROM regions;

SELECT
    r.region_name,
    c.country_name
FROM
    regions r,
    countries c
WHERE
    r.region_id = c.region_id
ORDER BY
    r.region_name desc, c.country_name desc;

--3.각 부서(department)에 대해서 부서번호(department_id), 부서이름(department_name), 매니저(manager)의 이름(first_name), 위치(locations)한 도시(city), 나라(countries)의 이름(countries_name) 그리고 지역구분(regions)의 이름(region_name)까지 전부 출력해 보세요.
select * from departments;
select * from locations;
select * from countries;
select * from regions;

SELECT 
    d.department_id,
    d.department_name,
    e.first_name,
    l.city,
    c.country_name,
    r.region_name
FROM
    departments d,
    employees e,
    locations l,
    countries c,
    regions r
WHERE
    d.manager_id = e.employee_id 
    and d.location_id = l.location_id 
    and l.country_id = c.country_id
    and c.region_id = r.region_id;
    
        
--4.‘Public Accountant’의 직책(job_title)으로 과거에 근무한 적이 있는 모든 사원의 사번과 이름을 출력하세요. (현재 ‘Public Accountant’의 직책(job_title)으로 근무하는 사원은 고려하지 않습니다.) 이름은 first_name과 last_name을 합쳐 출력합니다.
select * from job_history;
select * from employees;
select * from jobs;

SELECT
    e.employee_id,
    e.first_name || ' ' || e.last_name
FROM
    employees e,
    job_history jh,
    jobs j
WHERE
    j.job_id = jh.job_id
    and jh.employee_id = e.employee_id
    and j.job_title = 'Public Accountant';

--5.직원들의 사번(employee_id), 이름(first_name), 성(last_name)과 부서 이름(department_name)을 조회하여 성(last_name)순서로 오름차순 정렬하세요
select * from employees;

SELECT
    e.employee_id,
    e.first_name, 
    e.last_name, 
    d.department_name
FROM
    employees e, 
    departments d
WHERE e.department_id = d.department_id
ORDER BY last_name;


--6. 자신의 매니저보다 채용일(hire_date)이 빠른 사원의 사번(employee_id), 성(last_name)과 채용일(hire_date)을 조회하세요 
SELECT 
    e.employee_id,
    e.last_name,
    e.hire_date
FROM
    employees e,
    employees m
WHERE
    e.manager_id = m.employee_id
    and e.hire_date < m.hire_date;