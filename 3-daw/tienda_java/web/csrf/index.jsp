<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<t:template title="Error" selected="home">
    <p class="error">La sesión no se corresponde</p>
    <p>El valor "session" de la petición no se corresponde con el código de la sesión de tu navegador. Por seguridad y para <a href="https://es.wikipedia.org/wiki/Cross-site_request_forgery">evitar ataques de CSRF</a>, se ha bloqueado el intento de cierre de sesión.</p>
    <p>Vuelve atrás y reintenta realizar la operación. Si el problema persiste, <a href="/contact/">contacta con el administrador</a>.</p>
</t:template>
