#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ElGamalSerpent.h"
#include "ElGamal.h"
#include "Serpent.h"
#include "ECB.h"
#include "CBC.h"
#include "CFB.h"
#include "CTR.h"
#include "OFB.h"
#include "RandomDelta.h"
#include "mode_selection.h"
#include "iv_gen.h"

class ElGamalSerpent : public QMainWindow
{
    Q_OBJECT

public:
    ElGamalSerpent(QWidget *parent = nullptr);
    ~ElGamalSerpent();

private slots:
       void on_keyGen_clicked();
       void on_openInputFile_clicked();
       void on_openOutputFile_clicked();
       void updateKeysWidget();
       void on_pushStart_clicked();

private:
    Ui::ElGamalSerpentClass ui;
    ElGamal elgamal;
    Serpent serpent;
};
