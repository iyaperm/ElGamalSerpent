#include "ElGamalSerpent.h"
#include <qmessagebox.h>
#include <qtimer.h>
#include <qfiledialog.h>
#include <qdebug.h>
#include <qprogressdialog.h>

ElGamalSerpent::ElGamalSerpent(QWidget *parent)
    : QMainWindow(parent), elgamal(TestType::SolovayStrassen), serpent()
{
    ui.setupUi(this);
    ui.selectModeLabel->setVisible(false);
    ui.modes->setVisible(false);
    ui.elgamalPrimeNumber->setVisible(false);
    ui.elgamalRoot->setVisible(false);
    ui.elgamalSecretKey->setVisible(false);
    ui.elgamalY->setVisible(false);
    ui.serpentIV->setVisible(false);
    ui.serpentKey->setVisible(false);
    connect(ui.Serpent, &QRadioButton::clicked, this, &ElGamalSerpent::updateKeysWidget);
    connect(ui.ElGamal, &QRadioButton::clicked, this, &ElGamalSerpent::updateKeysWidget);
    connect(ui.encryption, &QRadioButton::clicked, this, &ElGamalSerpent::updateKeysWidget);
    connect(ui.decryption, &QRadioButton::clicked, this, &ElGamalSerpent::updateKeysWidget);
}

ElGamalSerpent::~ElGamalSerpent()
{}

void ElGamalSerpent::on_keyGen_clicked() {
    if (ui.ElGamal->isChecked()) {
        Keys keys = elgamal.GetKey();

        QString p = QString::fromStdString(keys.prime_number.str());
        QString root = QString::fromStdString(keys.primitive_root.str());
        QString y = QString::fromStdString(keys.y.str());
        QString secret = QString::fromStdString(keys.secret_key.str());

        QMessageBox msgBox;
        msgBox.setText("Your keys: \nprime number = " + p + "\nroot = " + root + "\ny = " + y + "\nsecret key = " + secret);
        msgBox.exec();
    }
    else if (ui.Serpent->isChecked()) {
        std::pair<std::string, std::string> key_iv = serpent.KeyIvGen();
        QString key = QString::fromStdString(key_iv.first);
        QString iv = QString::fromStdString(key_iv.second);

        QMessageBox msgBox;
        msgBox.setText("Your keys: \nkey = " + key + "\niv = " + iv);
        msgBox.exec();
    }
}

void ElGamalSerpent::updateKeysWidget() {
    if (ui.ElGamal->isChecked() && ui.encryption->isChecked()) {
        ui.selectModeLabel->setVisible(false);
        ui.modes->setVisible(false);
        ui.serpentIV->setVisible(false);
        ui.serpentKey->setVisible(false);
        ui.elgamalPrimeNumber->setVisible(true);
        ui.elgamalRoot->setVisible(true);
        ui.elgamalY->setVisible(true);
        ui.elgamalSecretKey->setVisible(false);
    }
    else if (ui.ElGamal->isChecked() && ui.decryption->isChecked()) {
        ui.selectModeLabel->setVisible(false);
        ui.modes->setVisible(false);
        ui.serpentIV->setVisible(false);
        ui.serpentKey->setVisible(false);
        ui.elgamalPrimeNumber->setVisible(true);
        ui.elgamalRoot->setVisible(false);
        ui.elgamalSecretKey->setVisible(true);
        ui.elgamalY->setVisible(false);
    }
    else if (ui.Serpent->isChecked() && (ui.encryption->isChecked() || ui.decryption->isChecked())) {
        ui.selectModeLabel->setVisible(true);
        ui.modes->setVisible(true);
        ui.serpentIV->setVisible(true);
        ui.serpentKey->setVisible(true);
        ui.elgamalPrimeNumber->setVisible(false);
        ui.elgamalRoot->setVisible(false);
        ui.elgamalSecretKey->setVisible(false);
        ui.elgamalY->setVisible(false);
    }
}

void ElGamalSerpent::on_openInputFile_clicked() {
    QString input_file = QFileDialog::getOpenFileName();

    ui.lineInputFile->setText(input_file);
}

void ElGamalSerpent::on_openOutputFile_clicked() {
    QString output_file = QFileDialog::getExistingDirectory();

    ui.lineOutputFile->setText(output_file);
}

