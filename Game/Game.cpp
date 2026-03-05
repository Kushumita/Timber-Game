#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

int main(){
    #pragma region
    VideoMode vm(1920,1080);
    RenderWindow window(vm,"Timber",Style::Fullscreen);
    View view(FloatRect(0,0,1920,1080));
    window.setView(view);

    //For Background
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(0,0);

    //For Tree
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree2.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810,0);

    //For Bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(0,800);

    //For Clouds
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);
    spriteCloud1.setPosition(0,0);
    spriteCloud2.setPosition(0,150);
    spriteCloud3.setPosition(0,300);
    //SpriteCloud2.setScale(0.5,0.5);
    
    //text
    String messageString="Enter \'Space Bar\' to start";
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    Text messageText;
    messageText.setFont(font);
    messageText.setFillColor(Color::Cyan);
    messageText.setCharacterSize(70);
    messageText.setString(messageString);
    FloatRect rect=messageText.getLocalBounds();
    // messageText.setOrigin(rect.width/2,rect.height/2);
    // messageText.setPosition(1920/2,1080/2);
    messageText.setOrigin(rect.width/2,rect.height/2);
    messageText.setPosition(1920/2,1080/2);
    



    float beeSpeed=200;
    bool beeActive=false;
    int cloud1Speed=1000, cloud2Speed=1000,cloud3Speed=1000;
    bool cloud1Active=false,cloud2Active=false,cloud3Active=false;
    bool gamePaused=true;

    Clock clock;
    Time dt;

    int x=1920;


    while(window.isOpen()){
        dt=clock.restart();
        Event event;
        while (window.pollEvent(event)){
            if (event.type==Event::Closed){
                window.close();
            }
            if (event.type==Event::KeyPressed){
                if(event.key.code==Keyboard::Escape){
                    window.close();
                }
                if(event.key.code==Keyboard::Space){
                    gamePaused=false;


                }
            }
        }

        if(!gamePaused){
        if(!beeActive){//for bee
            srand(time(0));
            int height=rand()%300+650;
            spriteBee.setPosition(2000,height);
            beeSpeed=rand()%450+150;
            beeActive=true;
        }else{
            spriteBee.setPosition(spriteBee.getPosition().x - beeSpeed*dt.asSeconds(),spriteBee.getPosition().y);
            if(spriteBee.getPosition().x<-100){
                beeActive=false;
            }
        }


        if(!cloud1Active){//For cloud1
            srand(time(0));
            int height=rand()%150;
            spriteCloud1.setPosition(-100,height);
            cloud1Speed=rand()%200+50;
            cloud1Active=true;
            float scale=(float)(rand()%40 + 60)/100;
            spriteCloud1.setScale(scale,scale);

        }else{
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed*dt.asSeconds(),spriteCloud1.getPosition().y);
            if(spriteCloud1.getPosition().x>2000){
                cloud1Active=false;
            }
        }
        

        if(!cloud2Active){//For cloud2
            srand(time(0)+30);
            int height=rand()%150+150;
            spriteCloud2.setPosition(-100,height);
            cloud2Speed=rand()%200+50;
            cloud2Active=true;
            float scale=(float)(rand()%40 + 60)/100;
            spriteCloud2.setScale(scale,scale);

        }else{
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + cloud2Speed*dt.asSeconds(),spriteCloud2.getPosition().y);
            if(spriteCloud2.getPosition().x>2000){
                cloud2Active=false;
            }
        }
        

        if(!cloud3Active){//For cloud3
            srand(time(0)+50);
            int height=rand()%150+300;
            spriteCloud3.setPosition(-100,height);
            cloud3Speed=rand()%200+50;
            cloud3Active=true;
            float scale=(float)(rand()%40 + 60)/100;
            spriteCloud3.setScale(scale,scale);
        }else{
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed*dt.asSeconds(),spriteCloud3.getPosition().y);
            if(spriteCloud3.getPosition().x>2000){
                cloud3Active=false;
            }
        }
    }


        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteBee);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        
        window.draw(spriteTree);
        if(gamePaused){
        window.draw(messageText);
        }
        
        window.display();
    }
    

    return 0;
}