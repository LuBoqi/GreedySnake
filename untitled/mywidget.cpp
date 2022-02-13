#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>
#include <QSound>
#include <QMediaPlayer>
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent):
    QWidget(parent), ui(new Ui::MyWidget), Run(false),Score(0),Speed(100),Begin(true),Space(false),Retry(false)
{
    ui->setupUi(this);
    this->setGeometry(QRect(500, 300, 960, 545));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Prompt = new Dialog(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget:: paintEvent(QPaintEvent *event){
    if(Begin){
        Start();
    }
    else{
        Ready();
    }
}

void MyWidget::InitSnake(){
    //参数初始化
    Run = true;
    End = false;
    Direction = 3;
    Display = "游戏运行中";
    Speed = 100;

    //食物及音效初始化
    Food = CreateFood();
    SoundFood = new QSound(":/source/sounds/eat.wav",this);
    SoundFood->setLoops(1);

    //背景音乐初始载入
    BGM = new QMediaPlayer;
    BGM->setMedia(QUrl("qrc:/source/sounds/bgm.mp3"));
    BGM->setVolume(100);
    BGM->play();

    //撞墙音效装载
    SoundWall = new QSound(":/source/sounds/wall.wav");
    SoundWall->setLoops(1);

    //撞自己音效装载
    SoundHitBody = new QSound(":/source/sounds/hitbody.wav");
    SoundHitBody->setLoops(1);

    //初始位置
    nSnakeRect.resize(3);
    for(int i = 0; i < nSnakeRect.size(); i++){
        QRect Rect(315 + i * 20, 255, 20, 20);
        nSnakeRect[i] = Rect;
    }

    Timer = new QTimer(this);
    Timer->start(Speed);
    connect(Timer, SIGNAL(timeout()), SLOT(UpdateSnake()));

}

void MyWidget::UpdateSnake(){
    SnakeHead = nSnakeRect.first();
    for(int i = nSnakeRect.size()-1; i > 0; i--){
        nSnakeRect[i] = nSnakeRect[i - 1];
    }
    switch(Direction){
    case 1://上
        SnakeHead.setTop(SnakeHead.top() - 20);
        SnakeHead.setBottom(SnakeHead.bottom() - 20);
        break;
    case 2://下
        SnakeHead.setTop(SnakeHead.top() + 20);
        SnakeHead.setBottom(SnakeHead.bottom() + 20);
        break;
    case 3://左
        SnakeHead.setLeft(SnakeHead.left() - 20);
        SnakeHead.setRight(SnakeHead.right() - 20);
        break;
    case 4://右
        SnakeHead.setLeft(SnakeHead.left() + 20);
        SnakeHead.setRight(SnakeHead.right() + 20);
        break;
    default:;
    }
    nSnakeRect[0] = SnakeHead;
    IsEat();
    IsHit();
    update();
    //repaint();
}

void MyWidget::keyPressEvent(QKeyEvent *event){
    QKeyEvent *Key = (QKeyEvent*) event;
    switch(Key->key()){
    case Qt::Key_Up:
        if(Direction == 2){
            break;
        }
        Direction = 1;
        break;
    case Qt::Key_Down:
        if(Direction == 1){
            break;
        }
        Direction = 2;
        break;
    case Qt::Key_Left:
        if(Direction == 4){
            break;
        }
        Direction = 3;
        break;
    case Qt::Key_Right:
        if(Direction == 3){
            break;
        }
        Direction = 4;
        break;
    default:;
    }
}


QRect MyWidget::CreateFood(){
    int x, y;
    x = qrand() % 31;
    y = qrand() % 25;
    QRect Rect(15 + x * 20, 15 + y * 20, 20, 20);
    return Rect;
}

void MyWidget::IsEat(){
    if(SnakeHead == Food){
        SnakeHead = Food;
        nSnakeRect.push_back(nSnakeRect.last());
        Food = CreateFood();
        Score += 10;
        if(Speed <= 5){

        }
        else if(Speed <= 10){
            Speed -= 1;
        }
        else if(Speed <= 20){
            Speed -= 3;
        }
        else{
            Speed -= 5;
        }
        SoundFood->play();
    }
}

void MyWidget::IsHit(){
    //我撞我自己
    for(int i = 1; i < nSnakeRect.size(); i++){
        if(SnakeHead == nSnakeRect[i]){
            SoundHitBody->play();
            End = true;
            Display = "游戏结束了";
            update();
            //repaint();
        }
    }

    //判断撞墙
    if(SnakeHead.left() < 15 || SnakeHead.right() > 655 || SnakeHead.top() < 15 || SnakeHead.bottom() > 535){
        SoundWall->play();
        End = true;
        Display = "游戏结束了";
        update();
        //repaint();
    }
}

void MyWidget::Start(){
    QPainter Painter(this);
    if(!Run){
        InitSnake();
    }

    //绘制背景
    //外墙
    Painter.setPen(Qt::BlankCursor);//设置笔的颜色
    Painter.setBrush(Qt::gray);//设置填充色
    Painter.drawRect(5, 5, 950, 535);//绘制矩形

    //内墙
    Painter.drawPixmap(15, 15, 640, 520, QPixmap(":/source/images/background.jpg"));
/*
    //画格子
    //竖线
    Painter.setPen(Qt::black);
    for(int i = 0; i < 63; i++){
        Painter.drawLine(i * 10 + 15, 15, i * 10 + 15, 525);
    }
    //横线
    for(int i = 0; i < 51; i++){
        Painter.drawLine(15, i * 10 + 15, 645, i * 10 + 15);
    }
*/

    //游戏提示
    QFont font1("Courier", 24);
    Painter.setFont(font1);
    Painter.setPen(Qt::red);
    Painter.setBrush(Qt::red);
    Painter.drawText(740, 100, Display);

    //画蛇
    Painter.setPen(Qt::black);
    Painter.setBrush(Qt::green);
    Painter.drawRects(&nSnakeRect[0], nSnakeRect.size());

    //画食物
    Painter.setPen(Qt::black);
    Painter.setBrush(Qt::red);
    //Painter.drawRect(Food);
    Painter.drawPixmap(Food, QPixmap(":/source/images/food.png"));

    //画分数
    QFont font2("Courier", 18);
    Painter.setFont(font2);
    Painter.setPen(Qt::yellow);
    Painter.setBrush(Qt::yellow);
    Painter.drawText(700, 200, "得分：");
    Painter.drawText(800, 200, QString::number(Score));

    //画提示
    //画分数
    QFont font4("Courier", 16);
    Painter.setFont(font4);
    Painter.setPen(Qt::white);
    Painter.setBrush(Qt::white);
    Painter.drawText(690, 400, "↑ ↓ ← → 按键移动");
    Painter.drawText(690, 450, "吃到食物加速");

    //画速度
    QFont font3("Courier", 18);
    Painter.setFont(font3);
    Painter.setPen(Qt::yellow);
    Painter.setBrush(Qt::yellow);
    Painter.drawText(700, 300, "速度：");
    Painter.drawText(800, 300, QString::number(105 - Speed));

    //切换速度
    Timer->start(Speed);

    //结束
    if(End){
        Over();
    }
}

void MyWidget::Ready(){

}

void MyWidget::Over(){
    Prompt->show();
    Timer->stop();
    BGM->stop();
    Retry = Prompt->exec();
    Run = false;
    if(Retry){
        Ready();
    }
    else{
        this->close();
    }
}
