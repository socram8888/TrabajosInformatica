<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>

<t:sqlconn>
    <sql:query var="productQuery" dataSource="${database}">
        SELECT name, description, price, image, available FROM products WHERE id = ? AND available = 1;
        <sql:param value="${param.id}" />
    </sql:query>
</t:sqlconn>

<c:choose>
    <c:when test="${productQuery.rowCount == 1}">
        <c:set var="product" value="${productQuery.rows[0]}" />

        <t:template title="${product.name}" selected="products">
            <div class="product-info">
                <div class="image">
                    <img src="${product.image}">
                </div>

                ${product.description}

                <form method="get" action="/cart/additem/">
                    <input name="quantity" type="number" min="1" step="1" max="99" value="1">
                    <input name="product" type="hidden" value="${param.id}">
                    <input name="session" type="hidden" value="${pageContext.session.id}">
                    <input type="submit" value="Comprar →">
                </form>
            </div>
        </t:template>
    </c:when>
    
    <c:otherwise>
        <t:template title="Producto no encontrado" selected="products">
            <p class="error">No se ha encontrado ningún producto con el ID especificado.</p>
        </t:template>
    </c:otherwise>
</c:choose>
