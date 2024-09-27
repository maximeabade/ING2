hjuy,;k<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>
<div class="grow w-screen text-center">
    <img class="mx-auto pointer-events-none w-2/3 lg:w-1/4 aspect-square"
         src="${pageContext.request.contextPath}/static/images/broken.png" alt="Content not found error icon"/>
    <h1 class="my-16 lg:my-8 text-5xl lg:text-xl font-bold"><%= pageContext.getAttribute("error") == null || pageContext.getAttribute("error").toString().isEmpty() ? "GRRRRR POURQUOI T'ES LA?!" : pageContext.getAttribute("error").toString() %>
    </h1>
    <span class="text-4xl lg:text-base">Tu peux retourner a l'<a href="${pageContext.request.contextPath}/">ACCUEIL</a> ou regarder le <a
        href="/explore">FIL</a> des discussions</span>
</div>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
</body>
</html>