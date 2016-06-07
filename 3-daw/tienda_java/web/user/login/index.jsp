<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:template title="Iniciar sesión" selected="user" level="guest">
    <c:url var="loginUrl" value="/user/login/execute/">
        <c:param name="redirect" value="${param.redirect}" />
    </c:url>

    <c:if test="${param.failed != null}">
        <p class="error">El usuario y contraseña especificados no se corresponden con ningún usuario activo registrado.</p>
    </c:if>

    <div>
        <form action="${loginUrl}" method="post">
            <label for="email">E-mail</label>: <input type="email" id="email" name="email"><br>
            <label for="password">Contraseña</label>: <input type="password" id="password" name="password"><br>
            <input type="submit" name="login" value="Iniciar sesión">
        </form>
    </div>

    <p>¿No tienes una cuenta? <a href="/user/register/">¡Regístrate!</a></p>
</t:template>
