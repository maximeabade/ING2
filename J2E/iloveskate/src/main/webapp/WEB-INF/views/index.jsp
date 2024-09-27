<!DOCTYPE html>
<html>
<jsp:include page="/WEB-INF/includes/head.jsp"/>
<body class="min-h-screen flex flex-col overflow-x-hidden ">
<jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>

<div class="grow w-screen px-16 break-words grid">
    <div class="max-w-full place-self-center font-bold text-7xl lg:text-5xl">
        <h1 style="color:rgb(104,0,0)">Bienvenue sur I Love Skate</h1>
        <h1>Ton forum ouvert sur le <span style="color: rgb(104,0,0)">Skateboard</span>, ta toute nouvelle plateforme ou tu peux partager ta passion! </h1>
        <div class="lg:max-w-[66%] my-16 text-5xl lg:text-3xl tracking-tight break-words">
            Connecte-toi pour rejoindre
            <a href="/explore"> les discussions</a>
            ou
            <a href="/new">en commencer une</a>! <br><br><br>
              C'EST TOI QUI FAIS VIVRE LE SITE!<br>
        </div>
    </div>
</div>
<jsp:include page="/WEB-INF/includes/footer.jsp"/>
</body>
</html>