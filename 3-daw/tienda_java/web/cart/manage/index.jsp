<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<t:csrfprotect>
    <t:requirelevel level="user">
        <c:choose>
            <c:when test="${param.buy != null}">
                <t:sqlconn>
                    <sql:transaction dataSource="${database}">
                        <sql:update var="orderQuery">
                            INSERT INTO orders(address) SELECT id FROM address WHERE id = ? AND user = ${sessionScope.userid};
                            <sql:param value="${param.address}" />
                        </sql:update>

                        <sql:query var="orderIdQuery">
                            SELECT LAST_INSERT_ID() as orderId;
                        </sql:query>
                    </sql:transaction>
                </t:sqlconn>

                <c:if test="${orderQuery == 0}">
                    <c:redirect url="/cart/?invalidaddress=1" />
                </c:if>

                <c:set var="orderId" value="${orderIdQuery.rows[0].orderId}" />
                <t:sqlconn>
                    <sql:transaction dataSource="${database}">
                        <sql:update>
                            INSERT
                                INTO orderproducts(orderid, product, quantity, price)
                                SELECT ${orderId}, id, quantity, price
                                FROM cart
                                JOIN products ON cart.product = products.id
                                WHERE user = ${sessionScope.userid};
                        </sql:update>

                        <sql:update>
                            DELETE FROM cart WHERE user = ${sessionScope.userid};
                        </sql:update>

                        <sql:update>
                            INSERT INTO orderevents(orderid, eventid) VALUES(${orderId}, 1);
                        </sql:update>
                    </sql:transaction>
                </t:sqlconn>

                <c:redirect url="/user/order/?id=${orderIdQuery.rows[0].orderId}" />
            </c:when>

            <c:when test="${param.clean != null}">
                <t:sqlconn>
                    <sql:update dataSource="${database}">
                        DELETE FROM cart WHERE user = ${sessionScope.userid};
                    </sql:update>
                </t:sqlconn>
            </c:when>
        </c:choose>

        <c:redirect url="/cart/" />
    </t:requirelevel>
</t:csrfprotect>
                        