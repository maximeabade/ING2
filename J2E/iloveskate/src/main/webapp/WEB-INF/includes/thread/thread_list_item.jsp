<jsp:useBean id="thread" scope="request" type="dev.max.iloveskate.model.Thread"/>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<div class="w-full text-5xl lg:text-base mb-8 lg:mb-0">
    <jsp:include page="taglist.jsp"/>
    <a class="font-bold inline-block mb-2 lg:mb-0"
       href="/threads/${thread.id}"><span
            class="text-slate-600 lg:text-sm" style="color:rgb(104,0,0)">${thread.entry.votesCount} like</span> - <span style="font-size:larger">${thread.title}</span> <c:if
            test="${thread.removed || thread.locked}"> <span class="text-slate-600">-<c:if
            test="${thread.removed}"> Supprime</c:if><c:if
            test="${thread.locked}"> Ferme</c:if></span></c:if></a>
    <jsp:include page="date-author.jsp"/>
    <a class="w-full text-4xl lg:text-base my-2 block text-slate-600"
       href="/threads/${thread.id}" style="color:rgb(0,0,104); margin-left: 5%">${thread.entry.getContentSummary(200)}</a>
</div>
<br>