----------------------------------------
--绊按包府, 惑前包府, 林巩包府
----------------------------------------
select * from client;
select * from product;
select * from shop;

declare
vno varchar2(20);
begin
    select to_char(sysdate, 'YYYY/MM/DD') into vno
    from dual;
    dbms_output.put_line(vno);
end;