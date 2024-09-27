<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col overflow-x-hidden">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>

<div class="grow w-screen px-16 grid">
    <form class="w-full text-4xl lg:text-base lg:w-1/2 lg:max-w-screen-sm place-self-center space-y-8 lg:space-y-3"
          method="post" action="/register">
        <div class="my-16">
            <h1 class="text-8xl lg:text-5xl font-black tracking-tight">Bienvenue, rider!</h1>
            <h2 class="text-4xl lg:text-2xl tracking-tight">Bah, comment ca t'as un compte ? <a
                    class="underline text-java-red"
                    href="${pageContext.request.contextPath}/login">Connexion</a></h2>
        </div>
        <div class="grid grid-cols-4 h-max">
            <input id="username" value="${username}"
                   class="col-span-3 inline-block px-8 py-5 lg:py-3 border-y-2 border-l-2 rounded-l ${empty error ? "border-java-black" : "border-java-red"} focus:border-background-default"
                   name="username" type="text" placeholder="Nom d'utilisateur"/>
            <button id="check-button"
                    class="text-background-default w-full border-2 border-r-2 inline-block rounded-r ${empty error ? "bg-java-black" : "bg-java-red"} ${empty error ? "border-java-black" : "border-java-red"}" style="background-color: black">
                Check
            </button>
        </div>
        <label class="px-2 text-slate-400 text-2xl lg:text-xs" for="username">4-16 caracteres, et unique tout comme toi</label>
        <input id="email" value="${email}"
               class="w-full block px-8 py-5 lg:py-3 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
               name="email" type="text" placeholder="Email"/>
        <label class="px-2 text-slate-400 text-2xl lg:text-xs" for="email">C'est qu'une demo du site, rentre ce que tu veux, hein... Tant que ya @ dedans...</label>
        <input id="password"
               class="w-full block px-8 py-5 lg:py-3 border-2 rounded-lg lg:rounded ${empty error ? "border-java-black" : "border-java-red"}"
               name="password" type="password" placeholder="Mot de Passe"/>
        <label class="px-2 text-slate-400 text-2xl lg:text-xs" for="password">Ton MDP doit etre compose de au moins ca:<span class="block px-2">^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$</span></label>
        <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
        <button class="w-full text-5xl lg:text-lg block px-8 py-6 lg:py-3 rounded-lg lg:rounded-lg  ${empty error ? "bg-java-black" : "bg-java-red"}" style="background-color:black; color: white"
                type="submit">${empty error ? "Connexion" : error }</button>
        <p id="help" class="w-full py-12 text-center">Mmmmmh... Deja besoin d'aide?<span
                class="text-java-red cursor-pointer underline">ALED!</span></p>
    </form>
</div>
<script src="${pageContext.request.contextPath}/static/js/account/smtp.js"></script>
<script src="${pageContext.request.contextPath}/static/js/account/usernamecheck.js"></script>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
</body>
</html>