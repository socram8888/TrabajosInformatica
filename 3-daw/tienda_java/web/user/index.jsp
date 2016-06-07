<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:template title="Usuario" selected="user" level="user">
    <t:sqlconn>
        <sql:query var="userDataQuery" dataSource="${database}">
            SELECT * FROM users WHERE id = ${sessionScope.userid} LIMIT 1;
        </sql:query>
            
        <sql:query var="addressQuery" dataSource="${database}">
            SELECT * FROM address WHERE user = ${sessionScope.userid} AND deleted = 0;
        </sql:query>

        <sql:query var="orderQuery" dataSource="${database}">
            SELECT orders.id, description AS status, time
                FROM orders
                JOIN address ON orders.address = address.id
                JOIN orderevents ON orders.id = orderevents.orderid
                JOIN events ON orderevents.eventid = events.id
                WHERE user = ${sessionScope.userid}
                    AND orderevents.id = (
                        SELECT id FROM orderevents
                            WHERE orderid = orders.id ORDER BY time DESC LIMIT 1)
                ORDER BY time DESC;
        </sql:query>
    </t:sqlconn>

    <ul>
        <li>ID de usuario: ${sessionScope.userid}</li>
        <li>Correo electrónico: ${userDataQuery.rows[0].email}</li>
        <li>Su contraseña se encuentra almacenada de forma segura con SHA-256 en nuestra base de datos</li>
        <li><a href="/user/logout/?session=${pageContext.session.id}">Cerrar sesión</a></li>
    </ul>

    <a name="address"><h2>Direcciones</h2></a>
    <c:if test="${param.addrcreated != null}">
        <p class="success">Dirección creada satisfactoriamente</p>
    </c:if>
    <ul>
        <c:forEach items="${addressQuery.rows}" var="address">
            <li>
                ${address.name},
                ${address.street},
                <c:if test="${address.streetdoor != null}">Nº${address.streetdoor},</c:if>
                <c:if test="${address.housedoor != null}">Pta ${address.housedoor},</c:if>
                ${address.city},
                CP ${address.zip},
                ${address.country}
                (<a href="/user/address/delete/?id=${address.id}&session=${pageContext.session.id}">Eliminar</a>)
            </li>
        </c:forEach>
        <li><a href="/user/address/">Añadir una nueva dirección</a></li>
    </ul>

    <a name="address"><h2>Pedidos</h2></a>
    <ul>
        <c:forEach items="${orderQuery.rows}" var="order">
            <li>
                <a href="/user/order/?id=${order.id}">Pedido #${order.id} (${order.time}: ${order.status})</a>
            </li>
        </c:forEach>
    </ul>
</t:template>
