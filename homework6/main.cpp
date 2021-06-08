#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Cube {
private:
    char up[3][3], front[3][3], left[3][3], right[3][3], back[3][3], down[3][3];
    vector <char> ans;

public:
    Cube() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                front[i][j] = 'w';
                back[i][j] = 'y';
                left[i][j] = 'g';
                right[i][j] = 'b';
                up[i][j] = 'o';
                down[i][j] = 'r';
            }
        }
    }

  void read() {
        ifstream fin("starting cube.in");
        string s;
        for (int i = 0; i < 6; i++) {
            fin >> s;
            if (s == "front") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> front[j][k];
                    }
                }
            }
            if (s == "left") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> left[j][k];
                    }
                }
            }
            if (s == "right") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> right[j][k];
                    }
                }
            }
            if (s == "back") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> back[j][k];
                    }
                }
            }
            if (s == "up") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> up[j][k];
                    }
                }
            }
            if (s == "down") {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        fin >> down[j][k];
                    }
                }
            }
        }

        fin.close();
    }
  
  void save() {
        ofstream fout("starting cube.out");

        for (int i = 0; i < 3; i++) {
            fout << "    ";
            for (int j = 0; j < 3; j++) {
                fout << up[i][j];
            }
            fout << endl;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fout << left[i][j];
            }
            fout << " ";
            for (int j = 0; j < 3; j++) {
                fout << front[i][j];
            }
            fout << " ";
            for (int j = 0; j < 3; j++) {
                fout << right[i][j];
            }
            fout << " ";
            for (int j = 0; j < 3; j++) {
                fout << back[i][j];
            }
            fout << endl;
        }
        for (int i = 0; i < 3; i++) {
            fout << "    ";
            for (int j = 0; j < 3; j++) {
                fout << down[i][j];
            }
            fout << endl;
        }
        fout << endl;
        fout.close();
    }
  
  void show() {
        int i, j;
        for (i = 0; i < 3; i++) {
            cout << "    ";
            for (j = 0; j < 3; j++) {
                cout << up[i][j];
            }
            cout << endl;
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                cout << left[i][j];
            }
            cout << " ";
            for (j = 0; j < 3; j++) {
                cout << front[i][j];
            }
            cout << " ";
            for (j = 0; j < 3; j++) {
                cout << right[i][j];
            }
            cout << " ";
            for (j = 0; j < 3; j++) {
                cout << back[i][j];
            }
            cout << endl;
        }
        for (i = 0; i < 3; i++) {
            cout << "    ";
            for (j = 0; j < 3; j++) {
                cout << down[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
  
  void Front() {
        int k, c, l;

        k = front[0][1];

        front[0][1] = front[1][0];
        front[1][0] = front[2][1];
        front[2][1] = front[1][2];
        front[1][2] = k;

        k = front[0][0];

        front[0][0] = front[2][0];
        front[2][0] = front[2][2];
        front[2][2] = front[0][2];
        front[0][2] = k;

        k = up[2][0];
        c = up[2][1];
        l = up[2][2];

        up[2][0] = left[2][2];
        up[2][1] = left[1][2];
        up[2][2] = left[0][2];

        left[2][2] = down[0][2];
        left[1][2] = down[0][1];
        left[0][2] = down[0][0];

        down[0][2] = right[0][0];
        down[0][1] = right[1][0];
        down[0][0] = right[2][0];

        right[0][0] = k;
        right[1][0] = c;
        right[2][0] = l;
        ans.push_back('F');
        ans.push_back(' ');
    }
  
  void Back() {
        int k, c, l;

        k = back[0][1];

        back[0][1] = back[1][0];
        back[1][0] = back[2][1];
        back[2][1] = back[1][2];
        back[1][2] = k;

        k = back[0][0];

        back[0][0] = back[2][0];
        back[2][0] = back[2][2];
        back[2][2] = back[0][2];
        back[0][2] = k;

        k = up[0][0];
        c = up[0][1];
        l = up[0][2];

        up[0][0] = right[0][2];
        up[0][1] = right[1][2];
        up[0][2] = right[2][2];

        right[2][2] = down[2][0];
        right[1][2] = down[2][1];
        right[0][2] = down[2][2];

        down[2][2] = left[2][0];
        down[2][1] = left[1][0];
        down[2][0] = left[0][0];

        left[0][0] = l;
        left[1][0] = c;
        left[2][0] = k;
        ans.push_back('B');
        ans.push_back(' ');
    }
  
  void Left() {
        int k, c, l;

        k = left[0][1];

        left[0][1] = left[1][0];
        left[1][0] = left[2][1];
        left[2][1] = left[1][2];
        left[1][2] = k;

        k = left[0][0];

        left[0][0] = left[2][0];
        left[2][0] = left[2][2];
        left[2][2] = left[0][2];
        left[0][2] = k;

        k = back[0][2];
        c = back[1][2];
        l = back[2][2];

        back[0][2] = down[2][0];
        back[1][2] = down[1][0];
        back[2][2] = down[0][0];

        down[2][0] = front[2][0];
        down[1][0] = front[1][0];
        down[0][0] = front[0][0];

        front[2][0] = up[2][0];
        front[1][0] = up[1][0];
        front[0][0] = up[0][0];

        up[2][0] = k;
        up[1][0] = c;
        up[0][0] = l;
        ans.push_back('L');
        ans.push_back(' ');
    }
  
  void Right() {
        int k, c, l;

        k = right[0][1];

        right[0][1] = right[1][0];
        right[1][0] = right[2][1];
        right[2][1] = right[1][2];
        right[1][2] = k;

        k = right[0][0];

        right[0][0] = right[2][0];
        right[2][0] = right[2][2];
        right[2][2] = right[0][2];
        right[0][2] = k;

        k = back[0][0];
        c = back[1][0];
        l = back[2][0];

        back[0][0] = up[2][2];
        back[1][0] = up[1][2];
        back[2][0] = up[0][2];

        up[2][2] = front[2][2];
        up[1][2] = front[1][2];
        up[0][2] = front[0][2];

        front[2][2] = down[2][2];
        front[1][2] = down[1][2];
        front[0][2] = down[0][2];

        down[2][2] = k;
        down[1][2] = c;
        down[0][2] = l;
        ans.push_back('R');
        ans.push_back(' ');
    }
  
  void Up() {
        int k, c, l;

        k = up[0][1];

        up[0][1] = up[1][0];
        up[1][0] = up[2][1];
        up[2][1] = up[1][2];
        up[1][2] = k;

        k = up[0][0];

        up[0][0] = up[2][0];
        up[2][0] = up[2][2];
        up[2][2] = up[0][2];
        up[0][2] = k;

        k = left[0][0];
        c = left[0][1];
        l = left[0][2];

        left[0][0] = front[0][0];
        left[0][1] = front[0][1];
        left[0][2] = front[0][2];

        front[0][0] = right[0][0];
        front[0][1] = right[0][1];
        front[0][2] = right[0][2];

        right[0][0] = back[0][0];
        right[0][1] = back[0][1];
        right[0][2] = back[0][2];

        back[0][0] = k;
        back[0][1] = c;
        back[0][2] = l;
        ans.push_back('U');
        ans.push_back(' ');
    }
  
  void Down() {
        int k, c, l;

        k = down[0][1];

        down[0][1] = down[1][0];
        down[1][0] = down[2][1];
        down[2][1] = down[1][2];
        down[1][2] = k;

        k = down[0][0];

        down[0][0] = down[2][0];
        down[2][0] = down[2][2];
        down[2][2] = down[0][2];
        down[0][2] = k;

        k = left[2][0];
        c = left[2][1];
        l = left[2][2];

        left[2][0] = back[2][0];
        left[2][1] = back[2][1];
        left[2][2] = back[2][2];

        back[2][0] = right[2][0];
        back[2][1] = right[2][1];
        back[2][2] = right[2][2];

        right[2][0] = front[2][0];
        right[2][1] = front[2][1];
        right[2][2] = front[2][2];

        front[2][0] = k;
        front[2][1] = c;
        front[2][2] = l;
        ans.push_back('D');
        ans.push_back(' ');
    }
  
  void FrontB() {
        int k, c, l;

        k = front[0][1];

        front[0][1] = front[1][2];
        front[1][2] = front[2][1];
        front[2][1] = front[1][0];
        front[1][0] = k;

        k = front[0][0];

        front[0][0] = front[0][2];
        front[0][2] = front[2][2];
        front[2][2] = front[2][0];
        front[2][0] = k;

        k = up[2][0];
        c = up[2][1];
        l = up[2][2];

        up[2][0] = right[0][0];
        up[2][1] = right[1][0];
        up[2][2] = right[2][0];

        right[0][0] = down[0][2];
        right[1][0] = down[0][1];
        right[2][0] = down[0][0];

        down[0][2] = left[2][2];
        down[0][1] = left[1][2];
        down[0][0] = left[0][2];

        left[0][2] = l;
        left[1][2] = c;
        left[2][2] = k;
        ans.push_back('F');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void BackB() {
        int k, c, l;

        k = back[0][1];

        back[0][1] = back[1][2];
        back[1][2] = back[2][1];
        back[2][1] = back[1][0];
        back[1][0] = k;

        k = back[0][0];

        back[0][0] = back[0][2];
        back[0][2] = back[2][2];
        back[2][2] = back[2][0];
        back[2][0] = k;

        k = up[0][0];
        c = up[0][1];
        l = up[0][2];

        up[0][0] = left[2][0];
        up[0][1] = left[1][0];
        up[0][2] = left[0][0];

        left[2][0] = down[2][2];
        left[1][0] = down[2][1];
        left[0][0] = down[2][0];

        down[2][2] = right[0][2];
        down[2][1] = right[1][2];
        down[2][0] = right[2][2];

        right[0][2] = k;
        right[1][2] = c;
        right[2][2] = l;
        ans.push_back('B');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void LeftB() {
        int k, c, l;

        k = left[0][1];

        left[0][1] = left[1][2];
        left[1][2] = left[2][1];
        left[2][1] = left[1][0];
        left[1][0] = k;

        k = left[0][0];

        left[0][0] = left[0][2];
        left[0][2] = left[2][2];
        left[2][2] = left[2][0];
        left[2][0] = k;

        k = back[0][2];
        c = back[1][2];
        l = back[2][2];

        back[0][2] = up[2][0];
        back[1][2] = up[1][0];
        back[2][2] = up[0][0];

        up[2][0] = front[2][0];
        up[1][0] = front[1][0];
        up[0][0] = front[0][0];

        front[2][0] = down[2][0];
        front[1][0] = down[1][0];
        front[0][0] = down[0][0];

        down[2][0] = k;
        down[1][0] = c;
        down[0][0] = l;
        ans.push_back('L');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void RightB() {
        int k, c, l;

        k = right[0][1];

        right[0][1] = right[1][2];
        right[1][2] = right[2][1];
        right[2][1] = right[1][0];
        right[1][0] = k;

        k = right[0][0];

        right[0][0] = right[0][2];
        right[0][2] = right[2][2];
        right[2][2] = right[2][0];
        right[2][0] = k;

        k = back[0][0];
        c = back[1][0];
        l = back[2][0];

        back[0][0] = down[2][2];
        back[1][0] = down[1][2];
        back[2][0] = down[0][2];

        down[2][2] = front[2][2];
        down[1][2] = front[1][2];
        down[0][2] = front[0][2];

        front[2][2] = up[2][2];
        front[1][2] = up[1][2];
        front[0][2] = up[0][2];

        up[2][2] = k;
        up[1][2] = c;
        up[0][2] = l;
        ans.push_back('R');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void UpB() {
        int k, c, l;

        k = up[0][1];

        up[0][1] = up[1][2];
        up[1][2] = up[2][1];
        up[2][1] = up[1][0];
        up[1][0] = k;

        k = up[0][0];

        up[0][0] = up[0][2];
        up[0][2] = up[2][2];
        up[2][2] = up[2][0];
        up[2][0] = k;

        k = left[0][0];
        c = left[0][1];
        l = left[0][2];

        left[0][0] = back[0][0];
        left[0][1] = back[0][1];
        left[0][2] = back[0][2];

        back[0][0] = right[0][0];
        back[0][1] = right[0][1];
        back[0][2] = right[0][2];

        right[0][0] = front[0][0];
        right[0][1] = front[0][1];
        right[0][2] = front[0][2];

        front[0][0] = k;
        front[0][1] = c;
        front[0][2] = l;
        ans.push_back('U');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void DownB() {
        int k, c, l;

        k = down[0][1];

        down[0][1] = down[1][2];
        down[1][2] = down[2][1];
        down[2][1] = down[1][0];
        down[1][0] = k;

        k = down[0][0];

        down[0][0] = down[0][2];
        down[0][2] = down[2][2];
        down[2][2] = down[2][0];
        down[2][0] = k;

        k = left[2][0];
        c = left[2][1];
        l = left[2][2];

        left[2][0] = front[2][0];
        left[2][1] = front[2][1];
        left[2][2] = front[2][2];

        front[2][0] = right[2][0];
        front[2][1] = right[2][1];
        front[2][2] = right[2][2];

        right[2][0] = back[2][0];
        right[2][1] = back[2][1];
        right[2][2] = back[2][2];

        back[2][0] = k;
        back[2][1] = c;
        back[2][2] = l;
        ans.push_back('D');
        ans.push_back('1');
        ans.push_back(' ');
    }
  
  void Random() {
        int j, k;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                front[j][k] = 'w';
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                back[j][k] = 'y';
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                left[j][k] = 'g';
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                right[j][k] = 'b';
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                up[j][k] = 'o';
            }
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                down[j][k] = 'r';
            }
        }
        int num = rand() % 10;
        for (j = 0; j < num; j++) {
            Right();
            Up();
            Back();
            for (k = 0; k < 6; k++) {
                ans.pop_back();
            }
        }
        num = rand() % 10;
        for (j = 0; j < num; j++) {
            Left();
            Up();
            Front();
            for (k = 0; k < 6; k++) {
                ans.pop_back();
            }
        }
        num = rand() % 10;
        for (j = 0; j < num; j++) {
            Right();
            Down();
            Front();
            for (k = 0; k < 6; k++) {
                ans.pop_back();
            }
        }
    }
  
  void Rotation(string k, int c) {
        if (k == "front") {
            for (int i = 0; i < c; i++) {
                Front();
            }
        }
        if (k == "back") {
            for (int i = 0; i < c; i++) {
                Back();
            }
        }
        if (k == "left") {
            for (int i = 0; i < c; i++) {
                Left();
            }
        }
       if (k == "right") {
            for (int i = 0; i < c; i++) {
                Right();
            }
        }
        if (k == "up") {
            for (int i = 0; i < c; i++) {
                Up();
            }
        }
        if (k == "down") {
            for (int i = 0; i < c; i++) {
                Down();
                show();
            }
        }
        if (k == "frontB") {
            for (int i = 0; i < c; i++) {
                FrontB();
            }
        }
        if (k == "backB") {
            for (int i = 0; i < c; i++) {
                BackB();
            }
        }
        if (k == "leftB") {
            for (int i = 0; i < c; i++) {
                LeftB();
            }
        }
        if (k == "rightB") {
            for (int i = 0; i < c; i++) {
                RightB();
            }
        }
        if (k == "upB") {
            for (int i = 0; i < c; i++) {
                UpB();
            }
        }
        if (k == "downB") {
            for (int i = 0; i < c; i++) {
                DownB();
            }
        }
        cout << "The rotation " << k << " for " << c << " times is done. The result:" << endl;
        show();
    }
  
  void Front_pif_paf() {
        Front();
        Up();
        FrontB();
        UpB();
    }

    void Back_pif_paf() {
        Back();
        Up();
        BackB();
        UpB();
    }

    void Right_pif_paf() {
        Right();
        Up();
        RightB();
        UpB();
    }

    void Left_pif_paf() {
        Left();
        Up();
        LeftB();
        UpB();
    }
  
  void first_step() {
        while (!check()) {
            if (front[1][2] == 'r' && up[1][2] != 'r') {
                Right();
            }
            else if (front[1][2] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
            }

            if (front[1][0] == 'r' && up[1][0] != 'r') {
                LeftB();
            }
            else if (front[1][0] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                LeftB();
            }

            if (down[1][0] == 'r' && up[1][0] != 'r') {
                LeftB();
                LeftB();
            }
            else if (down[1][0] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                LeftB();
                LeftB();
            }

            if (down[1][2] == 'r' && up[1][2] != 'r') {
                Right();
                Right();
            }
            else if (down[1][2] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
                Right();
            }

            if (left[1][0] == 'r' && up[0][1] != 'r') {
                BackB();
            }
            else if (left[1][0] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                BackB();
            }

            if (left[1][2] == 'r' && up[2][1] != 'r') {
                Front();
            }
            else if (left[1][2] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Front();
            }

            if (right[1][0] == 'r' && up[2][1] != 'r') {
                FrontB();
            }
            else if (right[1][0] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                FrontB();
            }

            if (right[1][2] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (right[1][2] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (back[1][0] == 'r' && up[1][2] != 'r') {
                RightB();
            }
            else if (back[1][0] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                RightB();
            }

            if (back[1][2] == 'r' && up[1][0] != 'r') {
                Left();
            }
            else if (back[1][2] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                Left();
            }

            if (front[0][1] == 'r' && up[1][2] != 'r') {
                Front();
                Right();
            }
            else if (front[0][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Front();
                Right();
            }

            if (front[2][1] == 'r' && up[1][2] != 'r') {
                FrontB();
                Right();
            }
            else if (front[2][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                FrontB();
                Right();
            }

            if (left[0][1] == 'r' && up[2][1] != 'r') {
                Left();
                Front();
            }
            else if (left[0][1] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Left();
                Front();
            }

            if (left[2][1] == 'r' && up[0][1] != 'r') {
                Left();
                BackB();
            }
            else if (left[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Left();
                BackB();
            }

            if (right[0][1] == 'r' && up[0][1] != 'r') {
                Right();
                Back();
            }
            else if (right[0][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Right();
                Back();
            }
            if (right[2][1] == 'r' && up[1][2] != 'r') {
                Right();
            }
            else if (right[2][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
            }

            if (back[0][1] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (back[0][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (back[2][1] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (back[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (down[0][1] == 'r' && up[2][1] != 'r') {
                Front();
                Front();
            }
            else if (down[0][1] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Front();
                Front();
            }

            if (down[2][1] == 'r' && up[0][1] != 'r') {
                Back();
                Back();
            }
            else if (down[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
                Back();
            }
        }

        bool ch = true;
        if (up[2][1] != 'r' || front[0][1] != 'w') {
            ch = false;
        }

        if (!ch) {
            while (!ch) {
                Up();
                ch = true;
                if (up[2][1] != 'r' || front[0][1] != 'w') {
                    ch = false;
                }
            }
        }
        Front();
        Front();

        ch = true;
        if (up[1][2] != 'r' || right[0][1] != 'b') {
            ch = false;
        }

        if (!ch) {
            while (!ch) {
                Up();
                ch = true;
                if (up[1][2] != 'r' || right[0][1] != 'b') {
                    ch = false;
                }
            }  
        }
        Right();
        Right();

        ch = true;
        if (up[0][1] != 'r' || back[0][1] != 'y') {
            ch = false;
        }

        if (!ch) {
            while (!ch) {
                Up();
                ch = true;
                if (up[0][1] != 'r' || back[0][1] != 'y') {
                    ch = false;
                }
            }
        }
        Back();
        Back();

        ch = true;
        if (up[1][0] != 'r' || left[0][1] != 'g') {
            ch = false;
        }
        if (!ch) {
            while (!ch) {
                Up();
                ch = true;
                if (up[1][0] != 'r' || left[0][1] != 'g') {
                    ch = false;
                }
            }
        }
        Left();
        Left();

        while (!check_edge()) {
            if ((front[0][2] == 'r' && right[0][0] == 'b' && up[2][2] == 'w') || (front[0][2] == 'r' && right[0][0] == 'w' && up[2][2] == 'b')
                || (front[0][2] == 'w' && right[0][0] == 'r' && up[2][2] == 'b') || (front[0][2] == 'w' && right[0][0] == 'b' && up[2][2] == 'r')
                || (front[0][2] == 'b' && right[0][0] == 'r' && up[2][2] == 'w') || (front[0][2] == 'b' && right[0][0] == 'w' && up[2][2] == 'r')) {
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((front[0][2] == 'w' && right[0][0] == 'g' && up[2][2] == 'r') || (front[0][2] == 'w' && right[0][0] == 'r' && up[2][2] == 'g')
                || (front[0][2] == 'r' && right[0][0] == 'w' && up[2][2] == 'g') || (front[0][2] == 'r' && right[0][0] == 'g' && up[2][2] == 'w')
                || (front[0][2] == 'g' && right[0][0] == 'r' && up[2][2] == 'w') || (front[0][2] == 'g' && right[0][0] == 'w' && up[2][2] == 'r')) {
                Up();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((front[0][2] == 'b' && right[0][0] == 'y' && up[2][2] == 'r') || (front[0][2] == 'b' && right[0][0] == 'r' && up[2][2] == 'y')
                || (front[0][2] == 'r' && right[0][0] == 'b' && up[2][2] == 'y') || (front[0][2] == 'r' && right[0][0] == 'y' && up[2][2] == 'b')
                || (front[0][2] == 'y' && right[0][0] == 'b' && up[2][2] == 'r') || (front[0][2] == 'y' && right[0][0] == 'r' && up[2][2] == 'b')) {
                UpB();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((front[0][2] == 'r' && right[0][0] == 'g' && up[2][2] == 'y') || (front[0][2] == 'r' && right[0][0] == 'y' && up[2][2] == 'g')
                || (front[0][2] == 'y' && right[0][0] == 'r' && up[2][2] == 'g') || (front[0][2] == 'y' && right[0][0] == 'g' && up[2][2] == 'r')
                || (front[0][2] == 'g' && right[0][0] == 'y' && up[2][2] == 'r') || (front[0][2] == 'g' && right[0][0] == 'r' && up[2][2] == 'y')) {
                Up();
                Up();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            }

            if ((right[0][2] == 'r' && back[0][0] == 'b' && up[0][2] == 'w') || (right[0][2] == 'r' && back[0][0] == 'w' && up[0][2] == 'b')
                || (right[0][2] == 'w' && back[0][0] == 'r' && up[0][2] == 'b') || (right[0][2] == 'w' && back[0][0] == 'b' && up[0][2] == 'r')
                || (right[0][2] == 'b' && back[0][0] == 'r' && up[0][2] == 'w') || (right[0][2] == 'b' && back[0][0] == 'w' && up[0][2] == 'r')) {
                Up();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((right[0][2] == 'w' && back[0][0] == 'g' && up[0][2] == 'r') || (right[0][2] == 'w' && back[0][0] == 'r' && up[0][2] == 'g')
                || (right[0][2] == 'r' && back[0][0] == 'w' && up[0][2] == 'g') || (right[0][2] == 'r' && back[0][0] == 'g' && up[0][2] == 'w')
                || (right[0][2] == 'g' && back[0][0] == 'r' && up[0][2] == 'w') || (right[0][2] == 'g' && back[0][0] == 'w' && up[0][2] == 'r')) {
                Up();
                Up();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((right[0][2] == 'b' && back[0][0] == 'y' && up[0][2] == 'r') || (right[0][2] == 'b' && back[0][0] == 'r' && up[0][2] == 'y')
                || (right[0][2] == 'r' && back[0][0] == 'b' && up[0][2] == 'y') || (right[0][2] == 'r' && back[0][0] == 'y' && up[0][2] == 'b')
                || (right[0][2] == 'y' && back[0][0] == 'b' && up[0][2] == 'r') || (right[0][2] == 'y' && back[0][0] == 'r' && up[0][2] == 'b')) {
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((right[0][2] == 'r' && back[0][0] == 'g' && up[0][2] == 'y') || (right[0][2] == 'r' && back[0][0] == 'y' && up[0][2] == 'g')
                || (right[0][2] == 'y' && back[0][0] == 'r' && up[0][2] == 'g') || (right[0][2] == 'y' && back[0][0] == 'g' && up[0][2] == 'r')
                || (right[0][2] == 'g' && back[0][0] == 'y' && up[0][2] == 'r') || (right[0][2] == 'g' && back[0][0] == 'r' && up[0][2] == 'y')) {
                UpB();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            }

            if ((back[0][2] == 'r' && left[0][0] == 'b' && up[0][0] == 'w') || (back[0][2] == 'r' && left[0][0] == 'w' && up[0][0] == 'b')
                || (back[0][2] == 'w' && left[0][0] == 'r' && up[0][0] == 'b') || (back[0][2] == 'w' && left[0][0] == 'b' && up[0][0] == 'r')
                || (back[0][2] == 'b' && left[0][0] == 'r' && up[0][0] == 'w') || (back[0][2] == 'b' && left[0][0] == 'w' && up[0][0] == 'r')) {
                UpB();
                UpB();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((back[0][2] == 'w' && left[0][0] == 'g' && up[0][0] == 'r') || (back[0][2] == 'w' && left[0][0] == 'r' && up[0][0] == 'g')
                || (back[0][2] == 'r' && left[0][0] == 'w' && up[0][0] == 'g') || (back[0][2] == 'r' && left[0][0] == 'g' && up[0][0] == 'w')
                || (back[0][2] == 'g' && left[0][0] == 'r' && up[0][0] == 'w') || (back[0][2] == 'g' && left[0][0] == 'w' && up[0][0] == 'r')) {
                UpB();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((back[0][2] == 'b' && left[0][0] == 'y' && up[0][0] == 'r') || (back[0][2] == 'b' && left[0][0] == 'r' && up[0][0] == 'y')
                || (back[0][2] == 'r' && left[0][0] == 'b' && up[0][0] == 'y') || (back[0][2] == 'r' && left[0][0] == 'y' && up[0][0] == 'b')
                || (back[0][2] == 'y' && left[0][0] == 'b' && up[0][0] == 'r') || (back[0][2] == 'y' && left[0][0] == 'r' && up[0][0] == 'b')) {
                Up();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((back[0][2] == 'r' && left[0][0] == 'g' && up[0][0] == 'y') || (back[0][2] == 'r' && left[0][0] == 'y' && up[0][0] == 'g')
                || (back[0][2] == 'y' && left[0][0] == 'r' && up[0][0] == 'g') || (back[0][2] == 'y' && left[0][0] == 'g' && up[0][0] == 'r')
                || (back[0][2] == 'g' && left[0][0] == 'y' && up[0][0] == 'r') || (back[0][2] == 'g' && left[0][0] == 'r' && up[0][0] == 'y')) {
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            } 

            if ((left[0][2] == 'r' && front[0][0] == 'b' && up[2][0] == 'w') || (left[0][2] == 'r' && front[0][0] == 'w' && up[2][0] == 'b')
                || (left[0][2] == 'w' && front[0][0] == 'r' && up[2][0] == 'b') || (left[0][2] == 'w' && front[0][0] == 'b' && up[2][0] == 'r')
                || (left[0][2] == 'b' && front[0][0] == 'r' && up[2][0] == 'w') || (left[0][2] == 'b' && front[0][0] == 'w' && up[2][0] == 'r')) {
                UpB();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((left[0][2] == 'w' && front[0][0] == 'g' && up[2][0] == 'r') || (left[0][2] == 'w' && front[0][0] == 'r' && up[2][0] == 'g')
                || (left[0][2] == 'r' && front[0][0] == 'w' && up[2][0] == 'g') || (left[0][2] == 'r' && front[0][0] == 'g' && up[2][0] == 'w')
                || (left[0][2] == 'g' && front[0][0] == 'r' && up[2][0] == 'w') || (left[0][2] == 'g' && front[0][0] == 'w' && up[2][0] == 'r')) {
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((left[0][2] == 'b' && front[0][0] == 'y' && up[2][0] == 'r') || (left[0][2] == 'b' && front[0][0] == 'r' && up[2][0] == 'y')
                || (left[0][2] == 'r' && front[0][0] == 'b' && up[2][0] == 'y') || (left[0][2] == 'r' && front[0][0] == 'y' && up[2][0] == 'b')
                || (left[0][2] == 'y' && front[0][0] == 'b' && up[2][0] == 'r') || (left[0][2] == 'y' && front[0][0] == 'r' && up[2][0] == 'b')) {
                Up();
                Up();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((left[0][2] == 'r' && front[0][0] == 'g' && up[2][0] == 'y') || (left[0][2] == 'r' && front[0][0] == 'y' && up[2][0] == 'g')
                || (left[0][2] == 'y' && front[0][0] == 'r' && up[2][0] == 'g') || (left[0][2] == 'y' && front[0][0] == 'g' && up[2][0] == 'r')
                || (left[0][2] == 'g' && front[0][0] == 'y' && up[2][0] == 'r') || (left[0][2] == 'g' && front[0][0] == 'r' && up[2][0] == 'y')) {
                Up();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            }

            if (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                if (front[2][2] == 'r' || right[2][0] == 'r' || down[0][2] == 'r') {
                    Right_pif_paf();
                }
            }

            if (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                if (front[2][0] == 'r' || left[2][2] == 'r' || down[0][0] == 'r') {
                    Front_pif_paf();
                }
            }

            if (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                if (back[2][0] == 'r' || right[2][2] == 'r' || down[2][2] == 'r') {
                    Back_pif_paf();
                }
            }

            if (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                if (back[2][2] == 'r' || left[2][0] == 'r' || down[2][0] == 'r') {
                    Left_pif_paf();
                }
            } 
        }
    }
  
  void second_step() {
        int p, c;

        while (!check_middle()) {
            c = 0;
            p = -1;

            while (c > p) {
                p = c;

                if (front[0][1] == 'w' || right[0][1] == 'w' || back[0][1] == 'w' || left[0][1] == 'w') {
                    if (front[0][1] != 'w') {
                        while (front[0][1] != 'w') {
                            Up();
                        }
                    }

                    if (up[2][1] == 'b') {
                        c++;
                        Up();
                        Right_pif_paf();
                        FrontB();
                        UpB();
                        Front();
                        Up();
                    }
                    else if (up[2][1] == 'g') {
                        c++;
                        UpB();
                        LeftB();
                        UpB();
                        Left();
                        Up();
                        Front_pif_paf();
                    }
                }

                if (front[0][1] == 'b' || right[0][1] == 'b' || back[0][1] == 'b' || left[0][1] == 'b') {
                    if (right[0][1] != 'b') {
                        while (right[0][1] != 'b') {
                            Up();
                        }
                    }

                    if (up[1][2] == 'y') {
                        c++;
                        Up();
                        Back_pif_paf();
                        RightB();
                        UpB();
                        Right();
                        Up();
                    }
                    else if (up[1][2] == 'w') {
                        c++;
                        UpB();
                        FrontB();
                        UpB();
                        Front();
                        Up();
                        Right_pif_paf();
                    }
                }

                if (front[0][1] == 'y' || right[0][1] == 'y' || back[0][1] == 'y' || left[0][1] == 'y') {
                    if (back[0][1] != 'y') {
                        while (back[0][1] != 'y') {
                            Up();
                        }
                    }

                    if (up[0][1] == 'g') {
                        c++;
                        Up();
                        Left_pif_paf();
                        BackB();
                        UpB();
                        Back();
                        Up();
                    }
                    else if (up[0][1] == 'b') {
                        c++;
                        UpB();
                        RightB();
                        UpB();
                        Right();
                        Up();
                        Back_pif_paf();
                    }
                }

                if (front[0][1] == 'g' || right[0][1] == 'g' || back[0][1] == 'g' || left[0][1] == 'g') {
                    if (left[0][1] != 'g') {
                        while (left[0][1] != 'g') {
                            Up();
                        }
                    }

                    if (up[1][0] == 'w') {
                        c++;
                        Up();
                        Front_pif_paf();
                        LeftB();
                        UpB();
                        Left();
                        Up();
                    }
                    else if (up[1][0] == 'y') {
                        c++;
                        UpB();
                        BackB();
                        UpB();
                        Back();
                        Up();
                        Left_pif_paf();
                    }
                }
            }

            if (front[1][2] != 'w') {
                Right_pif_paf();
                FrontB();
                UpB();
                Front();
                Up();
            }

            if (right[1][2] != 'b') {
                Back_pif_paf();
                RightB();
                UpB();
                Right();
                Up();
            }

            if (back[1][2] != 'y') {
                Left_pif_paf();
                BackB();
                UpB();
                Back();
                Up();
            }

            if (left[1][2] != 'g') {
                Front_pif_paf();
                LeftB();
                UpB();
                Left();
                Up();
            }
        }
    }
  
  void third_step() {
        while (!cross_check()) {
            if (up[0][1] == 'o' && up[1][2] == 'o' && up[2][1] != 'o' && up[1][0] != 'o') {
                Left();
                Front_pif_paf();
                LeftB();
            }
            else if (up[0][1] == 'o' && up[1][2] != 'o' && up[2][1] == 'o' && up[1][0] != 'o') {
                Left();
                Front_pif_paf();
                LeftB();
            }
            else if (up[0][1] != 'o' && up[1][2] == 'o' && up[2][1] == 'o' && up[1][0] != 'o') {
                Back();
                Left_pif_paf();
                BackB();
            }
            else if (up[0][1] == 'o' && up[1][2] != 'o' && up[2][1] != 'o' && up[1][0] == 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
            else if (up[0][1] != 'o' && up[1][2] == 'o' && up[2][1] != 'o' && up[1][0] == 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
            else if (up[0][1] != 'o' && up[1][2] != 'o' && up[2][1] == 'o' && up[1][0] == 'o') {
                Right();
                Back_pif_paf();
                RightB();
            }
            else if (up[0][1] != 'o' && up[1][2] != 'o' && up[2][1] != 'o' && up[1][0] != 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
        }

        bool ch = false;
        if (check_right_cross())
            ch = true;
        else {
            Up();
            if (check_right_cross())
                ch = true;
            else {
                Up();
                if (check_right_cross())
                    ch = true;
                else {
                    Up();
                    if (check_right_cross())
                        ch = true;
                }
            }
        }

        if (!ch) {
            while (!check_right_cross()) {
                Up();
                if (right[0][1] == 'b' && back[0][1] == 'y') {
                    Right();
                    Up();
                    RightB();
                    Up();
                    Right();
                    Up();
                    Up();
                    RightB();
                    Up();
                }
                else if (right[0][1] == 'b' && front[0][1] == 'w') {
                    Front();
                    Up();
                    FrontB();
                    Up();
                    Front();
                    Up();
                    Up();
                    FrontB();
                    Up();
                }
                else if (front[0][1] == 'w' && left[0][1] == 'g') {
                    Left();
                    Up();
                    LeftB();
                    Up();
                    Left();
                    Up();
                    Up();
                    LeftB();
                    Up();
                }
                else if (left[0][1] == 'g' && back[0][1] == 'y') {
                    Back();
                    Up();
                    BackB();
                    Up();
                    Back();
                    Up();
                    Up();
                    BackB();
                    Up();
                }
                else if (right[0][1] == 'b' && left[0][1] == 'g') {
                    Back();
                    Up();
                    BackB();
                    Up();
                    Back();
                    Up();
                    Up();
                    BackB();
                }
                else if (front[0][1] == 'w' && back[0][1] == 'y') {
                    Right();
                    Up();
                    RightB();
                    Up();
                    Right();
                    Up();
                    Up();
                    RightB();
                }
            }
        } 

        ch = ((up[2][2] == 'o' && front[0][2] == 'w' && right[0][0] == 'b') ||
            (up[2][2] == 'o' && front[0][2] == 'b' && right[0][0] == 'w') ||
            (up[2][2] == 'w' && front[0][2] == 'o' && right[0][0] == 'b') ||
            (up[2][2] == 'w' && front[0][2] == 'b' && right[0][0] == 'o') ||
            (up[2][2] == 'b' && front[0][2] == 'w' && right[0][0] == 'o') ||
            (up[2][2] == 'b' && front[0][2] == 'o' && right[0][0] == 'w')) &&
            ((front[0][0] == 'w' && left[0][2] == 'g' && up[2][0] == 'o') ||
                (front[0][0] == 'w' && left[0][2] == 'o' && up[2][0] == 'g') ||
                (front[0][0] == 'g' && left[0][2] == 'o' && up[2][0] == 'w') ||
                (front[0][0] == 'g' && left[0][2] == 'w' && up[2][0] == 'o') ||
                (front[0][0] == 'o' && left[0][2] == 'g' && up[2][0] == 'w') ||
                (front[0][0] == 'o' && left[0][2] == 'w' && up[2][0] == 'g')) &&
            ((up[0][2] == 'o' && right[0][2] == 'b' && back[0][0] == 'y') ||
                (up[0][2] == 'o' && right[0][2] == 'y' && back[0][0] == 'b') ||
                (up[0][2] == 'b' && right[0][2] == 'o' && back[0][0] == 'y') ||
                (up[0][2] == 'b' && right[0][2] == 'y' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'b' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'o' && back[0][0] == 'b')) &&
            ((up[0][0] == 'o' && back[0][2] == 'y' && left[0][0] == 'g') ||
                (up[0][0] == 'o' && back[0][2] == 'g' && left[0][0] == 'y') ||
                (up[0][0] == 'g' && back[0][2] == 'y' && left[0][0] == 'o') ||
                (up[0][0] == 'g' && back[0][2] == 'o' && left[0][0] == 'y') ||
                (up[0][0] == 'y' && back[0][2] == 'o' && left[0][0] == 'g') ||
                (up[0][0] == 'y' && back[0][2] == 'g' && left[0][0] == 'o'));

        while (!ch) {
            if ((up[2][2] == 'o' && front[0][2] == 'w' && right[0][0] == 'b') || (up[2][2] == 'o' && front[0][2] == 'b' && right[0][0] == 'w') ||
                (up[2][2] == 'w' && front[0][2] == 'o' && right[0][0] == 'b') || (up[2][2] == 'w' && front[0][2] == 'b' && right[0][0] == 'o') ||
                (up[2][2] == 'b' && front[0][2] == 'w' && right[0][0] == 'o') || (up[2][2] == 'b' && front[0][2] == 'o' && right[0][0] == 'w')) {
                Up();
                Right();
                UpB();
                LeftB();
                Up();
                RightB();
                UpB();
                Left();
            }
            else if ((front[0][0] == 'w' && left[0][2] == 'g' && up[2][0] == 'o') || (front[0][0] == 'w' && left[0][2] == 'o' && up[2][0] == 'g') ||
                (front[0][0] == 'g' && left[0][2] == 'o' && up[2][0] == 'w') || (front[0][0] == 'g' && left[0][2] == 'w' && up[2][0] == 'o') ||
                (front[0][0] == 'o' && left[0][2] == 'g' && up[2][0] == 'w') || (front[0][0] == 'o' && left[0][2] == 'w' && up[2][0] == 'g')) {
                Up();
                Front();
                UpB();
                BackB();
                Up();
                FrontB();
                UpB();
                Back();
            }
            else if ((up[0][2] == 'o' && right[0][2] == 'b' && back[0][0] == 'y') || (up[0][2] == 'o' && right[0][2] == 'y' && back[0][0] == 'b') ||
                (up[0][2] == 'b' && right[0][2] == 'o' && back[0][0] == 'y') || (up[0][2] == 'b' && right[0][2] == 'y' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'b' && back[0][0] == 'o') || (up[0][2] == 'y' && right[0][2] == 'o' && back[0][0] == 'b')) {
                Up();
                Back();
                UpB();
                FrontB();
                Up();
                BackB();
                UpB();
                Front();
            }
            else if ((up[0][0] == 'o' && back[0][2] == 'y' && left[0][0] == 'g') || (up[0][0] == 'o' && back[0][2] == 'g' && left[0][0] == 'y') ||
                (up[0][0] == 'g' && back[0][2] == 'y' && left[0][0] == 'o') || (up[0][0] == 'g' && back[0][2] == 'o' && left[0][0] == 'y') ||
                (up[0][0] == 'y' && back[0][2] == 'o' && left[0][0] == 'g') || (up[0][0] == 'y' && back[0][2] == 'g' && left[0][0] == 'o')) {
                Up();
                Left();
                UpB();
                RightB();
                Up();
                LeftB();
                UpB();
                Right();
            }
            else {
                Up();
                Right();
                UpB();
                LeftB();
                Up();
                RightB();
                UpB();
                Left();
            }
            ch = ((up[2][2] == 'o' && front[0][2] == 'w' && right[0][0] == 'b') ||
                (up[2][2] == 'o' && front[0][2] == 'b' && right[0][0] == 'w') ||
                (up[2][2] == 'w' && front[0][2] == 'o' && right[0][0] == 'b') ||
                (up[2][2] == 'w' && front[0][2] == 'b' && right[0][0] == 'o') ||
                (up[2][2] == 'b' && front[0][2] == 'w' && right[0][0] == 'o') ||
                (up[2][2] == 'b' && front[0][2] == 'o' && right[0][0] == 'w')) &&
                ((front[0][0] == 'w' && left[0][2] == 'g' && up[2][0] == 'o') ||
                    (front[0][0] == 'w' && left[0][2] == 'o' && up[2][0] == 'g') ||
                    (front[0][0] == 'g' && left[0][2] == 'o' && up[2][0] == 'w') ||
                    (front[0][0] == 'g' && left[0][2] == 'w' && up[2][0] == 'o') ||
                    (front[0][0] == 'o' && left[0][2] == 'g' && up[2][0] == 'w') ||
                    (front[0][0] == 'o' && left[0][2] == 'w' && up[2][0] == 'g')) &&
                ((up[0][2] == 'o' && right[0][2] == 'b' && back[0][0] == 'y') ||
                    (up[0][2] == 'o' && right[0][2] == 'y' && back[0][0] == 'b') ||
                    (up[0][2] == 'b' && right[0][2] == 'o' && back[0][0] == 'y') ||
                    (up[0][2] == 'b' && right[0][2] == 'y' && back[0][0] == 'o') ||
                    (up[0][2] == 'y' && right[0][2] == 'b' && back[0][0] == 'o') ||
                    (up[0][2] == 'y' && right[0][2] == 'o' && back[0][0] == 'b')) &&
                ((up[0][0] == 'o' && back[0][2] == 'y' && left[0][0] == 'g') ||
                    (up[0][0] == 'o' && back[0][2] == 'g' && left[0][0] == 'y') ||
                    (up[0][0] == 'g' && back[0][2] == 'y' && left[0][0] == 'o') ||
                    (up[0][0] == 'g' && back[0][2] == 'o' && left[0][0] == 'y') ||
                    (up[0][0] == 'y' && back[0][2] == 'o' && left[0][0] == 'g') ||
                    (up[0][0] == 'y' && back[0][2] == 'g' && left[0][0] == 'o'));
        }

        for (int i = 0; i < 5; i++) {
            if (up[0][0] != 'o')
                while (up[0][0] != 'o') {
                    Back();
                    Down();
                    BackB();
                    DownB();
                }
            Up();
        }

        ch = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (front[i][j] != 'w' || right[i][j] != 'b' || back[i][j] != 'y' || left[i][j] != 'g' || up[i][j] != 'o' || down[i][j] != 'r') {
                    ch = false;
                }
            }
        }

        while (!ch) {
            Up();
            ch = true;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (front[i][j] != 'w' || right[i][j] != 'b' || back[i][j] != 'y' || left[i][j] != 'g' || up[i][j] != 'o' || down[i][j] != 'r') {
                        ch = false;
                    }
                }
            }
        }
    }
  
  bool check() {
        bool ch = true;
        if (up[0][1] != 'r') {
            ch = false;
        }
        else if (up[1][2] != 'r') {
            ch = false;
        }
        else if (up[2][1] != 'r') {
            ch = false;
        }
        else if (up[1][0] != 'r') {
            ch = false;
        }
        return ch;
    }

    bool cross_check() {
        bool ch = true;
        if (up[0][1] != 'o' || up[1][2] != 'o' || up[2][1] != 'o' || up[1][0] != 'o') {
            ch = false;
        }
        return ch;
    }

    bool check_right_cross() {
        bool ch = true;
        if (up[0][1] != 'o' || up[1][2] != 'o' || up[2][1] != 'o' || up[1][0] != 'o') {
            ch = false;
        }
        if (front[0][1] != 'w' || right[0][1] != 'b' || back[0][1] != 'y' || left[0][1] != 'g') {
            ch = false;
        }
        return ch;
    }

    bool check_middle() {
        bool ch = true;
        if (front[1][0] != 'w' || front[1][2] != 'w' || right[1][0] != 'b' || right[1][2] != 'b' || back[1][0] != 'y' || back[1][2] != 'y' || left[1][0] != 'g' || left[1][2] != 'g') {
            ch = false;
        }
        return ch;
    }

    bool check_edge() {
        bool ch = true;
        for (int i = 0; i < 3; i++) {
            if (front[2][i] != 'w' || right[2][i] != 'b' || back[2][i] != 'y' || left[2][i] != 'g') {
                ch = false;
            }
        }
        if (down[0][0] != 'r' || down[0][2] != 'r' || down[2][0] != 'r' || down[2][2] != 'r') {
            ch = false;
        }
        return ch;
    }
  
  void solve() {
        first_step();
        cout << "The result after the first step" << endl;
        show();
        second_step();
        cout << "The result after the second step" << endl;
        show();
        third_step();
        cout << "The result after the third step" << endl;
        show();
    }
  
  void solution() {
        cout << "The solution:" << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
    }
  
      void go1() {
        read();
        cout << "Starting position" << endl;
        show();
        solve();
        solution();
    }

    void go2() {
        Random();
        save();
        cout << "Starting position" << endl;
        show();
        Rotation("left", 3);
        solve();
        solution();
    }
};

 Cube example;

int main() {
    cout << "Test 1" << endl;
    //The Rubik's cube is taken from file, displayed in console, assembled (state at different steps is displayed in console), solution is displayed as a sequence of turns of faces
    example.go1();
    cout << endl;
    cout << "Test 2" << endl;
    //The Rubik's cube is taken randomly, saved in file, displayed in console, rotation of left face for 3 times is shown, cube's assembled (state at different steps is displayed in console), solution is displayed as a sequence of turns of faces
    example.go2();
    return 0;
}
