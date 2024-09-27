<jsp:useBean id="post" scope="request" type="dev.max.iloveskate.model.Post"/>
<%@ page import="com.asosyalbebe.moment4j.Moment" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<div class="w-full text-5xl lg:text-base mb-8 lg:mb-0" style="color: rgb(175, 175, 175)">
    dans la conversation <a class="font-bold inline-block mb-2 lg:mb-0" href="/posts/${post.id}" style="color: rgb(104,0,0)">${post.thread.title}</a>
    <span
            class="text-slate-600 leading-none text-4xl lg:text-base" style="color: rgb(0,0,104)">le ${Moment.moment(post.creationDate).format("dd/MM/YY hh:mm")} </span>
    <a class="w-full text-4xl lg:text-base my-2 block text-slate-600"
       href="/posts/${post.id}" style="color: white; margin-left: 5%">${post.getContentSummary(100)}</a>
</div>
<br>