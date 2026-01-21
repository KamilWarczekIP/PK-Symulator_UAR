#include "mainwindow.h"
#include "State.h"
#include "ui_mainwindow.h"
#include "dialogarx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , samples_count(40)
    , miliseconds_of_simulation(0)
{
    ui->setupUi(this);
    this->ui->centralwidget->setLayout(ui->horizontalLayout_13);
    debug_dialog = new DialogDebug(this);

    chart_sterowanie = new QChart();
    // chart_sterowanie->setTitle(tr("Sterowanie (Wyjście z regulatora)"));
    // chart_sterowanie->legend()->hide();

    chart_uchyb = new QChart();
    // chart_uchyb->setTitle(tr("Uchyb"));
    // chart_uchyb->legend()->hide();

    chart_wartosc_zadana_i_regulowana = new QChart();
    // chart_wartosc_zadana_i_regulowana->setTitle(tr("Wartość zadana i regulowana"));
    // chart_wartosc_zadana_i_regulowana->legend()->hide();

    chart_skladowe_sterowania = new QChart();
    // chart_wszystko->setTitle(tr("Wszystko"));

    lista_sterowanie = new QList<QPointF>();
    lista_uchyb = new QList<QPointF>();
    lista_wartosc_zadana = new QList<QPointF>();
    lista_wartosc_regulowana = new QList<QPointF>();
    lista_sterowanie_P = new QList<QPointF>();
    lista_sterowanie_I = new QList<QPointF>();
    lista_sterowanie_D = new QList<QPointF>();

    {
        auto seria = new QLineSeries();
        seria->setName("Sterowanie");
        seria->setColor(QColor(30, 30, 220));
        chart_sterowanie->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Uchyb");
        seria->setColor(QColor(185, 0, 80));
        chart_uchyb->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Wartość zadana");
        seria->setColor(QColor(0, 180, 55));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Wartość regulowana");
        seria->setColor(QColor(130, 20, 150));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Część proporcjonalna");
        seria->setColor(QColor(0, 180, 55));
        chart_skladowe_sterowania->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Część różniczkująca");
        seria->setColor(QColor(185, 0, 80));
        chart_skladowe_sterowania->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Część całkująca");
        seria->setColor(QColor(130, 20, 150));
        chart_skladowe_sterowania->addSeries(seria);
    }

    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(0.0, 1.0);
    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(0.0, 1.0);
    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(0.0, 1.0);
    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_skladowe_sterowania->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_skladowe_sterowania->axes(Qt::Horizontal).at(0)->setRange(0.0, 1.0);
    chart_skladowe_sterowania->axes(Qt::Horizontal).at(0)->setTitleText("Czas [s]");
    chart_skladowe_sterowania->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_skladowe_sterowania->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

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

    chart_skladowe_sterowania->series().at(0)->attachAxis(chart_skladowe_sterowania->axes(Qt::Horizontal).at(0));
    chart_skladowe_sterowania->series().at(0)->attachAxis(chart_skladowe_sterowania->axes(Qt::Vertical).at(0));
    chart_skladowe_sterowania->series().at(1)->attachAxis(chart_skladowe_sterowania->axes(Qt::Horizontal).at(0));
    chart_skladowe_sterowania->series().at(1)->attachAxis(chart_skladowe_sterowania->axes(Qt::Vertical).at(0));
    chart_skladowe_sterowania->series().at(2)->attachAxis(chart_skladowe_sterowania->axes(Qt::Horizontal).at(0));
    chart_skladowe_sterowania->series().at(2)->attachAxis(chart_skladowe_sterowania->axes(Qt::Vertical).at(0));

    // chart_sterowanie->series().at(0)->setUseOpenGL(true);
    // chart_uchyb->series().at(0)->setUseOpenGL(true);
    // chart_wartosc_zadana_i_regulowana->series().at(0)->setUseOpenGL(true);
    // chart_wartosc_zadana_i_regulowana->series().at(1)->setUseOpenGL(true);
    // chart_skladowe_sterowania->series().at(0)->setUseOpenGL(true);
    // chart_skladowe_sterowania->series().at(1)->setUseOpenGL(true);
    // chart_skladowe_sterowania->series().at(2)->setUseOpenGL(true);


    auto q_chart_view = new QChartView(chart_sterowanie);
    chart_sterowanie->setMargins(QMargins(0,0,0,0));
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);


    q_chart_view = new QChartView(chart_uchyb);
    chart_uchyb->setMargins(QMargins(0,0,0,0));
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_wartosc_zadana_i_regulowana);
    chart_wartosc_zadana_i_regulowana->setMargins(QMargins(0,0,0,0));
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_skladowe_sterowania);
    chart_skladowe_sterowania->setMargins(QMargins(0,0,0,0));
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 4);

    State().setOutputCallback(std::bind(&MainWindow::addToPlots, this, std::placeholders::_1));

    debug_timer.start();
    debug_last_time = 0;

    QObject::connect(ui->actionzapisz_ustawienia, &QAction::triggered, this, &MainWindow::zapiszDoPliku);
    QObject::connect(ui->actionwczytaj_ustawienia, &QAction::triggered, this, &MainWindow::wczytajZPliku);
    QObject::connect(ui->actionokno_debugowania, &QAction::triggered, this, &MainWindow::przelaczOknoDebugowania);

    on_spinBox_generator_okres_editingFinished();
    updateUiFromState();

    update_charts_timer = new QTimer(this);
    update_charts_timer->setInterval(500);
    update_charts_timer->start();
    QObject::connect(update_charts_timer, &QTimer::timeout, this, &MainWindow::updateCharts);

}
void MainWindow::updateCharts()
{
    dynamic_cast<QLineSeries *>(chart_sterowanie->series().at(0))->replace(*lista_sterowanie);

    dynamic_cast<QLineSeries *>(chart_uchyb->series().at(0))->replace(*lista_uchyb);

    dynamic_cast<QLineSeries *>(chart_wartosc_zadana_i_regulowana->series().at(0))->replace(*lista_wartosc_zadana);
    dynamic_cast<QLineSeries *>(chart_wartosc_zadana_i_regulowana->series().at(1))->replace(*lista_wartosc_regulowana);

    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(0))->replace(*lista_sterowanie_P);
    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(1))->replace(*lista_sterowanie_I);
    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(2))->replace(*lista_sterowanie_D);
}
void MainWindow::addToPlots(TickData tick_data)
{
    int debug_current_time = debug_timer.elapsed();
    debug_dialog->write(QString::number(debug_current_time - debug_last_time));
    debug_last_time = debug_current_time;
    qint64 interwal_symulacji = State::getInstance().getSimmulationIntervalMS();
    qint64 liczba_probek = (double) ui->spinBox_symulacja_okno_obserwacji->value()
                           / ((double) interwal_symulacji / 1000.0);

    qreal seconds_of_simulation = (double) (miliseconds_of_simulation += interwal_symulacji) / 1000.0;

    lista_wartosc_zadana->append(QPointF(seconds_of_simulation, tick_data.wartosc_zadana));
    lista_wartosc_regulowana->append(QPointF(seconds_of_simulation, tick_data.wartosc_regulowana));
    lista_uchyb->append(QPointF(seconds_of_simulation, tick_data.uchyb));
    lista_sterowanie->append(QPointF(seconds_of_simulation, static_cast<double>(tick_data.sterowanie)));
    lista_sterowanie_P->append(QPointF(seconds_of_simulation, static_cast<double>(tick_data.sterowanie.Proportional)));
    lista_sterowanie_I->append(QPointF(seconds_of_simulation, static_cast<double>(tick_data.sterowanie.Integral)));
    lista_sterowanie_D->append(QPointF(seconds_of_simulation, static_cast<double>(tick_data.sterowanie.Derrivative)));

    // Osie poziome - skalowanie
    constexpr const qreal LICZBA_DODATKOWYCH_PROBEK_PO_PRAWEJ = 4.0;
    //qreal range_start = seconds_of_simulation - (qreal) (liczba_probek * interwal_symulacji) / 1000.0;
    //qreal range_end = seconds_of_simulation + LICZBA_DODATKOWYCH_PROBEK_PO_PRAWEJ * (qreal) (interwal_symulacji) / 1000.0;


    qreal range_start = lista_uchyb->front().x();
    qreal range_end = lista_uchyb->back().x() + LICZBA_DODATKOWYCH_PROBEK_PO_PRAWEJ * (qreal) (interwal_symulacji) / 1000.0;

    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_skladowe_sterowania->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);

    // Osie pionowe - skalowanie
    qreal max_uchyb = 0.0;
    qreal min_uchyb = 0.0;
    for (QList<QPointF>::iterator point = lista_uchyb->begin(); point != lista_uchyb->end(); point = std::next<>(point))
    {
        if (point->y() > max_uchyb)
            max_uchyb = point->y();
        else if (point->y() < min_uchyb)
            min_uchyb = point->y();
    }
    qreal range_width_uchyb = (max_uchyb - min_uchyb) * 0.1;
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(min_uchyb - range_width_uchyb, max_uchyb + range_width_uchyb);

    qreal max_sterowanie = 0.0;
    qreal min_sterowanie = 0.0;
    for (QList<QPointF>::iterator point = lista_sterowanie->begin(); point != lista_sterowanie->end(); point = std::next<>(point))
    {
        if (point->y() > max_sterowanie)
            max_sterowanie = point->y();
        else if (point->y() < min_sterowanie)
            min_sterowanie = point->y();
    }
    qreal range_width_sterowanie = (max_sterowanie - min_sterowanie) * 0.1;
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(min_sterowanie - range_width_sterowanie, max_sterowanie + range_width_sterowanie);

    qreal max_wartosc_zadana = 0.0;
    qreal min_wartosc_zadana = 0.0;
    for (QList<QPointF>::iterator point = lista_wartosc_zadana->begin();
         point != lista_wartosc_zadana->end();
         point = std::next<>(point))
    {
        if (point->y() > max_wartosc_zadana)
            max_wartosc_zadana = point->y();
        else if (point->y() < min_wartosc_zadana)
            min_wartosc_zadana = point->y();
    }

    qreal max_wartosc_regulowana = 0.0;
    qreal min_wartosc_regulowana = 0.0;
    for (QList<QPointF>::iterator point = lista_wartosc_regulowana->begin();
         point != lista_wartosc_regulowana->end();
         point = std::next<>(point))
    {
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

    chart_skladowe_sterowania->axes(Qt::Vertical)
        .at(0)
        ->setRange(min_wszystko - range_width_wszystko, max_wszystko + range_width_wszystko);

    if (lista_wartosc_zadana->count() > liczba_probek) {
        lista_wartosc_zadana->removeFirst();
        lista_wartosc_regulowana->removeFirst();
        lista_uchyb->removeFirst();
        lista_sterowanie->removeFirst();
        if (lista_wartosc_zadana->count() > liczba_probek) {
            lista_wartosc_zadana->removeFirst();
            lista_wartosc_regulowana->removeFirst();
            lista_uchyb->removeFirst();
            lista_sterowanie->removeFirst();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_symulacja_star_stop_released()
{
    if (State().getSimmulationRunning())
    {
        State().setSimmulationRunning(false);
        ui->pushButton_symulacja_star_stop->setText(tr("START"));
    }
    else
    {
        State().setSimmulationRunning(true);
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

void MainWindow::recalculate_generator_period()
{

    uint32_t interwal_symulacji = State::getInstance().getSimmulationIntervalMS();
    int new_generator_okres_value = ui->spinBox_generator_okres->value() / interwal_symulacji * interwal_symulacji;
    if(ui->spinBox_generator_okres->value() % interwal_symulacji > interwal_symulacji / 2)
        new_generator_okres_value += interwal_symulacji;

    ui->spinBox_generator_okres->setValue(new_generator_okres_value);
}

void MainWindow::on_spinBox_symulacja_interwal_editingFinished()
{
    State().setSimmulationIntervalMS(ui->spinBox_symulacja_interwal->value());

    uint32_t interwal_symulacji = State().getSimmulationIntervalMS();


    recalculate_generator_period();

    ui->spinBox_generator_okres->setMinimum(interwal_symulacji * 4);
    ui->spinBox_generator_okres->setMaximum(interwal_symulacji * 100);
    ui->spinBox_generator_okres->setSingleStep(interwal_symulacji);

    ui->horizontalSlider_generator_okres->setMinimum(interwal_symulacji * 4);
    ui->horizontalSlider_generator_okres->setMaximum(interwal_symulacji * 100);
    ui->horizontalSlider_generator_okres->setSingleStep(interwal_symulacji);
    ui->horizontalSlider_generator_okres->setPageStep(interwal_symulacji);
}
void MainWindow::on_horizontalSlider_symulacja_interwal_sliderReleased()
{
    on_spinBox_symulacja_interwal_editingFinished();
}

//Włączanie okna ustawień obiektu ARX
void MainWindow::on_pushButton_dostosuj_parametry_clicked()
{
    DialogArx arxDialog(this);
    arxDialog.exec();
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
    State().setGeneneratorAmplitude(ui->doubleSpinBox_generator_amplituda->value());
}
void MainWindow::on_verticalSlider_generator_amplituda_sliderReleased()
{
    on_doubleSpinBox_generator_amplituda_editingFinished();
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
    recalculate_generator_period();
    State().setGeneneratorPeriodMS(ui->spinBox_generator_okres->value());
}
void MainWindow::on_horizontalSlider_generator_okres_sliderReleased()
{
    on_spinBox_generator_okres_editingFinished();
}

//Zmiana używanego generatora
void MainWindow::on_comboBox_generator_typ_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Prostokątny")
    {
        ui->horizontalSlider_generator_wypelnienie->setEnabled(true);
        ui->spinBox_generator_wypelnienie->setEnabled(true);
        State().setGenerator(State::TypGeneratora::Prostokatny);
    }
    else
    {
        ui->horizontalSlider_generator_wypelnienie->setEnabled(false);
        ui->spinBox_generator_wypelnienie->setEnabled(false);
        if (arg1 == "Sinusoida")
            State().setGenerator(State::TypGeneratora::Sinusoidalny);
        else if (arg1 == "Ręczny") // TODO: dodac generator ręczny
            State().setGenerator(State::TypGeneratora::Reczny);
    }
}

// Wypelnienie generatora (P)
void MainWindow::on_spinBox_generator_wypelnienie_editingFinished()
{
    State().setGeneneratorDutyCycle(
        (double) ui->spinBox_generator_wypelnienie->value() / 100.0);
}
void MainWindow::on_horizontalSlider_generator_wypelnienie_sliderReleased()
{
    on_spinBox_generator_wypelnienie_editingFinished();
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
    State().resetSimmulation();

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

void MainWindow::on_checkBoxOgraniczenia_checkStateChanged(const Qt::CheckState &arg1)
{
    State().setARXLimitsEnabled(arg1 == Qt::Checked);
}

// PID - kontrolki całkowania i rozniczkowania
void MainWindow::on_radioButton_stala_calkowania_przed_clicked()
{
    State().setPIDIntegrationType(IntegType::outside);
}
void MainWindow::on_radioButton_stala_calkowania_pod_clicked()
{
    State().setPIDIntegrationType(IntegType::insde);
}
void MainWindow::on_pushButton_reset_pam_calk_clicked()
{
    State().resetPIDIntegration();
}
void MainWindow::on_pushButton_reset_pam_roz_clicked()
{
    State().resetPIDDerrivative();
}

// PID - część proporcjonalna (K)
void MainWindow::on_horizontalSlider_pid_k_valueChanged(int value)
{
    ui->doubleSpinBox_pid_k->setValue((double) value / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_k_editingFinished()
{
    State().setPIDProportional(ui->doubleSpinBox_pid_k->value());
}
void MainWindow::on_doubleSpinBox_pid_k_valueChanged(double arg1)
{
    ui->horizontalSlider_pid_k->setValue(arg1 * 100.0);
}
void MainWindow::on_horizontalSlider_pid_k_sliderReleased()
{
    on_doubleSpinBox_pid_k_editingFinished();
}

// PID - część całkująca (Ti)
void MainWindow::on_horizontalSlider_pid_Ti_valueChanged(int value)
{
    ui->doubleSpinBox_pid_Ti->setValue((double) value / 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Ti_valueChanged(double arg1)
{
    ui->horizontalSlider_pid_Ti->setValue(arg1 * 100.0);
}
void MainWindow::on_doubleSpinBox_pid_Ti_editingFinished()
{
    State().setPIDIntegration(ui->doubleSpinBox_pid_Ti->value());
}
void MainWindow::on_horizontalSlider_pid_Ti_sliderReleased()
{
    on_doubleSpinBox_pid_Ti_editingFinished();
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
    State().setPIDDerrivative(ui->doubleSpinBox_pid_Td->value());
}
void MainWindow::on_horizontalSlider_pid_Td_sliderReleased()
{
    on_doubleSpinBox_pid_Td_editingFinished();
}

void MainWindow::zapiszDoPliku()
{
    State().saveToFile(QFileDialog::getSaveFileName(this, tr("Zapisz konfigurację"), QDir::homePath(), tr("JSON (*.json)")).toStdString());
}
void MainWindow::wczytajZPliku()
{
    State().readFromFile(QFileDialog::getOpenFileName(this, tr("Wczytaj konfigurację"), QDir::homePath(), tr("JSON (*.json)")).toStdString());
    updateUiFromState();
}

void MainWindow::updateUiFromState()
{
    auto [arx, pid, typ_generatora, gen_sinusoida, gen_prostokatny] = State().getAppState();
    this->ui->checkBoxOgraniczenia->setCheckState(arx->getLimitsActive() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);


    this->ui->doubleSpinBox_pid_k->setValue(pid->getK());
    this->ui->doubleSpinBox_pid_Ti->setValue(pid->getT_i());
    this->ui->doubleSpinBox_pid_Td->setValue(pid->getT_d());

    this->ui->radioButton_stala_calkowania_pod->setChecked(pid->getIntegrationType() == IntegType::insde);
    this->ui->radioButton_stala_calkowania_przed->setChecked(pid->getIntegrationType() == IntegType::outside);

    const Generator* gen;
    switch(typ_generatora)
    {
    case State::TypGeneratora::Sinusoidalny:
        gen = gen_sinusoida;
        this->ui->comboBox_generator_typ->setCurrentIndex(0);
        break;
    case State::TypGeneratora::Prostokatny:
        gen = gen_prostokatny;
        this->ui->comboBox_generator_typ->setCurrentIndex(1);
        break;
    case State::TypGeneratora::Reczny:
        gen = gen_prostokatny; //TODO
        this->ui->comboBox_generator_typ->setCurrentIndex(2);
        break;
    }
    this->ui->doubleSpinBox_generator_amplituda->setValue(gen->getAmplitude());
    this->ui->spinBox_generator_okres->setValue(gen->getSamplesPerCycle() * State().getSimmulationIntervalMS());
    this->ui->spinBox_generator_wypelnienie->setValue(gen_prostokatny->getDutyCycle() * 100.0);

    this->ui->spinBox_symulacja_interwal->setValue(State().getSimmulationIntervalMS());
}

void MainWindow::przelaczOknoDebugowania()
{
    if(debug_dialog->isHidden())
        debug_dialog->show();
    else
        debug_dialog->hide();
}
