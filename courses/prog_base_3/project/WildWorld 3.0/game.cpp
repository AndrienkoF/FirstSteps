#include "game.h"

bool gamePlay(){
    sf::RenderWindow window(sf::VideoMode(1366, 768), "WildWorld", sf::Style::Fullscreen);
    menu(window);

	sf::View view;
    view.reset(sf::FloatRect(0, 0, 1200, 600));              //размер "вида" камеры

    ////////////////////////// ШРИФТ /////////////////////////////////////////////////////////////////////////////
    sf::Font font;
    font.loadFromFile("font/Belepotan.ttf");   //файл шрифта

    sf::Text textHealth("", font, 30);
    textHealth.setColor(sf::Color::Black);

    sf::Text text("", font, 20);
    text.setColor(sf::Color::Black);

    sf::Text textInfo("", font, 20);
    textInfo.setColor(sf::Color::Red);

    sf::Text textEnd("", font, 80);
    textEnd.setColor(sf::Color::Red);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Level lvl;  //создали экземпляр класса уровень
    lvl.LoadFromFile("map.tmx");

    ///////////////////////// MUSIC //////////////////////////////////////////////////////////////////////////////
    sf::Music music;                          //создаем объект музыки
    music.openFromFile("music/music.ogg");    //загружаем файл
    music.play();                           //воспроизводим музыку
    ///////////////////////// INFO FON ///////////////////////////////////////////////////////////////////////////
    sf::Image infoFonIm;
	infoFonIm.loadFromFile("images/infoFon2.png");
	sf::Texture infoFonT;
	infoFonT.loadFromImage(infoFonIm);
	sf::Sprite infoFonSp;
	infoFonSp.setTexture(infoFonT);
	infoFonSp.setTextureRect(sf::IntRect(0, 0, 1152, 598));
	infoFonSp.setScale(0.9f, 0.8f);
	//////////////////////// MARKET FON ///////////////////////////////////////////////////////////////////////////
    sf::Image marketFonIm;
	marketFonIm.loadFromFile("images/marketList1.png");
	sf::Texture marketFonT;
	marketFonT.loadFromImage(marketFonIm);
	sf::Sprite marketFonSp;
	marketFonSp.setTexture(marketFonT);
	marketFonSp.setTextureRect(sf::IntRect(0, 0, 1154, 729));
	marketFonSp.setScale(0.9f, 0.8f);
	/////////////////////////////// END //////////////////////////////////////////////////////////////////////////
	sf::Image endFonIm;
	endFonIm.loadFromFile("images/potracheno.jpg");
	sf::Texture endFonT;
	endFonT.loadFromImage(endFonIm);
	sf::Sprite endFonSp;
	endFonSp.setTexture(endFonT);
	endFonSp.setTextureRect(sf::IntRect(0, 0, 1366, 768));
	endFonSp.setScale(0.9f, 0.93f);
	/////////////////////////////// VICTORY //////////////////////////////////////////////////////////////////////////
	sf::Image vicFonIm;
	vicFonIm.loadFromFile("images/main.png");
	sf::Texture vicFonT;
	vicFonT.loadFromImage(vicFonIm);
	sf::Sprite vicFonSp;
	vicFonSp.setTexture(vicFonT);
	vicFonSp.setTextureRect(sf::IntRect(0, 0, 1366, 768));
	vicFonSp.setScale(0.9f, 0.93f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Image heroImage;
    heroImage.loadFromFile("images/Hero2.png");

    sf::Image infoImage;
    infoImage.loadFromFile("images/info.png");

    sf::Image hardEnemyIm;
    hardEnemyIm.loadFromFile("images/monkey.png");

    sf::Image marketImage;
    marketImage.loadFromFile("images/market.png");

    sf::Image easyEnemy1Image;
    easyEnemy1Image.loadFromFile("images/Goat.png");

    sf::Image groundImage;
    groundImage.loadFromFile("images/ground.png");

    sf::Image treeImage;
    treeImage.loadFromFile("images/trees.png");

    sf::Image solidImage;
    solidImage.loadFromFile("images/map2.png");

    sf::Image berryImage;
    berryImage.loadFromFile("images/berry.png");

    sf::Image goldImage;
    goldImage.loadFromFile("images/gold.jpg");

    sf::Image metalImage;
    metalImage.loadFromFile("images/metal.jpg");

    std::list<Entity*> entities;       //создаем список
    std::list<Entity*> grounds;
    std::list<Entity*> grass;
    std::list<Entity*> bushes;
    std::list<Entity*> elki;
    std::list<Entity*> solid;
    std::list<Entity*> berry;
    std::list<Entity*> gold;
    std::list<Entity*> metal;
    std::list<Entity*>::iterator it;   //итератор, чтобы проходить по элементам списка
    std::list<Entity*>::iterator it2;

    std::vector<Object> goldList = lvl.GetObjects("gold");
    for (unsigned int i = 0; i < goldList.size(); i++){
        gold.push_back(new Objects(goldImage, "Gold", lvl, goldList[i].rect.left, goldList[i].rect.top, 32, 32));
    }

    std::vector<Object> metalList = lvl.GetObjects("metal");
    for (unsigned int i = 0; i < metalList.size(); i++){
        metal.push_back(new Objects(metalImage, "Metal", lvl, metalList[i].rect.left, metalList[i].rect.top, 32, 32));
    }

    std::vector<Object> berryList = lvl.GetObjects("berry");
    for (unsigned int i = 0; i < berryList.size(); i++){
        berry.push_back(new Objects(berryImage, "Berry", lvl, berryList[i].rect.left, berryList[i].rect.top, 32, 32));
    }

    std::vector<Object> solidList = lvl.GetObjects("solid");
    for (unsigned int i = 0; i < solidList.size(); i++){
        solid.push_back(new Objects(solidImage, "Solid", lvl, solidList[i].rect.left, solidList[i].rect.top, 32, 32));
    }

    std::vector<Object> elkaList = lvl.GetObjects("elka");
    for (unsigned int i = 0; i < elkaList.size(); i++){
        elki.push_back(new Objects(treeImage, "Elka", lvl, elkaList[i].rect.left, elkaList[i].rect.top, 85, 60));
    }

    std::vector<Object> bushList = lvl.GetObjects("bush");
    for (unsigned int i = 0; i < bushList.size(); i++){
        bushes.push_back(new Objects(treeImage, "Bush", lvl, bushList[i].rect.left, bushList[i].rect.top, 48, 40));
    }

    std::vector<Object> grassList = lvl.GetObjects("grass");
    for (unsigned int i = 0; i < grassList.size(); i++){
        grass.push_back(new Objects(groundImage, "Grass", lvl, grassList[i].rect.left, grassList[i].rect.top, 32, 32));
    }

    std::vector<Object> groundList = lvl.GetObjects("ground");
    for (unsigned int i = 0; i < groundList.size(); i++){
        grounds.push_back(new Objects(groundImage, "Ground", lvl, groundList[i].rect.left, groundList[i].rect.top, 32, 32));
    }

    std::vector<Object> easyEnemy1List = lvl.GetObjects("easyEnemy");
    for (unsigned int i = 0; i < easyEnemy1List.size(); i++){
        entities.push_back(new Enemy(easyEnemy1Image, "EasyEnemy1", lvl, easyEnemy1List[i].rect.left, easyEnemy1List[i].rect.top, 46, 45));
    }

    Object info = lvl.GetObject("info");
    Objects myInfo(infoImage, "Info", lvl, info.rect.left, info.rect.top, 96, 96);

    Object hardEnemy = lvl.GetObject("hardEnemy");
    Enemy monkey(hardEnemyIm, "HardEnemy", lvl, hardEnemy.rect.left, hardEnemy.rect.top, 128, 125);

    Object market = lvl.GetObject("market");
    Objects myMarket(marketImage, "Market", lvl, market.rect.left, market.rect.top, 206, 216);

    Object player = lvl.GetObject("player");
    Player hero(heroImage, "Hero", lvl, player.rect.left, player.rect.top, 37, 55);

    float moveTimer = 0;
    int treesScore = 0, groundScore = 0, goatScore = 0, metalScore = 0, goldScore = 0;
    bool showInfo = true;
    bool showMarket = true;
    bool isMove = false;
    bool endGame = true;
    bool buyingMarket = false;

    hero.heroWithPick = false;
    hero.heroWithSword = false;
    hero.normalHero = true;

    sf::Clock clock;    //создаем переменную времени, привязка ко времени(а не загруженности/мощности процессора).
    while (window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();     //перезагружает время
        time = time / 800;   //скорость игры
        moveTimer += time;

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);   //координаты курсором
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);     //переход в игровые координаты

		sf::Event event;
		while (window.pollEvent(event)){
            if ((event.type == sf::Event::Closed))
            window.close();

            if (event.type == sf::Event::KeyPressed){
////////////////////////////////////////////// INFO ////////////////////////////////////////////
                if (event.key.code == sf::Keyboard::I){
                    switch (showInfo){
                        case true: {
                            infoFonSp.setPosition(view.getCenter().x - 520 , view.getCenter().y - 200);
                            showInfo = false;
                            break;
                        }
                        case false:{
                            showInfo = true;
                            break;
                        }
                    }
                }
/////////////////////////////////////////// MARKET //////////////////////////////////////////////
                if (event.key.code == sf::Keyboard::U){
                    if(hero.market == true){
                        switch (showMarket){
                            case true: {
                                marketFonSp.setPosition(view.getCenter().x - 520 , view.getCenter().y - 300);
                                buyingMarket = true;
                                showMarket = false;
                                break;
                            }
                            case false:{
                                showMarket = true;
                                break;
                            }
                        }
                    }
                }
//////////////////////////////////////////////// BUYING IN MARKET ////////////////////////////
                if (buyingMarket = true){
                    if (event.key.code == sf::Keyboard::J){
                            if (goatScore >= 5){
                                hero.health += 50;
                                goatScore -= 5;
                            }
                        }
                    if (event.key.code == sf::Keyboard::H){
                        if ((treesScore >= 5)&&(metalScore >= 2)){
                            hero.heroWithPick = true;
                            hero.normalHero = false;
                            hero.heroWithSword = false;
                            treesScore -= 5;
                            metalScore -= 2;
                        }
                    }
                    if (event.key.code == sf::Keyboard::K){
                        if ((treesScore >= 3)&&(goldScore >= 6)){
                            hero.heroWithPick = false;
                            hero.normalHero = false;
                            hero.heroWithSword = true;
                            goldScore -= 6;
                            treesScore -= 3;
                        }
                    }
                    buyingMarket = false;
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return false;
        }

        myInfo.update(&view, time);
        monkey.update(&view, time);
        myMarket.update(&view, time);
        hero.update(&view, time);
        for (it = metal.begin(); it != metal.end();){
            Entity *m = *it;
            m->update(&view, time);
            if (m->life == false){
                it = metal.erase(it);
                delete m;
            }else{
                it++;
            }
        }
        for (it = gold.begin(); it != gold.end();){
            Entity *go = *it;
            go->update(&view, time);
            if (go->life == false){
                it = gold.erase(it);
                delete go;
            }else{
                it++;
            }
        }
        for (it = berry.begin(); it != berry.end();){
            Entity *b = *it;
            b->update(&view, time);
            if (b->life == false){
                it = berry.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = entities.begin(); it != entities.end();){
            Entity *b = *it;
            b->update(&view, time);
            if (b->life == false){
                it = entities.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = elki.begin(); it != elki.end();){
            Entity *e = *it;
            e->update(&view, time);
            if (e->life == false){
                it = elki.erase(it);
                delete e;
            }else{
                it++;
            }
        }
        for (it = bushes.begin(); it != bushes.end();){
            Entity *b = *it;
            b->update(&view, time);
            if (b->life == false){
                it = bushes.erase(it);
                delete b;
            }else{
                it++;
            }
        }
        for (it = solid.begin(); it != solid.end();){
            Entity *s = *it;
            s->update(&view, time);
            if (s->life == false){
                it = solid.erase(it);
                delete s;
            }else{
                it++;
            }
        }
        for (it = grounds.begin(); it != grounds.end();){
            Entity *g = *it;
            g->update(&view, time);
            if ((g->life == false)){
                it = grounds.erase(it);
                delete g;
            }else{
                it++;
            }
        }
        for (it = grass.begin(); it != grass.end();){
            Entity *gr = *it;
            gr->update(&view, time);
            if (gr->life == false){
                it = grass.erase(it);
                delete gr;
            }else{
                it++;
            }
        }

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// COLISION WITH PLAYER //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
        for (it = elki.begin(); it != elki.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Elka"){
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E))){
                        if((moveTimer>5000)){
                            (*it)->dx = 0;
                            (*it)->health = 0;
                            treesScore++;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }
        for (it = bushes.begin(); it != bushes.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Bush"){
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)&&(moveTimer>5000))){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                        treesScore++;
                        moveTimer = 0;
                    }
                }
            }
        }
        for (it = berry.begin(); it != berry.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "Berry"){
                        (*it)->health = 0;
                        hero.health += 20;
                }
            }
        }
        for (it = gold.begin(); it != gold.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){
                if ((*it)->name == "Gold"){
                        (*it)->health = 0;
                        goldScore++;
                }
            }
        }
        for (it = metal.begin(); it != metal.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){
                if ((*it)->name == "Metal"){
                        (*it)->health = 0;
                        metalScore++;
                }
            }
        }



