#include "controller/SampleController.h"
#include "controller/ProductionController.h"
#include "controller/OrderController.h"
#include "controller/ReleaseController.h"
#include "view/MainView.h"
#include <iostream>

int main() {
    // 한글 출력을 위한 콘솔 코드페이지 설정
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    // 컨트롤러 초기화 (의존성 주입 순서 준수)
    SampleController     sampleCtrl;
    ProductionController productionCtrl(sampleCtrl);
    OrderController      orderCtrl(sampleCtrl, productionCtrl);

    // TODO: 데이터 영속성 - 파일에서 초기 데이터 로드
    // sampleCtrl.loadFromFile("samples.json");
    // orderCtrl.loadFromFile("orders.json");

    // 메인 뷰 실행
    MainView mainView(sampleCtrl, orderCtrl, productionCtrl);
    mainView.run();

    // TODO: 데이터 영속성 - 종료 전 파일에 저장
    // sampleCtrl.saveToFile("samples.json");
    // orderCtrl.saveToFile("orders.json");

    return 0;
}
