#include "../headers/libs.h"

int ground = 500;

class PLAYER { /* создаем класс PLAYER( нам нужно чтобы движения персонажа осуществлялись под действием  гравитации) */

public:
    float dx, dy, dz, gun, right_down, right_up; // скорость
    float dx_rev, gun_rev, right_down_rev, right_up_rev; // реверсивная скорость
    FloatRect rect; //  здесь rect(x, y, widht, height)
    bool onGround; /*  onGround- переменная, которая показывает, находится ли персонаж на земле */
    bool onMap;
    Sprite sprite; // сюда будем загружать картинку
    float currentFrame; //  текущий кадр для анимации
    bool life, isMove, isSelect; // добавили переменные состояния движения и выбора объекта
    int xPos, yPos;

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

    void update(float time, float player_scale_x, float player_scale_y) {
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
//        if (sprite.getPosition())
//        {
//
//        }

        if (rect.top > ground) {
            rect.top = ground;
            dy = 0;
            onGround = true;
        } // мы на земле

        std::cout << "X: " << xPos << " " << "Y: " << yPos << std::endl;

        currentFrame += 0.005 * time; // скорость анимации
        if (currentFrame > 6) currentFrame -= 7; // всего у нас 6 кадров
        if (dx > 0)sprite.setTextureRect(IntRect(64 * int(currentFrame), 64, 64,64)); /*  Бег (Вправо) ?? меняем первую координату, то есть рисунок текстуры сдвигается каждый раз на 40( при движении направо- правая анимация */
        if (dx < 0)sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 64, -64,64)); // Бег (Влево) ?? при движении налево- зеркальная
        if (dx_rev < 0) sprite.setTextureRect(IntRect(64 * int(currentFrame), 64, 64, 64));
        if (dx_rev > 0) sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 64, -64, 64));
        if (right_down > 0) sprite.setTextureRect(IntRect(320 * int(currentFrame), 320, 64, 64));
        if (right_down < 0) sprite.setTextureRect(IntRect(320 * int(currentFrame) + 64, 320, -64, 64));
        if (right_down_rev < 0) sprite.setTextureRect(IntRect(320 * int(currentFrame), 320, 64, 64));
        if (right_down_rev > 0) sprite.setTextureRect(IntRect(320 * int(currentFrame) + 64, 320, -64, 64));
        if (right_up > 0) sprite.setTextureRect(IntRect(192 * int(currentFrame), 192, 64, 64));
        if (right_up < 0) sprite.setTextureRect(IntRect(192 * int(currentFrame) + 64, 192, -64, 64));
        if (right_up_rev < 0) sprite.setTextureRect(IntRect(192 * int(currentFrame), 192, 64, 64));
        if (right_up_rev > 0) sprite.setTextureRect(IntRect(192 * int(currentFrame) + 64, 192, -64, 64));
        std::cout << currentFrame << std::endl;
        if (currentFrame > 3) currentFrame -= 4; // всего у нас 4 кадра
        if (dz > 0) sprite.setTextureRect(IntRect(384 * int(currentFrame), 384, 64, 64)); // Кувырок на ходу (Вправо)
        if (dz < 0)sprite.setTextureRect(IntRect(384 * int(currentFrame) + 64, 384, -64, 64)); // Кувырок на ходу (Влево)
        std::cout << currentFrame << std::endl;
        if (currentFrame > 4) currentFrame -= 5; // Всего у нас 5 кадров
        if (gun > 0) sprite.setTextureRect(IntRect(704 * int(currentFrame), 704, 64, 64)); // Стрельба на ходу (Вправо)
        if (gun < 0)sprite.setTextureRect(IntRect(704 * int(currentFrame) + 64, 704, -64, 64)); // Стрельба на ходу (Влево)
        std::cout << currentFrame << std::endl;

        if (rect.left < 0)
        {
            rect.left = 0;
        }
        if (rect.left > this->window.getSize().y)
        sprite.setPosition(rect.left, rect.top); // выводим наш спрайт в позицию x, y
        sprite.setScale(player_scale_x, player_scale_y);

        dx = dz = gun = right_down = right_up = 0;
        dx_rev = gun_rev = right_up_rev = right_down_rev = 0;
    }
};
//
// Created by Admin on 28.09.2020.
//

#ifndef GRAPH_PLAYER_H
#define GRAPH_PLAYER_H

#endif //GRAPH_PLAYER_H
