<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<jsp:useBean id="user" scope="session" type="dev.max.iloveskate.model.User"/>
<div id="profile-quick-access" class="w-full px-0 lg:px-3 mb-12 lg:mb-2 text-6xl lg:text-2xl select-none" style="background-color:rgba(160, 160, 160, 0)">
    <div class="font-bold truncate text-2xl" >
        Hey, ${user.username}
        <c:if test="${user.isAdmin()}">
            <span style="color:rgb(104, 0, 0)">(Administrateur)</span>
        </c:if>
    </div>
    <div class="border-l-2pl-2 text-2xl lg:text-xs">
        ${user.points} points
    </div>
</div>
<div id="profile-dropdown" class="px-0 lg:hidden text-3xl lg:text-xl lg:py-3">
    <ul class="py-3" style="color: white">
        <c:if test="${user.admin}">
            <li>
                <a href="/tags">#Tags</a>
            </li>
        </c:if>
        <li>
            <a href="/new">Nouvelle conv</a>
        </li>
        <li>
            <a href="/profile">Profil</a>
        </li>
        <li>
            <a href="/account">Params du compte</a>
        </li>
        <li>
            <form action="/logout" method="post">
                <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
                <input class="cursor-pointer" type="submit" value="Deco">
            </form>
        </li>
    </ul>
</div>