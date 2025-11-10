#include "mainwindow.h"
#include "State.h"
#include "ui_mainwindow.h"
#include "dialogarx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , samples_count(40)
{
    ui->setupUi(this);
    this->ui->centralwidget->setLayout(ui->horizontalLayout_13);

    chart_sterowanie = new QChart();
    chart_sterowanie->setTitle(tr("Sterowanie (Wyjście z regulatora)"));
    chart_sterowanie->legend()->hide();

    chart_uchyb = new QChart();
    chart_uchyb->setTitle(tr("Uchyb"));
    chart_uchyb->legend()->hide();

    chart_wszystko = new QChart();
    chart_wszystko->setTitle(tr("Wszystko"));

    chart_wartosc_zadana_i_regulowana = new QChart();
    chart_wartosc_zadana_i_regulowana->setTitle(tr("Wartość zadana i regulowana"));
    chart_wartosc_zadana_i_regulowana->legend()->hide();

    lista_sterowanie = new QList<QPointF>();
    lista_uchyb = new QList<QPointF>();
    lista_wartosc_zadana = new QList<QPointF>();
    lista_wartosc_regulowana = new QList<QPointF>();

    {
        auto seria = new QScatterSeries();
        seria->setName("Sterowanie");
        seria->setMarkerSize(13.0);
        seria->setMarkerShape(QScatterSeries::MarkerShapePentagon);
        seria->setColor(QColor(30, 30, 220));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_sterowanie->addSeries(seria);
    }
    {
        auto seria = new QScatterSeries();
        seria->setName("Uchyb");
        seria->setMarkerSize(10);
        seria->setMarkerShape(QScatterSeries::MarkerShapeTriangle);
        seria->setColor(QColor(185, 0, 80));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_uchyb->addSeries(seria);
    }
    {
        auto seria = new QScatterSeries();
        seria->setName("Wartość zadana");
        seria->setMarkerSize(13);
        seria->setMarkerShape(QScatterSeries::MarkerShapeRotatedRectangle);
        seria->setColor(QColor(0, 180, 55));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);

        seria = new QScatterSeries();
        seria->setName("Wartość regulowana");
        seria->setColor(QColor(130, 20, 150));
        seria->setMarkerSize(10);
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);
    }
    {
        auto seria = new QScatterSeries();
        seria->setName("Sterowanie");
        seria->setMarkerSize(13.0);
        seria->setMarkerShape(QScatterSeries::MarkerShapePentagon);
        seria->setColor(QColor(30, 30, 220));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_wszystko->addSeries(seria);

        seria = new QScatterSeries();
        seria->setName("Uchyb");
        seria->setMarkerSize(10);
        seria->setMarkerShape(QScatterSeries::MarkerShapeTriangle);
        seria->setColor(QColor(185, 0, 80));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_wszystko->addSeries(seria);

        seria = new QScatterSeries();
        seria->setName("Wartość zadana");
        seria->setMarkerSize(13);
        seria->setMarkerShape(QScatterSeries::MarkerShapeRotatedRectangle);
        seria->setColor(QColor(0, 180, 55));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        chart_wszystko->addSeries(seria);

        seria = new QScatterSeries();
        seria->setName("Wartość regulowana");
        seria->setColor(QColor(130, 20, 150));
        seria->setBorderColor(QColor(0, 0, 0, 0));
        seria->setMarkerSize(10);
        chart_wszystko->addSeries(seria);
    }

    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_wszystko->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wszystko->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_wszystko->axes(Qt::Horizontal).at(0)->setTitleText("Czas [s]");
    chart_wszystko->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wszystko->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_sterowanie->series().at(0)->attachAxis(chart_sterowanie->axes(Qt::Horizontal).at(0));
    chart_sterowanie->series().at(0)->attachAxis(chart_sterowanie->axes(Qt::Vertical).at(0));

    chart_uchyb->series().at(0)->attachAxis(chart_uchyb->axes(Qt::Horizontal).at(0));
    chart_uchyb->series().at(0)->attachAxis(chart_uchyb->axes(Qt::Vertical).at(0));

    chart_wartosc_zadana_i_regulowana->series().at(0)->attachAxis(
        chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(0)->attachAxis(
        chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(1)->attachAxis(
        chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(1)->attachAxis(
        chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0));

    chart_wszystko->series().at(0)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(0)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(1)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(1)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(2)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(2)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(3)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(3)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));

    auto q_chart_view = new QChartView(chart_sterowanie);
    chart_sterowanie->setMargins(QMargins(0, 0, 0, 0));
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_uchyb);
    chart_uchyb->setMargins(QMargins(0, 0, 0, 0));
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_wartosc_zadana_i_regulowana);
    chart_wartosc_zadana_i_regulowana->setMargins(QMargins(0, 0, 0, 0));
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_wszystko);
    chart_wszystko->setMargins(QMargins(0, 0, 0, 0));
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 4);

    QObject::connect(&State::getInstance(),
                     &State::sendTickDataToMainWindow,
                     this,
                     &MainWindow::addToPlots);
    debug_timer.start();
    debug_last_time = 0;
}
void MainWindow::addToPlots(TickData tick_data)
{
    int debug_current_time = debug_timer.elapsed();
    qDebug() << debug_current_time - debug_last_time;
    debug_last_time = debug_current_time;
    qint64 interwal_symulacji = State::getInstance().getInterwalSymulacjiMS();
    qint64 liczba_probek = (double) ui->spinBox_symulacja_okno_obserwacji->value()
                           / ((double) interwal_symulacji / 1000.0);

    qreal seconds_of_simulation = (double) (miliseconds_of_simulation += interwal_symulacji)
                                  / 1000.0;
    lista_wartosc_zadana->append(QPointF(seconds_of_simulation, tick_data.wartosc_zadana));
    lista_wartosc_regulowana->append(QPointF(seconds_of_simulation, tick_data.wartosc_regulowana));
    lista_uchyb->append(QPointF(seconds_of_simulation, tick_data.uchyb));
    lista_sterowanie->append(QPointF(seconds_of_simulation, tick_data.sterowanie));

    dynamic_cast<QScatterSeries *>(chart_sterowanie->series().at(0))->replace(*lista_sterowanie);

    dynamic_cast<QScatterSeries *>(chart_uchyb->series().at(0))->replace(*lista_uchyb);

    dynamic_cast<QScatterSeries *>(chart_wartosc_zadana_i_regulowana->series().at(0))
        ->replace(*lista_wartosc_zadana);
    dynamic_cast<QScatterSeries *>(chart_wartosc_zadana_i_regulowana->series().at(1))
        ->replace(*lista_wartosc_regulowana);

    dynamic_cast<QScatterSeries *>(chart_wszystko->series().at(0))->replace(*lista_sterowanie);
    dynamic_cast<QScatterSeries *>(chart_wszystko->series().at(1))->replace(*lista_uchyb);
    dynamic_cast<QScatterSeries *>(chart_wszystko->series().at(2))->replace(*lista_wartosc_zadana);
    dynamic_cast<QScatterSeries *>(chart_wszystko->series().at(3))
        ->replace(*lista_wartosc_regulowana);

    // Osie poziome - skalowanie
    qreal range_start = seconds_of_simulation
                        - (qreal) (liczba_probek * interwal_symulacji) / 1000.0;
    qreal range_end = seconds_of_simulation + 4.0 * (qreal) (interwal_symulacji) / 1000.0;
    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_wszystko->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);

    // Osie pionowe - skalowanie
    qreal max_uchyb = 0.0;
    qreal min_uchyb = 0.0;
    for (QList<QPointF>::iterator point = lista_uchyb->begin(); point != lista_uchyb->end();
         point = std::next<>(point)) {
        if (point->y() > max_uchyb)
            max_uchyb = point->y();
        else if (point->y() < min_uchyb)
            min_uchyb = point->y();
    }
    qreal range_width_uchyb = (max_uchyb - min_uchyb) * 0.1;
    chart_uchyb->axes(Qt::Vertical)
        .at(0)
        ->setRange(min_uchyb - range_width_uchyb, max_uchyb + range_width_uchyb);

    qreal max_sterowanie = 0.0;
    qreal min_sterowanie = 0.0;
    for (QList<QPointF>::iterator point = lista_sterowanie->begin();
         point != lista_sterowanie->end();
         point = std::next<>(point)) {
        if (point->y() > max_sterowanie)
            max_sterowanie = point->y();
        else if (point->y() < min_sterowanie)
            min_sterowanie = point->y();
    }
    qreal range_width_sterowanie = (max_sterowanie - min_sterowanie) * 0.1;
    chart_sterowanie->axes(Qt::Vertical)
        .at(0)
        ->setRange(min_sterowanie - range_width_sterowanie, max_sterowanie + range_width_sterowanie);

    qreal max_wartosc_zadana = 0.0;
    qreal min_wartosc_zadana = 0.0;
    for (QList<QPointF>::iterator point = lista_wartosc_zadana->begin();
         point != lista_wartosc_zadana->end();
         point = std::next<>(point)) {
        if (point->y() > max_wartosc_zadana)
            max_wartosc_zadana = point->y();
        else if (point->y() < min_wartosc_zadana)
            min_wartosc_zadana = point->y();
    }

    qreal max_wartosc_regulowana = 0.0;
    qreal min_wartosc_regulowana = 0.0;
    for (QList<QPointF>::iterator point = lista_wartosc_regulowana->begin();
         point != lista_wartosc_regulowana->end();
         point = std::next<>(point)) {
        if (point->y() > max_wartosc_regulowana)
            max_wartosc_regulowana = point->y();
        else if (point->y() < min_wartosc_regulowana)
            min_wartosc_regulowana = point->y();
    }
    qreal range_width_wartosc_zadana_i_regulowana = (std::max(max_wartosc_regulowana,
                                                              max_wartosc_zadana)
                                                     - std::min(min_wartosc_regulowana,
                                                                min_wartosc_zadana))
                                                    * 0.1;

    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical)
        .at(0)
        ->setRange(std::min(min_wartosc_regulowana, min_wartosc_zadana)
                       - range_width_wartosc_zadana_i_regulowana,
                   std::max(max_wartosc_regulowana, max_wartosc_zadana)
                       + range_width_wartosc_zadana_i_regulowana);

    qreal max_wszystko = std::max(std::max(max_uchyb, max_sterowanie),
                                  std::max(max_wartosc_zadana, max_wartosc_regulowana));
    qreal min_wszystko = std::min(std::min(min_uchyb, min_sterowanie),
                                  std::min(min_wartosc_zadana, min_wartosc_regulowana));
    qreal range_width_wszystko = (max_wszystko - min_wszystko) * 0.1;

    chart_wszystko->axes(Qt::Vertical)
        .at(0)
        ->setRange(min_wszystko - range_width_wszystko, max_wszystko + range_width_wszystko);

    if (lista_wartosc_zadana->count() > liczba_probek) {
        lista_wartosc_zadana->removeFirst();
        lista_wartosc_regulowana->removeFirst();
        lista_uchyb->removeFirst();
        lista_sterowanie->removeFirst();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_symulacja_star_stop_released()
{
    if (State::getInstance().getSymulacjaDziala()) {
        State::getInstance().setSymulacjaDziala(false);
        ui->pushButton_symulacja_star_stop->setText(tr("START"));
    } else {
        State::getInstance().setSymulacjaDziala(true);
        ui->pushButton_symulacja_star_stop->setText(tr("STOP"));
    }
}

// Interwał symulacji
void MainWindow::on_spinBox_symulacja_interwal_valueChanged(int arg1)
{
    ui->horizontalSlider_symulacja_interwal->setValue(arg1);
}
void MainWindow::on_horizontalSlider_symulacja_interwal_valueChanged(int value)
{
    ui->spinBox_symulacja_interwal->setValue(value);
}
void MainWindow::on_spinBox_symulacja_interwal_editingFinished()
{
    State::getInstance().setInterwalSymulacjiMS(ui->spinBox_symulacja_interwal->value());
}
void MainWindow::on_horizontalSlider_symulacja_interwal_sliderReleased()
{
    State::getInstance().setInterwalSymulacjiMS(ui->horizontalSlider_symulacja_interwal->value());
}

//Włączanie okna ustawień obiektu ARX
void MainWindow::on_pushButton_dostosuj_parametry_clicked()
{
    //this->hide();
    DialogArx arxDialog(this);
    arxDialog.exec();
    //arxDialog->show();
}

// Amplituda generatora
void MainWindow::on_verticalSlider_generator_amplituda_sliderMoved(int position)
{
    ui->doubleSpinBox_generator_amplituda->setValue((double) position / 100.0);
}
void MainWindow::on_doubleSpinBox_generator_amplituda_valueChanged(double arg1)
{
    ui->verticalSlider_generator_amplituda->setValue(arg1 * 100.0);
}
void MainWindow::on_doubleSpinBox_generator_amplituda_editingFinished()
{
    State::getInstance().getGeneratorProstokatny().setAmplitude(
        ui->doubleSpinBox_generator_amplituda->value());
    State::getInstance().getGeneratorSinusoida().setAmplitude(
        ui->doubleSpinBox_generator_amplituda->value());
}
void MainWindow::on_verticalSlider_generator_amplituda_sliderReleased()
{
    State::getInstance().getGeneratorProstokatny().setAmplitude(
        (double) ui->verticalSlider_generator_amplituda->value() / 100.0);
    State::getInstance().getGeneratorSinusoida().setAmplitude(
        (double) ui->verticalSlider_generator_amplituda->value() / 100.0);
}

// Okres generatora (T)
void MainWindow::on_horizontalSlider_generator_okres_valueChanged(int value)
{
    ui->spinBox_generator_okres->setValue(value);
}
void MainWindow::on_spinBox_generator_okres_valueChanged(int arg1)
{
    ui->horizontalSlider_generator_okres->setValue(arg1);
}
void MainWindow::on_spinBox_generator_okres_editingFinished()
{
    State::getInstance().getGeneratorProstokatny().setSamplesPerCycle(
        ui->spinBox_generator_okres->value());
    State::getInstance().getGeneratorSinusoida().setSamplesPerCycle(
        ui->spinBox_generator_okres->value());
}
void MainWindow::on_horizontalSlider_generator_okres_sliderReleased()
{
    State::getInstance().getGeneratorProstokatny().setSamplesPerCycle(
        ui->horizontalSlider_generator_okres->value());
    State::getInstance().getGeneratorSinusoida().setSamplesPerCycle(
        ui->horizontalSlider_generator_okres->value());
}

//Zmiana używanego generatora
void MainWindow::on_comboBox_generator_typ_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Prostokątny") {
        ui->horizontalSlider_generator_wypelnienie->setEnabled(true);
        ui->spinBox_generator_wypelnienie->setEnabled(true);
        State::getInstance().setGenerator(&State::getInstance().getGeneratorProstokatny());
    } else {
        ui->horizontalSlider_generator_wypelnienie->setEnabled(false);
        ui->spinBox_generator_wypelnienie->setEnabled(false);
        if (arg1 == "Sinusoida")
            State::getInstance().setGenerator(&State::getInstance().getGeneratorSinusoida());
        else if (arg1 == "Ręczny") // TODO: dodac generator ręczny
            State::getInstance().setGenerator(&State::getInstance().getGeneratorSinusoida());
    }
}

