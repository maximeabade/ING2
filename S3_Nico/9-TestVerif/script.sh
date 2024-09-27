javac -d out TD4EX2.java
javac -d out -cp junit-platform-console-standalone-1.8.1.jar:out TestTD4EX2.java
java -jar junit-platform-console-standalone-1.8.1.jar -cp out --scan-classpath
