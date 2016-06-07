<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql"%>
<%@taglib prefix="t" tagdir="/WEB-INF/tags"%>

<%@tag description="Initializes SQL stuff" pageEncoding="UTF-8"%>

<%@variable name-given="passSalt"%>
<c:set var="passSalt" value="pdmWodWXkTrm4AfIAiu44a1yuOXvLGK432azyBYdAhlAL72quB8mvNzpqCxbkKpr" />

<%@variable name-given="database"%>
<sql:setDataSource var="database" driver="com.mysql.jdbc.Driver"
        url="jdbc:mysql://localhost/cursodaw?useOldAliasMetadataBehavior=true"
        user="root" password="" />

<jsp:doBody />
