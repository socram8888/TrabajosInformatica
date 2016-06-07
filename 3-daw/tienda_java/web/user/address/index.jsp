<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>

<t:template title="Crear dirección" selected="user" level="user">
    <t:sqlconn>
        <sql:query var="countryQuery" dataSource="${database}">
            SELECT code, name FROM countries ORDER BY name;
        </sql:query>
    </t:sqlconn>

    <form method="post" action="/user/address/add/">
        <label for="addrname">Nombre y apellidos:</label> <input type="text" name="name" id="addrname" size="64"><br>
        <label for="addrstreet">Calle:</label> <input type="text" name="street" id="addrstreet" size="48"><br>
        <label for="addrstrno">Número:</label> <input type="text" name="streetdoor" id="addrstrno" size="4"><br>
        <label for="addrhouseno">Puerta:</label> <input type="text" name="housedoor" id="addrhouseno" size="4"><br>
        <label for="addrcity">Población:</label> <input type="text" name="city" id="addrcity" size="32"><br>
        <label for="addrzip">Código Postal:</label> <input type="text" name="zip" id="addrzip" size="8"><br>
        <label for="addrcountry">País:</label> <select name="country" id="addrcountry">
            <c:forEach items="${countryQuery.rows}" var="country">
                <option value="${country.code}"<c:if test="${country.code == 'ESP'}"> selected</c:if>>${country.name}</option>
            </c:forEach>
        </select><br>
        <input name="session" type="hidden" value="${pageContext.session.id}">
        <input type="submit" value="Crear">
    </form>
</t:template>
