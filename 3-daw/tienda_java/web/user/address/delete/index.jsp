<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<t:csrfprotect>
    <t:requirelevel level="user">
        <t:sqlconn>
            <sql:transaction dataSource="${database}">
                <sql:update>
                    UPDATE address SET deleted = 1 WHERE id = ? AND user = ${sessionScope.userid};
                    <sql:param value="${param.id}" />
                </sql:update>
            </sql:transaction>
        </t:sqlconn>

        <c:redirect url="/user/#address" />
    </t:requirelevel>
</t:csrfprotect>