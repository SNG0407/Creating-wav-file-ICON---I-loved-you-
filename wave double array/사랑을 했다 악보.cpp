#include <iostream>
#include<fstream>

using namespace std;
void wave(short* pArray, int n, int a, int f);
const float pi = 3.141592;

int main()
{
    
    char header[44];
    short data[50];
    //Sprint 1 
    //read binary file
    ifstream head("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::in);
    if (!head) return 999;
    head.read(header, sizeof(header));

    head.read((char*)data, sizeof(short) * 50);
    head.close();
    short* NumChannels = (short*)(header + 22); cout << "NumChannels : " << NumChannels << endl;
    int* sampleRate = (int*)(header + 24); cout << "sampling rate : " << sampleRate << endl;
    short* BitsPerSample = (short*)(header + 34); cout << "BitsPerSample: " << BitsPerSample << endl;

    //Sprint 2
    *sampleRate = 8000;
    *NumChannels = 2;

    int C4 = 262; //도 (4옥타브)
    int D4 = 294; //레
    int E4 = 330; //미
    int F4 = 349; //파
    int G4 = 392; //솔
    int A4 = 440; //라
    int B4 = 494; //시
    int Z0 = 0; //쉼표  왜 define으로 하면 함수의 매개변수로 못받지?


     // Open your own file
    ofstream myTract("사랑을 했다(화음).wav", ios::binary | ios::out);
    if (!myTract) return 666;  // 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
    myTract.write(header, 44 * sizeof(char));
    float dt = 1. / 8000.0;
    int n = 4000;
    float a = 20000.0, f = 440.0;// 라

    //15 + 19 + 19 + 22 + 18 93개 음
    /*
    사랑을 했다            우리가 만나~
    미레도 미솔            미레도 미레~
    E4,D4,C4,E4,G4, Z0,    E4,D4,C4,E4,D4,    Z0,
    n, n, n, n, n*3,n / 2, n, n, n, n, n * 3, n / 2,
    시라솔 시레            시라솔 시라
    B4,A4,G4,B4,2*D4, Z0,    B4,A4,G4,B4,A4,    Z0,

    지우지 못할          추억이 됐다~
    미레도 레레          도레도 미도~ @
    E4,D4,C4,D4,D4,      C4,D4,C4, E4,C4,    Z0,
    n, n, n, n, n * 2,   n, n, n,  n, n * 2, n / 2,
    시라솔 라라          솔라솔 시솔
    B4,A4,G4,A4,A4,      G4,A4,G4, B4,G4,    Z0,

    볼만한      멜로    드라마 ~
    미레도      레도    미미솔  @ 
    E4,D4,C4,   D4,C4,  E4,E4,G4, Z0, 
    n, n, n     n, n,   n, n, n * 3, n / 2,
    시라솔      라솔    시레(높은 음)~
    B4,A4,G4,   A4,G4,  B4,B4,2*D4, Z0,

    괜찮은      결말 ~
    미레도      미레 @ 
    E4,D4,C4,   E4,D4,Z0,
    n, n, n,    n, n*3, n/2,
    시라솔      시라
    B4,A4,G4,   B4,A4,Z0,

    그거면     됐다   널   사랑했다~
    미레도     레레   도   레도미도~ @ 
    E4,D4,C4,  D4,D4, C4,  D4,C4,E4,C4,  Z0
    n, n, n,   n, n,  n,   n, n, n, n*2, n/2
    시라솔     라라   솔   라솔시솔
    B4,A4,G4,  A4,A4, G4,  A4,G4,B4,G4,  Z0
    */ 
    int order[49] = {
    E4,D4,C4,E4,G4, Z0,    E4,D4,C4,E4,D4,    Z0, //12
    E4,D4,C4,D4,D4,      C4,D4,C4, E4,C4,    Z0,  //11
    E4,D4,C4,   D4,C4,  E4,E4,G4, Z0,             //9
    E4,D4,C4,   E4,D4,Z0,                         //6
    E4,D4,C4,  D4,D4, C4,  D4,C4,E4,C4,  Z0       //11
    }; //C도 D레 E미 F파 G솔 A라 B시 Z쉼표
    int order2[49] = {
    B4,A4,G4,B4,2*D4, Z0,    B4,A4,G4,B4,A4,    Z0,
    B4,A4,G4,A4,A4,      G4,A4,G4, B4,G4,    Z0,
    B4,A4,G4,   A4,G4,  B4,B4,2 * D4, Z0,
    B4,A4,G4,   B4,A4,Z0,
    B4,A4,G4,  A4,A4, G4,  A4,G4,B4,G4,  Z0
    };
    int nArray[49] = {
    n, n, n, n, n * 3,n / 2, n, n, n, n, n * 3, n / 2, //12
    n, n, n, n, n * 2,   n, n, n,  n, n * 2, n / 2,    //11 23
    n, n, n,     n, n,   n, n, n * 3, n / 2,           //9  32
    n, n, n,    n, n * 3, n / 2,                       //6  38
    n, n, n,   n, n,  n,   n, n, n, n * 2, n / 2       //11 49
    }; // n=팔분음표

    int test = 49;
    short** music = new short* [test];
    int i, j;
    for (i = 0; i < test; i++) {
        music[i] = new short[nArray[i]*2];
    }
    for (int i = 0; i < test; i++) {
        for (int j = 0; j < 2*nArray[i]; j++) {
            if (j % 2 == 0) { music[i][j] = (short)(a * sin(2.0 * pi * order[i]/2 * j * dt)); }
            else { music[i][j] = (short)(a * sin(2.0 * pi * order2[i]/2 * j * dt)); }

        }

    }
    for (i = 0; i < test; i++) {
        myTract.write((char*)music[i], sizeof(char) * nArray[i]*2);

    }

    myTract.close();
    for (i = 0; i < test; i++)
        free(music[i]);
    free(music); //메모리 해제


    return 1;
}
