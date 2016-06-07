<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<%@tag description="Protects against CSRF" pageEncoding="UTF-8"%>

<c:choose>
   <c:when test='${param.session != null && param.session == pageContext.session.id}'>
       <jsp:doBody />
   </c:when>

    <c:otherwise>
        <c:redirect url="/csrf/" />
    </c:otherwise>
</c:choose>
