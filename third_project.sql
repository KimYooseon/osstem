DROP TABLE Shop;
DROP TABLE Product;



SELECT 
   (SELECT VALUE FROM NLS_DATABASE_PARAMETERS WHERE PARAMETER='NLS_LANGUAGE')
    || '_' ||
    (SELECT VALUE FROM NLS_DATABASE_PARAMETERS WHERE PARAMETER='NLS_TERRITORY')
    || '.' ||
    (SELECT VALUE FROM NLS_DATABASE_PARAMETERS WHERE PARAMETER='NLS_CHARACTERSET')
FROM DUAL;


-----------

DROP TABLE client;
CREATE TABLE client(
  c_id    NUMBER(20),
  c_name  varchar2(100) NOT NULL,
  c_phonenum  varchar2(200) NOT NULL,
  c_addr  varchar2(200) NOT NULL,
  PRIMARY key(c_id)
);
DROP SEQUENCE seq_cust_c_id ;
CREATE SEQUENCE seq_client_c_id
INCREMENT BY 1 
START WITH 1 ;


DROP TABLE product;
CREATE TABLE product(
  p_id    NUMBER(20),
  p_pname  varchar2(100) NOT NULL,
  p_price NUMBER(20) NOT NULL,
  p_category varchar2(100) NOT NULL,
  PRIMARY key(p_id)
);
DROP SEQUENCE seq_product_p_id ;
CREATE SEQUENCE seq_product_p_id
INCREMENT BY 1 
START WITH 40001 ;



DROP TABLE shop;
CREATE TABLE shop(
  s_id    NUMBER(20),
  s_c_id  NUMBER(20) NOT NULL,
  s_p_id  NUMBER(20) NOT NULL,
  s_date  date NOT NULL,
  s_count NUMBER(20) NOT NULL,
  s_price NUMBER(20) NOT NULL,
  s_totalprice NUMBER(20) NOT NULL,
  s_address varchar2(200),
  s_phonenum varchar2(200),
  PRIMARY key(s_id),
  CONSTRAINT c_shop_fk1 FOREIGN KEY (s_c_id)
  REFERENCES client(c_id),
  CONSTRAINT c_shop_fk2 FOREIGN KEY (s_p_id)
  REFERENCES product(p_id)
);
DROP SEQUENCE seq_s_id ;
CREATE SEQUENCE seq_s_id
INCREMENT BY 1 
START WITH 70001 ;


-----------------------------
--Client 프로시저
-----------------------------
CREATE OR REPLACE PROCEDURE INSERT_CLIENT
( v1_cid IN client.c_id%TYPE,
  v1_name IN client.c_name%TYPE,
  v1_phonenum IN client.c_phonenum%TYPE,
  v1_addr   IN client.c_addr%TYPE)
IS
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    INSERT INTO client
    (c_id, c_name, c_phonenum, c_addr)
    VALUES(v1_cid, v1_name, v1_phonenum, v1_addr);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE( 'CLI NO : ' || v1_cid );
    DBMS_OUTPUT.PUT_LINE( 'CLI NAME : ' || v1_name );
    DBMS_OUTPUT.PUT_LINE( 'CLI PHONENUM : ' || v1_phonenum );
    DBMS_OUTPUT.PUT_LINE( 'CLI ADDR : ' || v1_addr );
END;
/
CALL THIRD_PROJECT.INSERT_CLIENT(1, '김유선', '010-1111-1111', '경기도');

/

CREATE OR REPLACE PROCEDURE UPDATE_CLIENT
( v1_cid IN client.c_                                                                     id%TYPE,
  v1_name IN client.c_name%TYPE,
  v1_phonenum IN client.c_phonenum%TYPE,
  v1_addr   IN client.c_addr%TYPE)
