SET SERVEROUTPUT ON;

-- Ejercicio 1
DECLARE
  prodstock NUMBER;
BEGIN
  SELECT COUNT(*) INTO prodstock FROM mi_productos;
  dbms_output.put_line('Productos en stock: ' || prodstock);
END;

-- Ejercicio 2
CREATE OR REPLACE PROCEDURE pr02 IS
  xparcial number := 0;
  xtotal number := 0;
BEGIN
  select count(*) into xtotal from mi_clientes;
  select count(*) into xparcial from mi_mascotas;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_animales;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_cursos;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_cursos_clientes;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_empleados;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_pedidos;
  xtotal := xtotal + xparcial;
  select count(*) intoxparcialfrommi_pedidos_producos;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_productos;
  xtotal := xtotal + xparcial;
  select count(*) into xparcial from mi_proveedores;
  xtotal := xtotal + xparcial;
  dbms_output.put_line('en total hay ' || to_char(xtotal) ||'registros');
END pr02;

-- Ejercicio 3
create or replace PROCEDURE PR03 IS
BEGIN
  INSERT INTO MI_PRODUCTOS VALUES (21, 'Champ� Canino, XX', 13.5, 15.5, 0, 2);
  COMMIT;
  dbms_output.put_line('Se ha realizado el commit');
exception
when others then
  rollback;
  dbms_output.put_line('No se ha realizado el commit');
end PR03;

-- Ejercicio 4
CREATE OR REPLACE PROCEDURE pr04
(xcodcurs in mi_cursos_clientes.idcurso%type, xtotal out number) IS
CURSO_NX EXCEPTION;
BEGIN
SELECT count(idcurso) INTO xtotal FROM mi_cursos_clientes where idcurso = xcodcurs;
IF (xtotal = 0) THEN
  RAISE CURSO_NX;
END IF;
dbms_output.put_line('Animales inscritos: ' || xtotal);
EXCEPTION
  WHEN CURSO_NX THEN
    dbms_output.put_line('Curso inexistente');
  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
END pr04;

-- Ejercicio 4a
create or replace FUNCTION fn04
(xcodcurs in mi_cursos_clientes.idcurso%type) RETURN NUMBER IS
XTOTAL NUMBER;
CURSO_NX EXCEPTION;
BEGIN
SELECT count(idcurso) INTO xtotal FROM mi_cursos_clientes where idcurso = xcodcurs;
IF (xtotal = 0) THEN
  RAISE CURSO_NX;
END IF;
dbms_output.put_line('Animales inscritos: ' || xtotal);
RETURN xtotal;
EXCEPTION
  WHEN CURSO_NX THEN
    dbms_output.put_line('Curso inexistente');
    RETURN -1;
  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
    RETURN -1;
END;

-- Ejercicio 5
create or replace FUNCTION fn05(
  xidcli mi_pedidos.idcliente%type,
  xfechaentrega mi_pedidos.fechaentrega%type,
  xdirentrega mi_pedidos.direccionentrega%type,
  xemp mi_pedidos.empleadoventa%type,
  xproducto mi_productos.idproducto%type,
  xcantidad mi_pedidos_productos.cantidad%type,
  xpvpreal mi_pedidos_productos.precioreal%type)
RETURN NUMBER IS
  wcliente number;
  wempventa number;
  wstock number;
  wproducto number;
  wultimopedido number;
  error_cliente exception;
  error_empleado exception;
  error_producto exception;
  error_fecha exception;
  error_stock exception;
begin
  select count(*) into wcliente from mi_clientes where idcliente = xidcli;
  select count(*) into wempventa from mi_empleados where idempleado = xemp;
  select stock into wstock from mi_productos where idproducto = xproducto;
  select max(idpedido) into wultimopedido from mi_pedidos;

  if wcliente = 0 then
    --excepcion de cliente
    raise error_cliente;
  end if;

  if wempventa = 0 then
    --excepcion de empleado inexistente
    raise error_empleado;
  end if;

  if wproducto = 0 then
    -- excepci�n de producto
    raise error_producto;
  end if;

  if wstock < xcantidad then
    --excepci�n de stock
    raise error_stock;
  end if;

  if xfechaentrega < sysdate then
    --excepci�n de fecha
    raise error_fecha;
  end if;

  insert into mi_pedidos values (wultimopedido+1, xidcli, sysdate, xfechaentrega, xdirentrega, xemp);
  insert into mi_pedidos_productos values (wultimopedido+1, xproducto, xcantidad, xpvpreal);
  update mi_productos set stock = stock - xcantidad where idproducto = xproducto;
  commit;
  dbms_output.put_line('Pedido grabado correctamente en el sistema');
  return 1;

