# ofUnderQml

Using openFrameworks for rendering with QML for the UI

The repository contains an empty example and a simple one which displays the result of the draw() method from openFrameworks with a button from QML (with both communicating).

Basically, the main class is ```ofUnderQml``` inheriting from  ```QQuickItem``` and does mainly two things : 
* Passes all user input to the openFrameworks app (named ```ofAppQml``` which inherits both ```QObject``` and ```ofBaseApp```)
* Enables the openFrameworks rendering 

On the OF side, the connection with the QML button is done in the setup using the Qt method ```connect```

 
