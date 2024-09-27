<jsp:useBean id="user" scope="session" type="dev.max.iloveskate.model.User"/>
<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col overflow-x-hidden">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>

<div class="grow w-screen px-16 min-h-[85vh] grid">
    <form class="w-full text-4xl lg:text-base lg:w-1/2 lg:max-w-screen-sm place-self-center"
          method="post" action="/account">
        <div class="my-16">
            <h1 class="text-8xl lg:text-5xl font-black tracking-tight">Compte</h1>
            <h2 class="text-4xl lg:text-2xl tracking-tight">Tu peux modifier ton profil ici</h2>
        </div>
        <label class="text-slate-600 text-xl" for="username" style="color:rgb(0,250,0)">Nom d'utilisateur</label>
        <input value="${user.username}"
               class="w-full block px-8 py-5 mb-8 lg:mb-4 lg:py-3 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
               id="username" name="username" type="text" placeholder="Nom d'utilisateur"/>
        <label class="text-slate-600 text-xl" for="email" style="color:rgb(0,250,0)">Email</label>
        <input value="${user.email}"
               class="w-full block px-8 py-5 mb-8 lg:mb-4 lg:py-3 border-2 rounded ${empty error ? "border-java-black" : "border-java-red"}"
               id="email" name="email" type="text" placeholder="Email"/>
        <label class="text-slate-600 text-xl" for="currpass" style="color:rgb(0,250,0)">Ton Mot de Passe Actuel</label>
        <input class="w-full block px-8 py-5 mb-8 lg:mb-4 lg:py-3 border-2 rounded-lg lg:rounded ${empty error ? "border-java-black" : "border-java-red"}"
               id="currpass" name="currentPassword" type="password" placeholder="Mot de passe"/>
        <label class="text-slate-600 text-xl" for="newpass" style="color:rgb(0,250,0)">Nouveau mot de passe</label>
        <input class="w-full block px-8 py-5 mb-8 lg:mb-4 lg:py-3 border-2 rounded-lg lg:rounded ${empty error ? "border-java-black" : "border-java-red"}"
               id="newpass" name="newPassword" type="password" placeholder="Nouveau mot de passe"/>
        <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
        <button class="w-full text-5xl lg:text-lg block px-8 py-6 lg:py-3 rounded-lg lg:rounded-lg  ${empty error ? "bg-java-black" : "bg-java-red"}"
                type="submit" style="background-color: black; color: white">${empty error ? "Mettre a jour" : error}</button>
    </form>
</div>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
</body>
</html>