// Wypelnienie generatora (P)
void MainWindow::on_spinBox_generator_wypelnienie_editingFinished()
{
    State::getInstance().getGeneratorProstokatny().setDutyCycle(
        (double) ui->spinBox_generator_wypelnienie->value() / 100.0);
}
void MainWindow::on_horizontalSlider_generator_wypelnienie_sliderReleased()
{
    State::getInstance().getGeneratorProstokatny().setDutyCycle(
        (double) ui->horizontalSlider_generator_wypelnienie->value() / 100.0);
}
void MainWindow::on_horizontalSlider_generator_wypelnienie_valueChanged(int value)
{
    ui->spinBox_generator_wypelnienie->setValue(ui->horizontalSlider_generator_wypelnienie->value());
}
void MainWindow::on_spinBox_generator_wypelnienie_valueChanged(int arg1)
{
    ui->horizontalSlider_generator_wypelnienie->setValue(ui->spinBox_generator_wypelnienie->value());
}

// reset symulacji
void MainWindow::on_pushButton_symulacja_reset_clicked()
{
    State::getInstance().getUAR().resetAll();
    State::getInstance().getGeneratorProstokatny().resetClock();
    State::getInstance().getGeneratorSinusoida().resetClock();

    delete this->lista_sterowanie;
    delete this->lista_uchyb;
    delete this->lista_wartosc_regulowana;
    delete this->lista_wartosc_zadana;

    this->lista_sterowanie = new QList<QPointF>();
    this->lista_uchyb = new QList<QPointF>();
    this->lista_wartosc_regulowana = new QList<QPointF>();
    this->lista_wartosc_zadana = new QList<QPointF>();

    miliseconds_of_simulation = 0;
}

