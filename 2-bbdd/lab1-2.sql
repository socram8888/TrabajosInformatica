/* AL043 */

/* Ejercicio 1 */
SELECT * FROM v_clientes;

/* Ejercicio 2 */
SELECT * FROM v_clientes WHERE ciudad = 'Burjassot';

/* Ejercicio 3 */
SELECT * FROM v_productos WHERE stock < 10 AND precio_venta > 20;

/* Ejercicio 4 */
SELECT nombre, apellido, email AS "dirección de correo" FROM v_clientes WHERE UPPER(apellido) = 'GARCÍA';

/* Ejercicio 5 */
SELECT idproducto, descripcion, (precio_venta - precio_compra) AS "margen de beneficio" FROM v_productos;

/* Ejercicio 6 */
SELECT * FROM v_clientes WHERE email IS NULL;

/* Ejercicio 7 */
SELECT * FROM v_clientes WHERE email LIKE '%@uv.es';

/* Ejercicio 8 */
SELECT nombremascota, FLOOR((SYSDATE - fechanac) / 365) AS edad FROM v_mascotas WHERE tipoanimal = 1 OR tipoanimal = 2 ORDER BY fechanac;

/* Ejercicio 9 */
SELECT v_clientes.nombre, v_clientes.apellido, v_cursos.titulo, v_cursos.descripcion
  FROM v_clientes
  JOIN v_cursos_clientes ON v_clientes.idcliente = v_cursos_clientes.idcliente
  JOIN v_cursos ON v_cursos_clientes.idcurso = v_cursos.idcurso;

/* Ejercicio 10 */
SELECT * from v_pedidos;
SELECT v_pedidos.* FROM v_pedidos
  JOIN v_pedidos_productos ON v_pedidos.idpedido = v_pedidos_productos.idpedido
  JOIN v_productos ON v_pedidos_productos.idproducto = v_productos.idproducto WHERE UPPER(descripcion) LIKE '%COMIDA PERIQUITOS%'
INTERSECT
SELECT v_pedidos.* FROM v_pedidos
  JOIN v_pedidos_productos ON v_pedidos.idpedido = v_pedidos_productos.idpedido
  JOIN v_productos ON v_pedidos_productos.idproducto = v_productos.idproducto WHERE UPPER(descripcion) LIKE '%COMIDA GATO%';

/* Ejercicio 11 */
SELECT * FROM v_empleados WHERE idempleado NOT IN (SELECT instructor FROM v_cursos WHERE idcurso = 1);

/* Ejercicio 12 */
SELECT COUNT(*) FROM v_cursos WHERE fechahora LIKE '%/08/14';

/* Ejercicio 13 */
SELECT EXTRACT(MONTH FROM fechahora) AS mes, COUNT(*) FROM v_cursos WHERE fechahora LIKE '%/%/14' GROUP BY EXTRACT(MONTH FROM fechahora);

/* Ejercicio 14 */
SELECT * FROM v_empleados WHERE (SELECT COUNT(*) FROM v_cursos WHERE idempleado = instructor) > 3;

/* Ejercicio 15 */
SELECT * FROM v_empleados WHERE salario > (SELECT AVG(salario) FROM v_empleados JOIN v_cursos ON instructor = idempleado);

/* Ejercicio 16 */
SELECT * FROM v_proveedores WHERE email LIKE '%@gmail.com';

/* Ejercicio 17 */
SELECT * FROM v_clientes WHERE idcliente IN (
  (SELECT v_cursos_clientes.idcliente FROM v_cursos_clientes
    JOIN v_cursos ON v_cursos_clientes.idcurso = v_cursos.idcurso
    JOIN v_animales ON v_cursos.tipoanimal = v_animales.tipoanimal WHERE v_animales.nombre = 'Perro')
  MINUS
  (SELECT v_cursos_clientes.idcliente FROM v_cursos_clientes
    JOIN v_cursos ON v_cursos_clientes.idcurso = v_cursos.idcurso
    JOIN v_animales ON v_cursos.tipoanimal = v_animales.tipoanimal WHERE v_animales.nombre != 'Perro')
);

/* Ejercicio 18 */
SELECT trabajo, MIN(salario), MAX(salario), AVG(salario) FROM v_empleados GROUP BY trabajo;

/* Ejercicio 19 */
SELECT nombre, COUNT(*) AS num FROM v_animales
JOIN v_mascotas ON v_animales.tipoanimal = v_mascotas.tipoanimal
GROUP BY nombre
HAVING COUNT(*) >= 2;

/* Ejercicio 20 */
SELECT EXTRACT(MONTH FROM fechapedido) AS mes, COUNT(*) FROM v_pedidos GROUP BY EXTRACT(MONTH FROM fechapedido);

/* Ejercicio 21 */
SELECT * FROM (
  SELECT descripcion,
    (SELECT NVL(SUM(cantidad), 0)
    FROM v_pedidos_productos
    WHERE v_pedidos_productos.idproducto = v_productos.idproducto)
    AS vendidos
  FROM v_productos
  ORDER BY vendidos DESC
) WHERE ROWNUM = 1;

/* Ejercicio 22 */
SELECT  v_cursos.idcurso           ,
        v_cursos.titulo            ,
        v_animales.nombre AS animal,
        v_empleados.nombre         ,
        v_empleados.apellidos
FROM    v_cursos
        LEFT JOIN v_animales
        ON      v_cursos.tipoanimal = v_animales.tipoanimal
        LEFT JOIN v_empleados
        ON      v_cursos.instructor        = v_empleados.idempleado
WHERE   EXTRACT(MONTH FROM fechahora)     >= 5
        AND EXTRACT(MONTH FROM fechahora) <= 7;

/* Ejercicio 23 */
SELECT * FROM (
  SELECT nombre, apellido,
    (SELECT SUM(v_productos.precio_venta * v_pedidos_productos.cantidad)
    FROM v_pedidos_productos, v_productos
    WHERE v_productos.idproducto = v_pedidos_productos.idproducto
    AND v_pedidos_productos.idpedido = v_pedidos.idpedido)
    AS importe
  FROM v_clientes, v_pedidos
  WHERE v_pedidos.idcliente = v_clientes.idcliente
  ORDER BY importe ASC
) WHERE ROWNUM = 1;

/* Ejercicio 24 */
SELECT descripcion,
	(precio_venta - precio_compra) * stock AS beneficio
FROM v_productos
ORDER BY beneficio DESC;

/* Ejercicio 25 */
SELECT idpedido FROM v_pedidos_productos WHERE idproducto=1
UNION
SELECT idpedido FROM v_pedidos_productos WHERE idproducto=5
MINUS
SELECT idpedido FROM v_pedidos_productos WHERE idproducto=3;

/* Ejercicio 26 */
SELECT  *
FROM    v_cursos
WHERE   fechahora >= sysdate
        AND max_num <=
        (
                SELECT  COUNT(*)
                FROM    v_cursos_clientes
                WHERE   v_cursos.idcurso = v_cursos_clientes.idcurso
        );
