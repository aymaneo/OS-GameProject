//
// Created by julie on 11/05/2025.
//

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H



class CollisionManager {
private:
    static bool isInsideRectangle(int x, int y, int rect_x, int rect_y, int rect_width, int rect_height);
public:
    static bool isColliding(int pos_x, int pos_y);
    static void applyCollision(int pos_x, int pos_y);
};



#endif //COLLISIONMANAGER_H
