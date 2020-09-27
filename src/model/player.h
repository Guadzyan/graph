#include "../headers/libs.h"

int ground = 500;

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
