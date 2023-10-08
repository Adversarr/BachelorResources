# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.4.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QHBoxLayout, QLabel,
    QMainWindow, QMenu, QMenuBar, QPlainTextEdit,
    QPushButton, QSizePolicy, QSpacerItem, QSpinBox,
    QStatusBar, QTextEdit, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1423, 857)
        self.actionOpen_File = QAction(MainWindow)
        self.actionOpen_File.setObjectName(u"actionOpen_File")
        self.actionSetup = QAction(MainWindow)
        self.actionSetup.setObjectName(u"actionSetup")
        self.actionExit = QAction(MainWindow)
        self.actionExit.setObjectName(u"actionExit")
        self.actionSetMiasPath = QAction(MainWindow)
        self.actionSetMiasPath.setObjectName(u"actionSetMiasPath")
        self.actionSetMicoPath = QAction(MainWindow)
        self.actionSetMicoPath.setObjectName(u"actionSetMicoPath")
        self.actionSetMuaPath = QAction(MainWindow)
        self.actionSetMuaPath.setObjectName(u"actionSetMuaPath")
        self.actionSetLinkerPath = QAction(MainWindow)
        self.actionSetLinkerPath.setObjectName(u"actionSetLinkerPath")
        self.actionAbout = QAction(MainWindow)
        self.actionAbout.setObjectName(u"actionAbout")
        self.actionSave = QAction(MainWindow)
        self.actionSave.setObjectName(u"actionSave")
        self.actionOpen_ASM_FIle = QAction(MainWindow)
        self.actionOpen_ASM_FIle.setObjectName(u"actionOpen_ASM_FIle")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        sizePolicy = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.centralwidget.sizePolicy().hasHeightForWidth())
        self.centralwidget.setSizePolicy(sizePolicy)
        self.verticalWidget_4 = QWidget(self.centralwidget)
        self.verticalWidget_4.setObjectName(u"verticalWidget_4")
        self.verticalWidget_4.setGeometry(QRect(0, 0, 1241, 781))
        self.mainLayout = QVBoxLayout(self.verticalWidget_4)
        self.mainLayout.setObjectName(u"mainLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.label_4 = QLabel(self.verticalWidget_4)
        self.label_4.setObjectName(u"label_4")

        self.verticalLayout_3.addWidget(self.label_4)

        self.textEdit = QTextEdit(self.verticalWidget_4)
        self.textEdit.setObjectName(u"textEdit")
        font = QFont()
        font.setFamilies([u"Consolas"])
        font.setPointSize(12)
        self.textEdit.setFont(font)

        self.verticalLayout_3.addWidget(self.textEdit)


        self.horizontalLayout.addLayout(self.verticalLayout_3)

        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.label = QLabel(self.verticalWidget_4)
        self.label.setObjectName(u"label")

        self.verticalLayout_2.addWidget(self.label)

        self.plainTextEdit_3 = QPlainTextEdit(self.verticalWidget_4)
        self.plainTextEdit_3.setObjectName(u"plainTextEdit_3")
        font1 = QFont()
        font1.setFamilies([u"Consolas"])
        font1.setPointSize(10)
        self.plainTextEdit_3.setFont(font1)

        self.verticalLayout_2.addWidget(self.plainTextEdit_3)

        self.label_2 = QLabel(self.verticalWidget_4)
        self.label_2.setObjectName(u"label_2")

        self.verticalLayout_2.addWidget(self.label_2)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.plainTextEdit = QPlainTextEdit(self.verticalWidget_4)
        self.plainTextEdit.setObjectName(u"plainTextEdit")
        self.plainTextEdit.setFont(font1)
        self.plainTextEdit.setReadOnly(True)

        self.horizontalLayout_2.addWidget(self.plainTextEdit)

        self.plainTextEdit_2 = QPlainTextEdit(self.verticalWidget_4)
        self.plainTextEdit_2.setObjectName(u"plainTextEdit_2")
        self.plainTextEdit_2.setFont(font1)
        self.plainTextEdit_2.setReadOnly(True)

        self.horizontalLayout_2.addWidget(self.plainTextEdit_2)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.horizontalLayout.addLayout(self.verticalLayout_2)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)

        self.label_3 = QLabel(self.verticalWidget_4)
        self.label_3.setObjectName(u"label_3")

        self.verticalLayout.addWidget(self.label_3)

        self.checkBox = QCheckBox(self.verticalWidget_4)
        self.checkBox.setObjectName(u"checkBox")
        self.checkBox.setChecked(True)
        self.checkBox.setTristate(False)

        self.verticalLayout.addWidget(self.checkBox)

        self.checkBox_2 = QCheckBox(self.verticalWidget_4)
        self.checkBox_2.setObjectName(u"checkBox_2")
        self.checkBox_2.setChecked(True)

        self.verticalLayout.addWidget(self.checkBox_2)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_7 = QLabel(self.verticalWidget_4)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_4.addWidget(self.label_7)

        self.spinBox_2 = QSpinBox(self.verticalWidget_4)
        self.spinBox_2.setObjectName(u"spinBox_2")
        self.spinBox_2.setMaximum(2)
        self.spinBox_2.setValue(2)

        self.horizontalLayout_4.addWidget(self.spinBox_2)


        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_6 = QLabel(self.verticalWidget_4)
        self.label_6.setObjectName(u"label_6")

        self.horizontalLayout_3.addWidget(self.label_6)

        self.spinBox = QSpinBox(self.verticalWidget_4)
        self.spinBox.setObjectName(u"spinBox")
        self.spinBox.setMaximum(32)
        self.spinBox.setValue(5)

        self.horizontalLayout_3.addWidget(self.spinBox)


        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.pushButton = QPushButton(self.verticalWidget_4)
        self.pushButton.setObjectName(u"pushButton")

        self.verticalLayout.addWidget(self.pushButton)

        self.pushButton_3 = QPushButton(self.verticalWidget_4)
        self.pushButton_3.setObjectName(u"pushButton_3")

        self.verticalLayout.addWidget(self.pushButton_3)

        self.pushButton_2 = QPushButton(self.verticalWidget_4)
        self.pushButton_2.setObjectName(u"pushButton_2")

        self.verticalLayout.addWidget(self.pushButton_2)

        self.pushButton_4 = QPushButton(self.verticalWidget_4)
        self.pushButton_4.setObjectName(u"pushButton_4")

        self.verticalLayout.addWidget(self.pushButton_4)


        self.horizontalLayout.addLayout(self.verticalLayout)


        self.mainLayout.addLayout(self.horizontalLayout)

        self.label_5 = QLabel(self.verticalWidget_4)
        self.label_5.setObjectName(u"label_5")

        self.mainLayout.addWidget(self.label_5)

        self.textEdit_4 = QTextEdit(self.verticalWidget_4)
        self.textEdit_4.setObjectName(u"textEdit_4")
        self.textEdit_4.setMinimumSize(QSize(0, 150))
        self.textEdit_4.setMaximumSize(QSize(16777215, 150))
        self.textEdit_4.setFont(font1)
        self.textEdit_4.setReadOnly(True)

        self.mainLayout.addWidget(self.textEdit_4)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1423, 25))
        self.menuOpen_File = QMenu(self.menubar)
        self.menuOpen_File.setObjectName(u"menuOpen_File")
        self.menuOptions = QMenu(self.menubar)
        self.menuOptions.setObjectName(u"menuOptions")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuOpen_File.menuAction())
        self.menubar.addAction(self.menuOptions.menuAction())
        self.menuOpen_File.addAction(self.actionOpen_File)
        self.menuOpen_File.addAction(self.actionOpen_ASM_FIle)
        self.menuOpen_File.addAction(self.actionSave)
        self.menuOpen_File.addAction(self.actionAbout)
        self.menuOpen_File.addAction(self.actionExit)
        self.menuOptions.addSeparator()
        self.menuOptions.addAction(self.actionSetMiasPath)
        self.menuOptions.addAction(self.actionSetMicoPath)
        self.menuOptions.addAction(self.actionSetMuaPath)
        self.menuOptions.addAction(self.actionSetLinkerPath)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Mide: Minimal ide for Minisys1a", None))
        self.actionOpen_File.setText(QCoreApplication.translate("MainWindow", u"Open C File", None))
