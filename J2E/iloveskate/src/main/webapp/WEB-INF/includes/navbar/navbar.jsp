<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page import="dev.max.iloveskate.model.User" %>
<%
    User user = (User) request.getAttribute("user");
%>
<div class="h-32 lg:h-20 navbar" style="background-color:rgb(130,130,130); background-attachment:fixed; padding:0%">
  <div id="navbar" class="w-screen fixed left-0 right-0 top-0 m-0 px-8 h-32 lg:h-20" style="background-color: rgb(130,130,130)">
    <div class=" w-full h-full flex">
        <a href="/" class="h-full flex-none align-middle cursor-pointer align-bottom">
            <img class="aspect-square inline-block h-full"
                 src="${pageContext.request.contextPath}/static/images/iloveskate-128x128.png"  alt="iloveskate-icon"/> 
            <div class="hidden lg:inline-block align-middle">
                <p class="font-black tracking-tight text-xl">I Love Skate</p>
                <p class="font-italic tracking-tighter text-sm leading-3">Le nouveau forum des amoureux du skate</p>
            </div>
        </a>
        <nav class="invisible lg:visible grow pl-20 w-max space-x-4 text-xl h-full align-bottom leading-[3rem]">
            <a href="/" >Accueil</a>
            <a href="/explore" >Fil</a>
            <a href="/top" >Top</a>
            <a href="/recent" >Recents</a>
            <a href="/about" >A propos</a>
            <c:if test="${user.isAdmin()}">
                <a href="/tags" >#Tags</a>
            </c:if>

        </nav>
        <jsp:include page="right-corner.jsp"/>
    </div>
  </div>
</div>