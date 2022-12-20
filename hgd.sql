create table book(
    book_id number(5),
    title varchar2(50),
    author varchar2(10),
    pub_date date
);
COMMIT;

SELECT *
FROM book;

ALTER TABLE book ADD (pubs VARCHAR2(50));
COMMIT;

ALTER TABLE book MODIFY (title VARCHAR2(100));
COMMIT;

ALTER TABLE book DROP (author);
COMMIT;

RENAME book TO article;

SELECT *
FROM article;

DROP TABLE article;


create table author(
    author_id NUMBER(10),
    author_name VARCHAR2(100) NOT NULL,
    author_desc VARCHAR2(500),
    PRIMARY KEY(author_id)  --autor_id�� PK�� ����=> �ڵ����� NOT NULL�� ������
);
COMMIT;
select * from author a;

DROP TABLE book;
CREATE TABLE book (
book_id NUMBER(10),
title VARCHAR2(100) NOT NULL,
pubs VARCHAR2(100),
pub_date DATE,
author_id NUMBER(10),
PRIMARY KEY(book_id),
CONSTRAINT c_book_fk FOREIGN KEY (author_id)
REFERENCES author(author_id)
);

select * from book;

INSERT INTO author(author_id, AUTHOR_NAME)
VALUES (2, '�̹���');

UPDATE author
SET author_name = '���84',
    author_desc = '�����۰�' 
WHERE author_id = 1 ;

--����: WHERE ���� �����Ǹ� ��� ���ڵ忡 ����
UPDATE author
SET author_name = '��Ǯ', 
author_desc = '�α��۰�';

DELETE FROM author
WHERE author_id = 1 ;

DELETE FROM author ;


DROP SEQUENCE seq_author_id;
CREATE SEQUENCE seq_author_id
INCREMENT BY 1 
START WITH 1 ;

SELECT seq_author_id.nextval FROM dual;
SELECT seq_author_id.currval FROM dual;


INSERT INTO author
VALUES (seq_author_id.nextval, '�ڰ渮', '���� �۰� ' );
INSERT INTO author 
VALUES (seq_author_id.nextval, '�̹���', '�ﱹ�� �۰�');

select * from author a;

SELECT * FROM USER_SEQUENCES;

-------------------
select * from author;
select * from book;

DROP TABLE author;
create table author(
    author_id NUMBER(10),
    author_name VARCHAR2(100) NOT NULL,
    author_desc VARCHAR2(500),
    PRIMARY KEY(author_id)  --author_id�� PK�� ����=> �ڵ����� NOT NULL�� ������
);
COMMIT;

DROP SEQUENCE seq_author_id;

CREATE SEQUENCE seq_author_id
INCREMENT BY 1
START WITH 1;

DELETE FROM author;

INSERT INTO author
VALUES (seq_author_id.nextval, '�̹���', '��� ����' );
INSERT INTO author
VALUES (seq_author_id.nextval, '�ڰ渮', '��󳲵� �뿵' );
INSERT INTO author
VALUES (seq_author_id.nextval, '���ù�', '17�� ��ȸ�ǿ�' );
INSERT INTO author
VALUES (seq_author_id.nextval, '���84', '��ȵ����� �� 84���' );
INSERT INTO author
VALUES (seq_author_id.nextval, '��Ǯ', '�¶��� ��ȭ�� 1����' );
INSERT INTO author
VALUES (seq_author_id.nextval, '�迵��', '�˶����' );

DROP SEQUENCE seq_book_id;
CREATE SEQUENCE seq_book_id
INCREMENT BY 1
START WITH 1;

INSERT INTO book
VALUES (seq_book_id.nextval, '�츮���� �ϱ׷��� ����', '�ٸ�', '1998-02-22', 1);

INSERT INTO book
VALUES (seq_book_id.nextval, '�ﱹ��', '������', '2002-03-01', 1);

INSERT INTO book
VALUES (seq_book_id.nextval, '����', '���δϿ��Ͻ�', '2012-08-15', 2);

INSERT INTO book
VALUES (seq_book_id.nextval, '���ù��� �۾��� Ư��', '�����Ǳ�', '2015-04-01', 3);

INSERT INTO book
VALUES (seq_book_id.nextval, '�мǿ�', '�߾ӺϽ�', '2012-02-22', 4);

INSERT INTO book
VALUES (seq_book_id.nextval, '������ȭ', '�������', '2011-08-03', 5);

INSERT INTO book
VALUES (seq_book_id.nextval, '�����λ��', '���е���', '2017-05-04', 6);

INSERT INTO book
VALUES (seq_book_id.nextval, '26��', '�������', '2012-02-04', 5);


SELECT b.book_id, b.title, b.pubs, b.pub_date, b.author_id, a.author_name, a.author_desc
FROM book b, author a
WHERE b.author_id = a.author_id;

UPDATE AUTHOR
SET AUTHOR_DESC = '����Ư����'
WHERE AUTHOR_ID = 5 ;

DELETE FROM AUTHOR a
WHERE a.AUTHOR_ID = 4;

DELETE FROM BOOK b
WHERE b.AUTHOR_ID = 4;

DELETE FROM AUTHOR a
WHERE a.AUTHOR_ID = 4;
----------------------------------------
----------------------------------------
--������
----------------------------------------
DROP TABLE customer;
create table customer(
    c_id NUMBER(10),
    c_name VARCHAR2(100) NOT NULL,
    c_phonenumber VARCHAR2(100) NOT NULL,
    c_addr VARCHAR2(100) NOT NULL,
    PRIMARY KEY(c_id)  --c_id�� PK�� ����=> �ڵ����� NOT NULL�� ������
);

DROP TABLE product;
create table product(
    p_id NUMBER(10),
    p_name VARCHAR2(20) NOT NULL,
    p_price NUMBER(10),
    p_addr VARCHAR2(50) NOT NULL,
    PRIMARY KEY(p_id)  --p_id�� PK�� ����=> �ڵ����� NOT NULL�� ������
);

DROP TABLE shop;
--id, cid, pid, date, count, price, totalprice, address, phonenumber
create table shop(
    o_id NUMBER(15),
    o_cid VARCHAR2(20) NOT NULL,
    o_pid VARCHAR2(20) NOT NULL,
    o_date VARCHAR2(20) NOT NULL,
    o_count VARCHAR2(10) NOT NULL,
    o_price NUMBER(20) NOT NULL,
    o_totalprice NUMBER(30) NOT NULL,
    o_address VARCHAR2(20) NOT NULL,
    o_phonenumber VARCHAR2(20) NOT NULL,
    PRIMARY KEY(o_id)  --o_id�� PK�� ����=> �ڵ����� NOT NULL�� ������
);


DROP TABLE client;
DROP TABLE product;
DROP TABLE shop;
