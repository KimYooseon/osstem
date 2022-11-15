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
           
-- �޿��� ���� ���� �޴� ����� �̸�, �޿�, �����ȣ��?     
select first_name, salary, employee_id
from employees
where salary = (select min(salary)
                from employees);
                
--��� �޿����� ���� �޴� ����� �̸�, �޿��� ����ϼ���
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


--1. ��� �޿����� ���� �޿��� �޴� ������ �� ���̳� �ֽ��ϱ�?
select count(first_name)
from employees
where salary < (select avg(salary) 
                  from employees);
                  
--3. �� ����(job) ���� �޿�(salary)�� ������ ���ϰ��� �մϴ�. �޿� ������ ���� ���� �������� ������(job_title)�� �޿� ������ ��ȸ�Ͻÿ� 
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


--4.�ڽ��� �μ� ��� �޿����� �޿�(salary)�� ���� ������ ������ȣ(employee_id), ��(last_name)�� �޿�(salary)�� ��ȸ�ϼ��� 
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


--1.����1. ���� �ʰ� �Ի��� ������ �̸�(first_name last_name)�� ����(salary)�� �ٹ��ϴ� �μ� �̸�(department_name)��?
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

--2.��ձ޿�(salary)�� ���� ���� �μ� �������� ������ȣ(employee_id), �̸�(first_name), ��(last_name)�� ����(job_title), �޿�(salary) �� ��ȸ�Ͻÿ�.
-- ex2.
-- ��ձ޿�(salary)�� ���� ���� �μ� 
-- �������� ������ȣ(employee_id), �̸�(first_name), ��(last_name)�� 
-- ����(job_title), �޿�(salary)�� ��ȸ�Ͻÿ�.
-- 1. �μ��� ���
SELECT e.DEPARTMENT_ID , avg(e.SALARY)
FROM EMPLOYEES e 
GROUP BY e.DEPARTMENT_ID ;
-- 2. �μ��� ����� �ִ�
SELECT max( avg(e.SALARY) ) 
FROM EMPLOYEES e 
GROUP BY e.DEPARTMENT_ID ;
-- 3. �μ��� ����� �ִ��� �μ�
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
-- ���� 
SELECT * FROM EMPLOYEES e WHERE e.DEPARTMENT_ID = 90;

--3. ��� �޿�(salary)�� ���� ���� �μ���? 
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