exception
  when error_cliente then
    dbms_output.put_line('Error -1: El cliente no existe. Primero debe registrarse en el sistema');
    return -1;

  when error_empleado then
    dbms_output.put_line('Error -2: Empleado inexistente');
    return -2;

  when error_producto then
    dbms_output.put_line('Error -3: Producto desconocido o inexistente');
    return -3;

  when error_stock then
    dbms_output.put_line('Error -4: No hay stock suficiente');
    return -4;

  when error_fecha then
    dbms_output.put_line('Error -5: Fecha de entrega anterior a fecha pedido');
    return -5;
  
  WHEN OTHERS THEN
    dbms_output.put_line('Error -10: error desconocido' ) ;
    dbms_output.put_line('Error Oracle ' || TO_CHAR(SQLCODE) || 'Mensaje: ' || SUBSTR(SQLERRM, 1, 200));
    ROLLBACK;
    return -10;
end fn05;

-- Ejercicio 6
DECLARE
  CURSOR c1 IS
    SELECT
      tipoanimal,
      COUNT(*) AS cantidadcursos,
      AVG(precio) AS preciomedio
      FROM mi_cursos
      GROUP BY tipoanimal;
  xtotal_cursos NUMBER;
  xtipo_animal MI_ANIMALES.NOMBRE%type;
  xprecio_medio_curso_animal NUMBER;
  total_porcentaje NUMBER;
BEGIN
  SELECT COUNT(*) INTO xtotal_cursos FROM mi_cursos;
  FOR reg IN c1
  LOOP
    IF reg.tipoanimal IS NULL then
      xtipo_animal := '(ninguno)';
    ELSE 
      SELECT nombre INTO xtipo_animal FROM mi_animales WHERE mi_animales.TIPOANIMAL = reg.tipoanimal;
    END IF;
  
    total_porcentaje := reg.cantidadcursos / xtotal_cursos * 100;
    dbms_output.put_line(
      rpad(xtipo_animal,10,' ') ||
      lpad(to_char(reg.cantidadcursos,'999999'),10,' ') ||
      lpad(to_char(total_porcentaje,'99999.99'),10,' ') ||
      lpad(to_char(reg.preciomedio, '999999'),10,' ')
    );
  END LOOP;
EXCEPTION WHEN OTHERS THEN dbms_output.put_line('Error -10: error no conocido'); dbms_output.put_line('Error Oracle ' || TO_CHAR(SQLCODE) || ' Mensaje: ' || SUBSTR(SQLERRM,1,200));
END;

-- Ejercicio 7
create or replace PROCEDURE PR07(
  XNOM MI_CLIENTES.NOMBRE%TYPE,
  XAPE MI_CLIENTES.APELLIDO%TYPE,
  XMAIL MI_CLIENTES.EMAIL%TYPE,
  XDIR MI_CLIENTES.DIRECCIONPOSTAL%TYPE,
  XCITY MI_CLIENTES.CIUDAD%TYPE,
  XTEL MI_CLIENTES.TELEFONO%TYPE
) IS
  WCLIENT NUMBER;
  WIDULTIMO NUMBER;
  ERROR_EXIST EXCEPTION;
  ERROR_MAIL EXCEPTION;
  ERROR_TEL EXCEPTION;
BEGIN
  SELECT COUNT(*) INTO WCLIENT FROM MI_CLIENTES WHERE NOMBRE = XNOM AND APELLIDO = XAPE;
  IF WCLIENT > 0 THEN
    RAISE ERROR_EXIST;
  END IF;

  IF XTEL < 600000000 OR (XTEL > 699999999 AND XTEL < 900000000) OR XTEL > 999999999 THEN
    RAISE ERROR_TEL;
  END IF;

  IF XMAIL NOT LIKE '%@%.%' THEN
    RAISE ERROR_MAIL;
  END IF;

  SELECT MAX(IDCLIENTE) INTO WIDULTIMO FROM MI_CLIENTES;
  INSERT INTO MI_CLIENTES (IDCLIENTE, NOMBRE, APELLIDO, EMAIL, DIRECCIONPOSTAL, CIUDAD, TELEFONO) VALUES (WIDULTIMO + 1, XNOM, XAPE, XMAIL, XDIR, XCITY, XTEL);
  COMMIT;

  dbms_output.put_line('Cliente registrado satisfactoriamente');
EXCEPTION
  WHEN ERROR_EXIST THEN
    dbms_output.put_line('Cliente ya registrado');

  WHEN ERROR_MAIL THEN
    dbms_output.put_line('Email no v�lido');

  WHEN ERROR_TEL THEN
    dbms_output.put_line('Tel�fono no v�lido');

  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
    ROLLBACK;
