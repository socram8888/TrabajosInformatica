<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:csrfprotect>
    <t:template title="Cerrar sesión" selected="user">
        <c:choose>
            <c:when test="${sessionScope.userid == null}">
                <h2>No has iniciado sesión</h2>
            </c:when>

            <c:otherwise>
                <c:remove scope="session" var="userid" />
                <h2>Sesión cerrada satisfactoriamente</h2>
            </c:otherwise>
        </c:choose>
    </t:template>
</t:csrfprotect>