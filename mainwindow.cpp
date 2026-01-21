#include "mainwindow.h"
#include "State.h"
#include "ui_mainwindow.h"
#include "dialogarx.h"
#include "BUILD_DEFINE.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , samples_count(40)
    , miliseconds_of_simulation(0)
    , uchyb(new ListWithExtremes())
    , lista_wartosc_zadana(new ListWithExtremes())
    , lista_wartosc_regulowana(new ListWithExtremes())
    , lista_sterowanie(new ListWithExtremes())
    , lista_sterowanie_P(new ListWithExtremes())
    , lista_sterowanie_I(new ListWithExtremes())
    , lista_sterowanie_D(new ListWithExtremes())

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


    {
        auto seria = new QLineSeries();
        seria->setName("Sterowanie");
        seria->setColor(QColor(30, 30, 220));
        chart_sterowanie->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Uchyb");
        seria->setColor(QColor(235, 0, 80));
        chart_uchyb->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Wartość zadana");
        seria->setColor(QColor(0, 200, 55));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Wartość regulowana");
        seria->setColor(QColor(130, 20, 150));
        chart_wartosc_zadana_i_regulowana->addSeries(seria);
    }
    {
        auto seria = new QLineSeries();
        seria->setName("Część proporcjonalna");
        seria->setColor(QColor(100, 200, 50));
        chart_skladowe_sterowania->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Część całkująca");
        seria->setColor(QColor(220, 220, 10));
        chart_skladowe_sterowania->addSeries(seria);

        seria = new QLineSeries();
        seria->setName("Część różniczkująca");
        seria->setColor(QColor(20, 10, 20));
        chart_skladowe_sterowania->addSeries(seria);

    }
    const qreal AXES_X_WIDTH = ui->spinBox_symulacja_interwal->value() / 1000.0 * 5.0;
    const qreal AXES_Y_HALFWIDTH = 1.0;

    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(0.0, AXES_X_WIDTH);
    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(-AXES_Y_HALFWIDTH, AXES_Y_HALFWIDTH);

    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(0.0, AXES_X_WIDTH);
    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(-AXES_Y_HALFWIDTH, AXES_Y_HALFWIDTH);

    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(0.0, AXES_X_WIDTH);
    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0)->setRange(-AXES_Y_HALFWIDTH, AXES_Y_HALFWIDTH);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setTitleText("Czas [s]");

    chart_skladowe_sterowania->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_skladowe_sterowania->axes(Qt::Horizontal).at(0)->setRange(0.0, AXES_X_WIDTH);
    chart_skladowe_sterowania->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_skladowe_sterowania->axes(Qt::Vertical).at(0)->setRange(-AXES_Y_HALFWIDTH, AXES_Y_HALFWIDTH);

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


    q_chart_view = new QChartView(chart_skladowe_sterowania);
    chart_skladowe_sterowania->setMargins(QMargins(0,0,0,0));
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    q_chart_view->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);


    q_chart_view = new QChartView(chart_wartosc_zadana_i_regulowana);
    chart_wartosc_zadana_i_regulowana->setMargins(QMargins(0,0,0,0));
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


    update_charts_timer = new QTimer(this);
    update_charts_timer->setInterval(250);
    update_charts_timer->start();
    QObject::connect(update_charts_timer, &QTimer::timeout, this, &MainWindow::updateCharts);

    updateUiFromState();
    on_spinBox_generator_okres_editingFinished();

}
void MainWindow::updateCharts()
{
    dynamic_cast<QLineSeries *>(chart_sterowanie->series().at(0))->replace(*lista_sterowanie->getList());

    dynamic_cast<QLineSeries *>(chart_uchyb->series().at(0))->replace(*uchyb->getList());

    dynamic_cast<QLineSeries *>(chart_wartosc_zadana_i_regulowana->series().at(0))->replace(*lista_wartosc_zadana->getList());
    dynamic_cast<QLineSeries *>(chart_wartosc_zadana_i_regulowana->series().at(1))->replace(*lista_wartosc_regulowana->getList());

    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(0))->replace(*lista_sterowanie_P->getList());
    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(1))->replace(*lista_sterowanie_I->getList());
    dynamic_cast<QLineSeries *>(chart_skladowe_sterowania->series().at(2))->replace(*lista_sterowanie_D->getList());


    constexpr const qreal ROZSZEZRENIE_SKALI_WYKRESOW_W_PIONIE = 0.1;

    // Osie pionowe - skalowanie
    qreal range_width_uchyb = (uchyb->max() - uchyb->min()) * ROZSZEZRENIE_SKALI_WYKRESOW_W_PIONIE;
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(uchyb->min() - range_width_uchyb, uchyb->max() + range_width_uchyb);


    qreal range_width_sterowanie = (lista_sterowanie->max() - lista_sterowanie->min()) * ROZSZEZRENIE_SKALI_WYKRESOW_W_PIONIE;
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(lista_sterowanie->min() - range_width_sterowanie, lista_sterowanie->max() + range_width_sterowanie);

    qreal range_width_wartosc_zadana_i_regulowana = (std::max(lista_wartosc_regulowana->max(), lista_wartosc_zadana->max())
                                                     - std::min(lista_wartosc_regulowana->min(), lista_wartosc_zadana->min()))
                                                    * ROZSZEZRENIE_SKALI_WYKRESOW_W_PIONIE;

    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical)
        .at(0)
        ->setRange(std::min(lista_wartosc_regulowana->min(), lista_wartosc_zadana->min())
                       - range_width_wartosc_zadana_i_regulowana,
                   std::max(lista_wartosc_regulowana->max(), lista_wartosc_zadana->max())
                       + range_width_wartosc_zadana_i_regulowana);

    qreal max_skladowych_sterowania = std::max(std::max(lista_sterowanie_P->max(), lista_sterowanie_I->max()),
                                               lista_sterowanie_D->max());
    qreal min_skladowych_sterowania = std::min(std::min(lista_sterowanie_P->min(), lista_sterowanie_I->min()),
                                               lista_sterowanie_D->min());
    qreal range_width_skladowych_sterowania = (max_skladowych_sterowania - min_skladowych_sterowania) * ROZSZEZRENIE_SKALI_WYKRESOW_W_PIONIE;

    chart_skladowe_sterowania->axes(Qt::Vertical)
        .at(0)
        ->setRange(min_skladowych_sterowania - range_width_skladowych_sterowania, max_skladowych_sterowania + range_width_skladowych_sterowania);

    // qDebug() << "P: " << lista_sterowanie_P->max()
    //     << "I: " << lista_sterowanie_I->max()
    //     << "D: " << lista_sterowanie_D->max();
}

