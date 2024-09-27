<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<div class="w-56 text-xl h-full align-bottom" style="background-color: rgb(130,130,130)">
    <div class="block lg:hidden p-2 w-full h-full">
    <span id="navbar-toggle" class="inline w-fit h-full text-4xl cursor-pointer select-none float-right">
          <button id="menu">MENU</button>
    </span>
    </div>
    <div id="navbar-content" 
         class="absolute left-0 right-0 h-screen lg:h-max lg:static hidden lg:block cursor-pointer float-right" >
        <div class="w-full px-48 lg:p-0 lg:px-4 z-50" style="background-color:rgb(130,130,130)">
            <nav class="block lg:hidden py-12 text-3xl" style="background-color: rgb(130,130,130)">
                <h2 class="text-4xl font-bold mb-12 cursor-default select-none" style="background-color:rgb(130,130,130)">Nav</h2>
                <jsp:include page="content.jsp"/>
            </nav>
            <c:choose>
                <c:when test="${empty user}">
                    <h2 class="lg:hidden text-4xl font-bold mb-12 cursor-default select-none">Compte</h2>
                    <a class="text-3xl lg:text-xl block rounded-lg px-0 lg:px-6 py-3 align-top" href="/login">Login</a>
                </c:when>
                <c:otherwise><h2 class="lg:hidden text-4xl font-bold mb-12 cursor-default select-none">Compte</h2>
                    <jsp:include page="profile.jsp"/>
                </c:otherwise>
            </c:choose>

        </div>
    </div>
</div>
<script>
    let menu = document.getElementById("menu");
    menu.addEventListener("click", function () {
        if (menu.innerHTML == "MENU") {
            menu.innerHTML = " X ";
            //rid of old classes
            menu.setAttribute("class", "");
            //add new classes
            menu.classList.add("text-3xl");
        } else {
            menu.innerHTML = "MENU";
                        //rid of old classes
            menu.setAttribute("class", "");
            //add new classes
            menu.classList.add("text-3xl");
        }
    });
</script>