IS
    v1_cli client%ROWTYPE;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    
    UPDATE client
    SET c_name = v1_name, c_phonenum = v1_phonenum, c_addr = v1_addr
    WHERE c_id = v1_cid;
    
   /* UPDATE client
    SET c_phonenum = v1_phonenum
    WHERE c_id = v1_cid;
    
    UPDATE client
    SET c_addr = v1_addr
    WHERE c_id = v1_cid;
    */
    COMMIT;
    
    DBMS_OUTPUT.PUT_LINE( 'Data Update Success ');
    
    SELECT c_id, c_name, c_phonenum, c_addr
    INTO v1_cli.v1_cid, v1_cli.v1_name, v1_cli.v1_phonenum ,v1_cli.v1_addr
    FROM client
    WHERE c_id = v1_cid;
    DBMS_OUTPUT.PUT_LINE( ' **** Confirm Update Data **** ' );
    DBMS_OUTPUT.PUT_LINE( 'CLI NO : ' || v1_cid );
    DBMS_OUTPUT.PUT_LINE( 'CLI NAME : ' || v1_name );
    DBMS_OUTPUT.PUT_LINE( 'CLI PHONENUM : ' || v1_phonenum );
    DBMS_OUTPUT.PUT_LINE( 'CLI ADDR : ' || v1_addr );
END;

/

CREATE OR REPLACE PROCEDURE DELETE_CLIENT
( p_cid IN client.c_id%TYPE)    --이 p_cid라고 써진 거는 뭔 뜻이쥐..
IS
    TYPE del_record IS RECORD
    ( v1_cid client.c_id%TYPE,
      v1_name client.c_name%TYPE,
      v1_phonenum client.c_phonenum%TYPE,
      v1_addr client.c_addr%TYPE );
    
    v1_cli del_record ;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    SELECT c_id, c_name, c_phonenum, c_addr
    INTO v1_cli.c_id, v1_cli.v1_name, v1_cli.v1_phonenum ,v1_cli.v1_addr
    FROM client
    WHERE c_id = p_cid;
    
    DBMS_OUTPUT.PUT_LINE( 'CLI NO : ' || v1_cli.v1_cid );
    DBMS_OUTPUT.PUT_LINE( 'CLI NAME : ' || v1_cli.v1_name );
    DBMS_OUTPUT.PUT_LINE( 'CLI PHONENUM : ' || v1_cli.v1_phonenum );
    DBMS_OUTPUT.PUT_LINE( 'CLI ADDR : ' || v1_cli.v1_addr );
    
    DELETE
    FROM client
    WHERE c_id = p_cid;
    
    COMMIT;
    
END;    
/
-----------------------------
--Product 프로시저
-----------------------------
CREATE OR REPLACE PROCEDURE INSERT_PRODUCT
( v2_pid IN product.p_id%TYPE,
  v2_pname IN product.p_pname%TYPE,
  v2_price IN product.p_price%TYPE,
  v2_category   IN product.p_category%TYPE)
IS
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    INSERT INTO product
    (p_id, p_pname, p_price, p_category)
    VALUES(v2_pid, v2_pname, v2_price, v2_category);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE( 'PRO NO : ' || v2_pid );
    DBMS_OUTPUT.PUT_LINE( 'PRO PNAME : ' || v2_pname );
    DBMS_OUTPUT.PUT_LINE( 'PRO PRICE : ' || v2_price );
    DBMS_OUTPUT.PUT_LINE( 'PRO CATEGORY : ' || v2_category );
END;
/
CALL THIRD_PROJECT.INSERT_PRODUCT(40001, '상품1', 500, '카테고리1');

/

CREATE OR REPLACE PROCEDURE UPDATE_PRODUCT
( v2_pid IN product.p_id%TYPE,
  v2_pname IN product.p_pname%TYPE,
  v2_price IN product.p_price%TYPE,
  v2_category   IN product.p_category%TYPE)
