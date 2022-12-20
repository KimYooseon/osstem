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

--Group by�� ������ �÷��̳� �׷��Լ��� �� �� �ִ�.
--select department_id, job_id, count(*), sum(salary)
--from employees
--group by department_id;

select department_id, job_id, count(*), sum(salary)
from employees
group by department_id, job_id
order by 1;

--����(salary)�� �հ谡 20000 �̻��� �μ��� �μ� ��ȣ�� , �ο���, �޿��հ踦 ����ϼ���
select department_id, count(*), sum(salary)
from employees
--where sum(salary) > 20000 =>where���� group by �� ������ �� �� X. having���� ǥ���ؾ���
group by department_id
having sum(salary) > 20000;

select department_id, count(*), sum(salary)
from employees
group by department_id
having sum(salary) > 20000
and department_id = 100;

--1
select max(salary)-min(salary) "�ְ��ӱ� - �����ӱ�" from employees;

--2
select max(to_char(hire_date, 'YYYY"��"MM"��"DD"��"')) from employees;

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
select to_char(min(hire_date), 'YYYY"��" MM"��" DD"��"')
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


--������ �̸�, �μ�, ���� ����ϼ���
--���� �μ��ڵ�� �����ϸ� �μ��ڵ尡 10~50 �̸� ��A-TEAM��
--60~100�̸� ��B-TEAM�� 110~150�̸� ��C-TEAM�� �������� ���������� ���� ����ϼ���
select * from departments;
select * from employees;

-- ���� �μ��ڵ�� �����ϸ� 
-- �μ��ڵ尡 10~50 �̸� ��A-TEAM��
-- 60~100�̸� ��B-TEAM��  
-- 110~150�̸� ��C-TEAM�� 
-- �������� ���������� ���� ����ϼ���
select first_name, department_id,
    case when department_id >= 10 and department_id<=50 then 'A-TEAM'
        when department_id >= 60 and department_id<=100 then 'B-TEAM'
        when department_id >= 110 and department_id<=150 then 'C-TEAM'
        else '�� ����'
END "��"
from employees;
     

select count(*) from employees, departments;


select * from employees;
select * from jobs;
select * from departments;


select e.first_name, j.job_id, j.job_title
from employees e, jobs j
where e.job_id = j.job_id;

--��� �����̸�, �μ��̸�, ������ �� ����ϼ���
select e.first_name, d.department_name, j.job_title
from employees e, departments d, jobs j
where e.job_id = j.job_id and e.department_id = d.department_id;

select emp.first_name, mgr.first_name, emp.manager_id, mgr.employee_id
from employees emp, employees mgr
where emp.manager_id = mgr.employee_id;

--NULL�� �����ϰ� ����� ���� ���� NULL�� �� �� �ִ� �� ���ǿ� (+)�� ���δ�
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

--1.�� ���(employee)�� ���ؼ� ���(employee_id), �̸�(first_name), �μ���(department_name), �Ŵ���(manager)�� �̸�(first_name)�� ��ȸ�ϼ���.
select emp.employee_id, emp.first_name, dep.department_name, mgr.first_name
from employees emp, employees mgr, departments dep
where emp.manager_id = mgr.employee_id and emp.department_id = dep.department_id;

SELECT
   e.EMPLOYEE_ID "���",
   e.FIRST_NAME "�̸�",
   d.DEPARTMENT_NAME "�μ���",
   m.FIRST_NAME "�Ŵ��� �̸�"
FROM
   EMPLOYEES e ,
   DEPARTMENTS d ,
   EMPLOYEES m
WHERE
   e.DEPARTMENT_ID = d.DEPARTMENT_ID
   AND e.MANAGER_ID = m.EMPLOYEE_ID ;
   
--2.����(regions)�� ���� ������� �����̸�(region_name), �����̸�(country_name)���� ����ϵ� �����̸�, �����̸� ������� ������������ �����ϼ���.
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

--3.�� �μ�(department)�� ���ؼ� �μ���ȣ(department_id), �μ��̸�(department_name), �Ŵ���(manager)�� �̸�(first_name), ��ġ(locations)�� ����(city), ����(countries)�� �̸�(countries_name) �׸��� ��������(regions)�� �̸�(region_name)���� ���� ����� ������.
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
    
        
--4.��Public Accountant���� ��å(job_title)���� ���ſ� �ٹ��� ���� �ִ� ��� ����� ����� �̸��� ����ϼ���. (���� ��Public Accountant���� ��å(job_title)���� �ٹ��ϴ� ����� ������� �ʽ��ϴ�.) �̸��� first_name�� last_name�� ���� ����մϴ�.
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

--5.�������� ���(employee_id), �̸�(first_name), ��(last_name)�� �μ� �̸�(department_name)�� ��ȸ�Ͽ� ��(last_name)������ �������� �����ϼ���
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


--6. �ڽ��� �Ŵ������� ä����(hire_date)�� ���� ����� ���(employee_id), ��(last_name)�� ä����(hire_date)�� ��ȸ�ϼ��� 
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