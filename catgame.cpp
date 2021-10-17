#define _CRT_SECURE_NO_WARNINGS

#include <bangtal>
using namespace bangtal;

#include <cstdlib>
#include <ctime>
#include <Windows.h>

ScenePtr mainscene;
ScenePtr town;
ScenePtr lake;
ScenePtr townhall;
ScenePtr field;
ScenePtr park;
ScenePtr home;
ScenePtr neigh;
ScenePtr mousehole;
ScenePtr finalscene;

SoundPtr bgmusic;
SoundPtr gamemusic;
TimerPtr show_end;

ScenePtr help1;
ScenePtr help2;
ScenePtr help3;
ScenePtr help4;
ScenePtr help5;
ScenePtr help6;
ScenePtr help7;
ScenePtr help8;
ScenePtr help9;
ScenePtr help10;

ObjectPtr warn99999_m;
ObjectPtr mousehole_black;
ObjectPtr minigame_notice_mouse;
ObjectPtr mouse1;
ObjectPtr mouse2;
ObjectPtr mouse3;
ObjectPtr mouse4;
ObjectPtr mouse5;
ObjectPtr mouse_success;
ObjectPtr mousegame_notice;
ObjectPtr mousegame_start;
ObjectPtr mousegame_back;
TimerPtr mousegame_again;
TimerPtr mousetimer;
int movecount = 100000;
int mousecount = 0;

ObjectPtr moneyprint[10];
int money = 0;
int moneycount = 0;

int godeunglove = 0;
int nabilove = 0;
int dustlove = 0;
int bestlove = 0;
int blacklove = 0;


//화면에 돈(캣닢) 표기
void printmoney(int nowmon, ScenePtr scene) {
	char Money[5] = { 0, };
	char moneyimg[5][20];

	//정수형의 돈을 각각 자리수에 맞는 배열에 넣어준다.
	Money[4] = nowmon % 10;
	Money[3] = (nowmon / 10) % 10;
	Money[2] = (nowmon / 100) % 10;
	Money[1] = (nowmon / 1000) % 10;
	Money[0] = (nowmon / 10000) % 10;

	//처음 표시할 때를 제외하고, 숫자 이미지가 겹치지 않도록 이전 숫자 이미지를 지운다.
	if (moneycount > 0) {
		for (int k = 0; k < 5; k++) {
			moneyprint[k]->hide();
		}
	}

	//배열에 각 숫자 이미지를 저장해둔다.
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (Money[i] == j) {
				sprintf(moneyimg[i], "Images/숫자/%d.png", j);
			}
		}
	}

	//저장해둔 숫자 이미지를 화면에 표시한다.
	for (int k = 0; k < 5; k++) {
		moneyprint[k] = Object::create(moneyimg[k], scene, 1015 + 50 * (k % 5), 655);
	}

	moneycount++;

}

void settown() { //마을 설정
	auto lakebutton = Object::create("Images/마을/낚시터.png", town, 0, 268);
	auto townhallbutton = Object::create("Images/마을/마을회관.png", town, 109, 74);
	auto fieldbutton = Object::create("Images/마을/캣닢밭.png", town, 325, 406);
	auto parkbutton = Object::create("Images/마을/공원.png", town, 823, 385);
	auto homebutton = Object::create("Images/마을/우리집.png", town, 580, 75);
	auto neighbutton = Object::create("Images/마을/이웃집.png", town, 965, 103);
	auto mouseholebutton = Object::create("Images/마을/쥐구멍.png", town, 1143, 408);
	auto tutorial = Object::create("Images/기타/튜토리얼.png", town, 900, 651);

	tutorial->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //튜토리얼 보기
		help1->enter();
		return true;
	});

	lakebutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		lake->enter();
		printmoney(money, lake);
		return true;
	});

	townhallbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		townhall->enter();
		printmoney(money, townhall);
		return true;
	});

	fieldbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		field->enter();
		printmoney(money, field);
		return true;
	});

	parkbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		park->enter();
		printmoney(money, park);
		return true;
	});

	homebutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		home->enter();
		printmoney(money, home);
		return true;
	});

	neighbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		neigh->enter();
		printmoney(money, neigh);
		return true;
	});

	warn99999_m = Object::create("Images/알림창/캣닢99999.png", town, 320, 280); //캣닢 최대로 모았을 때 알림창
	warn99999_m->hide();
	warn99999_m->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		warn99999_m->hide();
		return true;
	});

	mouseholebutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (money > 99899) {
			warn99999_m->show();
		}
		else {
			mousehole->enter();
			bgmusic->stop();
			gamemusic->play(true);
		}
		return true;
	});

	//쥐잡기게임 쿨타임 관련
	minigame_notice_mouse = Object::create("Images/알림창/미니게임쿨타임.png", town, 220, 290);  //쿨타임 알림창
	minigame_notice_mouse->hide();
	minigame_notice_mouse->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		minigame_notice_mouse->hide(); //알림창은 클릭하면 사라지도록 한다.
		return true;
	});

	mousehole_black = Object::create("Images/마을/쥐구멍_비활성.png", town, 1143, 408); //쥐구멍 어둡게 보임
	mousehole_black->hide();
	mousehole_black->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		minigame_notice_mouse->show(); //쥐구멍 비활성 상태에서 클릭하면 알림창을 띄운다.
		return true;
	});

	mousegame_again = Timer::create(60.f); //미니게임 쿨타임 60초
	mousegame_again->setOnTimerCallback([&](auto)->bool { 
		mousehole_black->hide(); //60초 지나면 쿨타임 해제
		mousegame_again->set(60.f); //쿨타임 리셋
		return true;
	});

}

void help() { //튜토리얼
	auto skip1 = Object::create("Images/기타/skip.png", help1, 1155, 670);
	skip1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //클릭하면 게임 시작
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip2 = Object::create("Images/기타/skip.png", help2, 1155, 670);
	skip2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip3 = Object::create("Images/기타/skip.png", help3, 1155, 670);
	skip3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip4 = Object::create("Images/기타/skip.png", help4, 1155, 600);
	skip4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip5 = Object::create("Images/기타/skip.png", help5, 1155, 670);
	skip5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip6 = Object::create("Images/기타/skip.png", help6, 1155, 670);
	skip6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip7 = Object::create("Images/기타/skip.png", help7, 1155, 670);
	skip7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip8 = Object::create("Images/기타/skip.png", help8, 1155, 670);
	skip8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});
	auto skip9 = Object::create("Images/기타/skip.png", help9, 1155, 670);
	skip9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});

	auto next1 = Object::create("Images/기타/다음.png", help1, 1200, 40);
	next1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help2->enter();
		return true;
		});
	auto next2 = Object::create("Images/기타/다음.png", help2, 1200, 40);
	next2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help3->enter();
		return true;
		});
	auto next3 = Object::create("Images/기타/다음.png", help3, 1200, 40);
	next3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help4->enter();
		return true;
		});
	auto next4 = Object::create("Images/기타/다음.png", help4, 1200, 40);
	next4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help5->enter();
		return true;
		});
	auto next5 = Object::create("Images/마을/우리집.png", help5, 580, 75);
	next5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help6->enter();
		return true;
		});
	auto next6 = Object::create("Images/기타/다음.png", help6, 1200, 40);
	next6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help7->enter();
		return true;
		});
	auto next7 = Object::create("Images/기타/backbutton.png", help7, 5, 650);
	next7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help8->enter();
		return true;
		});
	auto next8 = Object::create("Images/기타/다음.png", help8, 1200, 40);
	next8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help9->enter();
		return true;
		});
	auto next9 = Object::create("Images/기타/다음.png", help9, 1200, 40);
	next9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help10->enter();
		return true;
		});
	auto next10 = Object::create("Images/기타/다음.png", help10, 1200, 40);
	next10->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});

	auto back2 = Object::create("Images/기타/이전.png", help2, 1165, 40);
	back2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help1->enter();
		printmoney(money, town);
		return true;
		});
	auto back3 = Object::create("Images/기타/이전.png", help3, 1165, 40);
	back3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help2->enter();
		printmoney(money, town);
		return true;
		});
	auto back4 = Object::create("Images/기타/이전.png", help4, 1165, 40);
	back4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help3->enter();
		printmoney(money, town);
		return true;
		});
	auto back9 = Object::create("Images/기타/이전.png", help9, 1165, 40);
	back9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help8->enter();
		printmoney(money, town);
		return true;
		});
	auto back10 = Object::create("Images/기타/이전.png", help9, 1165, 40);
	back10->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		help9->enter();
		printmoney(money, town);
		return true;
		});

}

int loc_x() { //쥐 위치 x
	int x = rand() % 1100;
	return x;
}

int loc_y() { //쥐 위치 y
	int y = rand() % 590;
	return y;
}

