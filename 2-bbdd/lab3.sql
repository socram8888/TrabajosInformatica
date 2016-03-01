/*
  EN TODOS LOS EJERCICIOS USO COMO PREFIJO "" PARA EVITAR QUE
  AL TRABAJAR EN POKEMON2.UV.ES ME COLISIONARA CON LABORATORIOS
  Y EJERCICIOS FUTUROS
*/

/* Ejercicio 1 */
CREATE TABLE EMPLEADOS (
  IDEMPLEADO NUMBER,
  NOMBRE VARCHAR2(30),
  APELLIDOS VARCHAR2(50),
  EMAIL VARCHAR2(30),
  DIRECCION VARCHAR2(100),
  TELEFONO NUMBER,
  TRABAJO VARCHAR2(20),
  SALARIO NUMBER(*, 2),
  CONSTRAINT EMPLEADOS_PK PRIMARY KEY (IDEMPLEADO)
);

/* Ejercicio 2 */
ALTER TABLE EMPLEADOS ADD (
  CONSTRAINT EMPLEADOS_EMAIL CHECK (EMAIL LIKE '%@%'),
  CONSTRAINT EMPLEADOS_TEL CHECK (TELEFONO >= 600000000 AND TELEFONO <= 699999999 OR TELEFONO >= 900000000 AND TELEFONO <= 999999999),
  CONSTRAINT EMPLEADOS_TRAB CHECK (UPPER(TRABAJO) IN ('INSTRUCTOR', 'ADMINISTRATIVO', 'COMERCIAL', 'VENDEDOR', 'VETERINARIO')),
  CONSTRAINT EMPLEADOS_SAL CHECK (SALARIO > 650.0),
  CONSTRAINT EMPLEADOS_EM_UNIQ UNIQUE (EMAIL)
);

/* Ejercicio 3 */
CREATE TABLE CLIENTES (
  IDCLIENTE NUMBER,
  NOMBRE VARCHAR2(30),
  APELLIDO VARCHAR2(50),
  EMAIL VARCHAR2(30),
  DIRECCION VARCHAR2(100),
  CIUDAD VARCHAR2(30),
  TELEFONO NUMBER,
  CONSTRAINT CLIENTES_PK PRIMARY KEY (IDCLIENTE)
);
ALTER TABLE CLIENTES ADD (
  CONSTRAINT CLIENTES_EMAIL CHECK (EMAIL LIKE '%@%'),
  CONSTRAINT CLIENTES_MAYUS CHECK (NOMBRE = UPPER(NOMBRE) AND APELLIDO = UPPER(APELLIDO))
);

/* Ejercicio 4 */
CREATE TABLE CURSOS (
  idcurso number,
  titulo varchar2(30),
  descripcion VARCHAR2(100),
  max_num number,
  precio number,
  tipoanimal number,
  fechahora DATE,
  lugar VARCHAR2(30),
  instructor NUMBER,
  constraint cursos_pk PRIMARY KEY (idcurso),
  constraint cursos_empleados_fk FOREIGN KEY (instructor) REFERENCES EMPLEADOS(idempleado),
);

-- ALTER TABLE CURSOS ADD CONSTRAINT CURSOS_ANIMAL_FK FOREIGN KEY (TIPOANIMAL) REFERENCES ANIMALES(TIPOANIMAL)
-- No funcion porque la tabla a�n no ha sido creada

/* Ejercicio 5 */
ALTER TABLE CURSOS ADD (
  CONSTRAINT CURSOS_MAXNUM CHECK (MAX_NUM >= 10 AND MAX_NUM <= 30),
  CONSTRAINT CURSOS_HORARIO CHECK (EXTRACT(MONTH FROM FECHAHORA) >= 7 AND EXTRACT(MONTH FROM FECHAHORA) <= 8 AND TO_CHAR(FECHAHORA, 'HH24') >= 15)
);

/* Ejercicio 6 */
CREATE TABLE MASCOTAS (
  IDMASCOTA NUMBER,
  IDCLIENTE NUMBER,
  NOMBREMASCOTA VARCHAR2(20),
  TIPOANIMAL NUMBER,
  FECHANAC DATE,
  CONSTRAINT MASCOTAS_PK PRIMARY KEY (IDMASCOTA),
  CONSTRAINT MASCOTAS_CLIENTE_FK FOREIGN KEY (IDCLIENTE) REFERENCES CLIENTES(IDCLIENTE),
);

/* Ejercicio 7 */
CREATE TABLE CURSOS_CLIENTES (
  IDCURSO NUMBER,
  IDCLIENTE NUMBER,
  CONSTRAINT CURSOSCLIENTES_PKS PRIMARY KEY (IDCLIENTE, IDCURSO),
  CONSTRAINT CURSOSCLIENTES_CURSO_FK FOREIGN KEY (IDCURSO) REFERENCES CURSOS(IDCURSO),
  CONSTRAINT CURSOSCLIENTES_CLIENTE_FK FOREIGN KEY (IDCLIENTE) REFERENCES CLIENTES(IDCLIENTE)
);