END;

-- Ejercicio 8
CREATE OR REPLACE PROCEDURE PR08(
  XNOM MI_CLIENTES.NOMBRE%TYPE,
  XAPE MI_CLIENTES.APELLIDO%TYPE,
  XMAIL MI_CLIENTES.EMAIL%TYPE,
  XDIR MI_CLIENTES.DIRECCIONPOSTAL%TYPE,
  XCITY MI_CLIENTES.CIUDAD%TYPE,
  XTEL MI_CLIENTES.TELEFONO%TYPE
) IS
  WIDULTIMO NUMBER;
  ERROR_MAIL EXCEPTION;
  ERROR_TEL EXCEPTION;
BEGIN
  DELETE FROM MI_CLIENTES WHERE NOMBRE = XNOM AND APELLIDO = XAPE;

  IF XTEL < 600000000 OR (XTEL > 699999999 AND XTEL < 900000000) OR XTEL > 999999999 THEN
    RAISE ERROR_TEL;
  END IF;

  IF XMAIL NOT LIKE '%@%.%' THEN
    RAISE ERROR_MAIL;
  END IF;

  SELECT MAX(IDCLIENTE) INTO WIDULTIMO FROM MI_CLIENTES;
  INSERT INTO MI_CLIENTES (IDCLIENTE, NOMBRE, APELLIDO, EMAIL, DIRECCIONPOSTAL, CIUDAD, TELEFONO) VALUES (WIDULTIMO + 1, XNOM, XAPE, XMAIL, XDIR, XCITY, XTEL);
  COMMIT;

  dbms_output.put_line('Cliente registrado satisfactoriamente');
EXCEPTION
  WHEN ERROR_MAIL THEN
    dbms_output.put_line('Email no v�lido');

  WHEN ERROR_TEL THEN
    dbms_output.put_line('Tel�fono no v�lido');

  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
    ROLLBACK;
END;

-- Ejercicio 9
CREATE OR REPLACE FUNCTION
  FN09(XIDCLI MI_CLIENTES.IDCLIENTE%TYPE) RETURN NUMBER IS
  MEDIA NUMBER;
  CLINX EXCEPTION;  
BEGIN
  SELECT AVG(FECHAENTREGA - FECHAPEDIDO) INTO MEDIA FROM MI_PEDIDOS WHERE IDCLIENTE = XIDCLI;
  RETURN MEDIA;
END;

SELECT IDCLIENTE, FN09(IDCLIENTE) FROM MI_CLIENTES WHERE FN09(IDCLIENTE) <= 5;

-- Ejercicio 10
CREATE OR REPLACE PROCEDURE
  PR10(
    XIDPED MI_PEDIDOS.IDPEDIDO%TYPE,
    XNOMPROD MI_PRODUCTOS.DESCRIPCION%TYPE,
    XCANT NUMBER
  ) IS
  PRODID MI_PRODUCTOS.IDPRODUCTO%TYPE;
  PRODSTOCK NUMBER;
  PRECIOUNIDAD NUMBER;
  PEDEXIST NUMBER;
  PROD_NX EXCEPTION;
  PED_NX EXCEPTION;
  NO_STOCK EXCEPTION;
BEGIN
  SELECT COUNT(*) INTO PEDEXIST FROM MI_PEDIDOS WHERE IDPEDIDO = XIDPED;
  IF PEDEXIST = 0 THEN
    RAISE PED_NX;
  END IF;

  SELECT IDPRODUCTO INTO PRODID FROM MI_PRODUCTOS WHERE DESCRIPCION = XNOMPROD;
  IF PRODID IS NULL THEN
    RAISE PROD_NX;
  END IF;

  SELECT STOCK INTO PRODSTOCK FROM MI_PRODUCTOS WHERE IDPRODUCTO = PRODID;
  IF PRODSTOCK < XCANT THEN
    RAISE NO_STOCK;
  END IF;

  SELECT PRECIO_VENTA INTO PRECIOUNIDAD FROM MI_PRODUCTOS WHERE IDPRODUCTO = PRODID;
  INSERT INTO MI_PEDIDOS_PRODUCTOS VALUES (XIDPED, PRODID, XCANT, PRECIOUNIDAD);
  UPDATE MI_PRODUCTOS SET STOCK = PRODSTOCK - XCANT WHERE IDPRODUCTO = PRODID;
  COMMIT;