void mousegame() { //쥐잡기 미니게임
	mouse_success = Object::create("Images/알림창/미니게임성공.png", mousehole, 350, 280); mouse_success->hide(); //성공 시 보여줄 알림창

	mouse_success->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //성공 알림창 클릭 시
		mousecount = 0; //잡은 쥐의 수 초기화
		mouse_success->hide(); //알림창 숨기기
		mousegame_notice->show(); //게임 시작 전 보이던 알림창 다시 보이도록
		mousegame_start->show();
		mousegame_back->show();
		money = money + 500; //보유 캣닢 증가

		town->enter(); //마을로 돌아가기
		gamemusic->stop();
		bgmusic->play(true);
		mousehole_black->show(); //쥐구멍 아이콘을 어둡게 보이도록함
		mousegame_again->start(); //미니게임 쿨타임 시작
		printmoney(money, town);

		return true;
	});

	mouse1 = Object::create("Images/기타/쥐.png", mousehole, loc_x(), loc_y());
	mouse2 = Object::create("Images/기타/쥐.png", mousehole, loc_x(), loc_y());
	mouse3 = Object::create("Images/기타/쥐.png", mousehole, loc_x(), loc_y());
	mouse4 = Object::create("Images/기타/쥐.png", mousehole, loc_x(), loc_y());
	mouse5 = Object::create("Images/기타/쥐.png", mousehole, loc_x(), loc_y());

	movecount = 100000; //쥐가 계속 움직일 수 있도록 큰 수로

	mousetimer = Timer::create(0.4f); //0.4초마다 쥐가 움직이도록
	mousetimer->start();

	mousetimer->setOnTimerCallback([&](auto)->bool { //쥐가 랜덤하게 계속 돌아다님

		mouse1->locate(mousehole, loc_x(), loc_y());
		mouse2->locate(mousehole, loc_x(), loc_y());
		mouse3->locate(mousehole, loc_x(), loc_y());
		mouse4->locate(mousehole, loc_x(), loc_y());
		mouse5->locate(mousehole, loc_x(), loc_y());

		movecount--;
		if (movecount > 0) {
			mousetimer->set(0.4f);
			mousetimer->start();
		}

		return true;
	});

	mouse1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { 
		mouse1->hide();
		mousecount++;

		if (mousecount == 5) { 
			mouse_success->show();
			mousetimer->stop(); //5마리 모두 잡으면 타이머 끝
		}
		return true;
	});
	mouse2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		mouse2->hide();
		mousecount++;

		if (mousecount == 5) { 
			mouse_success->show();
			mousetimer->stop();
		}
		return true;
	});
	mouse3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		mouse3->hide();
		mousecount++;

		if (mousecount == 5) { 
			mouse_success->show();
			mousetimer->stop();
		}
		return true;
	});
	mouse4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		mouse4->hide();
		mousecount++;

		if (mousecount == 5) { 
			mouse_success->show();
			mousetimer->stop();
		}
		return true;
	});
	mouse5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		mouse5->hide();
		mousecount++;

		if (mousecount == 5) { 
			mouse_success->show();
			mousetimer->stop();
		}
		return true;
	});

}