IS
    v2_pro product%ROWTYPE;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    UPDATE product
    SET p_pname = v2_pname
    WHERE p_id = v2_pid;
    
    UPDATE product
    SET p_price = v2_price
    WHERE p_id = v2_pid;
    
    UPDATE product
    SET p_category = v2_category
    WHERE p_id = v2_pid;
    
    COMMIT;
    
    DBMS_OUTPUT.PUT_LINE( 'Data Update Success ');
    
    SELECT p_id, p_pname, p_price, p_category
    INTO v2_pro.v2_pid, v2_pro.v2_pname, v2_pro.v2_price ,v2_pro.v2_category
    FROM product
    WHERE p_id = v2_pid;
    DBMS_OUTPUT.PUT_LINE( ' **** Confirm Update Data **** ' );
    DBMS_OUTPUT.PUT_LINE( 'PRO NO : ' || v2_pid );
    DBMS_OUTPUT.PUT_LINE( 'PRO PNAME : ' || v2_pname );
    DBMS_OUTPUT.PUT_LINE( 'PRO PRICE : ' || v2_price );
    DBMS_OUTPUT.PUT_LINE( 'PRO CATEGORY : ' || v2_category );
END;

/

CREATE OR REPLACE PROCEDURE DELETE_PRODUCT
( p_pid IN product.p_id%TYPE)    --이 p_cid라고 써진 거는 뭔 뜻이쥐..
IS
    TYPE del_record IS RECORD
    ( v2_pid product.p_id%TYPE,
      v2_pname product.p_pname%TYPE,
      v2_price product.p_price%TYPE,
      v2_category product.p_category%TYPE);
    
    v2_pro del_record ;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    SELECT p_id, p_pname, p_price, p_category
    INTO v2_pro.v2_pid, v2_pro.v2_pname, v2_pro.v2_price ,v2_pro.v2_category
    FROM product
    WHERE p_id = p_pid;
        
    DBMS_OUTPUT.PUT_LINE( 'PRO NO : ' || v2_pid );
    DBMS_OUTPUT.PUT_LINE( 'PRO PNAME : ' || v2_pname );
    DBMS_OUTPUT.PUT_LINE( 'PRO PRICE : ' || v2_price );
    DBMS_OUTPUT.PUT_LINE( 'PRO CATEGORY : ' || v2_category );
    
    DELETE
    FROM product
    WHERE p_id = p_pid;
    
    COMMIT;
    
END;    
/
-----------------------------
--Shop 프로시저
-----------------------------
/*s_id    NUMBER(20),
  s_c_id  NUMBER(20) NOT NULL,
  s_p_id  NUMBER(20) NOT NULL,
  s_date  date NOT NULL,
  s_count NUMBER(20) NOT NULL,
  s_price NUMBER(20) NOT NULL,
  s_totalprice NUMBER(20) NOT NULL,
  s_address varchar2(200),
  s_phonenum*/
CREATE OR REPLACE PROCEDURE INSERT_SHOP
( v3_sid IN shop.s_id%TYPE,
  v3_cid IN shop.s_c_id%TYPE,
  v3_pid IN shop.s_p_id%TYPE,
  v3_date IN shop.s_date%TYPE,
  v3_count IN shop.s_count%TYPE,
  v3_price IN shop.s_price%TYPE,
  v3_totalprice IN shop.s_totalprice%TYPE,
  v3_address IN shop.s_address%TYPE,
  v3_phonenum IN shop.s_phonenum%TYPE)
