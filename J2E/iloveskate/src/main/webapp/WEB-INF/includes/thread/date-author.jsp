<jsp:useBean id="thread" scope="request" type="dev.max.iloveskate.model.Thread"/>
<%@ page import="com.asosyalbebe.moment4j.Moment" %>

<h2 class="text-slate-600 text-4xl lg:text-base leading-none" style="color:white">Cree
    le ${Moment.moment(thread.entry.creationDate).format("dd/MM/YY HH:mm")}
    par <a href="/users/${thread.entry.author.username}">${thread.entry.author.username}</a>
</h2>