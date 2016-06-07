<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<t:csrfprotect>
    <t:requirelevel level="guest">
        <c:set var="email" value="${fn:toLowerCase(param.email)}" />
        <t:rematch regex="^[a-z0-9._]+@[a-z0-9-]+(\.[a-z0-9-]+)+$" input="${email}" var="emailOk" />
        <c:set var="emailOk" value="${emailOk && fn:length(email) < 64}" />

        <c:choose>
            <c:when test="${emailOk}">
                <t:sqlconn>
                    <sql:transaction dataSource="${database}">
                        <sql:update var="createQuery">
                            INSERT IGNORE INTO users(email, password) VALUES(?, SHA2(CONCAT('${passSalt}', 0x00, email, 0x00, ?), 256));
                            <sql:param value="${email}" />
                            <sql:param value="${param.password}" />
                        </sql:update>

                        <sql:query var="userIdQuery">
                            SELECT LAST_INSERT_ID() as userId;
                        </sql:query>
                    </sql:transaction>
                </t:sqlconn>

                <c:choose>
                    <c:when test="${createQuery == 1}">
                        <c:set var="userid" scope="session" value="${userIdQuery.rows[0].userId}" />
                        <c:redirect url="/user/" />
                    </c:when>

                    <c:otherwise>
                        <c:redirect url="/user/register/?emailexists=true" />
                    </c:otherwise>
                </c:choose>
            </c:when>

            <c:otherwise>
                <c:redirect url="/user/register/?emailinvalid=true" />
            </c:otherwise>
        </c:choose>
    </t:requirelevel>
</t:csrfprotect>