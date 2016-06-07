<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<t:template title="Productos" selected="products">
    <t:sqlconn>
        <sql:query var="productQuery" dataSource="${database}">
            SELECT id, price, image FROM products WHERE available = true;
        </sql:query>
    </t:sqlconn>
            
    <div id="products">
        <c:forEach items="${productQuery.rows}" var="product">
            <div class="product" style="background-image: url('${product.image}');">
                <div class="pricing">${product.price} €</div>
                <a href="/products/view/?id=${product.id}"></a>
            </div>
        </c:forEach>
    </div>
</t:template>
