<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<t:template title="Carrito" selected="cart" level="user">
    <t:sqlconn>
        <sql:query var="cartQuery" dataSource="${database}">
            SELECT id, name, quantity, price * quantity AS subtotal FROM cart JOIN products ON cart.product = products.id WHERE user = ?;
            <sql:param value="${sessionScope.userid}" />
        </sql:query>

        <sql:query var="addressQuery" dataSource="${database}">
            SELECT id, address.name AS name, street, streetdoor, housedoor, city, zip, countries.name AS country FROM address JOIN countries ON address.country = countries.code WHERE user = ${sessionScope.userid} AND deleted = 0;
        </sql:query>
    </t:sqlconn>

    <c:choose>
        <c:when test="${cartQuery.rowCount == 0}"> 
            <h2>El carro está vacío</h2>
            <p>¡Pero no tiene porqué estarlo! ¡Échale un ojo a <a href="/products/">nuestros productos</a>!</p>
        </c:when>
            
        <c:otherwise>
            <h2>Productos</h2>
            
            <c:set var="total" value="0" />
            <table id="carttable">
                <tr>
                    <th>Producto</th>
                    <th>Subtotal</th>
                    <th>Cantidad</th>
                </tr>

                <c:forEach items="${cartQuery.rows}" var="cartItem">
                    <c:set var="total" value="${total + cartItem.subtotal}" />

                    <tr>
                        <td>${cartItem.name}</td>
                        <td>${cartItem.subtotal} €</td>
                        <td>
                            <form method="get" action="/cart/updateitem/">
                                <input name="quantity" type="number" min="0" step="1" max="99" value="${cartItem.quantity}">
                                <input name="product" type="hidden" value="${cartItem.id}">
                                <input name="session" type="hidden" value="${pageContext.session.id}">
                                <input type="submit" value="→">
                            </form>
                        </td>
                    </tr>
                </c:forEach>
            </table>
            <p>Total: ${total} €</p>
            
            <form method="get" action="/cart/manage/">
                <h2>Dirección de envío</h2>
                <ul>
                    <c:forEach items="${addressQuery.rows}" var="address">
                        <li>
                            <input name="address" value="${address.id}" type="radio" id="address${address.id}">
                            <label for="address${address.id}">
                                ${address.name},
                                ${address.street},
                                <c:if test="${address.streetdoor != null}">Nº${address.streetdoor},</c:if>
                                <c:if test="${address.housedoor != null}">Pta ${address.housedoor},</c:if>
                                ${address.city},
                                CP ${address.zip},
                                ${address.country}
                            </label>
                        </li>
                    </c:forEach>
                    <li><a href="/user/address/?cart=true">Añadir una nueva dirección</a></li>
                </ul>
                
                <h2>Trámites</h2>
                <input name="session" type="hidden" value="${pageContext.session.id}">
                <input type="submit" name="buy" value="Comprar">
                <input type="submit" name="clean" value="Vaciar">
            </form>
        </c:otherwise>
    </c:choose>
</t:template>
