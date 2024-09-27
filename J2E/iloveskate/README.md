# ILoveSkate - A new revolutionary forum for Skate Lovers

## Project structure

- src/main
    - java/dev/max/iloveskate
        - controller : Controller class
        - models :  Data model descriptions
    - ressources : config files and other utils
    - webapp
        - static : static assets
        - WEB-INF
            - views : Data views

## MySQL default configuration

| Option         | value            |
|----------------|------------------|
| Database name  | `iloveskate`     |
| MySQL User     | `iloveskate`     |
| MySQL Password | `Iloveskate123!` |

You can change the mysql connection details in `src/main/java/resources/application.properties`

## Tailwind styles build

We edited the css, we rebuilt tailwind styles with the following command :

`npm` is required for building the css files.

To generate the `style.css` file, we installed dependencies with

```shell
npm i
```

then launched the css building script

```shell
npm run build:postcss
```
Then, we added some more css, so make sure, to make it in another repository than the one you were in if you want so.

## Demo setup

To run the demo, you need to have a MySQL server running on your machine.

In the mysql server you'll need a table using the configuration detailed above in the MySQL default configuration
section.

In your mysqlDB, you will have to create a mysql user as previously said. Then, before launching the project, you'll need to create a database called 
```shell
iloveskate
```

## Run the project

Once the database is set up, you can build and run the project with the following command :

```shell
./mvnw spring-boot:run
```
