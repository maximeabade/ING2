<jsp:useBean id="error" scope="request" type="java.lang.String"/>
<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>
<div class="grow w-screen px-24 text-5xl lg:text-base grid mb-12">
    <div class="w-full lg:w-1/2 lg:max-w-screen-2xl place-self-center">
        <h1 class="text-8xl lg:text-5xl font-bold mt-8">Lance une conversation</h1>
        <p class="text-5xl lg:text-2xl mb-12">N'OUBLIE SURTOUT PAS LES <a href="/rules" referrerpolicy="no-referrer"
                                                                           target="_blank">REGLES</a>!</p>
        <form class="w-full" action="/threads" method="POST">
            <input class="block w-full px-4 py-4 lg:py-2 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
                   id="title" name="title" type="text" placeholder="Sujet" value="${title}"/>
            <textarea
                    class="block mt-4 resize-none w-full px-4 py-4 lg:py-2 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
                    id="content" name="content" placeholder="Raconte-nous tout...">${content}</textarea>
            <div id="preview-content"
                 class="w-full bg-slate-200 rounded-lg prose prose-xl p-2 hidden max-w-full overflow-x-scroll"></div>
            
            <div class="text-5xl lg:text-2xl my-8 lg:my-4 ">
                <h2 class="text-5xl lg:text-2xl text-black">Choisis ton flux de conversation</h2>
                <jsp:include page="../../includes/thread/fetch_tags.jsp"/>
            </div>

            <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
            <button class="w-full mt-4 text-5xl lg:text-lg block px-8 py-6 lg:py-3 rounded-lg lg:rounded-lg text-white bg-black" style="background-color:black; color: white" type="submit">${empty error ? "Lance la conv!" : error}</button>

        </form>
    </div>
</div>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
<script src="${pageContext.request.contextPath}/static/js/content/new.js"></script>
</body>
</html>