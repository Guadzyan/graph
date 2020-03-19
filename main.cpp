#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

using namespace sf;
int ground = 500;

class START
{
public:
    START() {
        sf::Font font;
        if (!font.loadFromFile("/Users/igorbacurin/CLionProjects/graph/fonts/ariel.ttf"));
        sf:Text text;
        text.setFont(font);
        text.setString("HelloWorld");
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Black);
    }
};

class PLAYER { /* создаем класс PLAYER( нам нужно чтобы движения персонажа осуществлялись под действием  гравитации) */

public:
    float dx, dy, dz; // скорость
    FloatRect rect; //  здесь rect(x, y, widht, height)
    bool onGround; /*  onGround- переменная, которая показывает, находится ли персонаж на земле */
    Sprite sprite; // сюда будем загружать картинку
    float currentFrame; //  текущий кадр для анимации

    PLAYER(Texture &image)
    {
        sprite.setTexture(image); // в конструктор класса загружаем картинку
        rect = FloatRect(0, 0, 40, 50); /* указываем первоначальные координаты x=0, y=0, ширина-40, высота-50 */

        dx = dy = dz = 0;
        currentFrame = 0;
    }

    void update(float time)
    {
        rect.left += dx*time; // rect.left-есть координата х, перемещаем ее на dx*time
        rect.left += dz*time; // dz переменная

        if (!onGround) dy = dy + 0.0005*time; /* если мы не на земле, то падаем с ускорением ( ускорение -0.005 умножаем на время получаем скорость) */
        rect.top += dy*time; // rect.top - есть координата у
        onGround = false;

        if (rect.top > ground)
        { rect.top = ground; dy = 0; onGround = true; } // мы на земле

        currentFrame += 0.005*time; // скорость анимации
        if (currentFrame > 6) currentFrame -= 6; // всего у нас 6 кадров
        if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50)); /* меняем первую координату, то есть рисунок текстуры сдвигается каждый раз на 40( при движении направо- правая анимация */
        if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50)); // при движении налево- зеркальная
        if (currentFrame > 4) currentFrame -= 4; // всего у нас 4 кадра
        if (dz > 0) sprite.setTextureRect(IntRect(36 * int(currentFrame),526,38,34));
        if (dz < 0) sprite.setTextureRect(IntRect(36 * int(currentFrame) + 40,526,-38,34));

        sprite.setPosition(rect.left, rect.top); // выводим наш спрайт в позицию x, y

        dx = dz = 0;
    }
};

    int main()
    {


    RenderWindow window(VideoMode(800, 600), "FangGame"); // создаем окно 600 на 600 с именем SFMLworks */
    if (window.isOpen())
    {
        std::cout << "Loaded" << std::endl;
    } else{
        std::cout << "Window error!" << std::endl;
    }
                                                                                              Texture t;
    t.loadFromFile("/Users/igorbacurin/CLionProjects/graph/images/fang.png"); // загружаем картинку
    float currentFrame = 0;

    PLAYER p(t); // загружаем текстуру


    Clock clock; /* засекаем время с последнего тика( чтобы привязка персонажа была ко времени, а не к мощности процессора) */


    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds(); /* создаем переменную время, getElapsedTime() - дать прошедшее время( возьмем  его в микросекундах) */

        clock.restart(); // перезагружает часы
        time = time / 800; //здесь происходит регулировка скорости движения персонажа

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close(); // обрабатываем событие закрытия окна
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) // если клавиша нажата и клавиша налево
        {
            p.dx = -0.1; // при нажатии налево- ускоряемся на -0.1
            ground = 500;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // если клавиша нажата и клавиша направо
        {
            p.dx = 0.1; // при нажатии направо- ускоряемся на 0.1
            ground = 500;
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

        p.update(time); // загружаем время


        window.clear(Color::White); // очищаем экран
        window.draw(p.sprite);// рисуем спрайт
        window.display(); // выводим на дисплей
    }
    return 0;
}