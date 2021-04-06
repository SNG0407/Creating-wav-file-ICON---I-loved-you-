#include <iostream>
#include<fstream>

using namespace std;
void wave(short* pArray, int n, int a, int f);
const float pi = 3.141592;

int main()
{
  
    char header[44];
    short data[4000];
    //Sprint 1 
    //read binary file
    ifstream head("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::in);
    if (!head) return 999;
    head.read(header, sizeof(header));

    head.read((char*)data, sizeof(short) * 4000);
    
    short* NumChannels = (short*)(header + 22); cout << "NumChannels : " << NumChannels << endl;
    int* sampleRate = (int*)(header + 24); cout << "sampling rate : " << sampleRate << endl;
    short* BitsPerSample = (short*)(header + 34); cout << "BitsPerSample: " << BitsPerSample << endl;

    //Sprint 2
    *sampleRate = 8000;
    *NumChannels = 1;
    *BitsPerSample = 16;

    head.close();
    int C4 = 262; //도 (4옥타브)
    int D4 = 294; //레
    int E4 = 330; //미
    int F4 = 349; //파
    int G4 = 392; //솔
    int A4 = 440; //라
    int B4 = 494; //시
    int Z0 = 0; //쉼표  왜 define으로 하면 함수의 매개변수로 못받지?

  
     // Open your own file
    ofstream myTract("사랑을 했다.wav", ios::binary | ios::out);
    if (!myTract) return 666;  // 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
    myTract.write(header, 44 * sizeof(char));
    float dt = 1. / 8000.0;
    int n = 4000;  float a = 10000.0, f = 440.0;// 라
    int order[15] = { E4,D4,C4,E4,G4,Z0,E4,D4,C4,E4,D4,Z0,E4,D4,C4 };
    int nArray[15] = { n,n,n,n,n,n*3,n/2,n,n,n,n*3,n/2,n,n,n };
    
    

   
    short** music = new short* [15];
    int i, j;
    for (i = 0; i < 15; i++) {
        music[i] = new short[4000];
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < nArray[i]; j++) {
            music[i][j] = (short)(a * sin(2.0 * pi * order[j] * j * dt));

        }

    }
    for (i = 0; i < 15; i++) {
        myTract.write((char*)music[i], sizeof(char) * 4000);

    }
    myTract.close();
    //myTract.write((char*)data1, n * sizeof(char));  myTract.write((char*)music[i][j], nArray[i] * sizeof(char));
    
    //#define C4 = 262 //도 (4옥타브)
    //#define D4 = 294 //레
    //#define E4 = 330 //미
    //#define F4 = 349 //파
    //#define G4 = 392 //솔
    //#define A4 = 440 //라
    //#define B4 = 494 //시
     //#define Z0 = 0 //쉼표
    
   // for (int i = 0; i < 15; i++) {
   //    wave(music[i][0], n, a, E4); //n = 44100, a = 30000.0, f = 440.0;// 라
   //    
   //}

   //15 + 19 + 19 + 22 + 18 93개 음 표현할 예정
    //int order[93] = { E4,D4,C4,E4,G4,Z0,E4,D4,C4,E4,D4,Z0,E4,D4,C4 };
    /* --------진폭 그대로, 주파수(계이름)변경, n은 1박 4000(0.5초) --------- */
    //for (int i = 0; i < 15; i++) {
    //    //wave(music[i][0], n, a, E4); //n = 44100, a = 30000.0, f = 440.0;// 라
    //    cout << " music   " << music[i][0] << endl;
    //}

    //myTract.write((char*)data1, n * sizeof(char));
    //myTract.write((char*)data2, n * sizeof(char));
    //myTract.write((char*)data3, n * sizeof(char));
    //myTract.write((char*)data4, n * sizeof(char));
    //myTract.write((char*)data5, n * 3*sizeof(char));
    //myTract.write((char*)data6, n/2 * sizeof(char));
    //myTract.write((char*)data7, n * sizeof(char));
    //myTract.write((char*)data8, n * sizeof(char));
    //myTract.write((char*)data9, n * sizeof(char));
    //myTract.write((char*)data10, n * sizeof(char));
    //myTract.write((char*)data11, n *3* sizeof(char));
    //myTract.write((char*)data12, n /2* sizeof(char));
    //myTract.write((char*)data13, n * sizeof(char));
    //myTract.write((char*)data14, n * sizeof(char));
    //myTract.write((char*)data15, n * sizeof(char));

    
    for (i = 0; i < 15; i++)
        free(music[i]);
    free(music); //메모리 해제
    //myTract.close();

    return 1;
}

void wave(short* pArray, int n, int a, int f) {
    float dt = 1. / 8000.0;
    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < n; i++) {
            pArray[j][&i] = (short)(a * sin(2.0 * pi * f * i * dt));

        }
    }
}