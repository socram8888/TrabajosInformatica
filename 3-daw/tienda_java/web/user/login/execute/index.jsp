<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<t:requirelevel level="guest">
    <c:if test="${param.email != null && param.password != null}">
        <t:sqlconn>
            <sql:query var="loginQuery" dataSource="${database}">
                SELECT id FROM users WHERE email = ? AND password = SHA2(CONCAT('${passSalt}', 0x00, email, 0x00, ?), 256) AND level > 0 LIMIT 1;
                <sql:param value="${param.email}" />
                <sql:param value="${param.password}" />
            </sql:query>

            <c:if test="${loginQuery.rowCount > 0}">
                <c:set var="userid" scope="session" value="${loginQuery.rows[0].id}" />
            </c:if>
        </t:sqlconn>
    </c:if>

    <c:choose>
        <c:when test="${sessionScope.userid == null}">
            <c:redirect url="/user/login/">
                <c:param name="failed" value="true" />
                <c:param name="redirect" value="${param.redirect}" />
            </c:redirect>
        </c:when>

        <c:when test='${param.redirect != null && param.redirect != ""}'>
            <c:redirect url="${param.redirect}" />
        </c:when>

        <c:otherwise>
            <c:redirect url="/user/" />
        </c:otherwise>
    </c:choose>
</t:requirelevel>