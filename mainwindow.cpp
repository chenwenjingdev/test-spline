#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qcustomplot.h"
#include "spline.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCustomPlot *customPlot = ui->widget;

    std::vector<double> X = {10.0, 20.0, 25.0, 30.0, 50.0}; // must be increasing
    std::vector<double> Y = {1550.0, 1552.0, 1555.0, 1550.0, 1551.0};

    // origin data
    {
        QVector<double> x, y;
        for (int i = 0; i < X.size(); ++i) {
            x.append(X[i]);
            y.append(Y[i]);
        }

        // create graph and assign data to it:
        customPlot->addGraph();
        customPlot->graph()->setPen(QColor(255, 0, 0));
        customPlot->graph()->setLineStyle(QCPGraph::lsLine);
        customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
        customPlot->graph()->setData(x, y);
        customPlot->graph()->rescaleAxes(true);

        // give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        customPlot->xAxis->setRange(8.0, 52.0);
        customPlot->yAxis->setRange(1545, 1560);
    }

    // cubic spline
    {
        tk::spline s(X, Y);
        QVector<double> x, y;
        for (int i = 10.0; i <= 50.0; i += 1) {
            x.append(i);
            y.append(s(i));
        }

        // create graph and assign data to it:
        customPlot->addGraph();
        customPlot->graph()->setPen(QColor(0, 0, 255));
        customPlot->graph()->setData(x, y);

        // give the axes some labels:
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        customPlot->xAxis->setRange(8.0, 52.0);
        customPlot->yAxis->setRange(1545, 1560);
    }

    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
