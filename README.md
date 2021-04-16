# Creating-wav-file-ICON---I-loved-you-
wav file의 헤더를 작성한 후
내가 원하는 노래의 멜로디를 wav형태로 저장하는 프로그램입니다.
for (int i = 0; i < test; i++) {
        for (int j = 0; j < 2 * nArray[i]; j++) {
            if (j % 2 == 0) { music[i][j] = (short)(a * sin(2.0 * pi * order[i] / 2 * j * dt)); }
            else { music[i][j] = (short)(a * sin(2.0 * pi * order2[i] / 2 * j * dt)); }

        }

    }
    a = 진폭
    order[i] = 주파수 배열
    nAraay[i] = 박자 배열
    사인함수의 진폭, 주파수를 변경하여 음의 세기와 높이를 표현해주었습니다.
    또한 사인함수를 몇 초 동안 점을 찍을 건지 결정하여 박자로 표현하였습니다.
    
    멜로디는 아이콘의 '사랑을 했다'의 일부분입니다.