/* Ejercicio 8 */
CREATE TABLE PRODUCTOS (
  IDPRODUCTO NUMBER,
  DESCRIPCION VARCHAR2(40),
  PRECIO_COMPRA NUMBER(*, 2),
  PRECIO_VENTA NUMBER(*, 2),
  STOCK NUMBER,
  IDPROVEEDOR NUMBER,
  CONSTRAINT PRODUCTOS_PK PRIMARY KEY (IDPRODUCTO),
  CONSTRAINT PRODUCTOS_PRECIO CHECK (PRECIO_COMPRA < PRECIO_VENTA)
  -- CONSTRAINT PRODUCTOS_PROVEDR_FK FOREIGN KEY (IDPROVEEDOR) REFERENCES PROVEEDOR(IDPROVEEDOR)
);

CREATE TABLE PEDIDOS (
  IDPEDIDO NUMBER,
  IDCLIENTE NUMBER,
  FECHAPEDIDO DATE,
  FECHAENTREGA DATE,
  DIRECCIONENTREGA VARCHAR2(40),
  EMPLEADOVENTA NUMBER,
  CONSTRAINT PEDIDOS_PK PRIMARY KEY (IDPEDIDO),
  CONSTRAINT PEDIDOS_CLIENTE_FK FOREIGN KEY (IDCLIENTE) REFERENCES CLIENTES(IDCLIENTE),
  CONSTRAINT PEDIDOS_VENDEDOR_FK FOREIGN KEY (EMPLEADOVENTA) REFERENCES EMPLEADOS(IDEMPLEADO)
);

CREATE TABLE PEDIDOS_PRODUCTOS (
  IDPEDIDO NUMBER,
  IDPRODUCTO NUMBER,
  CANTIDAD NUMBER,
  PRECIOREAL NUMBER,
  CONSTRAINT PEDIDOS_PRODUCTOS_PK PRIMARY KEY (IDPEDIDO, IDPRODUCTO),
  CONSTRAINT PEDIDOS_PRODUCTOS_PED_FK FOREIGN KEY (IDPEDIDO) REFERENCES PEDIDOS(IDPEDIDO),
  CONSTRAINT PEDIDOS_PRODUCTOS_PROD_FK FOREIGN KEY (IDPRODUCTO) REFERENCES PRODUCTOS(IDPRODUCTO)
);

/* Ejercicio 9 */
CREATE TABLE ANIMALES AS SELECT * FROM LBD2011.ANIMALES;
ALTER TABLE ANIMALES ADD CONSTRAINT ANIMALES_PK PRIMARY KEY (TIPOANIMAL);
ALTER TABLE CURSOS ADD CONSTRAINT CURSOS_ANIMAL_FK FOREIGN KEY (TIPOANIMAL) REFERENCES ANIMALES(TIPOANIMAL);
ALTER TABLE MASCOTAS ADD CONSTRAINT MASCOTAS_TIPO_FK FOREIGN KEY (TIPOANIMAL) REFERENCES ANIMALES(TIPOANIMAL);

/* Ejercicio 12 */
INSERT INTO CLIENTES SELECT * FROM LBD2011.CLIENTES;
INSERT INTO EMPLEADOS SELECT * FROM LBD2011.EMPLEADOS;
INSERT INTO MASCOTAS SELECT * FROM LBD2011.MASCOTAS;
INSERT INTO PRODUCTOS SELECT * FROM LBD2011.PRODUCTOS;
INSERT INTO PEDIDOS SELECT * FROM LBD2011.PEDIDOS;
INSERT INTO PEDIDOS_PRODUCTOS SELECT * FROM LBD2011.PEDIDOS_PRODUCTOS;
-- Algunos cursos no son v�lidos. Hay que filtrarlos o saltan las comprobaciones.
INSERT INTO CURSOS SELECT * FROM LBD2011.CURSOS WHERE EXTRACT(MONTH FROM FECHAHORA) >= 7 AND EXTRACT(MONTH FROM FECHAHORA) <= 8 AND TO_CHAR(FECHAHORA, 'HH24') >= 15;
INSERT INTO CURSOS_CLIENTES SELECT * FROM LBD2011.CURSOS_CLIENTES WHERE IDCLIENTE IN (SELECT IDCLIENTE FROM CLIENTES) AND IDCURSO IN (SELECT IDCURSO FROM CURSOS);

/* Ejercicio 13 */
INSERT INTO CLIENTES (IDCLIENTE, NOMBRE, APELLIDO, EMAIL, DIRECCION, CIUDAD) VALUES (14, 'ANA MAR�A', 'FERN�NDEZ MORALES', 'amfm@gmail.com', 'Plaza del Ayuntamiento, n� 1', 'Valencia');

/* Ejercicio 14 */
INSERT INTO CURSOS_CLIENTES (IDCLIENTE, IDCURSO) SELECT DISTINCT IDCLIENTE, IDCURSO FROM CURSOS, CLIENTES WHERE CLIENTES.NOMBRE = 'ANA MAR�A' AND CLIENTES.APELLIDO = 'FERN�NDEZ MORALES' AND CURSOS.TITULO = 'Como tratar una mascota';

/* Ejercicio 15 */
DELETE FROM CURSOS_CLIENTES WHERE IDCURSO = (SELECT IDCURSO FROM CURSOS WHERE TITULO = 'Higiene de gatos especiales');
-- Se borran 3 inscritos

/* Ejercicio 16 */
SELECT IDPRODUCTO FROM (SELECT IDPRODUCTO, COUNT(*) FROM PEDIDOS_PRODUCTOS GROUP BY IDPRODUCTO HAVING COUNT(*) = (SELECT MAX(NUM) FROM (SELECT COUNT(*) AS NUM FROM PEDIDOS_PRODUCTOS GROUP BY IDPRODUCTO)));
