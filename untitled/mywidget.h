#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QSound>
#include <QMediaPlayer>
#include <QPushButton>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void paintEvent(QPaintEvent *event);//图像界面绘制
    void keyPressEvent(QKeyEvent *event);//键盘响应
    void InitSnake();//初始化蛇
    QRect CreateFood();
    void IsEat();//判断进食
    void IsHit();//判断蛇撞自身
    void Ready();//预备阶段
    void Over();//游戏结算

private slots:
    void UpdateSnake();//更新游戏界面
    void Start();//游戏主体

private:
    Ui::MyWidget *ui;
    QRect SnakeRect;//蛇块
    QTimer *Timer;//计时器
    int Direction;//蛇的移动方向
    bool Run;
    bool End;
    QVector<QRect> nSnakeRect;//蛇
    QRect SnakeHead;//蛇头
    QRect Food;//食物
    QString Display;//游戏提示
    int Score;//分数
    int Speed;//速度
    bool Space;//暂停
    bool Begin;//进入游戏主体判定
    QSound* SoundFood;//吃苹果音效
    QSound* SoundWall;//撞墙音效
    QSound* SoundHitBody;//撞到自己
    QMediaPlayer* BGM;//背景音乐
    QDialog* Prompt;//游戏结束对话框
    bool Retry;//判定再来一局
};
#endif // MYWIDGET_H
