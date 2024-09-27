<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<jsp:useBean id="thread" scope="request" type="dev.max.iloveskate.model.Thread"/>
<span class="inline-block">
    [
    <c:forEach var="tag" items="${thread.tags}">
        <a class=" text-5xl lg:text-base" href="/tags/${tag.id}" style="color:rgb(0, 255, 0); ">${tag.displayName}</a>
    </c:forEach>
    ]
</span>