IS
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    INSERT INTO shop
    (s_id, s_c_id, s_p_id, s_date, s_count, s_price, s_totalprice, s_address, s_phonenum)
    VALUES(v3_sid, v3_cid, v3_pid, v3_date, v3_count, v3_price, v3_totalprice, v3_address, v3_phonenum);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE( 'SHOP NO : ' || v3_sid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP CID : ' || v3_cid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PID : ' || v3_pid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP DATE : ' || v3_date );
    DBMS_OUTPUT.PUT_LINE( 'SHOP COUNT : ' || v3_count );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PRICE : ' || v3_price );
    DBMS_OUTPUT.PUT_LINE( 'SHOP TOTALPRICE : ' || v3_totalprice );
    DBMS_OUTPUT.PUT_LINE( 'SHOP ADDR : ' || v3_address );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PHONENUM : ' || v3_phonenum );
    
END;
/
CALL THIRD_PROJECT.INSERT_SHOP(70001, 1, 40001, 2022-11-06, 5, 500, 2500, '경기도', 010-1111-1111);

/

CREATE OR REPLACE PROCEDURE UPDATE_SHOP
( v3_sid IN shop.s_id%TYPE,
  v3_cid IN shop.s_c_id%TYPE,
  v3_pid IN shop.s_p_id%TYPE,
  v3_date IN shop.s_date%TYPE,
  v3_count IN shop.s_count%TYPE,
  v3_price IN shop.s_price%TYPE,
  v3_totalprice IN shop.s_totalprice%TYPE,
  v3_address IN shop.s_address%TYPE,
  v3_phonenum IN shop.s_phonenum%TYPE)
IS
    v3_shop shop%ROWTYPE;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    UPDATE shop
    SET s_date = v3_date
    WHERE s_id = v3_sid;
    
    UPDATE shop
    SET s_count = v3_count
    WHERE s_id = v3_sid;
    
    COMMIT;
    
    DBMS_OUTPUT.PUT_LINE( 'Data Update Success ');
    
    SELECT s_id, s_c_id, s_p_id, s_date, s_count, s_price, s_totalprice, s_address, s_phonenum
    INTO v3_shop.v3_sid, v3_shop.v3_cid, v3_shop.v3_pid, v3_shop.v3_date, v3_shop.v3_count, 
         v3_shop.v3_price, v3_shop.v3_totalprice, v3_shop.v3_address, v3_shop.v3_phonenum
    FROM shop
    WHERE s_id = v3_sid;
    DBMS_OUTPUT.PUT_LINE( 'SHOP NO : ' || v3_sid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP CID : ' || v3_cid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PID : ' || v3_pid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP DATE : ' || v3_date );
    DBMS_OUTPUT.PUT_LINE( 'SHOP COUNT : ' || v3_count );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PRICE : ' || v3_price );
    DBMS_OUTPUT.PUT_LINE( 'SHOP TOTALPRICE : ' || v3_totalprice );
    DBMS_OUTPUT.PUT_LINE( 'SHOP ADDR : ' || v3_address );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PHONENUM : ' || v3_phonenum );
END;

/

CREATE OR REPLACE PROCEDURE DELETE_SHOP
( p_sid IN shop.s_id%TYPE)    --이 p_cid라고 써진 거는 뭔 뜻이쥐..
IS
    TYPE del_record IS RECORD
    ( v3_sid shop.s_id%TYPE,
      v3_cid shop.s_c_id%TYPE,
      v3_pid shop.s_p_id%TYPE,
      v3_date shop.s_date%TYPE,
      v3_count shop.s_count%TYPE,
      v3_price shop.s_price%TYPE,
      v3_totalprice shop.s_totalprice%TYPE,
      v3_address shop.s_address%TYPE,
      v3_phonenum shop.s_phonenum%TYPE);
    
    v3_shop del_record ;
BEGIN
    DBMS_OUTPUT.ENABLE;
    
    SELECT s_id, s_c_id, s_p_id, s_date, s_count, s_price, s_totalprice, s_address, s_phonenum
    INTO v3_shop.v3_sid, v3_shop.v3_cid, v3_shop.v3_pid, v3_shop.v3_date, v3_shop.v3_count, 
         v3_shop.v3_price, v3_shop.v3_totalprice, v3_shop.v3_address, v3_shop.v3_phonenum
    FROM shop
    WHERE s_id = p_sid;
    
    DBMS_OUTPUT.PUT_LINE( 'SHOP NO : ' || v3_sid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP CID : ' || v3_cid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PID : ' || v3_pid );
    DBMS_OUTPUT.PUT_LINE( 'SHOP DATE : ' || v3_date );
    DBMS_OUTPUT.PUT_LINE( 'SHOP COUNT : ' || v3_count );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PRICE : ' || v3_price );
    DBMS_OUTPUT.PUT_LINE( 'SHOP TOTALPRICE : ' || v3_totalprice );
    DBMS_OUTPUT.PUT_LINE( 'SHOP ADDR : ' || v3_address );
    DBMS_OUTPUT.PUT_LINE( 'SHOP PHONENUM : ' || v3_phonenum );
    
    DELETE
    FROM product
    WHERE s_id = p_sid;
    
    COMMIT;
    
END;    