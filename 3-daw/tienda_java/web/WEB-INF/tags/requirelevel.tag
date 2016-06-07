<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>

<%@tag description="Requires a certain privilege level" pageEncoding="UTF-8"%>
<%@attribute name="level" required="true"%>

<c:if test="${sessionScope.userid != null}">
    <t:sqlconn>
        <sql:query dataSource="${database}" var="userQuery">
            SELECT 1 FROM users WHERE id = ${sessionScope.userid} AND level > 0;
        </sql:query>
    </t:sqlconn>

    <c:if test="${userQuery.rowCount == 0}">
        <c:remove var="userid" scope="session" />
    </c:if>
</c:if>

<c:choose>
    <c:when test='${level == "user" && sessionScope.userid == null}'>
        <c:redirect url="/user/login/">
            <c:param name="redirect" value="${pageContext.request.requestURI}?${pageContext.request.queryString}" />
        </c:redirect>
    </c:when>

    <c:when test='${level == "guest" && sessionScope.userid != null}'>
        <c:redirect url="/user/" />
    </c:when>
</c:choose>

<jsp:doBody/>
