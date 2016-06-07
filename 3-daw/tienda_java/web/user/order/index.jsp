<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>

<t:template title="Pedido" selected="user" level="user">
    <t:sqlconn>
        <sql:query var="orderQuery" dataSource="${database}">
            SELECT orders.id, address.name AS name, street, streetdoor, housedoor, city, zip, countries.name AS country
            FROM orders
            JOIN address ON orders.address = address.id
            JOIN countries ON address.country = countries.code
            WHERE address.user = ${sessionScope.userid} AND orders.id = ?;
            <sql:param value="${param.id}" />
        </sql:query>
    </t:sqlconn>

    <c:choose>
        <c:when test="${orderQuery.rowCount > 0}">
            <c:set var="order" value="${orderQuery.rows[0]}" />

            <t:sqlconn>
                <sql:query var="statusQuery" dataSource="${database}">
                    SELECT time, description, trackingurl, trackingcode
                        FROM orderevents
                        JOIN events ON orderevents.eventid = events.id
                        WHERE orderid = ?
                        ORDER BY time DESC;
                    <sql:param value="${param.id}" />
                </sql:query>

                <sql:query var="productQuery" dataSource="${database}">
                    SELECT name, quantity, orderproducts.price * quantity AS subtotal
                        FROM orderproducts
                        JOIN products ON orderproducts.product = products.id
                        WHERE orderid = ?;
                    <sql:param value="${param.id}" />
                </sql:query>
            </t:sqlconn>

            <ul>
                <li>Código: ${order.id}</li>
                <li>Dirección:
                    ${order.name},
                    ${order.street},
                    <c:if test="${order.streetdoor != null}">Nº${order.streetdoor},</c:if>
                    <c:if test="${order.housedoor != null}">Pta ${order.housedoor},</c:if>
                    ${order.city},
                    CP ${order.zip},
                    ${order.country}
                </li>
            </ul>

            <h2>Estado</h2>
            <table id="carttable">
                <tr>
                    <th>Fecha</th>
                    <th>Estado</th>
                    <th>Seguimiento</th>
                </tr>

                <c:forEach items="${statusQuery.rows}" var="orderStatus">
                    <tr>
                        <td>${orderStatus.time}</td>
                        <td>${orderStatus.description}</td>
                        <td>
                            <c:choose>
                                <c:when test="${orderStatus.trackingcode != null and orderStatus.trackingurl != null}">
                                    <a href="${fn:replace(orderStatus.trackingurl, '%tracking%', orderStatus.trackingcode)}" target="_blank">${orderStatus.trackingcode}</a>
                                </c:when>
                                    
                                <c:when test="${orderStatus.trackingcode}">
                                    ${orderStatus.trackingcode}
                                </c:when>
                            </c:choose>
                        </td>
                    </tr>
                </c:forEach>
            </table>

            <h2>Productos</h2>
            <c:set var="total" value="0" />
            <table id="carttable">
                <tr>
                    <th>Producto</th>
                    <th>Subtotal</th>
                    <th>Cantidad</th>
                </tr>

                <t:sqlconn>
                    <sql:query var="productQuery" dataSource="${database}">
                        SELECT name, quantity, orderproducts.price * quantity AS subtotal
                            FROM orderproducts
                            JOIN products ON orderproducts.product = products.id
                            WHERE orderid = ?;
                        <sql:param value="${param.id}" />
                    </sql:query>
                </t:sqlconn>

                <c:forEach items="${productQuery.rows}" var="orderItem">
                    <c:set var="total" value="${total + orderItem.subtotal}" />

                    <tr>
                        <td>${orderItem.name}</td>
                        <td>${orderItem.subtotal} €</td>
                        <td>${orderItem.quantity}</td>
                    </tr>
                </c:forEach>
            </table>
            <p>Total: ${total} €</p>
        </c:when>
            
        <c:otherwise>
            <p class="error">No se ha encontrado el pedido especificado.</p>
        </c:otherwise>
    </c:choose>
</t:template>