//////////////////////////////////////////////// CRASHED GROUND //////////////////////////////
        for (unsigned int i = 0; i < hero.obj.size(); i++){
            if(sf::FloatRect(pos.x, pos.y,2,2).intersects(hero.obj[i].rect)){
                if((hero.obj[i].name == "ground")||(hero.obj[i].name == "grass")){
                    if (event.type == sf::Event::MouseButtonPressed){
                        if(event.key.code == sf::Mouse::Left){
                            hero.obj[i].name  = "";
                        }
                    }
                }
            }
        }

        for (it = grass.begin(); it != grass.end(); it++){
            if ((*it)->getRect().intersects(sf::FloatRect(pos.x, pos.y,2,2))){
                if ((*it)->name == "Grass"){
                    if (event.type == sf::Event::MouseButtonPressed){
                        if(event.key.code == sf::Mouse::Left){
                            (*it)->health = 0;
                            groundScore++;
                        }
                    }
                }
            }
        }
        for (it = grounds.begin(); it != grounds.end(); it++){
            if ((*it)->getRect().intersects(sf::FloatRect(pos.x, pos.y,2,2))){   //если объект пересекается с игроком
                if ((*it)->name == "Ground"){
                    if (event.type == sf::Event::MouseButtonPressed){
                        if(event.key.code == sf::Mouse::Left){
                            (*it)->health = 0;
                            groundScore++;
                        }
                    }
                }
            }
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        for (it = entities.begin(); it != entities.end(); it++){
            if ((*it)->getRect().intersects(hero.getRect())){   //если объект пересекается с игроком
                if ((*it)->name == "EasyEnemy1"){
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q))&&(!hero.normalHero)){
                        (*it)->dx = 0;
                        (*it)->health = 0;
                        goatScore++;
                    }else{
                        if(moveTimer>2000){
                            hero.health -= 20;
                            moveTimer = 0;
                        }
                    }
                }
            }
        }

