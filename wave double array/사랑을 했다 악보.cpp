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

    int C4 = 262; //�� (4��Ÿ��)
    int D4 = 294; //��
    int E4 = 330; //��
    int F4 = 349; //��
    int G4 = 392; //��
    int A4 = 440; //��
    int B4 = 494; //��
    int Z0 = 0; //��ǥ  �� define���� �ϸ� �Լ��� �Ű������� ������?


     // Open your own file
    ofstream myTract("����� �ߴ�(ȭ��).wav", ios::binary | ios::out);
    if (!myTract) return 666;  // ���� ������ ������ ������ ���α׷��� ������. 
    myTract.write(header, 44 * sizeof(char));
    float dt = 1. / 8000.0;
    int n = 4000;
    float a = 20000.0, f = 440.0;// ��

    //15 + 19 + 19 + 22 + 18 93�� ��
    /*
    ����� �ߴ�            �츮�� ����~
    �̷��� �̼�            �̷��� �̷�~
    E4,D4,C4,E4,G4, Z0,    E4,D4,C4,E4,D4,    Z0,
    n, n, n, n, n*3,n / 2, n, n, n, n, n * 3, n / 2,
    �ö�� �÷�            �ö�� �ö�
    B4,A4,G4,B4,2*D4, Z0,    B4,A4,G4,B4,A4,    Z0,

    ������ ����          �߾��� �ƴ�~
    �̷��� ����          ������ �̵�~ @
    E4,D4,C4,D4,D4,      C4,D4,C4, E4,C4,    Z0,
    n, n, n, n, n * 2,   n, n, n,  n, n * 2, n / 2,
    �ö�� ���          �ֶ�� �ü�
    B4,A4,G4,A4,A4,      G4,A4,G4, B4,G4,    Z0,

    ������      ���    ��� ~
    �̷���      ����    �̹̼�  @ 
    E4,D4,C4,   D4,C4,  E4,E4,G4, Z0, 
    n, n, n     n, n,   n, n, n * 3, n / 2,
    �ö��      ���    �÷�(���� ��)~
    B4,A4,G4,   A4,G4,  B4,B4,2*D4, Z0,

    ������      �ḻ ~
    �̷���      �̷� @ 
    E4,D4,C4,   E4,D4,Z0,
    n, n, n,    n, n*3, n/2,
    �ö��      �ö�
    B4,A4,G4,   B4,A4,Z0,

    �װŸ�     �ƴ�   ��   ����ߴ�~
    �̷���     ����   ��   �����̵�~ @ 
    E4,D4,C4,  D4,D4, C4,  D4,C4,E4,C4,  Z0
    n, n, n,   n, n,  n,   n, n, n, n*2, n/2
    �ö��     ���   ��   ��ֽü�
    B4,A4,G4,  A4,A4, G4,  A4,G4,B4,G4,  Z0
    */ 
    int order[49] = {
    E4,D4,C4,E4,G4, Z0,    E4,D4,C4,E4,D4,    Z0, //12
    E4,D4,C4,D4,D4,      C4,D4,C4, E4,C4,    Z0,  //11
    E4,D4,C4,   D4,C4,  E4,E4,G4, Z0,             //9
    E4,D4,C4,   E4,D4,Z0,                         //6
    E4,D4,C4,  D4,D4, C4,  D4,C4,E4,C4,  Z0       //11
    }; //C�� D�� E�� F�� G�� A�� B�� Z��ǥ
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
    }; // n=�Ⱥ���ǥ

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
    free(music); //�޸� ����


    return 1;
}
