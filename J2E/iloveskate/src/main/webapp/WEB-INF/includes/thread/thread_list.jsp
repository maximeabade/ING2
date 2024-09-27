<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<jsp:useBean id="threads" scope="request" type="java.util.List<dev.max.iloveskate.model.Thread>"/>
<c:choose>
    <c:when test="${empty threads}">
        <div class=" text-center" style="margin-left:10%">
            <img class="mx-auto pointer-events-none w-2/3 lg:w-1/4 aspect-square"
                 src="${pageContext.request.contextPath}/static/images/broken.png"
                 alt="Content not found error icon"/>
            <h1 class="my-16 lg:my-8 text-5xl lg:text-xl font-bold">Ya rien ici...</h1>
            <span class="text-4xl lg:text-base">Tu peux retourner a l'<a href="${pageContext.request.contextPath}/">ACCUEIL</a> ou regarder le <a
                    href="/explore">FIL</a> des discussions</span>
        </div>
    </c:when>
    <c:otherwise>
        <c:forEach items="${threads}" var="thread_item">
            <c:set value="${thread_item}" var="thread" scope="request"/>
            <jsp:include page="thread_list_item.jsp"/>
        </c:forEach>
    </c:otherwise>
</c:choose>

