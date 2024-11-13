//cohen sutherland algorithm(Experiment no 2)
#include<iostream>
#include<graphics.h>
using namespace std;

struct PT {
    int x, y;
    char code[4];
};

void drawWindow() {
    line(50, 150, 450, 150);
    line(450, 150, 450, 350);
    line(450, 350, 50, 350);
    line(50, 350, 50, 150);
}

void drawLine(PT p1, PT p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

PT setcode(PT p) {
    PT temp;
    temp.code[0] = (p.y < 100) ? '1' : '0';
    temp.code[1] = (p.y > 300) ? '1' : '0';
    temp.code[2] = (p.x > 400) ? '1' : '0';
    temp.code[3] = (p.x < 100) ? '1' : '0';
    return temp;
}

int visibility(PT p1, PT p2) {
    for (int i = 0; i < 4; i++) {
        if (p1.code[i] != '0' || p2.code[i] != '0') return 2;
        return 0;
    }
}

PT resetEndPoint(PT p1, PT p2) {
    PT temp = p1;
    float m = (p2.x != p1.x) ? (float)(p2.y - p1.y) / (p2.x - p1.x) : 0;
    float k = (p2.y != p1.y) ? (float)(p2.x - p1.x) / (p2.y - p1.y) : 0;

    if (p1.code[3] == '1') temp.x = 150, temp.y = p1.y + m * (150 - p1.x);
    else if (p1.code[2] == '1') temp.x = 450, temp.y = p1.y + m * (450 - p1.x);
    else if (p1.code[0] == '1') temp.y = 100, temp.x = p1.x + k * (100 - p1.y);
    else if (p1.code[1] == '1') temp.y = 300, temp.x = p1.x + k * (300 - p1.y);

    return temp;
}

int main() {
    PT p1, p2, p3, p4;
    cout << "\nEnter x1 and y1: ";
    cin >> p1.x >> p1.y;
    cout << "\nEnter x2 and y2: ";
    cin >> p2.x >> p2.y;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawWindow();
    delay(500);
    drawLine(p1, p2);
    delay(500);
    cleardevice();
    delay(500);

    p1 = setcode(p1);
    p2 = setcode(p2);
    int v = visibility(p1, p2);
    delay(500);

    switch (v) {
        case 0 :
            drawWindow();
            delay(500);
            drawLine(p1,p2);
            break;
        case 1:
            drawWindow();
            delay(500);
            break;
        case 2:
            p3 = resetEndPoint(p1 ,p2);
            p4 = resetEndPoint(p2 , p1);

            drawWindow();
            delay(500);
            drawline(p3, p4);
            break;
    }

    delay(5000);
    closegraph();
    return 0;
}