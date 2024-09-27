<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<jsp:useBean id="tags" scope="request" type="java.util.List<dev.max.iloveskate.model.Tag>"/>

<!DOCTYPE html>
<html>
    <jsp:include page="/WEB-INF/includes/head.jsp"/>
    <body class="min-h-screen flex flex-col" style="background-color:rgb(100,100,100)">
        <jsp:include page="/WEB-INF/includes/navbar/navbar.jsp"/>
        <c:if test="${not empty error}">
            <h1 class="text-4xl ">${error}</h1>
        </c:if>
        <div class="w-screen min-h-full my-48 lg:my-28 grow" style="background-color:rgb(100,100,100)">
            <div class="w-full mx-auto lg:w-2/3" style="background-color:rgb(100,100,100)">
                <table class="table text-center w-full" style="background-color:rgb(100,100,100)">
                    <thead style="background-color: rgb(100,100,100)">
                        <tr class="font-bold w-full border-b-2 "style="background-color: rgb(100,100,100)">
                            <th style="background-color: rgb(100,100,100)" >Nom</th>
                            <th style="background-color: rgb(100,100,100)" >Description</th>
                            <th style="background-color: rgb(100,100,100)" colspan="2">Actions</th>
                        </tr>
                    </thead>
                    <tbody>
                        <c:forEach var="tag" items="${tags}">
                            <tr class="w-full" id="edit-tag-${tag.id}" style="background-color:rgba(100, 100, 100, 0)">
                                <td class="w-2/12"style="background-color:rgb(0, 0, 0)"><input class="w-full p-1 text-center" type="text" name="name" value="${tag.displayName}" style="background-color:rgb(0, 0, 0); color:rgb(0, 255, 0)"></td>
                                <td class="w-6/12"><input class="w-full p-1 text-center" type="text" name="description" value="${tag.description}" style="background-color:rgb(100, 100, 100); color:rgb(104, 0,0)"></td>
                                <td class="w-1/12" style="background-color:rgb(0, 0, 0)"><button id="save-tag-${tag.id}" class="w-full" style="background-color:rgb(0, 0, 0); color:white">Editer</button></td>
                                <td class="w-1/12" style="background-color:rgb(0, 0, 0)"><button id="delete-tag-${tag.id}" class="w-full"style="background-color:rgb(0, 0, 0); color:white">Supprimer</button></td>
                            </tr>
                        </c:forEach>
                        <tr class="w-full" id="new-tag" style="background-color:rgb(100, 100, 100)">
                            <td style="display:none"><input class="w-full p-1 text-center" type="text" name="id" ></td>
                            <td><input class="w-full p-1 text-center" type="text" name="name" placeholder="Nom du TAG"></td>
                            <td><input class="w-full p-1 text-center" type="text" name="description" placeholder="Description"></td>
                            <td colspan="2" style="background-color:black"><button class="w-full" id="create-tag" style="background-color:rgb(0, 0, 0); color:white" onfocus="idmaker()">Creer un Nouvel #Tag</button></td>
                        </tr>
                    </tbody>
                </table>
            </div>
            <input id="csrf" type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>

        </div>
        <jsp:include page="/WEB-INF/includes/footer.jsp"/>
        <script src="/static/js/content/tags.js"></script>
        <script>
            function idmaker(){
                var id = document.getElementById("new-tag").getElementsByTagName("input")[0];
                id.value = document.getElementById("new-tag").getElementsByTagName("input")[1].value;
                console.log(id.value);
            }
        </script>
    </body>
</html>