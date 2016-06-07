<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:csrfprotect>
    <t:requirelevel level="user">
        <c:if test='${param.product != null && param.quantity != null}'>
            <c:if test="${param.quantity > 0}">
                <t:sqlconn>
                    <sql:update dataSource="${database}">
                        INSERT INTO cart(user, product, quantity) VALUES(${sessionScope.userid}, ?, ?) ON DUPLICATE KEY UPDATE quantity = quantity + ?;
                        <sql:param value="${param.product}" />
                        <sql:param value="${param.quantity}" />
                        <sql:param value="${param.quantity}" />
                    </sql:update>
                </t:sqlconn>
            </c:if>
        </c:if>

        <c:redirect url="/cart/" />
    </t:requirelevel>
</t:csrfprotect>
                        