//////////////////////////////////////////////// MONKEY AND HERO ////////////////////////////////////////////////////////////
        if (monkey.getRect().intersects(hero.getRect())){
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q))&&(hero.heroWithSword)){
                monkey.health -= 1;
                monkey.dy = -0.8;
            }else{
                if(moveTimer>2000){
                    hero.health -= 40;
                    moveTimer = 0;
                }
            }
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.setView(view);
		window.clear();
		lvl.Draw(window); //рисуем карту

        //////////////////////////////////////// ТЕКСТ ///////////////////////////////////////////////////////////////

        std::ostringstream treesText;
        treesText << treesScore;
		text.setString("Trees: " + treesText.str());
		text.setPosition(view.getCenter().x - 110, view.getCenter().y - 300);
		window.draw(text);

        std::ostringstream groundText;
		groundText << groundScore;
		text.setString("Ground:" + groundText.str());
		text.setPosition(view.getCenter().x - 310, view.getCenter().y - 300);
		window.draw(text);

        std::ostringstream metalText;
		metalText << metalScore;
		text.setString("Metal:" + metalText.str());
		text.setPosition(view.getCenter().x - 310, view.getCenter().y - 260);
		window.draw(text);

		std::ostringstream goatText;
		goatText << goatScore;
		text.setString("Goat:" + goatText.str());
		text.setPosition(view.getCenter().x - 510, view.getCenter().y - 300);
		window.draw(text);

		std::ostringstream goldText;
        goldText << goldScore;
		text.setString("Gold: " + goldText.str());
		text.setPosition(view.getCenter().x - 510, view.getCenter().y - 260);
		window.draw(text);

		if (hero.info == true){
            textInfo.setString("If you want to call a dashboard,\n        you must press \"I\" ");
            textInfo.setPosition(view.getCenter().x - 510, view.getCenter().y - 150);
            window.draw(textInfo);
        }
        if (hero.market == true){
            textInfo.setString("If you want to enter the store,\n        you must press \"U\" ");
            textInfo.setPosition(view.getCenter().x - 510, view.getCenter().y - 150);
            window.draw(textInfo);
        }

        if(monkey.health > 0){
            std::ostringstream monkeyHealthString;
            monkeyHealthString << monkey.health;
            text.setString("Health: " + monkeyHealthString.str());
            text.setPosition(monkey.x , monkey.y-20);
            window.draw(text);
        }
        if(hero.health >= 0){
            std::ostringstream playerHealthString;
            playerHealthString << hero.health;
            textHealth.setString("Health: " + playerHealthString.str());
            textHealth.setPosition(view.getCenter().x + 300, view.getCenter().y - 300);
            window.draw(textHealth);
        }else{
            hero.sprite.setTextureRect(sf::IntRect(0, 188, 34, 55));
            textHealth.setString("Health: 0");
            textHealth.setPosition(view.getCenter().x + 300, view.getCenter().y - 300);
            window.draw(textHealth);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.draw(myInfo.sprite);
        window.draw(myMarket.sprite);
        if(monkey.health > 0){
            window.draw(monkey.sprite);
        }
        for (it = solid.begin(); it != solid.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = elki.begin(); it != elki.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = bushes.begin(); it != bushes.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = grass.begin(); it != grass.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = grounds.begin(); it != grounds.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = metal.begin(); it != metal.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = gold.begin(); it != gold.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = berry.begin(); it != berry.end(); it++){
            window.draw((*it)->sprite);
        }
        for (it = entities.begin(); it != entities.end(); it++){
            window.draw((*it)->sprite);
        }
		window.draw(hero.sprite);     //выводим спрайт на экран
		if (!showInfo) {
            infoFonSp.setPosition(view.getCenter().x - 520 , view.getCenter().y - 200);   //позиция фона
			window.draw(infoFonSp);
        }
        if (!showMarket) {
            marketFonSp.setPosition(view.getCenter().x - 520 , view.getCenter().y - 300);   //позиция фона
			window.draw(marketFonSp);
        }
        if(hero.health <= 0){
            endFonSp.setPosition(0,0 );
            window.draw(endFonSp);
        }
        if(monkey.health <= 0){
            vicFonSp.setPosition(0,0 );
            window.draw(vicFonSp);
        }
		window.display();
	}
    return false;
}

void checkGamePlay(){
    if(gamePlay() == true){
        checkGamePlay();
    }
}

void runningGame(void(*cb)(void)){
    printf("Working correctly!\n");
    cb();
    printf("The game is closed!");
}
