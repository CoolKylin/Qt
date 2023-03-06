#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <typeinfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    ui->lyrics_lb->setText("");
    fileList = readFile();
    lrcList = readIrc();


    initUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

QStringList Widget::readFile()
{
    //设置遍历目录
    QDir dir(str_musicpath);

    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤器格式
    nameFilters << "*.mp3" << "*.flac" << "*.wav" << "*.mflac";
    //将过滤后的文件名存入到list中
    QStringList files = dir.entryList(nameFilters,QDir::Files|QDir::Readable,QDir::Name);
    //添加到listwidget的item中
    ui->listwidget->addItems(files);
    //把item加入到listwidget中排序,若对排序无要求,可忽略此步
    ui->listwidget->sortItems();

    //设置默认情况下选中第一行
    lst_item = ui->listwidget->item(0);
    lst_item->setSelected(true);

    return files;
}

QStringList Widget::readIrc()
{
    //设置遍历目录
    QDir dir(str_lrcpath);

    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤器格式
    nameFilters << "*.lrc";
    //将过滤后的文件名存入到list中
    QStringList files = dir.entryList(nameFilters,QDir::Files|QDir::Readable,QDir::Name);

    return files;
}

void Widget::initUI()
{
    //调试

    connect(ui->listwidget,SIGNAL(currentRowChanged(int)),this,SLOT(slot_musicListRowNum(int)));
    connect(ui->btn_up,SIGNAL(clicked()),this,SLOT(slot_btnup_clicked()));
    connect(ui->btn_down,SIGNAL(clicked()),this,SLOT(slot_btndown_clicked()));
    connect(ui->btn_play,SIGNAL(clicked()),this,SLOT(slot_btnplay_clicked()));
    connect(ui->hSliderPlayProgress,SIGNAL(sliderMoved(int)),this,SLOT(slot_setSliderValue(int)));
    connect(ui->vSliderVolume,SIGNAL(valueChanged(int)),this,SLOT(slot_setVliderVolume(int)));
    connect(mplayer,SIGNAL(durationChanged(qint64)),this,SLOT(slot_getMusicTime()));
    connect(mplayer,SIGNAL(positionChanged(qint64)),this,SLOT(slot_getPlayDuration()));

}

void Widget::slot_showCurrentWord(int time)
{
    if(lrc_map.contains(time))
    {
        ui->lyrics_lb->setText(lrc_map.value(time));
    }
    else{
//        qDebug()<<"继续上一句歌词";
    }
}

void Widget::slot_musicListRowNum(int n_number)
{
    qDebug()<<"切歌了";
    n_music_seq = n_number;
    n_position = 0;
    ui->lyrics_lb->clear();
    ui->musicname_lb->clear();
    slot_clearLastMap();
    slot_showCurrentLrc();
    n_volume = float(ui->vSliderVolume->sliderPosition())/100;
    str_music = ui->listwidget->item(n_number)->text();
    mplayer->setAudioOutput(audioOutput);
    mplayer->setSource(QUrl::fromLocalFile(str_musicpath + '/' + str_music));
    audioOutput->setVolume(n_volume); //0~100音量范围,默认是100
    ui->hSliderPlayProgress->setValue(n_position);
    Widget::ifplay();
}

void Widget::ifplay()
{
    if(if_play_music)
    {
        mplayer->play();//暂停
    }
    else
    {
        mplayer->stop();//播放
    }
}

void Widget::slot_btnup_clicked()
{
    mplayer->stop();
    slot_clearLastMap();
    int n_max = ui->listwidget->count();
    if(n_music_seq==0)
    {
        n_music_seq = n_max-1;
    }
    else
    {
        n_music_seq = n_music_seq-1;
    }
    str_music = ui->listwidget->item(n_music_seq)->text();
    lst_item = ui->listwidget->item(n_music_seq);
    lst_item->setSelected(true);
    slot_musicListRowNum(n_music_seq);
}

void Widget::slot_btndown_clicked()
{
    mplayer->stop();
    slot_clearLastMap();
    int n_max = ui->listwidget->count();
    if(n_music_seq==n_max-1)
    {
        n_music_seq = 0;
    }
    else
    {
        n_music_seq = n_music_seq+1;
    }
    str_music = ui->listwidget->item(n_music_seq)->text();
    lst_item = ui->listwidget->item(n_music_seq);
    lst_item->setSelected(true);
    slot_musicListRowNum(n_music_seq);
}

void Widget::slot_btnplay_clicked()
{
    if(if_play_music)
    {
        ui->btn_play->setStyleSheet("QPushButton#btn_play{border-image: url(:/images/pause.png);}");
        if_play_music = false;
        mplayer->pause();//暂停
    }
    else
    {
        ui->btn_play->setStyleSheet("QPushButton#btn_play{border-image: url(:/images/play.png);}");
        if_play_music = true;
        mplayer->play();//播放
    }

}

