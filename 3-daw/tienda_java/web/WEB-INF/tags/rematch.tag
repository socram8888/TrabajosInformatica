<%@tag description="Executes if pattern matches the input" pageEncoding="UTF-8"%>
<%@attribute name="var" type="java.lang.String"%>
<%@attribute name="regex" type="java.lang.String" required="true"%>
<%@attribute name="input" type="java.lang.String" required="true"%>
<%@attribute name="casefold" type="java.lang.Boolean"%>

<%
    java.util.regex.Pattern pat;
    if (casefold == Boolean.TRUE) {
        pat = java.util.regex.Pattern.compile(regex, java.util.regex.Pattern.UNICODE_CASE);
    } else {
        pat = java.util.regex.Pattern.compile(regex);
    }

    boolean matches = pat.matcher(input).matches();
    if (var != null) {
        jspContext.setAttribute(var, Boolean.valueOf(matches), PageContext.REQUEST_SCOPE);
    }

    if (matches) {
%>
        <jsp:doBody />
<%
    }
%>
