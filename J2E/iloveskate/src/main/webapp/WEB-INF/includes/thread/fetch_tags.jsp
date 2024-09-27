<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<jsp:useBean id="tags" scope="request" type="java.util.List<dev.max.iloveskate.model.Tag>"/>
<c:forEach var="tag" items="${tags}">
    <label>
        <input type="checkbox" name="tag" value="${tag.id}" style="color:rgb(104,0,0)"/>
            ${tag.displayName}
    </label>
</c:forEach>