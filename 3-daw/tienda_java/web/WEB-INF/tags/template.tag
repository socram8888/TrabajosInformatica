<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<%@tag description="Base template" pageEncoding="UTF-8"%>
<%@attribute name="title" required="true"%>
<%@attribute name="selected"%>
<%@attribute name="level"%>

<t:requirelevel level="${level}">

<!DOCTYPE html>
<html>
    <head>
        <title>${title} - SleepingDogs</title>
        <meta charset="utf-8">
        <link rel="stylesheet" type="text/css" href="/static/style.css">
    </head>
    <body>
        <div id="logo">
            <h1>Sleeping<wbr>Dogs</h1>
        </div>
        <div id="pagechooser">
            <ul>
                <li><a href="/"<c:if test='${selected == "home"}'> class="selected"</c:if>>Inicio</a></li>
                <li><a href="/about/"<c:if test='${selected == "about"}'> class="selected"</c:if>>Empresa</a></li>
                <li><a href="/contact/"<c:if test='${selected == "contact"}'> class="selected"</c:if>>Contacto</a></li>
                <li><a href="/products/"<c:if test='${selected == "products"}'> class="selected"</c:if>>Productos</a></li>
                <li><a href="/cart/"<c:if test='${selected == "cart"}'> class="selected"</c:if>>Carrito</a></li>
                <li><a href="/user/"<c:if test='${selected == "user"}'> class="selected"</c:if>>Usuario</a></li>
                <li><a href="http://localhost/daw/"<c:if test='${selected == "admin"}'> class="selected"</c:if>>Administrador</a></li>
            </ul>
        </div>
        <div id="content">
            <h1>${title}</h1>
            <jsp:doBody />
        </div>
        <div id="footer">
            &copy;2016 <a href="https://socram.ovh/">socram</a>
        </div>
    </body>
</html>

</t:requirelevel>
