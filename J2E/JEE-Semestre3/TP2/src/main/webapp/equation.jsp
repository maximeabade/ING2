<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Equation</title>
</head>
<body>
	<p>
		<%
			String aStr = request.getParameter("a");
			String bStr = request.getParameter("b");
			String cStr = request.getParameter("c");
			float a = Float.parseFloat(aStr);
			float b = Float.parseFloat(bStr);
			float c = Float.parseFloat(cStr); 

			float delta = b*b-4*a*c;
			if(delta < 0){
				%><p style="color: red"> <%
				//cas ou ya pas de racine reelle
				out.println("Pas de racine reelle... T_T");
				%></p><%
			}
			else if(delta == 0) {
				//cas ou il ya une seule racine reelle
				%><p style = "color : rgb(215,128,0)">
				<%
				//LOGIKK
				float result = -b/(2*a);
				out.println("Racine unique x =" + result);
				%>
				</p><%
			}
			else {
				//cas de deux racines reelles
				%><p style = "color : rgb(0,0,255)">
				<%
				//Logikk
				double racine1 = (-b - Math.sqrt(delta))/(2*a);
				double racine2 =(-b + Math.sqrt(delta))/(2*a);
				out.println("premiere racine : " + racine1 + " , et voici la seconde racine : " + racine2);
			}
		%>
	</p>


</body>
</html>