void Widget::slot_setSliderValue(int position)
{
    n_position = position;

    mplayer->setPosition(mplayer->duration()*position/100);
    ui->hSliderPlayProgress->setValue(position);
}

void Widget::slot_setVliderVolume(int vol)
{
    n_volume = float(vol)/100;
    mplayer->audioOutput()->setVolume(n_volume);
}

QString Widget::settime(int time)
{
    int minute,seconds;
    time /= 1000;  //获得的时间是以毫秒为单位的
    minute = time/60;
    seconds = time-minute*60;
    int lrctime = minute*60*1000 + seconds*1000;
    QString t_str = t_str.asprintf("%02d:%02d", minute, seconds);
    Widget::slot_showCurrentWord(lrctime);
    return t_str;
}

void Widget::slot_getPlayDuration()
{

    if(mplayer->position()>mplayer->duration()&&mplayer->duration()>0)
    {
//        qDebug()<< "slot_getPlayDuration100" << mplayer->position() << mplayer->duration() << n_position;
        ui->playtime_lb->setText(settime(mplayer->duration()));
        ui->hSliderPlayProgress->setValue(n_position);
        QTest::qSleep(1000);
        slot_btndown_clicked();
    }
    else
    {
        if(mplayer->duration()>0){
            n_position = mplayer->position()*100/mplayer->duration();
//            qDebug()<< "slot_getPlayDuration" << mplayer->position() << mplayer->duration() << n_position;
            ui->hSliderPlayProgress->setValue(n_position);
            ui->playtime_lb->setText(settime(mplayer->position()));
        }
    }
}

void Widget::slot_getMusicTime()
{
    playtime = mplayer->duration();
    ui->musictime_lb->setText(settime(playtime));
}

void Widget::slot_showCurrentLrc()
{
//    qDebug()<< "slot_showCurrentLrc" << n_music_seq;
    QListWidgetItem *item = ui->listwidget->item(n_music_seq);
    QString mscname = item->text().left(item->text().lastIndexOf(".")) + ".lrc";
    qDebug()<< mscname;
    ui->musicname_lb->setText(item->text().left(item->text().lastIndexOf(".")));

    if(find_lrcname(mscname))
    {
        readLyricsFile(mscname);//读取歌词文件内容
    }
    else
    {
        ui->lyrics_lb->setText("未检测到歌词文件");
    }
}

void Widget::readLyricsFile(QString lrcname)
{
    QString str_currentlrcPath = str_lrcpath + '/' + lrcname;
    QFile file(str_currentlrcPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line="";
//    lrc_map.erase(lrc_map.begin(),lrc_map.end());
    while(!file.atEnd()){
        line = file.readLine();
        analysisLyricsFile(line);//解析歌词文件内容
    }
}

void Widget::analysisLyricsFile(QString line)
{

    QRegularExpression regularExpression("\\[(\\d+)?:(\\d+)?(\\.\\d+)?\\](.*)?");
    int index = 0;
    QRegularExpressionMatch match;
    match = regularExpression.match(line, index);
    QString regline = match.captured();
    if(match.hasMatch()) {


        QString currentTime = regline.mid(0,regline.lastIndexOf("]"));/*   获取歌词文本*/
        QString currentText = regline.mid(regline.lastIndexOf("]")+1);/*   获取歌词文本*/

        QStringList list = currentTime.split("]");
        for(int i = 0; i < list.count(); i++)
        {
            QString temp = list.at(i);
            QString lrc_time = temp.mid(temp.lastIndexOf("[")+1);
            int lrc_m = int(lrc_time.mid(0,lrc_time.lastIndexOf(":")).toFloat());
            int lrc_ss = int(lrc_time.mid(lrc_time.lastIndexOf(":")+1).toFloat());
            int totalTime;
            totalTime = lrc_m * 60000 + lrc_ss * 1000;                    /*计算该时间点毫秒数*/
            lrc_map.insert(totalTime, currentText);
        }
    }
}

bool Widget::find_lrcname(QString lrcname)
{
    QList<QString>::Iterator it = lrcList.begin(),itend = lrcList.end();
    int i = 0;
    for (;it != itend; it++,i++){
        if (*it == lrcname){//找到，播放歌词
            return true;
        }
    }
    return false;
}

void Widget::slot_clearLastMap()
{
    lrc_map.erase(lrc_map.begin(),lrc_map.end());
}

void Widget::on_btnMin_clicked()
{
    //最小化窗口
    this->showMinimized();
}

void Widget::on_btnClose_clicked()
{
    //关闭窗口
    this->close();
}