// okno obserwacji - zmiany w wykresach
void MainWindow::on_horizontalSlider_symulacja_okno_obserwacji_valueChanged(int value)
{
    ui->spinBox_symulacja_okno_obserwacji->setValue(value);
}
void MainWindow::on_spinBox_symulacja_okno_obserwacji_valueChanged(int arg1)
{
    ui->horizontalSlider_symulacja_okno_obserwacji->setValue(arg1);
}
void MainWindow::on_spinBox_symulacja_okno_obserwacji_editingFinished()
{
    //TODO
}
void MainWindow::on_horizontalSlider_symulacja_okno_obserwacji_sliderReleased()
{
    //TODO
}

void MainWindow::on_checkBox_ograniczenia_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
        State::getInstance().getARX().disableLimits();
    else
        State::getInstance().getARX().enableLimits();
}

// PID - kontrolki całkowania i rozniczkowania
void MainWindow::on_pushButton_reset_pam_calk_clicked()
{
    State::getInstance().getPID().resetIntegrationPart();
}
void MainWindow::on_radioButton_stala_calkowania_przed_clicked()
{
    State::getInstance().getPID().setIntegrationType(IntegType::outside);
}
void MainWindow::on_radioButton_stala_calkowania_pod_clicked()
{
    State::getInstance().getPID().setIntegrationType(IntegType::insde);
}
void MainWindow::on_pushButton_reset_pam_roz_clicked()
{
    State::getInstance().getPID().resetDerrivativePart();
}