void gotoend() {
	if (godeunglove > 199 && nabilove > 199 && dustlove > 199 && bestlove > 199 && blacklove > 199) {
		finalscene->enter();
		show_end->start();
	}
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	srand((unsigned int)time(NULL));

	mainscene = Scene::create("", "Images/배경/시작화면.jpg");
	town = Scene::create("", "Images/배경/town.jpg");
	lake = Scene::create("", "Images/배경/낚시터.jpg");
	townhall = Scene::create("", "Images/배경/마을회관.jpg");
	field = Scene::create("", "Images/배경/캣닢밭.jpg");
	park = Scene::create("", "Images/배경/공원.jpg");
	neigh = Scene::create("", "Images/배경/이웃집.jpg");
	home = Scene::create("", "Images/배경/우리집.jpg");
	mousehole = Scene::create("", "Images/배경/쥐구멍.jpg");
	auto trashgame = Scene::create("", "Images/배경/쓰레기.jpg");
	finalscene = Scene::create("", "Images/배경/끝.jpg");

	help1 = Scene::create("", "Images/도움말/도움1.jpg");
	help2 = Scene::create("", "Images/도움말/도움2.jpg");
	help3 = Scene::create("", "Images/도움말/도움3.jpg");
	help4 = Scene::create("", "Images/도움말/도움4.jpg");
	help5 = Scene::create("", "Images/도움말/도움5.jpg");
	help6 = Scene::create("", "Images/도움말/도움6.jpg");
	help7 = Scene::create("", "Images/도움말/도움7.jpg");
	help8 = Scene::create("", "Images/도움말/도움8.jpg");
	help9 = Scene::create("", "Images/도움말/도움9.jpg");
	help10 = Scene::create("", "Images/도움말/도움10.jpg");

	bgmusic = Sound::create("sound/전체.mp3"); //전체 배경음악
	gamemusic = Sound::create("sound/미니게임.mp3"); //미니게임 배경음악 
	SoundPtr effectsound = Sound::create("sound/start.mp3"); //효과음

	auto startbutton = Object::create("Images/기타/startbutton.png", mainscene, 545, 15); startbutton->hide();	//시작버튼
	auto endbutton = Object::create("Images/기타/endbutton.png", finalscene, 470, 410); endbutton->hide();	//종료

	auto show_start = Timer::create(1.f); //1초 뒤에 시작버튼이 나타나도록
	show_end = Timer::create(3.f); //1.5초 뒤에 종료버튼이 나타나도록
	auto stop_sound = Timer::create(1.f); //게임 시작버튼 효과음 1번만 내고 끄는 용도
	show_start->start();

	show_start->setOnTimerCallback([&](TimerPtr)->bool {
		startbutton->show();
		effectsound->play(true);
		stop_sound->start();
		return true;
	});

	stop_sound->setOnTimerCallback([&](TimerPtr)->bool {
		effectsound->stop();
		stop_sound->set(1.f);
		return true;
	});

	startbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //클릭하면 튜토리얼부터 시작
		bgmusic->play(true);
		help1->enter();
		return true;
	});

	show_end->setOnTimerCallback([&](TimerPtr)->bool {
		endbutton->show();
		effectsound->play(true);
		stop_sound->start();
		return true;
	});

	endbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //클릭하면 게임 종료
		endGame();
		return true;
	});

	help();//튜토리얼

	settown();


	//낚시터

	auto cat_lake = Object::create("Images/고양이/앉은고등어.png", lake, 600, 100); //배경에 앉아있는 고양이
	auto cheese_lake = Object::create("Images/고양이/치즈.png", lake, 920, 179); cheese_lake->hide(); //치즈
	auto godeung = Object::create("Images/고양이/고등어.png", lake, 40, 170); godeung->hide(); //고등어
	auto godeung_sad = Object::create("Images/고양이/고등어_시무룩.png", lake, 40, 170); godeung_sad->hide(); //고등어 시무룩
	auto godeung_happy = Object::create("Images/고양이/고등어_웃음.png", lake, 40, 170); godeung_happy->hide(); //고등어 웃음
	
	auto lake_talk1 = Object::create("Images/대사/고등어1.png", lake, 28, 20); lake_talk1->hide(); //고등어 대사1
	auto lake_ans_1_1 = Object::create("Images/선택지/선물하기.png", lake, 1000, 100); lake_ans_1_1->hide(); //선물하기
	auto lake_ans_1_2 = Object::create("Images/선택지/닫기.png", lake, 1000, 50); lake_ans_1_2->hide(); //닫기
	auto lake_present = Object::create("Images/알림창/선물.png", lake, 345, 350); lake_present->hide(); //선물할까요?
	auto lake_nomoney = Object::create("Images/알림창/캣닢부족.png", lake, 450, 330); lake_nomoney->hide(); //캣닢 부족
	auto lake_present_yes = Object::create("Images/알림창/선물네.png", lake, 654, 270); lake_present_yes->hide(); //네
	auto lake_present_no = Object::create("Images/알림창/선물아니오.png", lake, 345, 270); lake_present_no->hide(); //아니오
	auto lake_what_present = Object::create("Images/알림창/선물_고등어.png", lake, 345, 200); lake_what_present->hide(); //무슨 선물?
	auto lake_present_1 = Object::create("Images/선물/미끼.png", lake, 420, 300); lake_present_1->hide(); //미끼
	auto lake_present_2 = Object::create("Images/선물/낚싯대.png", lake, 720, 300); lake_present_2->hide(); //낚싯대
	auto lake_talk1_1 = Object::create("Images/대사/고등어_미끼.png", lake, 28, 20); lake_talk1_1->hide(); //미끼 선택 시 답변
	auto lake_talk1_2 = Object::create("Images/대사/고등어_낚싯대.png", lake, 28, 20); lake_talk1_2->hide(); //낚싯대 선택 시 답변
	auto lake_talk1_close = Object::create("Images/선택지/닫기.png", lake, 1080, 50); lake_talk1_close->hide(); //창 닫기

	auto lake_talk2 = Object::create("Images/대사/고등어2.png", lake, 28, 20); lake_talk2->hide(); //고등어 대사2
	auto lake_ans_2_1 = Object::create("Images/선택지/참치.png", lake, 1080, 100); lake_ans_2_1->hide(); //참치
	auto lake_ans_2_2 = Object::create("Images/선택지/연어.png", lake, 1080, 50); lake_ans_2_2->hide(); //연어
	auto lake_talk2_1 = Object::create("Images/대사/고등어_참치.png", lake, 28, 20); lake_talk2_1->hide(); //참치 선택 시 답변
	auto lake_talk2_2 = Object::create("Images/대사/고등어_연어.png", lake, 28, 20); lake_talk2_2->hide(); //연어 선택 시 답변
	auto lake_talk2_close = Object::create("Images/선택지/닫기.png", lake, 1080, 50); lake_talk2_close->hide(); //창 닫기

	auto lake_talk3 = Object::create("Images/대사/고등어3.png", lake, 28, 20); lake_talk3->hide(); //고등어 대사3
	auto lake_heart = Object::create("Images/기타/하트.png", lake, 1186, 148); lake_heart->hide(); //친밀도 최고 시 표시됨
	auto lake_talk3_close = Object::create("Images/선택지/닫기.png", lake, 1080, 50); lake_talk3_close->hide(); //창 닫기

	auto lake_to_town = Object::create("Images/기타/backbutton.png", lake, 5, 650); //뒤로가기

	cat_lake->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //배경에 있는 고양이를 누르면 대화 시작
		cat_lake->hide();
		cheese_lake->show();
		lake_to_town->hide();

		if (godeunglove < 100) { //친밀도 1단계
			godeung_sad->show();
			lake_talk1->show();
			lake_ans_1_1->show();
			lake_ans_1_2->show();
		}

		else if (godeunglove > 99 && godeunglove < 200) { //친밀도 2단계
			godeung->show();
			lake_talk2->show();
			lake_ans_2_1->show();
			lake_ans_2_2->show();
		}

		else if (godeunglove > 199) { //친밀도 3단계
			godeung_happy->show();
			lake_talk3->show();
			lake_heart->show();
			lake_talk3_close->show();
		}

		return true;
		});

	//첫번째 대화
	lake_ans_1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//선물하기
		lake_ans_1_1->hide();
		lake_ans_1_2->hide();
		lake_present->show(); //진짜?
		lake_present_yes->show(); //네
		lake_present_no->show(); //아니오
		return true;
		});
	lake_ans_1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닫기
		cat_lake->show();
		lake_to_town->show();
		cheese_lake->hide();
		godeung_sad->hide();
		lake_talk1->hide();
		lake_ans_1_1->hide();
		lake_ans_1_2->hide();
		return true;
		});
	lake_present_yes->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_네
		lake_present->hide();
		lake_present_yes->hide();
		lake_present_no->hide();

		if (money < 400) { //캣닢 부족
			lake_nomoney->show();
		}

		else {
			lake_what_present->show(); //무슨 선물?
			lake_present_1->show();//미끼
			lake_present_2->show();//낚싯대
		}

		return true;
		});
	lake_present_no->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_아니오
		lake_present->hide();
		lake_present_yes->hide();
		lake_present_no->hide();
		lake_ans_1_1->show();
		lake_ans_1_2->show();
		return true;
		});
	lake_nomoney->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢부족? > ok > 창 다 닫기
		lake_nomoney->hide();
		godeung_sad->hide();
		cheese_lake->hide();
		lake_talk1->hide();
		cat_lake->show();
		lake_to_town->show();
		return true;
		});
	lake_present_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //미끼를 선물
		lake_what_present->hide();
		lake_present_1->hide();
		lake_present_2->hide();
		godeung_sad->hide();
		lake_talk1->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, lake); //보유 캣닢 갱신
		godeunglove = godeunglove + 100; //친밀도 100증가
		godeung_happy->show(); //고등어 표정 바뀜
		lake_talk1_1->show();
		lake_talk1_close->show();
		return true;
		});
	lake_present_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //낚싯대를 선물
		lake_what_present->hide();
		lake_present_1->hide();
		lake_present_2->hide();
		godeung_sad->hide();
		lake_talk1->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, lake); //보유 캣닢 갱신
		godeunglove = godeunglove + 40; //친밀도 40증가
		godeung->show(); //고등어 표정 바뀜
		lake_talk1_2->show();
		lake_talk1_close->show();
		return true;
		});
	lake_talk1_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화1 닫기
		lake_talk1_1->hide();
		lake_talk1_2->hide();
		lake_talk1_close->hide();
		godeung_happy->hide();
		godeung->hide();
		cheese_lake->hide();
		cat_lake->show();
		lake_to_town->show();
		return true;
		});

	//두번째 대화
	lake_ans_2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //참치를 선택
		lake_talk2->hide();
		lake_ans_2_1->hide();
		lake_ans_2_2->hide();
		godeung->hide();
		godeunglove = godeunglove + 100; //친밀도 100증가
		godeung_happy->show(); //고등어 표정 바뀜
		lake_talk2_1->show();
		lake_talk2_close->show();
		return true;
		});
	lake_ans_2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //연어를 선택
		lake_talk2->hide();
		lake_ans_2_1->hide();
		lake_ans_2_2->hide();
		godeunglove = godeunglove + 40; //친밀도 40증가
		lake_talk2_2->show();
		lake_talk2_close->show();
		return true;
		});
	lake_talk2_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화2 닫기
		godeung_happy->hide();
		godeung->hide();
		cheese_lake->hide();
		lake_talk2_1->hide();
		lake_talk2_2->hide();
		lake_talk2_close->hide();
		cat_lake->show();
		lake_to_town->show();
		return true;
		});

	//세번째 대화
	lake_talk3_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//대화3 닫기
		godeung_happy->hide();
		cheese_lake->hide();
		lake_talk3_close->hide();
		lake_heart->hide();
		lake_talk3->hide();
		cat_lake->show();
		lake_to_town->show();
		gotoend();
		return true;
	});

	//뒤로가기
	lake_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
		});


	//마을회관

	auto cat_townhall = Object::create("Images/고양이/앉은최고냥.png", townhall, 740, 410); //배경에 앉아있는 고양이
	auto cheese_townhall = Object::create("Images/고양이/치즈.png", townhall, 920, 179); cheese_townhall->hide(); //치즈
	auto best = Object::create("Images/고양이/최고냥.png", townhall, 40, 170); best->hide(); //최고냥
	auto best_sad = Object::create("Images/고양이/최고냥_시무룩.png", townhall, 40, 170); best_sad->hide(); //최고냥 시무룩
	auto best_happy = Object::create("Images/고양이/최고냥_웃음.png", townhall, 40, 170); best_happy->hide(); //최고냥 웃음

	auto townhall_talk1 = Object::create("Images/대사/최고냥1.png", townhall, 28, 20); townhall_talk1->hide(); //최고냥 대사1
	auto townhall_ans_1_1 = Object::create("Images/선택지/무계획.png", townhall, 1000, 50); townhall_ans_1_1->hide(); //계획 없음
	auto townhall_ans_1_2 = Object::create("Images/선택지/마을둘러보기.png", townhall, 1000, 100); townhall_ans_1_2->hide(); //마을 둘러보기
	auto townhall_talk1_1 = Object::create("Images/대사/최고냥_무계획.png", townhall, 28, 20); townhall_talk1_1->hide(); //무계획 시 답변
	auto townhall_talk1_2 = Object::create("Images/대사/최고냥_마을.png", townhall, 28, 20); townhall_talk1_2->hide(); //마을 둘러보기 시 답변
	auto townhall_talk1_close = Object::create("Images/선택지/닫기.png", townhall, 1080, 50); townhall_talk1_close->hide(); //창 닫기

	auto townhall_talk2 = Object::create("Images/대사/최고냥2.png", townhall, 28, 20); townhall_talk2->hide(); //최고냥 대사2
	auto townhall_ans_2_1 = Object::create("Images/선택지/선물하기.png", townhall, 1080, 100); townhall_ans_2_1->hide(); //선물하기
	auto townhall_ans_2_2 = Object::create("Images/선택지/닫기.png", townhall, 1080, 50); townhall_ans_2_2->hide(); //닫기
	auto townhall_present = Object::create("Images/알림창/선물.png", townhall, 345, 350); townhall_present->hide(); //선물할까요?
	auto townhall_nomoney = Object::create("Images/알림창/캣닢부족.png", townhall, 450, 330); townhall_nomoney->hide(); //캣닢 부족
	auto townhall_present_yes = Object::create("Images/알림창/선물네.png", townhall, 654, 270); townhall_present_yes->hide(); //네
	auto townhall_present_no = Object::create("Images/알림창/선물아니오.png", townhall, 345, 270); townhall_present_no->hide(); //아니오
	auto townhall_what_present = Object::create("Images/알림창/선물_최고냥.png", townhall, 345, 200); townhall_what_present->hide(); //무슨 선물?
	auto townhall_present_1 = Object::create("Images/선물/캣닢차.png", townhall, 420, 300); townhall_present_1->hide(); //캣닢차
	auto townhall_present_2 = Object::create("Images/선물/생선포.png", townhall, 720, 300); townhall_present_2->hide(); //생선포
	auto townhall_talk2_1 = Object::create("Images/대사/최고냥_캣닢차.png", townhall, 28, 20); townhall_talk2_1->hide(); //캣닢차 선택 시 답변
	auto townhall_talk2_2 = Object::create("Images/대사/최고냥_포.png", townhall, 28, 20); townhall_talk2_2->hide(); //생선포 선택 시 답변
	auto townhall_talk2_close = Object::create("Images/선택지/닫기.png", townhall, 1080, 50); townhall_talk2_close->hide(); //창 닫기

	auto townhall_talk3 = Object::create("Images/대사/최고냥3.png", townhall, 28, 20); townhall_talk3->hide(); //최고냥 대사3
	auto townhall_heart = Object::create("Images/기타/하트.png", townhall, 1186, 148); townhall_heart->hide(); //친밀도 최고 시 표시됨
	auto townhall_talk3_close = Object::create("Images/선택지/닫기.png", townhall, 1080, 50); townhall_talk3_close->hide(); //창 닫기

	auto townhall_to_town = Object::create("Images/기타/backbutton.png", townhall, 5, 650); //뒤로가기

	cat_townhall->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //배경에 있는 고양이를 누르면 대화 시작
		cat_townhall->hide();
		cheese_townhall->show();
		townhall_to_town->hide();

		if (bestlove < 100) { //친밀도 1단계
			best_happy->show();
			townhall_talk1->show();
			townhall_ans_1_1->show();
			townhall_ans_1_2->show();
		}

		else if (bestlove > 99 && bestlove < 200) { //친밀도 2단계
			best_sad->show();
			townhall_talk2->show();
			townhall_ans_2_1->show();
			townhall_ans_2_2->show();
		}

		else if (bestlove > 199) { //친밀도 3단계
			best_happy->show();
			townhall_talk3->show();
			townhall_heart->show();
			townhall_talk3_close->show();
		}

		return true;
	});

	//첫번째 대화
	townhall_ans_1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//계획 없음 선택 시
		townhall_talk1->hide();
		townhall_ans_1_1->hide();
		townhall_ans_1_2->hide();
		bestlove = bestlove + 100; //친밀도 100 증가
		townhall_talk1_1->show();
		townhall_talk1_close->show();
		return true;
	});
	townhall_ans_1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //마을 둘러보기 선택 시
		townhall_talk1->hide();
		townhall_ans_1_1->hide();
		townhall_ans_1_2->hide();
		best_happy->hide();
		bestlove = bestlove + 40; //친밀도 40증가
		best->show(); //최고냥 표정 변화
		townhall_talk1_2->show();
		townhall_talk1_close->show();
		return true;
	});
	townhall_talk1_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화1 닫기
		townhall_talk1_1->hide();
		townhall_talk1_2->hide();
		townhall_talk1_close->hide();
		best_happy->hide();
		best->hide();
		cheese_townhall->hide();
		cat_townhall->show();
		townhall_to_town->show();
		return true;
	});

	//두번째 대화
	townhall_ans_2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물하기
		townhall_ans_2_1->hide();
		townhall_ans_2_2->hide();
		townhall_present->show(); //진짜?
		townhall_present_yes->show(); //네
		townhall_present_no->show(); //아니오
		return true;
	});
	townhall_ans_2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닫기
		cat_townhall->show();
		townhall_to_town->show();
		cheese_townhall->hide();
		best_sad->hide();
		townhall_talk2->hide();
		townhall_ans_2_1->hide();
		townhall_ans_2_2->hide();
		return true;
	});
	townhall_present_yes->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_네
		townhall_present->hide();
		townhall_present_yes->hide();
		townhall_present_no->hide();

		if (money < 400) { //캣닢 부족
			townhall_nomoney->show();
		}

		else {
			townhall_what_present->show(); //무슨 선물?
			townhall_present_1->show();//캣닢차
			townhall_present_2->show();//생선포
		}

		return true;
	});
	townhall_present_no->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_아니오
		townhall_present->hide();
		townhall_present_yes->hide();
		townhall_present_no->hide();
		townhall_ans_2_1->show();
		townhall_ans_2_2->show();
		return true;
	});
	townhall_nomoney->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢부족? > ok > 창 다 닫기
		townhall_nomoney->hide();
		best_sad->hide();
		cheese_townhall->hide();
		townhall_talk2->hide();
		cat_townhall->show();
		townhall_to_town->show();
		return true;
	});
	townhall_present_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢차 선물
		townhall_what_present->hide();
		townhall_present_1->hide();
		townhall_present_2->hide();
		best_sad->hide();
		townhall_talk2->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, townhall); //보유 캣닢 갱신
		bestlove = bestlove + 100; //친밀도 100증가
		best_happy->show(); //최고냥 표정 바뀜
		townhall_talk2_1->show();
		townhall_talk2_close->show();
		return true;
	});
	townhall_present_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //생선포 선물
		townhall_what_present->hide();
		townhall_present_1->hide();
		townhall_present_2->hide();
		best_sad->hide();
		townhall_talk2->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, townhall); //보유 캣닢 갱신
		bestlove = bestlove + 40; //친밀도 40증가
		best->show(); //최고냥 표정 바뀜
		townhall_talk2_2->show();
		townhall_talk2_close->show();
		return true;
	});
	townhall_talk2_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화2 닫기
		best_happy->hide();
		best->hide();
		cheese_townhall->hide();
		townhall_talk2_1->hide();
		townhall_talk2_2->hide();
		townhall_talk2_close->hide();
		cat_townhall->show();
		townhall_to_town->show();
		return true;
	});

	//세번째 대화
	townhall_talk3_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//대화3 닫기
		best_happy->hide();
		cheese_townhall->hide();
		townhall_talk3_close->hide();
		townhall_heart->hide();
		townhall_talk3->hide();
		cat_townhall->show();
		townhall_to_town->show();
		gotoend();
		return true;
	});

	//뒤로가기
	townhall_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
	});


	//캣닢밭

	auto cat_field = Object::create("Images/고양이/앉은나비.png", field, 730, 60); //배경에 앉아있는 고양이
	auto cheese_field = Object::create("Images/고양이/치즈.png", field, 920, 179); cheese_field->hide(); //치즈
	auto nabi = Object::create("Images/고양이/나비.png", field, 40, 170); nabi->hide(); //나비
	auto nabi_happy = Object::create("Images/고양이/나비_웃음.png", field, 40, 170); nabi_happy->hide(); //나비 웃음

	auto field_talk1 = Object::create("Images/대사/나비1.png", field, 28, 20); field_talk1->hide(); //나비 대사1
	auto field_ans_1_1 = Object::create("Images/선택지/선물하기.png", field, 1000, 100); field_ans_1_1->hide(); //선물하기
	auto field_ans_1_2 = Object::create("Images/선택지/닫기.png", field, 1000, 50); field_ans_1_2->hide(); //닫기
	auto field_present = Object::create("Images/알림창/선물.png", field, 345, 350); field_present->hide(); //선물할까요?
	auto field_nomoney = Object::create("Images/알림창/캣닢부족.png", field, 450, 330); field_nomoney->hide(); //캣닢 부족
	auto field_present_yes = Object::create("Images/알림창/선물네.png", field, 654, 270); field_present_yes->hide(); //네
	auto field_present_no = Object::create("Images/알림창/선물아니오.png", field, 345, 270); field_present_no->hide(); //아니오
	auto field_what_present = Object::create("Images/알림창/선물_나비.png", field, 345, 200); field_what_present->hide(); //무슨 선물?
	auto field_present_1 = Object::create("Images/선물/참치캔.png", field, 420, 300); field_present_1->hide(); //참치캔
	auto field_present_2 = Object::create("Images/선물/츄르.png", field, 720, 300); field_present_2->hide(); //츄르
	auto field_talk1_1 = Object::create("Images/대사/나비_참치캔.png", field, 28, 20); field_talk1_1->hide(); //참치캔 선택 시 답변
	auto field_talk1_2 = Object::create("Images/대사/나비_츄르.png", field, 28, 20); field_talk1_2->hide(); //츄르 선택 시 답변
	auto field_talk1_close = Object::create("Images/선택지/닫기.png", field, 1080, 50); field_talk1_close->hide(); //창 닫기

	auto field_talk2 = Object::create("Images/대사/나비2.png", field, 28, 20); field_talk2->hide(); //나비 대사2
	auto field_ans_2_1 = Object::create("Images/선택지/좋아.png", field, 1080, 100); field_ans_2_1->hide(); //좋아
	auto field_ans_2_2 = Object::create("Images/선택지/안돼.png", field, 1080, 50);	field_ans_2_2->hide();  //안돼
	auto field_talk2_1 = Object::create("Images/대사/나비_좋아.png", field, 28, 20); field_talk2_1->hide(); //좋아 선택 시 답변
	auto field_talk2_2 = Object::create("Images/대사/나비_안돼.png", field, 28, 20); field_talk2_2->hide(); //안돼 선택 시 답변
	auto field_talk2_close = Object::create("Images/선택지/닫기.png", field, 1080, 50); field_talk2_close->hide();//창 닫기

	auto field_talk3 = Object::create("Images/대사/나비3.png", field, 28, 20); field_talk3->hide(); //나비 대사3
	auto field_heart = Object::create("Images/기타/하트.png", field, 1186, 148); field_heart->hide(); //친밀도 최고 시 표시됨
	auto field_talk3_close = Object::create("Images/선택지/닫기.png", field, 1080, 50); field_talk3_close->hide(); //창 닫기
	auto field_to_town = Object::create("Images/기타/backbutton.png", field, 5, 650); //뒤로가기

	cat_field->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //배경에 있는 고양이를 누르면 대화 시작
		cat_field->hide();
		cheese_field->show();
		field_to_town->hide();

		if (nabilove < 100) { //친밀도 1단계
			nabi->show();
			field_talk1->show();
			field_ans_1_1->show();
			field_ans_1_2->show();
		}

		else if (nabilove > 99 && nabilove < 200) { //친밀도 2단계
			nabi->show();
			field_talk2->show();
			field_ans_2_1->show();
			field_ans_2_2->show();
		}

		else if (nabilove > 199) { //친밀도 3단계
			nabi_happy->show();
			field_talk3->show();
			field_heart->show();
			field_talk3_close->show();
		}

		return true;
		});

	//첫번째 대화
	field_ans_1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//선물하기
		field_ans_1_1->hide();
		field_ans_1_2->hide();
		field_present->show(); //진짜?
		field_present_yes->show(); //네
		field_present_no->show(); //아니오
		return true;
		});
	field_ans_1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닫기
		cat_field->show();
		field_to_town->show();
		cheese_field->hide();
		nabi->hide();
		field_talk1->hide();
		field_ans_1_1->hide();
		field_ans_1_2->hide();
		return true;
		});
	field_present_yes->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_네
		field_present->hide();
		field_present_yes->hide();
		field_present_no->hide();

		if (money < 400) { //캣닢 부족
			field_nomoney->show();
		}

		else {
			field_what_present->show(); //무슨 선물?
			field_present_1->show();//참치캔
			field_present_2->show();//츄르
		}

		return true;
		});
	field_present_no->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_아니오
		field_present->hide();
		field_present_yes->hide();
		field_present_no->hide();
		field_ans_1_1->show();
		field_ans_1_2->show();
		return true;
		});
	field_nomoney->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢부족? > ok > 창 다 닫기
		field_nomoney->hide();
		nabi->hide();
		cheese_field->hide();
		field_talk1->hide();
		cat_field->show();
		field_to_town->show();
		return true;
		});
	field_present_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //참치캔 선물
		field_what_present->hide();
		field_present_1->hide();
		field_present_2->hide();
		field_talk1->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, field); //보유 캣닢 갱신
		nabilove = nabilove + 40; //친밀도 40증가
		field_talk1_1->show();
		field_talk1_close->show();
		return true;
		});
	field_present_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //츄르 선물
		field_what_present->hide();
		field_present_1->hide();
		field_present_2->hide();
		nabi->hide();
		field_talk1->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, field); //보유 캣닢 갱신
		nabilove = nabilove + 100; //친밀도 100증가
		nabi_happy->show(); //나비 표정 바뀜
		field_talk1_2->show();
		field_talk1_close->show();
		return true;
		});
	field_talk1_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화1 닫기
		field_talk1_1->hide();
		field_talk1_2->hide();
		field_talk1_close->hide();
		nabi_happy->hide();
		nabi->hide();
		cheese_field->hide();
		cat_field->show();
		field_to_town->show();
		return true;
		});

	//두번째 대화
	field_ans_2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //좋아 선택
		field_talk2->hide();
		field_ans_2_1->hide();
		field_ans_2_2->hide();
		nabilove = nabilove + 40; //친밀도 40증가
		field_talk2_1->show();
		field_talk2_close->show();
		return true;
		});
	field_ans_2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //안돼 선택
		field_talk2->hide();
		field_ans_2_1->hide();
		field_ans_2_2->hide();
		nabi->hide();
		nabilove = nabilove + 100; //친밀도 100증가
		nabi_happy->show();//나비 표정 바뀜
		field_talk2_2->show();
		field_talk2_close->show();
		return true;
		});
	field_talk2_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화2 닫기
		nabi_happy->hide();
		nabi->hide();
		cheese_field->hide();
		field_talk2_1->hide();
		field_talk2_2->hide();
		field_talk2_close->hide();
		cat_field->show();
		field_to_town->show();
		return true;
		});

	//세번째 대화
	field_talk3_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//대화3 닫기
		nabi_happy->hide();
		cheese_field->hide();
		field_talk3_close->hide();
		field_heart->hide();
		field_talk3->hide();
		cat_field->show();
		field_to_town->show();
		gotoend();
		return true;
		});

	//뒤로가기
	field_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
	});


	//공원 게임
	auto cat_park = Object::create("Images/고양이/앉은까망.png", park, 750, 270); //배경에 앉아있는 고양이
	auto trash = Object::create("Images/기타/쓰레기더미.png", park, 100, 50); //쓰레기 더미
	
	ObjectPtr items[50];
	char trash_leaf[50]; //기본 전부 쓰레기 (0은 쓰레기, 1은 잎)
	bool rightkey = false; //올바른 키를 눌렀을 때만 게임 진행 가능

	trash->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //쓰레기더미 클릭하면 게임 시작
		trashgame->enter();
		bgmusic->stop();
		gamemusic->play(true);
		return true;
	});

	auto foot = Object::create("Images/기타/발.png", trashgame, 980, 290);
	auto trash_notice = Object::create("Images/알림창/분류안내.png", trashgame, 0, 0);
	auto trash_start = Object::create("Images/알림창/게임시작.png", trashgame, 205, 60);
	auto trash_back = Object::create("Images/알림창/뒤로가기.png", trashgame, 665, 60);

	trash_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //게임시작 버튼
		trash_notice->hide();
		trash_start->hide();
		trash_back->hide(); //각종 안내창을 숨긴다
		rightkey = true;

		//게임 설정
		int rn;
		int temp;
		int leaves = rand() % 11 + 20; //잎 개수는 50개 중 20~30개 사이로 랜덤 생성

		for (int i = 0; i < 50; i++) {
			trash_leaf[i] = 0; //배열 초기화
		}

		for (int i = 0; i < leaves; i++) { //랜덤 개수로 생긴 잎을 넣어준다.
			trash_leaf[i] = 1;
		}

		for (int i = 0; i < 49; i++) { //순서 섞기
			rn = rand() % (50 - i) + i;
			temp = trash_leaf[i];
			trash_leaf[i] = trash_leaf[rn];
			trash_leaf[rn] = temp;
		}

		for (int i = 0; i < 50; i++) { //trash_leaf 배열에 따라 순서대로 쓰레기와 잎 이미지 생성
			if (trash_leaf[i] == 0) {
				items[i] = Object::create("Images/기타/쓰레기.png", trashgame, 800 - i * 150, 300);
			}
			else {
				items[i] = Object::create("Images/기타/잎.png", trashgame, 800 - i * 150, 300);
			}
		}

		return true;

	});

	trash_back->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //뒤로가기
		park->enter();
		gamemusic->stop();
		bgmusic->play(true);
		printmoney(money, park);
		return true;
	});

	auto trash_success = Object::create("Images/알림창/미니게임성공.png", trashgame, 350, 280); trash_success->hide(); //성공 시 보여줄 알림창
	auto trash_black = Object::create("Images/기타/쓰레기더미_비활성.png", park, 100, 50); trash_black->hide(); //쓰레기더미 검게 보임
	auto minigame_notice_trash = Object::create("Images/알림창/미니게임쿨타임.png", park, 220, 290); minigame_notice_trash->hide();  //쿨타임 알림창
	auto trashgame_again = Timer::create(60.f); //미니게임 쿨타임 60초

	auto footup = Object::create("Images/기타/발위.png", trashgame, 1020, 306);	footup->hide();
	auto footdown = Object::create("Images/기타/발아래.png", trashgame, 1020, 234);	footdown->hide();

	auto stamp1 = Object::create("Images/기타/튜토리얼.png", trashgame, 25, 645); stamp1->hide(); //분류 10개마다 보여줄 발바닥
	auto stamp2 = Object::create("Images/기타/튜토리얼.png", trashgame, 85, 645); stamp2->hide();
	auto stamp3 = Object::create("Images/기타/튜토리얼.png", trashgame, 145, 645); stamp3->hide();
	auto stamp4 = Object::create("Images/기타/튜토리얼.png", trashgame, 205, 645); stamp4->hide();
	auto stamp5 = Object::create("Images/기타/튜토리얼.png", trashgame, 265, 645); stamp5->hide();

	int whatkey = 0;
	auto keytimer = Timer::create(0.001f);
	auto delay = Timer::create(3.f); //틀렸을 때 지연되도록 함.
	auto wrong = Object::create("Images/기타/wrong.png", trashgame, 980, 320); wrong->hide(); //잘못 눌렀을 때 X표시

	trashgame->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool { //키보드 방향키 누르기

		if (rightkey) { //키 잘 눌렀을 때만 계속 진행 가능
			if (key == KeyCode::KEY_UP_ARROW) {
				whatkey = 84;
			}
			else if (key == KeyCode::KEY_DOWN_ARROW) {
				whatkey = 85;
			}
			else { //방향키 위, 아래로만 조작 가능
				whatkey = 0;
			}

			if (pressed) keytimer->start();
			if (!pressed) keytimer->stop();
		}

		return true;
		});

	delay->setOnTimerCallback([&](auto)->bool { //딜레이 끝날 때 해야할 것들
		rightkey = true; //다시 키 누를 수 있도록
		wrong->hide(); //X 표시 없애기
		delay->set(3.f); //타이머 리셋
		return true;
		});

	int now = 0; //지금 분류해야 할 것이 무엇인가
	int itemcount = 0; //아이템 몇 개를 분류했는가

	keytimer->setOnTimerCallback([&](auto)->bool { //방향키 눌렀을 때 동작할 것들

		if (whatkey == 84) { //방향키 위 (잎이 가야할 곳)
			if (trash_leaf[now] == 1) { //잘 눌렀을 때
				foot->hide();
				footdown->hide();
				footup->show();

				items[now]->hide(); //잘 분류된 아이템 숨기기
				itemcount++; //아이템 분류 누적 +1개
				now++; //다음 아이템으로 넘어간다

				for (int i = now; i < 50; i++) {
					items[i]->locate(trashgame, 800 - (i - now) * 150, 300); //분류할 것들 오른쪽으로 밀어줌
				}
			}
			else if (trash_leaf[now] == 0) { //잘못 눌렀을 때
				delay->start(); //딜레이 시작
				rightkey = false; //키 잘못 눌렀음
				wrong->show(); //X표시
			}
		}

		else if (whatkey == 85) {//방향키 아래 (쓰레기가 가야할 곳)
			if (trash_leaf[now] == 0) { //잘 눌렀을 때
				foot->hide();
				footup->hide();
				footdown->show();

				items[now]->hide(); //잘 분류된 아이템 숨기기
				itemcount++; //아이템 분류 누적 +1개
				now++; //다음 아이템으로 넘어간다

				for (int i = now; i < 50; i++) {
					items[i]->locate(trashgame, 800 - (i - now) * 150, 300); //분류할 것들 오른쪽으로 밀어줌
				}
			}
			else if (trash_leaf[now] == 1) { //잘못 눌렀을 때
				delay->start(); //딜레이 시작
				rightkey = false; //키 잘못 눌렀음
				wrong->show(); //X표시
			}
		}

		if (itemcount == 10) stamp1->show(); //분류 10개마다 발바닥 하나씩 표시
		else if (itemcount == 20) stamp2->show();
		else if (itemcount == 30) stamp3->show();
		else if (itemcount == 40) stamp4->show();
		else if (itemcount == 50) { //모든 아이템 분류 완료 시(게임이 끝났을 때)
			stamp5->show();
			trash_success->show();
		}

		keytimer->set(0.001f);//방향키 다시 눌러도 동잘할 수 있도록

		return true;
		});

	trash_success->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //성공 알림창 클릭 시
		itemcount = 0; //아이템 분류 개수 초기화
		now = 0; //분류할 아이템 상태 초기화
		trash_success->hide(); //알림창 숨기기
		stamp1->hide();
		stamp2->hide();
		stamp3->hide();
		stamp4->hide();
		stamp5->hide();
		foot->show();
		footup->hide();
		footdown->hide();
		trash_notice->show(); //게임 시작 전 보이던 알림창 다시 보이도록
		trash_start->show();
		trash_back->show();
		rightkey = false;
		money = money + 400; //보유 캣닢 증가

		park->enter(); //공원으로 돌아가기
		gamemusic->stop();
		bgmusic->play(true);
		trash_black->show(); //쥐구멍 아이콘을 어둡게 보이도록함
		trashgame_again->start(); //미니게임 쿨타임 시작
		printmoney(money, park);

		return true;
		});

	minigame_notice_trash->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //알림창은 클릭하면 사라짐
		minigame_notice_trash->hide();
		return true;
		});

	trash_black->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //쿨타임 상태에서 누르면 알림창 뜸
		minigame_notice_trash->show();
		return true;
		});

	trashgame_again->setOnTimerCallback([&](auto)->bool { //쿨타임
		trash_black->hide(); //60초 지나면 쿨타임 해제
		trashgame_again->set(60.f); //쿨타임 리셋
		return true;
		});


	//공원
	
	auto cheese_park = Object::create("Images/고양이/치즈.png", park, 920, 179); cheese_park->hide(); //치즈
	auto black = Object::create("Images/고양이/까망.png", park, 40, 170); black->hide(); //까망
	auto black_sleep = Object::create("Images/고양이/까망_졸림.png", park, 40, 170); black_sleep->hide(); //까망 졸림
	auto black_happy = Object::create("Images/고양이/까망_웃음.png", park, 40, 170); black_happy->hide(); //까망 웃음

	auto park_talk1 = Object::create("Images/대사/까망1.png", park, 28, 20); park_talk1->hide(); //까망 대사1
	auto park_ans_1_1 = Object::create("Images/선택지/창가.png", park, 1000, 100); park_ans_1_1->hide(); //따뜻한 창가
	auto park_ans_1_2 = Object::create("Images/선택지/상자.png", park, 1000, 50); park_ans_1_2->hide(); //안락한 상자
	auto park_talk1_1 = Object::create("Images/대사/까망_창가.png", park, 28, 20); park_talk1_1->hide(); //창가 시 답변
	auto park_talk1_2 = Object::create("Images/대사/까망_상자.png", park, 28, 20); park_talk1_2->hide(); //상자 시 답변
	auto park_talk1_close = Object::create("Images/선택지/닫기.png", park, 1080, 50); park_talk1_close->hide(); //창 닫기

	auto park_talk2 = Object::create("Images/대사/까망2.png", park, 28, 20); park_talk2->hide(); //까망 대사2
	auto park_ans_2_1 = Object::create("Images/선택지/선물하기.png", park, 1080, 100); park_ans_2_1->hide(); //선물하기
	auto park_ans_2_2 = Object::create("Images/선택지/닫기.png", park, 1080, 50); park_ans_2_2->hide(); //닫기
	auto park_present = Object::create("Images/알림창/선물.png", park, 345, 350); park_present->hide(); //선물할까요?
	auto park_nomoney = Object::create("Images/알림창/캣닢부족.png", park, 450, 330); park_nomoney->hide(); //캣닢 부족
	auto park_present_yes = Object::create("Images/알림창/선물네.png", park, 654, 270); park_present_yes->hide(); //네
	auto park_present_no = Object::create("Images/알림창/선물아니오.png", park, 345, 270); park_present_no->hide(); //아니오
	auto park_what_present = Object::create("Images/알림창/선물_까망.png", park, 345, 200); park_what_present->hide(); //무슨 선물?
	auto park_present_1 = Object::create("Images/선물/붕어빵인형.png", park, 420, 300); park_present_1->hide(); //붕어빵 인형
	auto park_present_2 = Object::create("Images/선물/실뭉치.png", park, 720, 300); park_present_2->hide(); //실뭉치
	auto park_talk2_1 = Object::create("Images/대사/까망_붕어빵.png", park, 28, 20); park_talk2_1->hide(); //붕어빵 인형 선택 시 답변
	auto park_talk2_2 = Object::create("Images/대사/까망_실뭉치.png", park, 28, 20); park_talk2_2->hide(); //실뭉치 선택 시 답변
	auto park_talk2_close = Object::create("Images/선택지/닫기.png", park, 1080, 50); park_talk2_close->hide(); //창 닫기

	auto park_talk3 = Object::create("Images/대사/까망3.png", park, 28, 20); park_talk3->hide(); //까망 대사3
	auto park_heart = Object::create("Images/기타/하트.png", park, 1186, 148); park_heart->hide(); //친밀도 최고 시 표시됨
	auto park_talk3_close = Object::create("Images/선택지/닫기.png", park, 1080, 50); park_talk3_close->hide(); //창 닫기

	auto park_to_town = Object::create("Images/기타/backbutton.png", park, 5, 650); //뒤로가기

	cat_park->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //배경에 있는 고양이를 누르면 대화 시작
		cat_park->hide();
		cheese_park->show();
		park_to_town->hide();

		if (blacklove < 100) { //친밀도 1단계
			black_sleep->show();
			park_talk1->show();
			park_ans_1_1->show();
			park_ans_1_2->show();
		}

		else if (blacklove > 99 && blacklove < 200) { //친밀도 2단계
			black->show();
			park_talk2->show();
			park_ans_2_1->show();
			park_ans_2_2->show();
		}

		else if (blacklove > 199) { //친밀도 3단계
			black_happy->show();
			park_talk3->show();
			park_heart->show();
			park_talk3_close->show();
		}

		return true;
	});

	//첫번째 대화
	park_ans_1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//창가 선택 시
		park_talk1->hide();
		park_ans_1_1->hide();
		park_ans_1_2->hide();
		blacklove = blacklove + 100; //친밀도 100 증가
		park_talk1_1->show();
		park_talk1_close->show();
		return true;
	});
	park_ans_1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //상자 선택 시
		park_talk1->hide();
		park_ans_1_1->hide();
		park_ans_1_2->hide();
		black_sleep->hide();
		blacklove = blacklove + 40; //친밀도 40증가
		black->show(); //까망 표정 변화
		park_talk1_2->show();
		park_talk1_close->show();
		return true;
	});
	park_talk1_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화1 닫기
		park_talk1_1->hide();
		park_talk1_2->hide();
		park_talk1_close->hide();
		black_sleep->hide();
		black->hide();
		cheese_park->hide();
		cat_park->show();
		park_to_town->show();
		return true;
	});

	//두번째 대화
	park_ans_2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물하기
		park_ans_2_1->hide();
		park_ans_2_2->hide();
		park_present->show(); //진짜?
		park_present_yes->show(); //네
		park_present_no->show(); //아니오
		return true;
	});
	park_ans_2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닫기
		cat_park->show();
		park_to_town->show();
		cheese_park->hide();
		black->hide();
		park_talk2->hide();
		park_ans_2_1->hide();
		park_ans_2_2->hide();
		return true;
	});
	park_present_yes->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_네
		park_present->hide();
		park_present_yes->hide();
		park_present_no->hide();

		if (money < 400) { //캣닢 부족
			park_nomoney->show();
		}

		else {
			park_what_present->show(); //무슨 선물?
			park_present_1->show();//붕어빵인형
			park_present_2->show();//실뭉치
		}

		return true;
	});
	park_present_no->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_아니오
		park_present->hide();
		park_present_yes->hide();
		park_present_no->hide();
		park_ans_2_1->show();
		park_ans_2_2->show();
		return true;
	});
	park_nomoney->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢부족? > ok > 창 다 닫기
		park_nomoney->hide();
		black->hide();
		cheese_park->hide();
		park_talk2->hide();
		cat_park->show();
		park_to_town->show();
		return true;
	});
	park_present_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //붕어빵인형 선물
		park_what_present->hide();
		park_present_1->hide();
		park_present_2->hide();
		park_talk2->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, park); //보유 캣닢 갱신
		blacklove = blacklove + 40; //친밀도 40증가
		park_talk2_1->show();
		park_talk2_close->show();
		return true;
	});
	park_present_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //실뭉치 선물
		park_what_present->hide();
		park_present_1->hide();
		park_present_2->hide();
		black->hide();
		park_talk2->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, park); //보유 캣닢 갱신
		blacklove = blacklove + 100; //친밀도 100증가
		black_happy->show(); //까망 표정 바뀜
		park_talk2_2->show();
		park_talk2_close->show();
		return true;
	});
	park_talk2_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화2 닫기
		black_happy->hide();
		black->hide();
		cheese_park->hide();
		park_talk2_1->hide();
		park_talk2_2->hide();
		park_talk2_close->hide();
		cat_park->show();
		park_to_town->show();
		return true;
	});

	//세번째 대화
	park_talk3_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//대화3 닫기
		black_happy->hide();
		cheese_park->hide();
		park_talk3_close->hide();
		park_heart->hide();
		park_talk3->hide();
		cat_park->show();
		park_to_town->show();
		gotoend();
		return true;
	});

	//뒤로가기
	park_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
	});


	//이웃집

	auto cat_neigh = Object::create("Images/고양이/앉은먼지.png", neigh, 190, 380); //배경에 앉아있는 고양이
	auto cheese_neigh = Object::create("Images/고양이/치즈.png", neigh, 920, 179); cheese_neigh->hide(); //치즈
	auto dust = Object::create("Images/고양이/먼지.png", neigh, 40, 170); dust->hide(); //먼지
	auto dust_worry = Object::create("Images/고양이/먼지_고민.png", neigh, 40, 170); dust_worry->hide(); //먼지 고민
	auto dust_happy = Object::create("Images/고양이/먼지_웃음.png", neigh, 40, 170); dust_happy->hide(); //먼지 웃음
	
	auto neigh_talk1 = Object::create("Images/대사/먼지1.png", neigh, 28, 20); neigh_talk1->hide(); //먼지 대사1
	auto neigh_ans_1_1 = Object::create("Images/선택지/쥐돌이.png", neigh, 1000, 50); neigh_ans_1_1->hide(); //쥐돌이 인형
	auto neigh_ans_1_2 = Object::create("Images/선택지/깃털.png", neigh, 1000, 100); neigh_ans_1_2->hide(); //깃털 장난감
	auto neigh_talk1_1 = Object::create("Images/대사/먼지_쥐돌이.png", neigh, 28, 20); neigh_talk1_1->hide(); //쥐돌이 시 답변
	auto neigh_talk1_2 = Object::create("Images/대사/먼지_깃털.png", neigh, 28, 20); neigh_talk1_2->hide(); //깃털 시 답변
	auto neigh_talk1_close = Object::create("Images/선택지/닫기.png", neigh, 1080, 50); neigh_talk1_close->hide(); //창 닫기
	
	auto neigh_talk2 = Object::create("Images/대사/먼지2.png", neigh, 28, 20); neigh_talk2->hide(); //먼지 대사2
	auto neigh_ans_2_1 = Object::create("Images/선택지/선물하기.png", neigh, 1080, 100); neigh_ans_2_1->hide(); //선물하기
	auto neigh_ans_2_2 = Object::create("Images/선택지/닫기.png", neigh, 1080, 50); neigh_ans_2_2->hide(); //닫기
	auto neigh_present = Object::create("Images/알림창/선물.png", neigh, 345, 350); neigh_present->hide(); //선물할까요?
	auto neigh_nomoney = Object::create("Images/알림창/캣닢부족.png", neigh, 450, 330); neigh_nomoney->hide(); //캣닢 부족
	auto neigh_present_yes = Object::create("Images/알림창/선물네.png", neigh, 654, 270); neigh_present_yes->hide(); //네
	auto neigh_present_no = Object::create("Images/알림창/선물아니오.png", neigh, 345, 270); neigh_present_no->hide(); //아니오
	auto neigh_what_present = Object::create("Images/알림창/선물_먼지.png", neigh, 345, 200); neigh_what_present->hide(); //무슨 선물?
	auto neigh_present_1 = Object::create("Images/선물/닭가슴살.png", neigh, 420, 300); neigh_present_1->hide(); //닭가슴살
	auto neigh_present_2 = Object::create("Images/선물/싱싱생선.png", neigh, 720, 300); neigh_present_2->hide(); //생선
	auto neigh_talk2_1 = Object::create("Images/대사/먼지_닭가슴살.png", neigh, 28, 20); neigh_talk2_1->hide(); //닭가슴살 선택 시 답변
	auto neigh_talk2_2 = Object::create("Images/대사/먼지_생선.png", neigh, 28, 20); neigh_talk2_2->hide(); //생선 선택 시 답변
	auto neigh_talk2_close = Object::create("Images/선택지/닫기.png", neigh, 1080, 50); neigh_talk2_close->hide(); //창 닫기
	
	auto neigh_talk3 = Object::create("Images/대사/먼지3.png", neigh, 28, 20); neigh_talk3->hide(); //먼지 대사3
	auto neigh_heart = Object::create("Images/기타/하트.png", neigh, 1186, 148); neigh_heart->hide(); //친밀도 최고 시 표시됨
	auto neigh_talk3_close = Object::create("Images/선택지/닫기.png", neigh, 1080, 50); neigh_talk3_close->hide(); //창 닫기

	auto neigh_to_town = Object::create("Images/기타/backbutton.png", neigh, 5, 650); //뒤로가기

	cat_neigh->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //배경에 있는 고양이를 누르면 대화 시작
		cat_neigh->hide();
		cheese_neigh->show();
		neigh_to_town->hide();

		if (dustlove < 100) { //친밀도 1단계
			dust_worry->show();
			neigh_talk1->show();
			neigh_ans_1_1->show();
			neigh_ans_1_2->show();
		}

		else if (dustlove > 99 && dustlove < 200) { //친밀도 2단계
			dust->show();
			neigh_talk2->show();
			neigh_ans_2_1->show();
			neigh_ans_2_2->show();
		}

		else if (dustlove > 199) { //친밀도 3단계
			dust_happy->show();
			neigh_talk3->show();
			neigh_heart->show();
			neigh_talk3_close->show();
		}

		return true;
	});

	//첫번째 대화
	neigh_ans_1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//쥐돌이 선택 시
		neigh_talk1->hide();
		neigh_ans_1_1->hide();
		neigh_ans_1_2->hide();
		dust_worry->hide();
		dustlove = dustlove + 100; //친밀도 100 증가
		dust_happy->show(); //먼지 표정 변화
		neigh_talk1_1->show();
		neigh_talk1_close->show();
		return true;
	});
	neigh_ans_1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //깃털 선택 시
		neigh_talk1->hide();
		neigh_ans_1_1->hide();
		neigh_ans_1_2->hide();
		dust_worry->hide();
		dustlove = dustlove + 40; //친밀도 40증가
		dust->show(); //먼지 표정 변화
		neigh_talk1_2->show();
		neigh_talk1_close->show();
		return true;
	});
	neigh_talk1_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화1 닫기
		neigh_talk1_1->hide();
		neigh_talk1_2->hide();
		neigh_talk1_close->hide();
		dust_happy->hide();
		dust->hide();
		cheese_neigh->hide();
		cat_neigh->show();
		neigh_to_town->show();
		return true;
	});

	//두번째 대화
	neigh_ans_2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물하기
		neigh_ans_2_1->hide();
		neigh_ans_2_2->hide();
		neigh_present->show(); //진짜?
		neigh_present_yes->show(); //네
		neigh_present_no->show(); //아니오
		return true;
	});
	neigh_ans_2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닫기
		cat_neigh->show();
		neigh_to_town->show();
		cheese_neigh->hide();
		dust->hide();
		neigh_talk2->hide();
		neigh_ans_2_1->hide();
		neigh_ans_2_2->hide();
		return true;
	});
	neigh_present_yes->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_네
		neigh_present->hide();
		neigh_present_yes->hide();
		neigh_present_no->hide();

		if (money < 400) { //캣닢 부족
			neigh_nomoney->show();
		}

		else {
			neigh_what_present->show(); //무슨 선물?
			neigh_present_1->show();//닭가슴살
			neigh_present_2->show();//생선
		}

		return true;
	});
	neigh_present_no->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //선물_아니오
		neigh_present->hide();
		neigh_present_yes->hide();
		neigh_present_no->hide();
		neigh_ans_2_1->show();
		neigh_ans_2_2->show();
		return true;
	});
	neigh_nomoney->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //캣닢부족? > ok > 창 다 닫기
		neigh_nomoney->hide();
		dust->hide();
		cheese_neigh->hide();
		neigh_talk2->hide();
		cat_neigh->show();
		neigh_to_town->show();
		return true;
	});
	neigh_present_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //닭가슴살 선물
		neigh_what_present->hide();
		neigh_present_1->hide();
		neigh_present_2->hide();
		neigh_talk2->hide();
		dust->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, neigh); //보유 캣닢 갱신
		dustlove = dustlove + 100; //친밀도 100증가
		dust_happy->show(); //먼지 표정 바뀜
		neigh_talk2_1->show();
		neigh_talk2_close->show();
		return true;
	});
	neigh_present_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //싱싱생선 선물
		neigh_what_present->hide();
		neigh_present_1->hide();
		neigh_present_2->hide();
		neigh_talk2->hide();
		money = money - 400; //캣닢 소모
		printmoney(money, neigh); //보유 캣닢 갱신
		dustlove = dustlove + 40; //친밀도 40증가
		neigh_talk2_2->show();
		neigh_talk2_close->show();
		return true;
	});
	neigh_talk2_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //대화2 닫기
		dust_happy->hide();
		dust->hide();
		cheese_neigh->hide();
		neigh_talk2_1->hide();
		neigh_talk2_2->hide();
		neigh_talk2_close->hide();
		cat_neigh->show();
		neigh_to_town->show();
		return true;
	});

	//세번째 대화
	neigh_talk3_close->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {//대화3 닫기
		dust_happy->hide();
		cheese_neigh->hide();
		neigh_talk3_close->hide();
		neigh_heart->hide();
		neigh_talk3->hide();
		cat_neigh->show();
		neigh_to_town->show();
		gotoend();
		return true;
	});

	//뒤로가기
	neigh_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
	});


	//쥐구멍
	mousegame_notice = Object::create("Images/알림창/쥐잡기안내.png", mousehole, 215, 230);
	mousegame_start = Object::create("Images/알림창/게임시작.png", mousehole, 215, 100);
	mousegame_back = Object::create("Images/알림창/뒤로가기.png", mousehole, 650, 100);

	mousegame_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //게임시작 버튼
		mousegame_notice->hide();
		mousegame_start->hide();
		mousegame_back->hide(); //각종 안내창을 숨긴다
		mousegame(); //게임 시작
		return true;
	});

	mousegame_back->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool { //뒤로가기
		town->enter();
		gamemusic->stop();
		bgmusic->play(true);
		printmoney(money, town);
		return true;
	});


	//우리집
	auto pot1 = Object::create("Images/기타/화분.png", home, 117, 30);
	auto pot2 = Object::create("Images/기타/화분.png", home, 505, 30);
	auto pot3 = Object::create("Images/기타/화분.png", home, 899, 30);

	bool pot1_can = true; //캣닢이 수확 가능한 상태인가
	bool pot2_can = true;
	bool pot3_can = true;

	auto leaf1 = Object::create("Images/기타/잎왼.png", home, 80, 350);
	auto leaf2 = Object::create("Images/기타/잎왼.png", home, 80, 450);
	auto leaf3 = Object::create("Images/기타/잎오.png", home, 245, 300);
	auto leaf4 = Object::create("Images/기타/잎오.png", home, 245, 400);
	auto leaf5 = Object::create("Images/기타/잎오.png", home, 245, 500);
	auto leaf6 = Object::create("Images/기타/잎왼.png", home, 470, 350);
	auto leaf7 = Object::create("Images/기타/잎왼.png", home, 470, 450);
	auto leaf8 = Object::create("Images/기타/잎오.png", home, 635, 300);
	auto leaf9 = Object::create("Images/기타/잎오.png", home, 635, 400);
	auto leaf10 = Object::create("Images/기타/잎오.png", home, 635, 500);
	auto leaf11 = Object::create("Images/기타/잎왼.png", home, 865, 350);
	auto leaf12 = Object::create("Images/기타/잎왼.png", home, 865, 450);
	auto leaf13 = Object::create("Images/기타/잎오.png", home, 1025, 300);
	auto leaf14 = Object::create("Images/기타/잎오.png", home, 1025, 400);
	auto leaf15 = Object::create("Images/기타/잎오.png", home, 1025, 500);

	auto growagain1 = Timer::create(30.f); //캣닢 다시 자랄 타이머
	auto growagain2 = Timer::create(30.f);
	auto growagain3 = Timer::create(30.f);

	auto warn99999 = Object::create("Images/알림창/캣닢99999.png", home, 320, 280); //캣닢 최대로 모았을 때 알림창
	warn99999->hide();
	warn99999->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		warn99999->hide(); //알림창은 클릭하면 사라진다.
		return true;
	});

	pot1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (money > 99949) {
			warn99999->show();
		}
		else if (pot1_can) { //화분 클릭 시
			leaf1->hide();
			leaf2->hide();
			leaf3->hide();
			leaf4->hide();
			leaf5->hide(); //수확한 캣닢 숨기기
			growagain1->start(); //캣닢 다시 자랄 타이머 시작
			pot1_can = false; //캣닢 수확 불가능한 상태로 전환
			money = money + 50; //보유 캣닢 증가
			printmoney(money, home); //보유 캣닢 정보 갱신
		}
		return true;
	});
	pot2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (money > 99949) {
			warn99999->show();
		}
		else if (pot2_can) {
			leaf6->hide();
			leaf7->hide();
			leaf8->hide();
			leaf9->hide();
			leaf10->hide();
			growagain2->start();
			pot2_can = false;
			money = money + 50;
			printmoney(money, home);
		}
		return true;
	});
	pot3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (money > 99949) {
			warn99999->show();
		}
		else if (pot3_can) {
			leaf11->hide();
			leaf12->hide();
			leaf13->hide();
			leaf14->hide();
			leaf15->hide();
			growagain3->start();
			pot3_can = false;
			money = money + 50;
			printmoney(money, home);
		}
		return true;
	});

	growagain1->setOnTimerCallback([&](TimerPtr)->bool { //캣닢 타이머 끝나면
		leaf1->show();
		leaf2->show();
		leaf3->show();
		leaf4->show();
		leaf5->show(); //캣닢 다시 보여줌
		pot1_can = true; //캣닢 수확 가능한 상태로 전환
		growagain1->set(30.f); //타이머 리셋
		return true;
	});
	growagain2->setOnTimerCallback([&](TimerPtr)->bool {
		leaf6->show();
		leaf7->show();
		leaf8->show();
		leaf9->show();
		leaf10->show();
		pot2_can = true;
		growagain2->set(30.f);
		return true;
	});
	growagain3->setOnTimerCallback([&](TimerPtr)->bool {
		leaf11->show();
		leaf12->show();
		leaf13->show();
		leaf14->show();
		leaf15->show();
		pot3_can = true;
		growagain3->set(30.f);
		return true;
	});

	auto home_to_town = Object::create("Images/기타/backbutton.png", home, 5, 650); //뒤로가기

	home_to_town->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		town->enter();
		printmoney(money, town);
		return true;
	});

	startGame(mainscene);

	return 0;
}