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
    PRIMARY KEY(author_id)  --autor_id를 PK로 설정=> 자동으로 NOT NULL로 설정됨
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
VALUES (2, '이문열');

UPDATE author
SET author_name = '기안84',
    author_desc = '웹툰작가' 
WHERE author_id = 1 ;

--주의: WHERE 절이 생략되면 모든 레코드에 적용
UPDATE author
SET author_name = '강풀', 
author_desc = '인기작가';

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
VALUES (seq_author_id.nextval, '박경리', '토지 작가 ' );
INSERT INTO author 
VALUES (seq_author_id.nextval, '이문열', '삼국지 작가');

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
    PRIMARY KEY(author_id)  --author_id를 PK로 설정=> 자동으로 NOT NULL로 설정됨
);
COMMIT;

DROP SEQUENCE seq_author_id;

CREATE SEQUENCE seq_author_id
INCREMENT BY 1
START WITH 1;

DELETE FROM author;

INSERT INTO author
VALUES (seq_author_id.nextval, '이문열', '경북 영양' );
INSERT INTO author
VALUES (seq_author_id.nextval, '박경리', '경상남도 통영' );
INSERT INTO author
VALUES (seq_author_id.nextval, '유시민', '17대 국회의원' );
INSERT INTO author
VALUES (seq_author_id.nextval, '기안84', '기안동에서 산 84년생' );
INSERT INTO author
VALUES (seq_author_id.nextval, '강풀', '온라인 만화가 1세대' );
INSERT INTO author
VALUES (seq_author_id.nextval, '김영하', '알뜰신잡' );

DROP SEQUENCE seq_book_id;
CREATE SEQUENCE seq_book_id
INCREMENT BY 1
START WITH 1;

INSERT INTO book
VALUES (seq_book_id.nextval, '우리들의 일그러진 영웅', '다림', '1998-02-22', 1);

INSERT INTO book
VALUES (seq_book_id.nextval, '삼국지', '민음사', '2002-03-01', 1);

INSERT INTO book
VALUES (seq_book_id.nextval, '토지', '마로니에북스', '2012-08-15', 2);

INSERT INTO book
VALUES (seq_book_id.nextval, '유시민의 글쓰기 특강', '생각의길', '2015-04-01', 3);

INSERT INTO book
VALUES (seq_book_id.nextval, '패션왕', '중앙북스', '2012-02-22', 4);

INSERT INTO book
VALUES (seq_book_id.nextval, '순정만화', '재미주의', '2011-08-03', 5);

INSERT INTO book
VALUES (seq_book_id.nextval, '오직두사람', '문학동네', '2017-05-04', 6);

INSERT INTO book
VALUES (seq_book_id.nextval, '26년', '재미주의', '2012-02-04', 5);


SELECT b.book_id, b.title, b.pubs, b.pub_date, b.author_id, a.author_name, a.author_desc
FROM book b, author a
WHERE b.author_id = a.author_id;

UPDATE AUTHOR
SET AUTHOR_DESC = '서울특별시'
WHERE AUTHOR_ID = 5 ;

DELETE FROM AUTHOR a
WHERE a.AUTHOR_ID = 4;

DELETE FROM BOOK b
WHERE b.AUTHOR_ID = 4;

DELETE FROM AUTHOR a
WHERE a.AUTHOR_ID = 4;
----------------------------------------
----------------------------------------
--고객관리
----------------------------------------
DROP TABLE customer;
create table customer(
    c_id NUMBER(10),
    c_name VARCHAR2(100) NOT NULL,
    c_phonenumber VARCHAR2(100) NOT NULL,
    c_addr VARCHAR2(100) NOT NULL,
    PRIMARY KEY(c_id)  --c_id를 PK로 설정=> 자동으로 NOT NULL로 설정됨
);

DROP TABLE product;
create table product(
    p_id NUMBER(10),
    p_name VARCHAR2(20) NOT NULL,
    p_price NUMBER(10),
    p_addr VARCHAR2(50) NOT NULL,
    PRIMARY KEY(p_id)  --p_id를 PK로 설정=> 자동으로 NOT NULL로 설정됨
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
    PRIMARY KEY(o_id)  --o_id를 PK로 설정=> 자동으로 NOT NULL로 설정됨
);


DROP TABLE client;
DROP TABLE product;
DROP TABLE shop;