EXCEPTION
  WHEN PED_NX THEN
    dbms_output.put_line('Pedido no encontrado');

  WHEN PROD_NX THEN
    dbms_output.put_line('Producto no encontrado');

  WHEN NO_STOCK THEN
    dbms_output.put_line('No hay stock suficiente');

  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
    ROLLBACK;
END;

CREATE OR REPLACE PROCEDURE 
  PR12(
    XCURSO MI_CURSOS.IDCURSO%TYPE
  ) IS
  XINSTRUCTOR MI_CURSOS.INSTRUCTOR%TYPE;
BEGIN
  SELECT INSTRUCTOR INTO XINSTRUCTOR FROM MI_CURSOS WHERE IDCURSO=XCURSO;
END;

--- Ejercicio 11
--- Enunciado demasiado rebuscado, no sé qué hacer

--- Ejercicio 12
CREATE OR REPLACE PROCEDURE 
  PR12(
    XCURSO MI_CURSOS.IDCURSO%TYPE
  ) IS
  XINSTRUCTOR MI_CURSOS.INSTRUCTOR%TYPE;
  XCLIENTOTAL NUMBER;
  XCLIENTECUR NUMBER;
  XNUMCURSOS NUMBER;
  CURS_NX EXCEPTION;
BEGIN
  SELECT INSTRUCTOR INTO XINSTRUCTOR FROM MI_CURSOS WHERE IDCURSO=XCURSO;
  IF XINSTRUCTOR IS NULL THEN
    RAISE CURS_NX;
  END IF;

  XCLIENTOTAL := 0;
  XNUMCURSOS := 0;

  DECLARE CURSOR CR IS SELECT IDCURSO FROM MI_CURSOS WHERE INSTRUCTOR = XINSTRUCTOR;
  BEGIN
    FOR REG IN CR
    LOOP
      SELECT COUNT(*) INTO XCLIENTECUR FROM MI_CURSOS_CLIENTES WHERE MI_CURSOS_CLIENTES.IDCURSO = REG.IDCURSO;
      dbms_output.put_line(' - Curso ' || REG.IDCURSO || ': ' || XCLIENTECUR || ' apuntados');
      XCLIENTOTAL := XCLIENTOTAL + XCLIENTECUR;
      XNUMCURSOS := XNUMCURSOS + 1;
    END LOOP;
  END;

  dbms_output.put_line('Total alumnos: ' || XCLIENTOTAL || ' (media: ' || (XCLIENTOTAL / XNUMCURSOS) || ' alum/cur)');
EXCEPTION
  WHEN CURS_NX THEN
    dbms_output.put_line('Curso no valido (no existe o no tiene instructor)');
  WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
END;

--- Ejercicio 13
CREATE OR REPLACE PROCEDURE 
  PR13 IS
  XNUMCURSOS NUMBER;
  XBONUS DECIMAL;
BEGIN
  DECLARE CURSOR CEMP IS SELECT IDEMPLEADO, NOMBRE, APELLIDOS, SALARIO FROM MI_EMPLEADOS WHERE TRABAJO = 'instructor';
  BEGIN
    FOR REMP IN CEMP
    LOOP
      SELECT COUNT(*) INTO XNUMCURSOS FROM MI_CURSOS WHERE INSTRUCTOR = REMP.IDEMPLEADO;
      IF XNUMCURSOS = 0 THEN
        dbms_output.put_line('ALERTA! ALERTA! ' || REMP.NOMBRE || ' ' || REMP.APELLIDOS || ' es un gandul!');
      ELSE
        XBONUS := 0;
        IF XNUMCURSOS >= 2 THEN
          IF XNUMCURSOS >= 4 THEN
            XBONUS := REMP.SALARIO * 0.06;
          ELSE
            XBONUS := REMP.SALARIO * 0.04;
          END IF;
        END IF;

        SELECT COUNT(*) INTO XNUMCURSOS FROM MI_CURSOS WHERE MAX_NUM = (SELECT COUNT(*) FROM MI_CURSOS_CLIENTES WHERE MI_CURSOS.IDCURSO = MI_CURSOS_CLIENTES.IDCURSO);
        XBONUS := XBONUS + XNUMCURSOS * 50;
        dbms_output.put_line(REMP.NOMBRE || ' ' || REMP.APELLIDOS || ': plus de ' || XBONUS || '€');
        --UPDATE MI_EMPLEADOS SET SALARIO = SALARIO + XBONUS WHERE MI_EMPLEADOS.IDEMPLEADO = REMP.IDEMPLEADO;
      END IF;
    END LOOP;
  END;
EXCEPTION WHEN OTHERS THEN
    dbms_output.put_line('Error inesperado');
END;