// PID - część proporcjonalna (K)
void MainWindow::on_horizontalSlider_pid_k_valueChanged(int value)
{
    ui->doubleSpinBox_pid_k->setValue((double) value / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_k_editingFinished()
{
    State::getInstance().getPID().setK(ui->doubleSpinBox_pid_k->value());
}
void MainWindow::on_horizontalSlider_pid_k_sliderReleased()
{
    State::getInstance().getPID().setK((double) ui->horizontalSlider_pid_k->value() / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_k_valueChanged(double arg1)
{
    ui->horizontalSlider_pid_k->setValue(arg1 * 100.0);
}

// PID - część całkująca (Ti)
void MainWindow::on_horizontalSlider_pid_Ti_valueChanged(int value)
{
    ui->doubleSpinBox_pid_Ti->setValue((double) value / 100.0);
}
void MainWindow::on_horizontalSlider_pid_Ti_sliderReleased()
{
    State::getInstance().getPID().setT_i((double) ui->horizontalSlider_pid_Ti->value() / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Ti_valueChanged(double arg1)
{
    ui->horizontalSlider_pid_Ti->setValue(arg1 * 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Ti_editingFinished()
{
    State::getInstance().getPID().setT_i(ui->doubleSpinBox_pid_Ti->value());
}

// PID - część różniczkująca (Td)
void MainWindow::on_horizontalSlider_pid_Td_valueChanged(int value)
{
    ui->doubleSpinBox_pid_Td->setValue((double) value / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Td_valueChanged(double arg1)
{
    ui->horizontalSlider_pid_Td->setValue(arg1 * 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Td_editingFinished()
{
    State::getInstance().getPID().setT_d(ui->doubleSpinBox_pid_Td->value());
}
void MainWindow::on_horizontalSlider_pid_Td_sliderReleased()
{
    State::getInstance().getPID().setT_d((double) ui->horizontalSlider_pid_Td->value() / 100.0);
}
