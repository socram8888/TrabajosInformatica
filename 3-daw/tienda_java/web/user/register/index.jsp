<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:template title="Registrarse" selected="user" level="guest">
    <c:if test="${param.emailexists != null}">
        <p class="error">El correo electrónico especificado ya ha sido registrado en nuestro sistema.</p>
    </c:if>

    <c:if test="${param.emailinvalid != null}">
        <p class="error">El correo electrónico especificado no es válido.</p>
    </c:if>

    <form action="/user/register/execute/" method="post">
        <label for="email">E-mail</label>: <input type="email" id="email" name="email"><br>
        <label for="password">Contraseña</label>: <input type="password" id="password" name="password"><br>
        <input type="hidden" name="session" value="${pageContext.session.id}" />
        <input type="submit" name="register" value="Registrarse">
    </form>
</t:template>
