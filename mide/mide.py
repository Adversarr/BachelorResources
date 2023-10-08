# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtWidgets import QApplication, QMainWindow
from PySide6 import QtCore, QtGui, QtWidgets
import os
from PySide6.QtGui import QFont, QIcon, QSyntaxHighlighter, QTextCharFormat
# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_MainWindow


import subprocess
import platform

plat = platform.system()


QRegularExpression = QtCore.QRegularExpression
Qt = QtCore.Qt
QIODevice = QtCore.QIODevice


class MyHighlighter(QSyntaxHighlighter):
    def highlightBlock(self, text):
        myClassFormat = QTextCharFormat()
        myClassFormat.setFontWeight(QFont.Bold)
        myClassFormat.setForeground(Qt.darkMagenta)
        expression = QRegularExpression(
            "\\b(signed|union|struct|int|float|double|char|short|long|unsigned|void|bool)\\b")
        i = expression.globalMatch(text)
        while i.hasNext():
            match = i.next()
            self.setFormat(match.capturedStart(),
                           match.capturedLength(), myClassFormat)
        myClassFormat = QTextCharFormat()
        myClassFormat.setFontWeight(QFont.Bold)
        myClassFormat.setForeground(Qt.blue)
        expression = QRegularExpression(
            "\\b(class|for|while|do|return|static|volatile|if|else)\\b")
        i = expression.globalMatch(text)
        while i.hasNext():
            match = i.next()
            self.setFormat(match.capturedStart(),
                           match.capturedLength(), myClassFormat)

        myClassFormat = QTextCharFormat()
        myClassFormat.setFontItalic(True)
        myClassFormat.setForeground(Qt.blue)
        expression = QRegularExpression("\\$\\((0x)?[0-9]+\\)")
        i = expression.globalMatch(text)
        while i.hasNext():
            match = i.next()
            self.setFormat(match.capturedStart(),
                           match.capturedLength(), myClassFormat)

        multiLineCommentFormat = QTextCharFormat()
        multiLineCommentFormat.setForeground(Qt.red)
        startExpression = QRegularExpression("/\\*")
        s = startExpression.match(text)
        endExpression = QRegularExpression("\\*/")
        self.setCurrentBlockState(0)
        startIndex = -1
        if self.previousBlockState() != 1 and s.hasMatch():
            startIndex = s.capturedStart()
            print(startIndex)
        while startIndex >= 0:
            t = endExpression.match(text, startIndex)
            endIndex = t.capturedStart()
            print(startIndex - endIndex)
            commentLength = int()
            if endIndex == -1:
                self.setCurrentBlockState(1)
                commentLength = len(text) - startIndex
            else:
                commentLength = endIndex - startIndex + t.capturedLength()
            self.setFormat(startIndex, commentLength, multiLineCommentFormat)
            if endIndex == -1:
                break
            else:
                s = startExpression.match(text, endIndex)
                startIndex = -1
                if s.hasMatch():
                    startIndex = s.capturedStart()


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.actionOpen_File.triggered.connect(self.on_actionOpen_File)
        self.ui.actionSave.triggered.connect(self.on_actionSave)
        self.ui.actionAbout.triggered.connect(self.on_actionAbout)
        self.ui.actionExit.triggered.connect(self.on_actionExit)
        self.ui.pushButton.pressed.connect(self.on_compile)
        self.ui.pushButton_2.pressed.connect(self.on_link)
        self.ui.pushButton_3.pressed.connect(self.on_asm)
        self.ui.checkBox.stateChanged.connect(self.on_verbose_change)
        self.ui.pushButton_4.pressed.connect(self.on_download)

        self.ui.actionOpen_ASM_FIle.triggered.connect(self.on_action_openasm)

        self.syntax_highlighter = MyHighlighter(self.ui.textEdit.document())
        self.mias_path = "mias.exe"
        self.bios_path = "bios.s"
        self.mico_path = "mico.exe"
        self.mua_path = "mua.exe"
        self.verbose_mode = True
        self.linker_path = "milk.exe"
        self.working_dir = os.getcwd()
        self.opened_file = "temporary.c"
        self.doLog(f"Working Dir = {self.working_dir}")
        self.update_title()
        self.build_dir = "build"
        icon = QIcon("Mua-Logo-Blu.png")
        self.setWindowIcon(icon)

        if not plat == 'Windows':
            self.change_font('Source Code Pro')

    def change_font(self, font_name):
        font = QtGui.QFont(font_name)
        self.ui.plainTextEdit.setFont(font)
        self.ui.plainTextEdit_2.setFont(font)
        self.ui.plainTextEdit_3.setFont(font)
        self.ui.textEdit.setFont(font)
        self.ui.textEdit_4.setFont(font)

    def on_download(self):
        print("Download to board!")
        if plat != "Windows":
            self.doLog("MUA Downloader only available under Windows!")

        output = os.path.join(self.working_dir, self.build_dir, 'uart_out.txt')
        uart_out = QtCore.QFile(output)
        if not uart_out.exists():
            self.doLog(
                "Error: cannot find uart_out.txt in build dir ({self.build_dir}). Recompile and assemble source file, or place uart_out.txt in build dir.")
            return
        com = self.ui.spinBox.value()
        args = [self.mua_path, '-f', output, ]

        self.doLog(
            f"==================================\nMua download begin (COM = {com})")
        if self.verbose_mode:
            args.append('-v')
            self.doLog(f"Mua download with {args}")

        p = subprocess.Popen(args, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, shell=True)

        try:
            out, err = p.communicate(timeout=30.0)

            if p.returncode == 0:
                self.doLog("Mua downloader exit success!")
            elif p.returncode == 127:
                self.doLog("Mua downloader not found!")
                return
            else:
                self.doLog(
                    f"Mua downloader exit with code={p.returncode}, turn on verbose mode and check console log for more details")
            if self.verbose_mode:
                err = err.decode('utf-8', 'ignore')
                err_l = err.splitlines()
                out = out.decode('utf-8', 'ignore')
                out_l = out.splitlines()
                err_l.extend(out_l)
                for l in err_l:
                    self.doLog(l)

        except OSError as ose:
            self.doLog(f"OsError: {ose}, please check the path for mua!")
        except subprocess.TimeoutExpired:
            self.doLog(
                f"Time out expired, flashing not finished. Consider whether the board is under DOWNLOAD state!")
            p.kill()
        self.doLog("Mua download done.")

    def on_verbose_change(self):
        self.verbose_mode = self.ui.checkBox.isChecked()
        if self.verbose_mode:
            self.doLog("Verbose mode on")
        else:
            self.doLog("Verbose mode off")

    def update_title(self):
        self.setWindowTitle(f"Mide [{self.opened_file}]")

    def doLog(self, text):
        self.ui.textEdit_4.append(text)

    def resizeEvent(self, e):
        self.on_resize(int(e.size().width()), int(e.size().height() - 50))

    def on_resize(self, width, height):
        print(f"Resize central widget to ({width}, {height})")
        self.ui.verticalWidget_4.setFixedSize(width, height)

    def on_action_openasm(self):
        print("Open asm file!")
    def on_actionOpen_File(self):
        print("Open File begin")
        fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self,
                                                            "Open C Source File", self.working_dir, "C Source File (*.c)")
        file = QtCore.QFile(fileName)
        QIODevice = QtCore.QIODevice
        if not file.open(QIODevice.ReadWrite | QIODevice.Text):
            self.doLog(f"Failed to open file {fileName}")
        else:
            self.opened_file = fileName
            text = file.readAll().toStdString()
            file.close()
            self.ui.textEdit.document().setPlainText(text)
            self.update_title()
            self.doLog(f"File opened: {fileName}")

    def on_actionSave(self):
        print("Save file begin.")
        file = QtCore.QFile(self.opened_file)

        if not file.open(QIODevice.WriteOnly | QIODevice.Text):
            self.doLog(f"Failed to save {self.opened_file}")
        else:
            text = self.ui.textEdit.document().toPlainText()
            data = QtCore.QByteArray.fromStdString(text)
            file.write(data)
            file.close()
            self.doLog(f"{self.opened_file} written.")

    def on_actionAbout(self):
        print("About begin")
        QtWidgets.QMessageBox.about(
            self, "Mide", "Mide is a minimal IDE for Minisys1A")

    def on_actionExit(self):
        print("Exit action begin")
        self.close()

    def ensure_output_folder(self):
        dir = os.path.join(self.working_dir, self.build_dir)
        qd = QtCore.QDir(dir)
        if not qd.exists():
            qd.mkdir(dir)
            self.doLog("mk build dir: {dir}")
        return dir

    def set_asm(self, text, clear=True):
        if clear:
            self.ui.plainTextEdit_3.clear()
        if type(text) == str:
            self.ui.plainTextEdit_3.setPlainText(text)
        elif type(text) == list:
            for l in text:
                self.ui.plainTextEdit_3.appendPlainText(l)

    def update_coe(self, dmem, prgmem):
        d = QtCore.QFile(dmem)
        p = QtCore.QFile(prgmem)
        if not d.open(QIODevice.ReadOnly | QIODevice.Text) or not p.open(QIODevice.ReadOnly | QIODevice.Text):
            self.doLog(
                f"Cannot open file coe file! check the status of assembler.")

        dmem = d.readAll().toStdString().splitlines()
        prgmem = p.readAll().toStdString().splitlines()
        self.ui.plainTextEdit.clear()
        self.ui.plainTextEdit_2.clear()

        for l in dmem:
            self.ui.plainTextEdit.appendPlainText(l)

        for l in prgmem:
            self.ui.plainTextEdit_2.appendPlainText(l)

    def on_asm(self):
        print("Assemble asm")
        dir = self.ensure_output_folder()
        temp_file_path = os.path.join(dir, "asm.s")
        out_file_path = os.path.join(dir, "uart_out.txt")
        dmem = os.path.join(dir, "dmem.coe")
        prgmem = os.path.join(dir, "prgmem.coe")
        temp_file = QtCore.QFile(temp_file_path)
        if not temp_file.open(QIODevice.WriteOnly | QIODevice.Text):
            self.doLog(
                f"Error creating temporary file {temp_file_path} for assamble.")
            return
        text = self.ui.plainTextEdit_3.toPlainText()
        temp_file.write(QtCore.QByteArray.fromStdString(text))
        temp_file.close()

        args = [self.mias_path, "-i", temp_file_path,
                "-o", out_file_path, "-c", "-f", "-d", os.path.join(self.working_dir, self.build_dir)]
        self.doLog(f"==================================\nMias assemble begin")
        if self.verbose_mode:
            args.append("-v")
            self.doLog(f"Mias assemble with: {args}")

        p = subprocess.Popen(args, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, shell=True)
        try:
            out, err = p.communicate(10.0)

            if p.returncode == 0:
                self.doLog("Mias assembler exit success!")
            elif p.returncode == 127:
                self.doLog("Mias assembler not found!")
                return
            else:
                self.doLog(
                    f"Mias assembler exit with code={p.returncode}, turn on verbose mode and check console log for more details")
            if self.verbose_mode:
                err = out + err
                err = err.decode('utf-8', 'ignore')
                err_l = err.splitlines()
                for l in err_l:
                    self.doLog(l)

        except OSError as ose:
            self.doLog(f"OsError: {ose}, please check the path for mias!")
        self.update_coe(dmem, prgmem)
        self.doLog("Mias assemble done.")

    def on_link(self):
        print("Linking")
        dir = self.ensure_output_folder()
        temp_file_path = os.path.join(dir, "asm.s")
        temp_file = QtCore.QFile(temp_file_path)
        if not QtCore.QFile.exists(self.bios_path):
            self.doLog(f"BIOS File not found \"{self.bios_path}\"");
        if not temp_file.open(QIODevice.WriteOnly | QIODevice.Text):
            self.doLog(
                f"Error creating temporary file {temp_file_path} for assamble.")
            return
        text = self.ui.plainTextEdit_3.toPlainText()
        temp_file.write(QtCore.QByteArray.fromStdString(text))
        temp_file.close()
        args = [self.linker_path, self.bios_path, temp_file_path, '-b']
        if self.ui.checkBox_2.isChecked():
            args.append('-s')
        if self.verbose_mode:
            args.append("-v")
            self.doLog(f"Linking with arguments: {args}")

        p = subprocess.Popen(args, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, shell=True)
        try:
            out, err = p.communicate(10.0)
            if p.returncode == 127:
                self.doLog(f"Linker path {self.linker_path} is not valid")
                return
            elif p.returncode != 0:
                self.doLog(f"Linker error! turn on verbose mode for more detailed logs.")
                return
            
            if self.verbose_mode:
                err = err.decode(errors='ignore')
                for line in err.splitlines():
                    self.doLog(line)
            out = out.decode('utf-8')
            self.set_asm(out.splitlines())

        except subprocess.TimeoutExpired:
            self.doLog("Linker timeout.")
        except OSError as e:
            self.doLog(f"Os Error: {e}")

        self.doLog("Milk done.")

    def on_compile(self):
        print("Compile c code")
        dir = self.ensure_output_folder()
        temp_file_path = os.path.join(dir, "_t.c")
        temp_file = QtCore.QFile(temp_file_path)
        if not temp_file.open(QIODevice.WriteOnly | QIODevice.Text):
            self.doLog(
                f"Error creating temporary file {temp_file_path} for compile")
            return
        text = self.ui.textEdit.document().toPlainText()
        data = QtCore.QByteArray.fromStdString(text)
        temp_file.write(data)
        temp_file.close()
        self.doLog(f"===================================\nBegin Mico Compile")
        self.doLog(f"Precompile Step: storing buffer to {temp_file_path}")
        args = [self.mico_path, "-i", temp_file_path,
                "-O" + str(self.ui.spinBox_2.value())]
        if self.verbose_mode:
            args.append("-v")
            self.doLog(f"Mico compile with: {args}")
        p = subprocess.Popen(args, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, shell=True)
        try:
            out, err = p.communicate(10.0)

            if p.returncode == 0:
                self.doLog("Mico compiler exit success!")
                out = out.decode('utf-8')
                self.set_asm(out.splitlines())
            elif p.returncode == 127:
                self.doLog("Mico compiler not found!")
            else:
                self.doLog(
                    f"Mico compiler exit with code={p.returncode}, turn on verbose mode and check console log for more details.")

            if self.verbose_mode:
                err = err.decode('utf-8', 'ignore')
                err_l = err.splitlines()
                for l in err_l:
                    self.doLog(l)

        except OSError as ose:
            self.doLog(f"OsError: {ose}, please check the path for mico!")

        self.doLog("Mico compile done.")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())
