<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ page import="dev.max.iloveskate.model.Thread" %>
<%@ page import="dev.max.iloveskate.model.Post" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>

<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col overflow-x-hidden">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>
<%
    Thread thread = (Thread) request.getAttribute("thread");
%>
<div class="grow w-screen min-h-screen lg:px-24 text-5xl lg:text-base grid mb-12" style="background-color:rgb(150,150,150)">
    <div class="w-screen px-8 lg:p-0 lg:w-1/2 lg:max-w-screen-2xl place-self-center">
        <c:if test="${thread.removed}">
            <h2 class="text-6xl lg:text-4xl mt-4 lg:mb-2 font-bold break-keep block">
                Supprime
            </h2>
        </c:if>
        <c:if test="${thread.locked}">
            <h2 class="text-6xl lg:text-4xl mt-4 lg:mb-2 font-bold  break-keep block">
                Verouille
            </h2>
        </c:if>
        <h1 class="text-8xl lg:text-5xl mt-4 mb-2 font-bold decoration-4  break-keep block">
            <%=thread.getTitle()%>
        </h1>
        <c:if test="${user != null && (user.admin || user.id == thread.entry.author.id)}">
            <button class="text-slate-600 text-5xl mb-4 lg:mb-0 lg:text-sm hover:underline"
                    id="rm-thread-${thread.id}" style="color:rgb(104,0,0)">Supprimer
            </button> | 
            <c:if test="${user.admin}">
                <button class="text-slate-600 text-5xl lg:text-sm hover:underline "
                        id="lock-thread-${thread.id}"" style="color:rgb(104,0,0)">Fermer
                </button>
            </c:if>
        </c:if>
        <div class="text-3xl lg:text-lg" style="color:rgb(0,0,104); font-size:x-large">
            #
            <jsp:include page="/WEB-INF/includes/thread/taglist.jsp"/>
        </div>
        <div class="text-2xl lg:text-base mb-4 lg:mb-2" style="color:rgb(0, 0, 0); margin-left:5%">
            <jsp:include page="/WEB-INF/includes/thread/date-author.jsp"/>
        </div>
        <div class="my-2 z-0">
            <%
                List<Post> posts = new ArrayList<>();
                posts.add(((Thread) request.getAttribute("thread")).getEntry());
                request.setAttribute("posts", posts);
            %>
            <jsp:include page="/WEB-INF/includes/thread/post.jsp"/>
        </div>
    </div>
    <input id="csrf" type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
</div>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
<script src="${pageContext.request.contextPath}/static/js/content/threads.js"></script>
</body>
</html>