#if QT_CONFIG(shortcut)
        self.actionOpen_File.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+O", None))
#endif // QT_CONFIG(shortcut)
        self.actionSetup.setText(QCoreApplication.translate("MainWindow", u"Setup", None))
        self.actionExit.setText(QCoreApplication.translate("MainWindow", u"Exit", None))
#if QT_CONFIG(shortcut)
        self.actionExit.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+Q", None))
#endif // QT_CONFIG(shortcut)
        self.actionSetMiasPath.setText(QCoreApplication.translate("MainWindow", u"Set Mias Path", None))
        self.actionSetMicoPath.setText(QCoreApplication.translate("MainWindow", u"Set Mico Path", None))
        self.actionSetMuaPath.setText(QCoreApplication.translate("MainWindow", u"Set Mua Path", None))
        self.actionSetLinkerPath.setText(QCoreApplication.translate("MainWindow", u"Set Linker Path", None))
        self.actionAbout.setText(QCoreApplication.translate("MainWindow", u"About", None))
        self.actionSave.setText(QCoreApplication.translate("MainWindow", u"Save", None))
#if QT_CONFIG(shortcut)
        self.actionSave.setShortcut(QCoreApplication.translate("MainWindow", u"Ctrl+S", None))
#endif // QT_CONFIG(shortcut)
        self.actionOpen_ASM_FIle.setText(QCoreApplication.translate("MainWindow", u"Open ASM File", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"C source file", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"asm output", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"coe output(d/p)", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"Options", None))
        self.checkBox.setText(QCoreApplication.translate("MainWindow", u"Verbose", None))
        self.checkBox_2.setText(QCoreApplication.translate("MainWindow", u"Sort", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"Opt", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"COM:", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"Compile", None))
#if QT_CONFIG(tooltip)
        self.pushButton_3.setToolTip(QCoreApplication.translate("MainWindow", u"<html><head/><body><p>asm</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        self.pushButton_3.setWhatsThis(QCoreApplication.translate("MainWindow", u"<html><head/><body><p>assemble</p><p><br/></p></body></html>", None))
#endif // QT_CONFIG(whatsthis)
        self.pushButton_3.setText(QCoreApplication.translate("MainWindow", u"Assemble", None))
        self.pushButton_2.setText(QCoreApplication.translate("MainWindow", u"Link", None))
        self.pushButton_4.setText(QCoreApplication.translate("MainWindow", u"Download", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"Log:", None))
        self.menuOpen_File.setTitle(QCoreApplication.translate("MainWindow", u"Open", None))
        self.menuOptions.setTitle(QCoreApplication.translate("MainWindow", u"Options", None))
    # retranslateUi

