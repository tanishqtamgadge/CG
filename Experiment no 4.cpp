#include <iostream>
#include <cmath>
#include <graphics.h>
using namespace std;

class Matrix {
public:
    int n, tx, ty, sx, sy, i, j, k;
    double a[6][3], b[6][3], mat3[6][3];
    double ang = 0, angle = 0;
    
public:
    void get() {
        cout << "\nEnter the number of vertices of the polygon: ";
        cin >> n;
        for (i = 0; i < n; i++) {
            cout << "Enter x and y coordinates: ";
            cin >> b[i][0] >> b[i][1];
            b[i][2] = 1;
        }
        cout << "\nOriginal coordinates:\n";
        for (i = 0; i < n; i++) {
            for (j = 0; j < 3; j++) {
                cout << b[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void identityMatrix() {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                a[i][j] = (i == j) ? 1 : 0;
            }
        }
    }

    void translate() {
        cout << "Enter values of tx and ty: ";
        cin >> tx >> ty;
        a[2][0] = tx;
        a[2][1] = ty;
        displayMatrix("Translation Matrix");
    }

    void scale() {
        cout << "Enter values of sx and sy: ";
        cin >> sx >> sy;
        a[0][0] = sx;
        a[1][1] = sy;
        displayMatrix("Scaling Matrix");
    }

    void rotate() {
        cout << "Enter the rotation angle: ";
        cin >> ang;
        angle = (ang * M_PI) / 180;
        double cosA = cos(angle), sinA = sin(angle);

        a[0][0] = cosA;
        a[0][1] = -sinA;
        a[1][0] = sinA;
        a[1][1] = cosA;
        
        displayMatrix("Rotation Matrix");
    }

    void multiply() {
        for (i = 0; i < n; i++) {
            for (j = 0; j < 3; j++) {
                mat3[i][j] = 0;
                for (k = 0; k < 3; k++) {
                    mat3[i][j] += b[i][k] * a[k][j];
                }
            }
        }
    }

    void display() {
        cout << "\nTransformed coordinates:\n";
        for (i = 0; i < n; i++) {
            for (j = 0; j < 3; j++) {
                cout << mat3[i][j] << " ";
            }
            cout << "\n";
        }

        int gd = DETECT, gm;
        initgraph(&gd, &gm, NULL);
        for (int i = 0; i < n - 1; i++) {
            line(b[i][0], b[i][1], b[i + 1][0], b[i + 1][1]);
        }
        line(b[n - 1][0], b[n - 1][1], b[0][0], b[0][1]);

        for (int i = 0; i < n - 1; i++) {
            line(mat3[i][0], mat3[i][1], mat3[i + 1][0], mat3[i + 1][1]);
        }
        line(mat3[n - 1][0], mat3[n - 1][1], mat3[0][0], mat3[0][1]);

        delay(5000);
        closegraph();
    }

private:
    void displayMatrix(const char* msg) {
        cout << msg << ":\n";
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                cout << a[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

int main() {
    Matrix g;
    int choice;
    char ans;
    g.get();
    g.identityMatrix();

    do {
        cout << "Menu\n1. Translation\n2. Scaling\n3. Rotation\nChoose a transformation: ";
        cin >> choice;
        g.identityMatrix();

        switch (choice) {
            case 1:
                g.translate();
                g.multiply();
                g.display();
                break;
            case 2:
                g.scale();
                g.multiply();
                g.display();
                break;
            case 3:
                g.rotate();
                g.multiply();
                g.display();
                break;
            default:
                cout << "Invalid choice.";
        }
        cout << "\nDo you want to continue? (Y/N): ";
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');

    return 0;
}
