#include <iostream>
#include<fstream>

using namespace std;
void wave(short* pArray, int n, int a, int f);
const float pi = 3.141592;

int main()
{
    cout << "������ ���� ���� ��...." << endl;
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
    *NumChannels = 1;

    int C4 = 262; //�� (4��Ÿ��)
    int D4 = 294; //��
    int E4 = 330; //��
    int F4 = 349; //��
    int G4 = 392; //��
    int A4 = 440; //��
    int B4 = 494; //��
    int Z0 = 0; //��ǥ  �� define���� �ϸ� �Լ��� �Ű������� ������?


     // Open your own file
    ofstream myTract("����� �ߴ�.wav", ios::binary | ios::out);
    if (!myTract) return 666;  // ���� ������ ������ ������ ���α׷��� ������. 
    myTract.write(header, 44 * sizeof(char));
    float dt = 1. / 8000.0;
    int n = 4000;
    float a = 20000.0, f = 440.0;// ��

    //15 + 19 + 19 + 22 + 18 93�� ��
    int order[93] = {
        E4,D4,C4,E4,G4,Z0,E4,D4,C4,E4,D4,Z0,E4,D4,C4, //ù �� - �̷��� �̼� �̷��� �̷� �̷���
        D4,D4,C4, D4,C4, E4,C4, Z0, E4,D4,C4, D4,C4, E4,G4, Z0, E4,D4,C4,// �ι� ° �� - ������ ���� �̵�~ @ �̷��� ���� �̼� @ �̷��� 
        E4,D4, Z0, E4,D4,C4, D4,D4, C4,D4,C4, E4,C4, Z0, E4,D4,C4, C4,C4,// ���� ° �� - �̷� @ �̷��� ���� ������ �̵�~ @ �̷��� ����
        A4,G4, E4,D4,C4, E4,D4, Z0, C4,C4,C4, A4,G4, E4,D4,C4, D4,C4,Z0, C4,C4,C4, // �׹� ° �� - ��� �̷��� �̷� @ ������ ��� �̷��� ���� @ ������ 
        A4,C4, A4,A4,C4, A4,G4, Z0, C4,C4,C4, A4,G4, E4,D4,C4,D4,C4,// �ټ��� ° �� - �� ��� ��� @ ������ ��� �̷��� ����
    }; //C�� D�� E�� F�� G�� A�� B�� Z��ǥ
    int nArray[93] = {
        n,n,n,n,n*3,n/2,n,n,n,n,n * 3,n / 2,n,n,n, //15
        n,n*2,n, n,n, n,n*2, n/2, n,n,n, n,n*3, n/2, n, n,n, //19 = 34
        n,n*3, n/2, n,n,n, n,n, n,n,n, n,n*2,n, n/2, n,n, n,n, //19 = 53
        n*2,n,n*3, n,n, n,n*3, n/2,  n,n,n, n*2,n,n*3, n,n, n,n*3, n/2, n,n,n, //22 = 75
        n,n,n, n,n, n,n, n,n,n, n,n,n, n,n,
    };

    int test = 34;
    short** music = new short* [test];
    int i, j;
    for (i = 0; i < test; i++) {
        music[i] = new short[nArray[i]];
    }
    for (int i = 0; i < test; i++) {
        for (int j = 0; j < nArray[i]; j++) {
            music[i][j] = (short)(a * sin(2.0 * pi * order[i] * j * dt));
            // 1,0 1 2 3
        }

    }
    for (i = 0; i < test; i++) {
        myTract.write((char*)music[i], sizeof(char) * nArray[i]);

    }

    myTract.close();
    for (i = 0; i < test; i++)
        free(music[i]);
    free(music); //�޸� ����


    return 1;
}
