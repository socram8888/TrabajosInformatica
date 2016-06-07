<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<t:csrfprotect>
    <t:requirelevel level="user">
        <c:set var="email" value="${fn:toLowerCase(param.email)}" />
        <t:rematch regex="^[a-z0-9._]+@[a-z0-9-]+(\.[a-z0-9-]+)+$" input="${email}" var="emailOk" />
        <c:set var="emailOk" value="${emailOk && fn:length(email) < 64}" />

        <c:choose>
            <c:when test="${
                fn:length(param.name) > 1 &&
                fn:length(param.street) > 1 &&
                fn:length(param.city) > 1 &&
                fn:length(param.zip) > 1 &&
                fn:length(param.country) == 3
            }">
                <t:sqlconn>
                    <sql:transaction dataSource="${database}">
                        <sql:update var="createQuery">
                            INSERT
                                INTO address(user, name, street, streetdoor, housedoor, city, zip, country)
                                VALUES(${sessionScope.userid}, ?, ?, NULLIF(?, ''), NULLIF(?, ''), ?, ?, ?);
                            <sql:param value="${param.name}" />
                            <sql:param value="${param.street}" />
                            <sql:param value="${param.streetdoor}" />
                            <sql:param value="${param.housedoor}" />
                            <sql:param value="${param.city}" />
                            <sql:param value="${param.zip}" />
                            <sql:param value="${param.country}" />
                        </sql:update>
                    </sql:transaction>
                </t:sqlconn>

                <c:redirect url="/user/?addrcreated=true#address" />
            </c:when>

            <c:otherwise>
                <c:redirect url="/user/address/?addrinvalid=true" />
            </c:otherwise>
        </c:choose>
    </t:requirelevel>
</t:csrfprotect>