void ElGamalSerpent::on_pushStart_clicked() {
    if (ui.ElGamal->isChecked()) {
        if (ui.encryption->isChecked()) {
            QString input_file = ui.lineInputFile->text();
            QFileInfo input_file_info(input_file);
            QString input_format = input_file_info.suffix();
            std::wstring input_format_str = input_format.toStdWString();
            std::wstring input_file_str = input_file.toStdWString();
            QString output_file = ui.lineOutputFile->text();
            std::wstring output_file_str = output_file.toStdWString();
            output_file_str += L"/elgamal_encrypted." + input_format_str;
            QString prime_number = ui.elgamalPrimeNumber->text();
            cpp_int prime_number_int(prime_number.toStdString());
            QString root = ui.elgamalRoot->text();
            cpp_int root_int(root.toStdString());
            QString y = ui.elgamalY->text();
            cpp_int y_int(y.toStdString());
            if (input_file.isEmpty() || output_file.isEmpty() || prime_number.isEmpty() || root.isEmpty() || y.isEmpty()) {
                QMessageBox::warning(this, "Warning", "Fill in all fields.");
                return;
            }
            QFile file(input_file);
            qint64 file_size = file.size();
            QProgressDialog progress("Encrypting...", nullptr, 0, file_size, this);
            progress.setWindowModality(Qt::WindowModal);
            elgamal.encrypt_file(input_file_str, output_file_str, prime_number_int, root_int, y_int, progress);
            if (ui.deleteFile->isChecked()) {
                QFile::remove(input_file);
            }
        }
        else if (ui.decryption->isChecked()) {
            QString input_file = ui.lineInputFile->text();
            QFileInfo input_file_info(input_file);
            QString input_format = input_file_info.suffix();
            std::wstring input_format_str = input_format.toStdWString();
            std::wstring input_file_str = input_file.toStdWString();
            QString output_file = ui.lineOutputFile->text();
            std::wstring output_file_str = output_file.toStdWString();
            output_file_str += L"/elgamal_decrypted." + input_format_str;
            QString prime_number = ui.elgamalPrimeNumber->text();
            cpp_int prime_number_int(prime_number.toStdString());
            QString secret_key = ui.elgamalSecretKey->text();
            cpp_int secret_key_int(secret_key.toStdString());
            if (input_file.isEmpty() || output_file.isEmpty() || prime_number.isEmpty() || secret_key.isEmpty()) {
                QMessageBox::warning(this, "Warning", "Fill in all fields.");
                return;
            }
            QFile file(input_file);
            qint64 file_size = file.size() / 40;
            QProgressDialog progress("Decrypting...", nullptr, 0, file_size, this);
            progress.setWindowModality(Qt::WindowModal);
            elgamal.decrypt_file(input_file_str, output_file_str, prime_number_int, secret_key_int, progress);
            if (ui.deleteFile->isChecked()) {
                QFile::remove(input_file);
            }
        }
    }
    else if (ui.Serpent->isChecked()) {
        if (ui.encryption->isChecked()) {
            bool encrypt = true;
            QString input_file = ui.lineInputFile->text();
            QFileInfo input_file_info(input_file);
            QString input_format = input_file_info.suffix();
            std::wstring input_format_str = input_format.toStdWString();
            std::wstring input_file_str = input_file.toStdWString();
            QString output_file = ui.lineOutputFile->text();
            std::wstring output_file_str = output_file.toStdWString();
            output_file_str += L"/serpent_encrypted." + input_format_str;
            QString mode = ui.modes->currentText();
            std::string mode_str = mode.toStdString();
            QString key = ui.serpentKey->text();
            std::string key_str = key.toStdString();
            QString iv = ui.serpentIV->text();
            std::string iv_str = iv.toStdString();
            if (input_file.isEmpty() || output_file.isEmpty() || iv.isEmpty() || key.isEmpty()) {
                QMessageBox::warning(this, "Warning", "Fill in all fields.");
                return;
            }
            QFile file(input_file);
            qint64 file_size = file.size() / 16;
            QProgressDialog progress("Encrypting...", nullptr, 0, file_size, this);
            progress.setWindowModality(Qt::WindowModal);
            mode_selection(mode_str, key_str, iv_str, input_file_str, output_file_str, encrypt, progress);
            if (ui.deleteFile->isChecked()) {
                QFile::remove(input_file);
            }
        }
        else if (ui.decryption->isChecked()) {
            bool encrypt = false;
            QString input_file = ui.lineInputFile->text();
            QFileInfo input_file_info(input_file);
            QString input_format = input_file_info.suffix();
            std::wstring input_format_str = input_format.toStdWString();
            std::wstring input_file_str = input_file.toStdWString();
            QString output_file = ui.lineOutputFile->text();
            std::wstring output_file_str = output_file.toStdWString();
            output_file_str += L"/serpent_decrypted." + input_format_str;
            QString mode = ui.modes->currentText();
            std::string mode_str = mode.toStdString();
            QString key = ui.serpentKey->text();
            std::string key_str = key.toStdString();
            QString iv = ui.serpentIV->text();
            std::string iv_str = iv.toStdString();
            if (input_file.isEmpty() || output_file.isEmpty() || iv.isEmpty() || key.isEmpty()) {
                QMessageBox::warning(this, "Warning", "Fill in all fields.");
                return;
            }
            QFile file(input_file);
            qint64 file_size = file.size() / 16;
            QProgressDialog progress("Decrypting...", nullptr, 0, file_size, this);
            progress.setWindowModality(Qt::WindowModal);
            mode_selection(mode_str, key_str, iv_str, input_file_str, output_file_str, encrypt, progress);
            if (ui.deleteFile->isChecked()) {
                QFile::remove(input_file);
            }
        }
    }
    ui.lineInputFile->clear();
    ui.lineOutputFile->clear();
    ui.elgamalPrimeNumber->clear();
    ui.elgamalRoot->clear();
    ui.elgamalY->clear();
    ui.elgamalSecretKey->clear();
    ui.serpentKey->clear();
    ui.serpentIV->clear();
}
