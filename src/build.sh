echo "Start compiling..."
g++ main.cpp gamelogic.cpp backgroundcontroller.cpp textures.cpp GameObjects/animationcontroller.cpp GameObjects/gameobject.cpp GameObjects/playergameobject.cpp GameObjects/blockgameobject.cpp -o ./output -lsfml-graphics -lsfml-window -lsfml-system
echo "Finished compiling..."