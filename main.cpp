#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unistd.h>

using namespace sf;
int ground = 500;

class START {
public:
    START() {
        sf::Font font;
        if (font.loadFromFile("fonts/ariel.ttf"));
        sf:
        Text text;
        text.setFont(font);
        text.setString("HelloWorld");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
    }
};

class PLAYER { /* создаем класс PLAYER( нам нужно чтобы движения персонажа осуществлялись под действием  гравитации) */

public:
    float dx, dy, dz, gun, right_down, right_up; // скорость
    float dx_rev, gun_rev, right_down_rev, right_up_rev; // реверсивная скорость
    FloatRect rect; //  здесь rect(x, y, widht, height)
    bool onGround; /*  onGround- переменная, которая показывает, находится ли персонаж на земле */
    Sprite sprite; // сюда будем загружать картинку
    float currentFrame; //  текущий кадр для анимации
    bool life, isMove, isSelect; // добавили переменные состояния движения и выбора объекта

    PLAYER(Texture &image) {
        life = true;
        isMove = false;
        isSelect = false;
        sprite.setTexture(image); // в конструктор класса загружаем картинку
        rect = FloatRect(0, 0, 40, 50); /* указываем первоначальные координаты x=0, y=0, ширина-40, высота-50 */

        dx = dy = dz = gun = right_down = right_up = 0;
        dx_rev = gun_rev = right_up_rev = right_down_rev = 0;
        currentFrame = 0;
    }

    void update(float time) {
        rect.left += dx * time; // rect.left-есть координата х, перемещаем ее на dx*time
        rect.left += dz * time; // dz переменная
        rect.left += gun * time; // ходьба с оружием
        rect.left += right_down * time; // вправо-вниз
        rect.left += right_up * time; // вправо-вверх
        rect.left += gun_rev * time; // реверсивная переменная gun
        rect.left += right_down_rev * time; // реверсивная переменная right_down
        rect.left += right_up_rev * time; // реверсивная переменная right_up
        rect.left += dx_rev * time; // реверсивная переменная dx

        if (!onGround)
            dy = dy + 0.0005 *
                      time; /* если мы не на земле, то падаем с ускорением ( ускорение -0.005 умножаем на время получаем скорость) */
        rect.top += dy * time; // rect.top - есть координата у
        onGround = false;

        if (rect.top > ground) {
            rect.top = ground;
            dy = 0;
            onGround = true;
        } // мы на земле

        currentFrame += 0.005 * time; // скорость анимации
        if (currentFrame > 6) currentFrame -= 6; // всего у нас 6 кадров
        if (dx > 0)
            sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40,
                                          50)); /*  Бег (Вправо) ?? меняем первую координату, то есть рисунок текстуры сдвигается каждый раз на 40( при движении направо- правая анимация */
        if (dx < 0)
            sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40,
                                          50)); // Бег (Влево) ?? при движении налево- зеркальная
        if (dx_rev < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
        if (dx_rev > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
        if (right_down > 0) sprite.setTextureRect(IntRect(34 * int(currentFrame), 469, 35, 50));
        if (right_down < 0) sprite.setTextureRect(IntRect(34 * int(currentFrame) + 40, 469, -35, 50));
        if (right_down_rev < 0) sprite.setTextureRect(IntRect(34 * int(currentFrame), 469, 35, 50));
        if (right_down_rev > 0) sprite.setTextureRect(IntRect(34 * int(currentFrame) + 40, 469, -35, 50));
        if (right_up > 0) sprite.setTextureRect(IntRect(39 * int(currentFrame), 370, 41, 58));
        if (right_up < 0) sprite.setTextureRect(IntRect(39 * int(currentFrame) + 40, 370, -41, 58));
        if (right_up_rev < 0) sprite.setTextureRect(IntRect(39 * int(currentFrame), 370, 41, 58));
        if (right_up_rev > 0) sprite.setTextureRect(IntRect(39 * int(currentFrame) + 40, 370, -41, 58));
        if (currentFrame > 4) currentFrame -= 4; // всего у нас 4 кадра
        if (dz > 0) sprite.setTextureRect(IntRect(36 * int(currentFrame), 526, 38, 34)); // Кувырок на ходу (Вправо)
        if (dz < 0)
            sprite.setTextureRect(IntRect(36 * int(currentFrame) + 40, 526, -38, 34)); // Кувырок на ходу (Влево)
        if (currentFrame > 5) currentFrame -= 5; // Всего у нас 5 кадров
        if (gun > 0) sprite.setTextureRect(IntRect(44 * int(currentFrame), 902, 45, 50)); // Стрельба на ходу (Вправо)
        if (gun < 0)
            sprite.setTextureRect(IntRect(44 * int(currentFrame) + 40, 902, -45, 50)); // Стрельба на ходу (Влево)


        sprite.setPosition(rect.left, rect.top); // выводим наш спрайт в позицию x, y
        sprite.setScale(1.4, 1.4);

        dx = dz = gun = right_down = right_up = 0;
        dx_rev = gun_rev = right_up_rev = right_down_rev = 0;
    }
};

