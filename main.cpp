#include "src/headers/libs.h"
#include "src/model/player.h"
#include "server/hdr/TcpServer.h"
#include "server/src/TcpServer.cpp"
#include <mutex>

std::string getHostStr(const TcpServer::Client& client) {
    uint32_t ip = client.getHost ();
    return std::string() + std::to_string(int(reinterpret_cast<char*>(&ip)[0])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[1])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[2])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[3])) + ':' +
           std::to_string( client.getPort ());
}
std::string getHostStr(uint32_t ip, uint16_t port) {
    return std::string() + std::to_string(int(reinterpret_cast<char*>(&ip)[0])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[1])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[2])) + '.' +
           std::to_string(int(reinterpret_cast<char*>(&ip)[3])) + ':' +
           std::to_string( port );
}

int main() {
    TcpServer::Client* wait_client = nullptr;
    std::mutex mtx;

    //Create object of TcpServer
    TcpServer server( 8080,
            //P2P connection
                      [&wait_client, &mtx](TcpServer::Client client){
                          mtx.lock();
                          if(wait_client == nullptr){
                              wait_client = &client;
                              std::cout << "Client " << getHostStr(client) << " wait other client...\n";
                              mtx.unlock();
                              client.waitConnect();
                          } else {
                              TcpServer::Client* other_client = wait_client;
                              wait_client = nullptr;
                              std::cout << "Client " << getHostStr(client) << " connected to client " << getHostStr(*other_client) <<'\n';
                              mtx.unlock();
                              client.connectTo (*other_client);
                          }
                          std::cout << "Peer pair disconnected" << std::endl;
                      });

    //Start server
    if(server.start() == TcpServer::status::up) {
        std::cout<<"Server listen on port:"<<server.getPort()<<std::endl;
        server.joinLoop();
    } else {
        std::cout<<"Server start error! Error code:"<< int(server.getStatus()) <<std::endl;
        return -1;
    }
//    float scaling_ground, scaling_ground_down;
//    int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
//    int tempY = 0;//коорд Y
//    float distance = 0;//это расстояние от объекта до тыка курсора
//    sf::Texture BackgroundTexture;
//    sf::Texture MiddleBackgroundTexture;
//    sf::Sprite MiddleBackground;
//    sf::Sprite background;
//    sf::Vector2u TextureSize;  //Added to store texture size.
//    sf::Vector2u WindowSize;
//    sf::Vector2u MiddleTextureSize;  //Added to store texture size.
//
//    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fang Game");
//    window.setVerticalSyncEnabled(true);
//    float WindowSizeY = window.getSize().y;
//    float WindowSizeX = window.getSize().x;
////    float WindowSizeYUpper = WindowSizeY;
////    float WindowSizeYMiddle = WindowSizeY*2/3;
////    float WindowSizeYDown = WindowSizeY/3;
//    float WindowSizeYUpper = WindowSizeY/3*2;
//    float WindowSizeYDown = WindowSizeY/3;
//
//    sf::RectangleShape example_shape(sf::Vector2f(100, 50));
//    sf::Event event;
//    if (!window.getSize().y != 720)
//    {
//        scaling_ground = WindowSizeY/2.05;
//        scaling_ground_down = WindowSizeY/1.89;
//        std::cout << "Upper:" << WindowSizeYUpper << std::endl << "Down:" << WindowSizeYDown << std::endl;
//    }
//
//    if (window.isOpen()
//
//            ) {
//        std::cout << "Loaded" << std::endl;
//    } else {
//        std::cout << "Window loading error!" << std::endl;
//    }
//    Texture t;
////    Texture background;
////    background.loadFromFile("images/background.jpg");
//    t.loadFromFile("images/fang.png"); // загружаем картинку
//    float currentFrame = 0;
//
//    PLAYER p(t); // загружаем текстуру
////    PLAYER b(background);
//    if(!BackgroundTexture.loadFromFile("images/background.png"))
//    {
//        return -1;
//    }
//    else
//    {
//        TextureSize = BackgroundTexture.getSize(); //Get size of texture.
//        WindowSize = window.getSize();             //Get size of window.
//
//        float ScaleX = (float) WindowSize.x / TextureSize.x;
//        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.
//        background.setTexture(BackgroundTexture);
//        background.setScale(ScaleX, ScaleY);      //Set scale.
//        if(!MiddleBackgroundTexture.loadFromFile("images/borders.png"))
//        {
//            return -1;
//        }
//        else
//        {
//            TextureSize = MiddleBackgroundTexture.getSize(); //Get size of texture.
//            MiddleBackground.setTexture(MiddleBackgroundTexture);
//            MiddleBackground.setScale(ScaleX, ScaleY);      //Set scale.
//        }
//    }
//
//
//    Clock clock; /* засекаем время с последнего тика( чтобы привязка персонажа была ко времени, а не к мощности процессора) */
//
//
//    while (window.
//
//            isOpen()
//
//            ) {
//        float time = clock.getElapsedTime().asMicroseconds(); /* создаем переменную время, getElapsedTime() - дать прошедшее время( возьмем  его в микросекундах) */
//
//        clock.restart(); // перезагружает часы
//        time = time / 400; //здесь происходит регулировка скорости движения персонажа
//
//        Vector2i pixelPos;
//        pixelPos = Mouse::getPosition(window);//забираем коорд курсора
//        Vector2f pos;
//        pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
//
//
//        Event event;
//
//        while (window.pollEvent(event)) {
//
//            switch (event.type) {
//                case sf::Event::Closed:
//                    window.close();
//                    break;
//                case sf::Event::Resized: {
//                    float w = static_cast<float>(event.size.width);
//                    float h = static_cast<float>(event.size.height);
//                    window.setView(
//                            sf::View(
//                                    sf::Vector2f(w / 2.0, h / 2.0),
//                                    sf::Vector2f(w, h)
//                            )
//                    );
//                    break;
//                }
//                default:
//                    break;
//            }
//
//            if (event.type == Event::MouseButtonPressed) //если нажата клавиша мыши
//                if (event.key.code == Mouse::Left) {  //а именно левая
//                    if (p.sprite.getGlobalBounds().contains(pos.x,
//                                                            pos.y))//и при этом координата курсора попадает в спрайт
//                    {
//                        std::cout << "X:" << pos.x << " Y:" << pos.y << std::endl;
//
//                    }
//                }
//            if (p.isSelect)//если выбрали объект
//                if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
//                    if (event.key.code == Mouse::Right) { //а именно правая
//// nothing
//                        tempX = pos.x;//забираем координату нажатия курсора Х
//                        tempY = pos.y;//и Y
//                        std::cout << "tempX:" << tempX << " tempY:" << tempY << std::endl;
//                    }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Left)) // если клавиша нажата и клавиша налево
//        {
//            if (pos.x < WindowSizeX/2 && pos.y > WindowSizeYUpper) {
//                p.right_down = -0.1; // при нажатии направо- ускоряемся на 0.
//                ground = scaling_ground;
//            }
//            if (pos.x < WindowSizeX/2 && pos.y > WindowSizeYDown && pos.y < WindowSizeYUpper) {
//                p.dx = -0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x < WindowSizeX/2 && pos.y < WindowSizeYDown) {
//                p.right_up = -0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x > WindowSizeX/2 && pos.y > WindowSizeYUpper) {
//                p.right_down_rev = -0.1; // при нажатии направо- ускоряемся на 0.
//                ground = scaling_ground;
//            }
//            if (pos.x > WindowSizeX/2 && pos.y > WindowSizeYDown && pos.y < WindowSizeYUpper) {
//                p.dx_rev = -0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x > WindowSizeX/2 && pos.y < WindowSizeYDown) {
//                p.right_up_rev = -0.1;
//                ground = scaling_ground;
//            }
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Right)) // если клавиша нажата и клавиша направо
//        {
//            if (pos.x > WindowSizeX/2 && pos.y > WindowSizeYUpper) {
//                p.right_down = 0.1; // при нажатии направо- ускоряемся на 0.1
//                ground = scaling_ground;
//            }
//            if (pos.x > WindowSizeX/2 && pos.y > WindowSizeYDown && pos.y < WindowSizeYUpper) {
//                p.dx = 0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x > WindowSizeX/2 && pos.y < WindowSizeYDown) {
//                p.right_up = 0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x < WindowSizeX/2 && pos.y > WindowSizeYUpper) {
//                p.right_down_rev = 0.1; // при нажатии направо- ускоряемся на 0.1
//                ground = scaling_ground;
//            }
//            if (pos.x < WindowSizeX/2 && pos.y > WindowSizeYDown && pos.y < WindowSizeYUpper) {
//                p.dx_rev = 0.1;
//                ground = scaling_ground;
//            }
//            if (pos.x < WindowSizeX/2 && pos.y < WindowSizeYDown) {
//                p.right_up_rev = 0.1;
//                ground = scaling_ground;
//            }
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down) &&
//            Keyboard::isKeyPressed(Keyboard::Right)) // если клавиша вправо нажата и клавиша пробел
//        {
//            p.dz = 0.1;
//            ground = scaling_ground_down;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down) &&
//            Keyboard::isKeyPressed(Keyboard::Left)) // если клавиша влево нажата и клавиша пробел
//        {
//            p.dz = -0.1;
//            ground = scaling_ground_down;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Up)) // вверх
//        {
//            if (p.onGround) {
//                p.dy = -0.5;
//                p.onGround = false;
//            } // если мы на земле, то только тогда можем осуществить прыжок
//            ground = scaling_ground;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::RAlt) && Keyboard::isKeyPressed(Keyboard::Right)) {
//            p.gun = 0.1;
//            ground = scaling_ground;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::RAlt) && Keyboard::isKeyPressed(Keyboard::Left)) {
//            p.gun = -0.1;
//            ground = scaling_ground;
//        }
//
//
//        p.update(time,WindowSizeY/430,WindowSizeY/430); // загружаем время
//
//
//        window.clear(Color::White); // очищаем экран
//        window.draw(background); // background image
//        window.draw(p.sprite);// рисуем спрайт
//        window.draw(MiddleBackground); // middle background
//        window.display(); // выводим на дисплей
//    }

    return 0;
}