void MainWindow::addToPlots(TickData tick_data)
{
#ifdef DEBUGING
    int debug_current_time = debug_timer.elapsed();
    debug_dialog->write(QString::number(debug_current_time - debug_last_time));
    debug_last_time = debug_current_time;
#endif
    const qint64 interwal_symulacji = State::getInstance().getSimmulationIntervalMS();
    const qint64 liczba_probek = (double) ui->spinBox_symulacja_okno_obserwacji->value()
                           / ((double) interwal_symulacji / 1000.0);

    const qreal seconds_of_simulation = (double) (miliseconds_of_simulation += interwal_symulacji) / 1000.0;

    lista_wartosc_zadana->appendLastValue(QPointF(seconds_of_simulation, tick_data.wartosc_zadana));
    lista_wartosc_regulowana->appendLastValue(QPointF(seconds_of_simulation, tick_data.wartosc_regulowana));
    uchyb->appendLastValue(QPointF(seconds_of_simulation, tick_data.uchyb));
    lista_sterowanie->appendLastValue(QPointF(seconds_of_simulation, static_cast<double>(tick_data.sterowanie)));
    lista_sterowanie_P->appendLastValue(QPointF(seconds_of_simulation, tick_data.sterowanie.Proportional));
    lista_sterowanie_I->appendLastValue(QPointF(seconds_of_simulation, tick_data.sterowanie.Integral));
    lista_sterowanie_D->appendLastValue(QPointF(seconds_of_simulation, tick_data.sterowanie.Derrivative));

    // Osie poziome - skalowanie
    constexpr const qreal LICZBA_DODATKOWYCH_PROBEK_PO_PRAWEJ = 4.0;

    qreal range_start = uchyb->getList()->front().x();
    qreal range_end = uchyb->getList()->back().x() + LICZBA_DODATKOWYCH_PROBEK_PO_PRAWEJ * (qreal) (interwal_symulacji) / 1000.0;

    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);
    chart_skladowe_sterowania->axes(Qt::Horizontal).at(0)->setRange(range_start, range_end);


    if (uchyb->getList()->count() > liczba_probek) {
        lista_wartosc_zadana->deleteFirstValue();
        lista_wartosc_regulowana->deleteFirstValue();
        uchyb->deleteFirstValue();
        lista_sterowanie->deleteFirstValue();
        lista_sterowanie_P->deleteFirstValue();
        lista_sterowanie_I->deleteFirstValue();
        lista_sterowanie_D->deleteFirstValue();
        if (uchyb->getList()->count() > liczba_probek) {
            lista_wartosc_zadana->deleteFirstValue();
            lista_wartosc_regulowana->deleteFirstValue();
            uchyb->deleteFirstValue();
            lista_sterowanie->deleteFirstValue();
            lista_sterowanie_P->deleteFirstValue();
            lista_sterowanie_I->deleteFirstValue();
            lista_sterowanie_D->deleteFirstValue();
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

    ui->spinBox_generator_okres->setMinimum(interwal_symulacji * 8);
    ui->spinBox_generator_okres->setMaximum(interwal_symulacji * 100);
    ui->spinBox_generator_okres->setSingleStep(interwal_symulacji);

    ui->horizontalSlider_generator_okres->setMinimum(interwal_symulacji * 8);
    ui->horizontalSlider_generator_okres->setMaximum(interwal_symulacji * 100);
    ui->horizontalSlider_generator_okres->setSingleStep(interwal_symulacji);
    ui->horizontalSlider_generator_okres->setPageStep(interwal_symulacji);
}

void MainWindow::on_spinBox_symulacja_interwal_editingFinished()
{
    State().setSimmulationIntervalMS(ui->spinBox_symulacja_interwal->value());


    recalculate_generator_period();
    emit ui->horizontalSlider_generator_okres->sliderReleased();
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

    this->lista_sterowanie->clear();
    this->uchyb->clear();
    this->lista_wartosc_regulowana->clear();
    this->lista_wartosc_zadana->clear();
    this->lista_sterowanie->clear();
    this->lista_sterowanie_P->clear();
    this->lista_sterowanie_I->clear();
    this->lista_sterowanie_D->clear();

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
    this->ui->doubleSpinBox_generator_bias->setValue(gen->getBias());
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


void MainWindow::on_checkBoxOgraniczenia_clicked()
{
    State().setARXLimitsEnabled(ui->checkBoxOgraniczenia->isChecked());
}


void MainWindow::on_doubleSpinBox_generator_bias_valueChanged(double arg1)
{
    ui->horizontalSlider_generator_bias->setValue(arg1 * 100);
}


void MainWindow::on_doubleSpinBox_generator_bias_editingFinished()
{
    State().setGeneratorSkladowaStala(ui->doubleSpinBox_generator_bias->value());
}


void MainWindow::on_horizontalSlider_generator_bias_sliderReleased()
{
    on_doubleSpinBox_generator_bias_editingFinished();
}


void MainWindow::on_horizontalSlider_generator_bias_valueChanged(int value)
{
    ui->doubleSpinBox_generator_bias->setValue(value / 100.0);
}

