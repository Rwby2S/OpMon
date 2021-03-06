#include "MainMenu.hpp"
#include "../../utils/StringKeys.hpp"
#include "../../utils/defines.hpp"
#include "../../utils/log.hpp"
#include "../model/storage/ResourceLoader.hpp"
#include "OptionsMenu.hpp"
#include "Window.hpp"
#include <iostream>

namespace OpMon {
    namespace View {

        void MainMenu::initStrings() {
            auto kget = Utils::StringKeys::get;

            playtx.setString(kget("title.1"));
            charge.setString(kget("title.2"));
            options.setString(kget("title.3"));
            exit.setString(kget("title.4"));
        }

        MainMenu::MainMenu(Model::MainMenuData &data)
          : data(data) {
            sf::Text *textPos[4] = {&playtx, &charge, &options, &exit};
            for(int i = 0, j = 175; i < 4; i++) {
                curPos[i].x = 10;
                curPos[i].y = j;
                textPos[i]->setPosition(sf::Vector2f(60, j));
                j += 85;
            }
            Model::ResourceLoader::load(sounds[0], "audio/sounds/select.ogg");
            Model::ResourceLoader::load(sounds[1], "audio/sounds/selectbuttons.ogg");
            //sounds[2].loadFromFile(RESSOURCES_PATH + "audio/sounds/nope.ogg");
            bg.setTexture(data.getTitlescreen());
            cursor.setTexture(data.getArrChoice());
            bruitArr.setBuffer(sounds[0]);
            bruitPush.setBuffer(sounds[1]);
            //bruitNope.setBuffer(sounds[2]);
            cursor.setScale(3, 3);
            initStrings();

            for(auto *text : {&playtx, &charge, &options, &exit}) {
                text->setSfmlColor(sf::Color::White);
                text->setFont(data.getUiDataPtr()->getFont());
                text->setCharacterSize(FONT_SIZE_DEFAULT);
            }

            //Mix_Volume(2, MIX_MAX_VOLUME / 4);
            //Mix_Volume(1, MIX_MAX_VOLUME);
            //Mix_Volume(0, MIX_MAX_VOLUME / 2);

            data.getUiDataPtr()->getJukebox().play("Title");
        }

        MainMenu::~MainMenu() {
        }

        void MainMenu::onLangChanged() {
            initStrings();
        }

        void MainMenu::pause() {
        }

        void MainMenu::play() {
            data.getUiDataPtr()->getJukebox().play("Title");
        }

        void MainMenu::moveArrow(bool direction) {
            if(direction /* == true*/) {
                curPosI--;
            } else {
                curPosI++;
            }

            if(curPosI >= 4) {
                curPosI = 0;
            } else if(curPosI < 0) {
                curPosI = 3;
            }
        }

        void MainMenu::draw(sf::RenderTexture &frame) {
            frame.clear(sf::Color::Black);
            frame.draw(bg);
            frame.draw(playtx),
              frame.draw(charge);
            frame.draw(options);
            frame.draw(exit);
            cursor.setPosition(curPos[curPosI]);
            frame.draw(cursor);
        }

    } // namespace View
} // namespace OpMon