int main() {
    int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
    int tempY = 0;//коорд Y
    float distance = 0;//это расстояние от объекта до тыка курсора
    sf::Texture BackgroundTexture;
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Fang Game");
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape example_shape(sf::Vector2f(100, 50));
    sf::Event event;
    //RenderWindow Frames(VideoMode(200,100), "Loading");

    if (window.isOpen()) {
        std::cout << "Loaded" << std::endl;
    } else {
        std::cout << "Window loading error!" << std::endl;
    }
    Texture t;
//    Texture background;
//    background.loadFromFile("images/background.jpg");
    t.loadFromFile("images/fang.png"); // загружаем картинку
    float currentFrame = 0;

    PLAYER p(t); // загружаем текстуру
//    PLAYER b(background);
    if(!BackgroundTexture.loadFromFile("images/background.jpg"))
    {
        return -1;
    }
    else
    {
        TextureSize = BackgroundTexture.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(BackgroundTexture);
        background.setScale(ScaleX, ScaleY);      //Set scale.
    }


    Clock clock; /* засекаем время с последнего тика( чтобы привязка персонажа была ко времени, а не к мощности процессора) */


    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds(); /* создаем переменную время, getElapsedTime() - дать прошедшее время( возьмем  его в микросекундах) */

        clock.restart(); // перезагружает часы
        time = time / 800; //здесь происходит регулировка скорости движения персонажа

        Vector2i pixelPos;
        pixelPos = Mouse::getPosition(window);//забираем коорд курсора
        Vector2f pos;
        pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


        Event event;

        while (window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    float w = static_cast<float>(event.size.width);
                    float h = static_cast<float>(event.size.height);
                    window.setView(
                            sf::View(
                                    sf::Vector2f(w / 2.0, h / 2.0),
                                    sf::Vector2f(w, h)
                            )
                    );
                    break;
                }
                default:
                    break;
            }

            if (event.type == Event::MouseButtonPressed) //если нажата клавиша мыши
                if (event.key.code == Mouse::Left) {  //а именно левая
                    if (p.sprite.getGlobalBounds().contains(pos.x,
                                                            pos.y))//и при этом координата курсора попадает в спрайт
                    {
                        std::cout << "X:" << pos.x << " Y:" << pos.y << std::endl;

                    }
                }
            if (p.isSelect)//если выбрали объект
                if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                    if (event.key.code == Mouse::Right) { //а именно правая
                        // nothing
                        tempX = pos.x;//забираем координату нажатия курсора Х
                        tempY = pos.y;//и Y
                        std::cout << "tempX:" << tempX << " tempY:" << tempY << std::endl;
                    }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) // если клавиша нажата и клавиша налево
        {
            if (pos.x < 400 && pos.y > 500) {
                p.right_down = -0.1; // при нажатии направо- ускоряемся на 0.
                ground = 500;
            }
            if (pos.x < 400 && pos.y > 300 && pos.y < 500) {
                p.dx = -0.1;
                ground = 500;
            }
            if (pos.x < 400 && pos.y < 300) {
                p.right_up = -0.1;
                ground = 500;
            }
            if (pos.x > 400 && pos.y > 500) {
                p.right_down_rev = -0.1; // при нажатии направо- ускоряемся на 0.
                ground = 500;
            }
            if (pos.x > 400 && pos.y > 300 && pos.y < 500) {
                p.dx_rev = -0.1;
                ground = 500;
            }
            if (pos.x > 400 && pos.y < 300) {
                p.right_up_rev = -0.1;
                ground = 500;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // если клавиша нажата и клавиша направо
        {
            if (pos.x > 400 && pos.y > 500) {
                p.right_down = 0.1; // при нажатии направо- ускоряемся на 0.1
                ground = 500;
            }
            if (pos.x > 400 && pos.y > 300 && pos.y < 500) {
                p.dx = 0.1;
                ground = 500;
            }
            if (pos.x > 400 && pos.y < 300) {
                p.right_up = 0.1;
                ground = 500;
            }
            if (pos.x < 400 && pos.y > 500) {
                p.right_down_rev = 0.1; // при нажатии направо- ускоряемся на 0.1
                ground = 500;
            }
            if (pos.x < 400 && pos.y > 300 && pos.y < 500) {
                p.dx_rev = 0.1;
                ground = 500;
            }
            if (pos.x < 400 && pos.y < 300) {
                p.right_up_rev = 0.1;
                ground = 500;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) &&
            Keyboard::isKeyPressed(Keyboard::Right)) // если клавиша вправо нажата и клавиша пробел
        {
            p.dz = 0.1;
            ground = 525;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) &&
            Keyboard::isKeyPressed(Keyboard::Left)) // если клавиша влево нажата и клавиша пробел
        {
            p.dz = -0.1;
            ground = 525;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) // вверх
        {
            if (p.onGround) {
                p.dy = -0.5;
                p.onGround = false;
            } // если мы на земле, то только тогда можем осуществить прыжок
            ground = 500;
        }
        if (Keyboard::isKeyPressed(Keyboard::RAlt) && Keyboard::isKeyPressed(Keyboard::Right)) {
            p.gun = 0.1;
            ground = 500;
        }
        if (Keyboard::isKeyPressed(Keyboard::RAlt) && Keyboard::isKeyPressed(Keyboard::Left)) {
            p.gun = -0.1;
            ground = 500;
        }


        p.update(time); // загружаем время


        window.clear(Color::White); // очищаем экран
        window.draw(background); // background image
        window.draw(p.sprite);// рисуем спрайт
        window.display(); // выводим на дисплей
    }
    return 0;
}