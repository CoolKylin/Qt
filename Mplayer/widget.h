#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QDir>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QTime>
#include <QTest>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString settime(int time);

private:
    Ui::Widget *ui;

private:
    QString str_musicpath = "G:/QTproject/QtOnline/Mplayer/source/music";//音乐文件夹路径
    QString str_lrcpath = "G:/QTproject/QtOnline/Mplayer/source/lrc";//歌词路径
    QListWidgetItem *lst_item;//音乐列表
    bool if_play_music = false;//是否播放音乐
    QMediaPlayer *mplayer= new QMediaPlayer;
    QAudioOutput *audioOutput= new QAudioOutput;
    QString str_music;//播放名称
    int n_music_seq=0;
    float n_volume=0.5;//初始音量为50
    QTimer *timer;//定时器
    int playtime;
    int n_position=0;//初始进度为0
    QMap<int, QString> lrc_map;

private:
    void paintEvent(QPaintEvent *event);
    //读取歌曲文件
    QStringList readFile();
    //读取歌词文件
    QStringList readIrc();
    //寻找歌词名称
    bool find_lrcname(QString);
    //读取歌词文件
    void readLyricsFile(QString);
    //解析歌词文件
    void analysisLyricsFile(QString);
    //初始化界面
    void initUI();
    //判断是否播放
    void ifplay();
    QStringList fileList;   //文件名称
    QStringList lrcList;

private slots:
    void slot_btnup_clicked();//上一曲
    void slot_btndown_clicked();//下一曲
    void slot_btnplay_clicked();//播放
    void slot_musicListRowNum(int);//切歌
    void slot_setSliderValue(int);//设置进度
    void slot_setVliderVolume(int);//设置音量
    void slot_getPlayDuration();//获得当前播放进度
    void slot_getMusicTime();//获得播放总时长
    void slot_showCurrentLrc();//初始化歌词
    void slot_showCurrentWord(int time);//显示歌词
    void slot_clearLastMap();//清除上一首歌词
    void on_btnClose_clicked();
    void on_btnMin_clicked();
};
#endif // WIDGET_H
