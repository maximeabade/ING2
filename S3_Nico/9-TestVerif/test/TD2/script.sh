javac -d out Exo1.java
javac -d out -cp junit-platform-console-standalone-1.8.1.jar:out TestExo1.java
java -jar junit-platform-console-standalone-1.8.1.jar -cp out --scan-classpath
