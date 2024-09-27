<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col overflow-x-hidden">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>

<div class="grow w-screen px-16 grid">
    <form class="w-full text-4xl lg:text-base lg:w-1/2 lg:max-w-screen-sm place-self-center space-y-8 lg:space-y-3"
          method="post" action="${pageContext.request.contextPath}/login">
        <div class="my-16">
            <h1 class="text-8xl lg:text-5xl font-black tracking-tight">Re, cher rider!</h1>
            <h2 class="text-4xl lg:text-2xl tracking-tight">Genre t'as pas de compte? <a href="/register" style="color:rgb(104,0,0);text-decoration: underline">Inscris-toi</a>, tu vas voir on est bien la</h2>
        </div>
        <input value="${login}"
               class="w-full block px-8 py-5 lg:py-3 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
                   name="login" type="text" placeholder="Nom d'utilisateur"/>
        <input class="w-full block px-8 py-5 lg:py-3 border-2 rounded-lg lg:rounded ${empty error ? "border-java-black" : "border-java-red"}"
               name="password" type="password" placeholder="Mot de passe"/>
        <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
        <button class="w-full text-5xl lg:text-lg block px-8 py-6 lg:py-3 rounded-lg lg:rounded-lg  ${empty error ? "bg-java-black" : "bg-java-red"}" style="background-color: black; color: white"
                type="submit">${empty error ? "Connexion" : "Bouh, c'est pas bon!"}</button>
        <p id="help" class="w-full py-12 text-center">Ptit probleme... ou <span
                class=" cursor-pointer underline" style="color: rgb(104,0,0)">t'as oublie tes logs?</span> ?</p>
    </form>
</div>
<script src="${pageContext.request.contextPath}/static/js/account/smtp.js"></script>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
</body>
</html>