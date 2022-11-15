select salary
from employees
where first_name='Den';

select employee_id, first_name, salary
from employees
where salary = (select salary 
                from employees 
                where first_name='Den');

select employee_id, first_name, salary
from employees
where salary > (select salary 
                from employees 
                where first_name='Den');
           
-- 급여를 가장 적게 받는 사람의 이름, 급여, 사원번호는?     
select first_name, salary, employee_id
from employees
where salary = (select min(salary)
                from employees);
                
--평균 급여보다 적게 받는 사람의 이름, 급여를 출력하세요
select first_name, salary
from employees
where salary < (select avg(salary)
                from employees);
                
select first_name, salary
from employees
where salary in (select salary
                 from employees
                 where department_id = 110);
                 
select first_name, salary
from employees
where salary > any (select salary
                    from employees
                    where department_id = 110);
                    
select first_name, salary
from employees
where salary > all (select salary
                    from employees
                    where department_id = 110);                

select department_id, first_name, salary
from employees 
where (department_id, salary) in (select department_id, max(salary)
                                  from employees
                                  group by department_id);

select e.department_id, e.employee_id, e.first_name, e.salary
from employees e, (select department_id, max(salary) salary
                   from employees
                   group by department_id) s 
where e.department_id = s.department_id
and e.salary = s.salary;


--1. 평균 급여보다 적은 급여을 받는 직원은 몇 명이나 있습니까?
select count(first_name)
from employees
where salary < (select avg(salary) 
                  from employees);
                  
--3. 각 업무(job) 별로 급여(salary)의 총합을 구하고자 합니다. 급여 총합이 가장 높은 업무부터 업무명(job_title)과 급여 총합을 조회하시오 
select e.job_id, sum(e.salary)
from employees e
group by job_id;

select j.job_title, salary
from jobs j, (select job_id, sum(salary) salary
        from employees
        group by job_id) e
where e.job_id = j.job_id
order by salary desc;

select j.job_title, sum(e.salary) 
from employees e, jobs j
where e.job_id = j.job_id
group by j.job_title
order by 2 desc;


--4.자신의 부서 평균 급여보다 급여(salary)가 많은 직원의 직원번호(employee_id), 성(last_name)과 급여(salary)을 조회하세요 
select e.employee_id, e.last_name, e.salary, a.salary
from employees e, (select department_id, avg(salary) salary
                    from employees e
                    group by department_id) a
where e.department_id = a.department_id
and e.salary > a.salary;

-----------------

select 
    rownum, 
    first_name, 
    salary
from employees ;


select 
    rownum, 
    first_name, 
    salary
from employees
order by salary desc;

select 
    rownum,
    first_name,
    salary
from (  select first_name, 
        salary
        from employees
        order by salary desc  ) ;
        

select 
    rownum,
    first_name,
    salary
from (  select first_name, 
        salary
        from employees
        order by salary desc  )
where rownum <= 10 ; 

select 
    rn, 
    first_name, 
    salary
from (select rownum rn, 
             first_name,
             salary 
from (select first_name, 
             salary
      from employees
      order by salary desc)
)
where rn >= 11
and rn <= 20;


--1.문제1. 가장 늦게 입사한 직원의 이름(first_name last_name)과 연봉(salary)과 근무하는 부서 이름(department_name)은?
select 
    e.first_name || ' ' || e.last_name,
    e.salary * 12,
    d.department_name,
    e.hire_date
from employees e, departments d
where e.department_id = d.department_id
and e.hire_date = (select 
                        max(hire_date)
                   from employees);

--2.평균급여(salary)가 가장 높은 부서 직원들의 직원번호(employee_id), 이름(first_name), 성(last_name)과 업무(job_title), 급여(salary) 을 조회하시오.
-- ex2.
-- 평균급여(salary)가 가장 높은 부서 
-- 직원들의 직원번호(employee_id), 이름(first_name), 성(last_name)과 
-- 업무(job_title), 급여(salary)를 조회하시오.
-- 1. 부서별 평균
SELECT e.DEPARTMENT_ID , avg(e.SALARY)
FROM EMPLOYEES e 
GROUP BY e.DEPARTMENT_ID ;
-- 2. 부서별 평균의 최대
SELECT max( avg(e.SALARY) ) 
FROM EMPLOYEES e 
GROUP BY e.DEPARTMENT_ID ;
-- 3. 부서별 평균이 최대인 부서
SELECT e.DEPARTMENT_ID , avg(e.SALARY)
FROM EMPLOYEES e 
GROUP BY e.DEPARTMENT_ID 
HAVING avg(e.SALARY) = (SELECT max( avg(SALARY) ) 
						FROM EMPLOYEES 
						GROUP BY DEPARTMENT_ID);
-- 4. Join
SELECT e.EMPLOYEE_ID , e.FIRST_NAME , e.LAST_NAME , j.JOB_TITLE , e.SALARY , e.DEPARTMENT_ID 
FROM EMPLOYEES e , 
     JOBS j ,
     (SELECT e.DEPARTMENT_ID , avg(e.SALARY)
		FROM EMPLOYEES e 
		GROUP BY e.DEPARTMENT_ID 
		HAVING avg(e.SALARY) = (SELECT max( avg(SALARY) ) 
								FROM EMPLOYEES 
								GROUP BY DEPARTMENT_ID)
	 ) ma_dept
WHERE e.JOB_ID = j.JOB_ID 
AND   e.DEPARTMENT_ID = ma_dept.DEPARTMENT_ID;
-- 검증 
SELECT * FROM EMPLOYEES e WHERE e.DEPARTMENT_ID = 90;

--3. 평균 급여(salary)가 가장 높은 부서는? 
--select d.department_name
--from employees e, departments d, (select e.department_id from employees e order by salary desc)
--where e.department_id = d.department_id and rownum = 1;

select d.department_name, a.avg_salary
from departments d,
     (select avg(salary) avg_salary, department_id
      from employees
      group by department_id) a
where d.department_id = a.department_id      
and a.avg_salary = (select max(avg(salary)) max_salary
                   from employees
                   group by department_id);

