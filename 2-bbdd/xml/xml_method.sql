-- NOTA: Las tablas se llaman "MI_*" (ej MI_CLIENTES en lugar de simplemente CLIENTES) porque era el nombre de las tablas privadas de cada usuario de los laboratorios

CREATE OR REPLACE PROCEDURE SALELOG IS
BEGIN
	DBMS_OUTPUT.PUT_LINE('<store>');
	DBMS_OUTPUT.PUT_LINE('    <clients>');
	DECLARE CURSOR CR IS SELECT IDCLIENTE, NOMBRE, APELLIDO, EMAIL, DIRECCIONPOSTAL, CIUDAD FROM MI_CLIENTES;
	BEGIN
		FOR REG IN CR
		LOOP
			DBMS_OUTPUT.PUT_LINE('        <client id="' || REG.IDCLIENTE || '">');
			DBMS_OUTPUT.PUT_LINE('            <name>' || REG.NOMBRE || '</name>');
			DBMS_OUTPUT.PUT_LINE('            <surname>' || REG.APELLIDO || '</surname>');
			DBMS_OUTPUT.PUT_LINE('            <email>' || REG.EMAIL || '</email>');
			DBMS_OUTPUT.PUT_LINE('            <address>' || REG.DIRECCIONPOSTAL || '</address>');
			DBMS_OUTPUT.PUT_LINE('            <city>' || REG.CIUDAD || '</city>');
			DBMS_OUTPUT.PUT_LINE('        </client>');
		END LOOP;
	END;
	DBMS_OUTPUT.PUT_LINE('    </clients>');
	DBMS_OUTPUT.PUT_LINE('');
	DBMS_OUTPUT.PUT_LINE('    <products>');
	DECLARE CURSOR CR IS SELECT IDPRODUCTO, DESCRIPCION, PRECIO_VENTA, STOCK FROM MI_PRODUCTOS;
	BEGIN
		FOR REG IN CR
		LOOP
			DBMS_OUTPUT.PUT_LINE('        <product id="' || REG.IDPRODUCTO || '">');
			DBMS_OUTPUT.PUT_LINE('            <desc>' || REG.DESCRIPCION || '</desc>');
			DBMS_OUTPUT.PUT_LINE('            <price>' || REG.PRECIO_VENTA || '</price>');
			DBMS_OUTPUT.PUT_LINE('            <quantity>' || REG.STOCK || '</quantity>');
			DBMS_OUTPUT.PUT_LINE('        </product>');
		END LOOP;
	END;
	DBMS_OUTPUT.PUT_LINE('    </products>');
	DBMS_OUTPUT.PUT_LINE('');
	DBMS_OUTPUT.PUT_LINE('    <sales>');
	DECLARE CURSOR CSALE IS SELECT IDPEDIDO, IDCLIENTE, FECHAPEDIDO, FECHAENTREGA, DIRECCIONENTREGA FROM MI_PEDIDOS;
	BEGIN
		FOR RSALE IN CSALE
		LOOP
			DBMS_OUTPUT.PUT_LINE('        <sale id="' || RSALE.IDPEDIDO || '">');
			DBMS_OUTPUT.PUT_LINE('            <clientid>' || RSALE.IDCLIENTE || '</clientid>');
			DBMS_OUTPUT.PUT_LINE('            <buydate>' || RSALE.FECHAPEDIDO || '</buydate>');
			DBMS_OUTPUT.PUT_LINE('            <arrivaldate>' || RSALE.FECHAENTREGA || '</arrivaldate>');
			DBMS_OUTPUT.PUT_LINE('            <address>' || RSALE.DIRECCIONENTREGA || '</address>');

			DBMS_OUTPUT.PUT_LINE('            <items>');
			DECLARE CURSOR CITEM IS SELECT IDPRODUCTO, CANTIDAD, PRECIOREAL FROM MI_PEDIDOS_PRODUCTOS WHERE IDPEDIDO = RSALE.IDPEDIDO;
			BEGIN
				FOR RITEM IN CITEM
				LOOP
					DBMS_OUTPUT.PUT_LINE('                <item>');
					DBMS_OUTPUT.PUT_LINE('                    <itemid>' || RITEM.IDPRODUCTO || '</itemid>');
					DBMS_OUTPUT.PUT_LINE('                    <quantity>' || RITEM.CANTIDAD || '</quantity>');
					DBMS_OUTPUT.PUT_LINE('                    <price>' || RITEM.PRECIOREAL || '</price>');
					DBMS_OUTPUT.PUT_LINE('                </item>');
				END LOOP;
			END;
			DBMS_OUTPUT.PUT_LINE('            </items>');

			DBMS_OUTPUT.PUT_LINE('        </sale>');
		END LOOP;
	END;
	DBMS_OUTPUT.PUT_LINE('    </sales>');
	DBMS_OUTPUT.PUT_LINE('</store>');
END;
