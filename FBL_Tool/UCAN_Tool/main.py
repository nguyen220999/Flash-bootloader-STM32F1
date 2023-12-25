#----------------------------- Ask Menu implementation----------------------------------------
import sys
from PyQt5 import QtWidgets

import configurate

class Worker(QObject):
    finished = pyqtSignal()
    intReady = pyqtSignal(str)

    @pyqtSlot()
    def __init__(self):
        super(Worker, self).__init__()
        self.working = True

    def work(self):
        while self.working:
            if ser.isOpen():
                line = ser.readline().decode('utf-8')
            else:
                line = ''

            if line != '':
                print(line)
                time.sleep(0.1)
                self.intReady.emit(line)

        self.finished.emit()

class qt(QMainWindow):

    def __init__(self):

        QMainWindow.__init__(self)
        loadUi('qt_main.ui', self)

        self.thread = None
        self.worker = None
        self.connectBtn.clicked.connect(self.start_loop)
        self.pushBtnClicked = False
        self.CopyFlag = 0

    def loop_finished(self):
        print('Loop Finished')

    def start_loop(self):
        #Verify the correct COM Port
        try:
            
            global ser
            ser = serial.Serial(self.com_portText.currentText(), 115200, timeout=1)  # (ports[0], 115200)    #('COM1', 115200, timeout=1)
            
            self.statusText.setText("Connected")
            self.statusText.setStyleSheet('color: green')
        except:
            msgBox = QMessageBox()
            msgBox.setWindowTitle("COM Port Error!")
            msgBox.setIcon(QMessageBox.Warning)
            msgBox.setText("Selected COM port does not exist. Please verify the COM port Number.")
            msgBox.exec()
            self.statusText.setText("Not Connected")
            self.statusText.setStyleSheet('color: red')
            return



        self.worker = Worker()   # a new worker to perform those tasks
        self.thread = QThread()  # a new thread to run our background tasks in
        self.worker.moveToThread(self.thread)  # move the worker into the thread, do this first before connecting the signals

        self.thread.started.connect(self.worker.work) # begin our worker object's loop when the thread starts running

        self.worker.intReady.connect(self.onIntReady)

        self.disconnectBtn.clicked.connect(self.stop_loop)      # stop the loop on the stop button click

        self.worker.finished.connect(self.loop_finished)       # do something in the gui when the worker loop ends
        self.worker.finished.connect(self.thread.quit)         # tell the thread it's time to stop running
        self.worker.finished.connect(self.worker.deleteLater)  # have worker mark itself for deletion
        self.thread.finished.connect(self.thread.deleteLater)  # have thread mark itself for deletion
        self.thread.start()

    def stop_loop(self):
        self.worker.working = False
        self.statusText.setText("Not Connected")
        self.statusText.setStyleSheet('color: red')
        ser.close()

    def onIntReady(self, i):
        if i != '':
            self.textEdit_3.append("{}".format(i))
            print(i)
            if i.find('CINE Frames') != -1:
                #IQ file stored make beep
                winsound.Beep(1740, 800)

            if self.ck_AuSC.isChecked():
                #Auto Copy files
                if i.find('io copy j:') != -1:
                    #First autocopy condition
                    self.CopyFlag = 1

                if i.find('nvdbg>') != -1 and self.CopyFlag == 1:
                    count = self.sb_Num.value()
                    if count < 10:
                        numb = '0' + str(count)
                    else:
                        numb = str(count)

                    mytext = "io copy j:" + self.txtIQfile.toPlainText() + numb + ".iq " + self.cb_Drive.currentText() + "\n"
                    ser.write(mytext.encode())

                    #Check for final file copy
                    if count == self.sb_NumFin.value():
                        self.ck_AuSC.setCheckState(False)
                        self.sb_NumFin.setEnabled(False)
                        self.CopyFlag = 0
                        mytext = "\n"       #Clear buffer
                        ser.write(mytext.encode())
                    else:
                        self.sb_Num.setValue(count + 1)


    # TXT Save
    #def on_pushButton_5_clicked(self):
    #    if self.pushBtnClicked:
    #        self.pushBtnClicked = False
    #        return
#
    #    fileName = QFileDialog.getSaveFileName(self, 'Select location to Log', "", '*.txt')
    #    if not fileName:
    #        return
#
    #    with open(fileName[0], 'w') as f:
    #        my_text = self.textEdit_3.toPlainText()
    #        f.write(my_text)
#
    #    self.textEdit_3.append("Log Saved in :" + fileName[0] + "\r\n")
    #    self.pushBtnClicked = True

    #def on_pushButton_2_clicked(self):
    #    self.textEdit.setText('Stopped! Please click CONNECT...')

    #def on_pb_Clr_clicked(self):
    #    if self.pushBtnClicked:
    #        self.pushBtnClicked = False
    #        return
#
    #    #Clear serial screen
    #    self.textEdit_3.setText('')
    #    mytext = "\n"  # Clear buffer
    #    ser.write(mytext.encode())
#
    #    self.pushBtnClicked = True

    def on_connectBtn_clicked(self):
        if self.pushBtnClicked:
            self.pushBtnClicked = False
            return

        # Port Detection START
        self.start_loop()

        self.pushBtnClicked = True



name = input("Enter the Port Name of your device(Ex: COM3):")
ret = 0
ret=Serial_Port_Configuration(name)
if(ret < 0):
    decode_menu_command_code(0)
    


  
while True:
    print("\n +==========================================+")
    print(" |               Menu                       |")
    print(" |         STM32F4 BootLoader v1            |")
    print(" +==========================================+")

  
    
    print("\n   Which BL command do you want to send ??\n")
    print("   BL_GET_VER                            --> 1")
    print("   BL_GET_HLP                            --> 2")
    print("   BL_GET_CID                            --> 3")
    print("   BL_GET_RDP_STATUS                     --> 4")
    print("   BL_GO_TO_ADDR                         --> 5")
    print("   BL_FLASH_MASS_ERASE                   --> 6")
    print("   BL_FLASH_ERASE                        --> 7")
    print("   BL_MEM_WRITE                          --> 8")
    print("   BL_EN_R_W_PROTECT                     --> 9")
    print("   BL_MEM_READ                           --> 10")
    print("   BL_READ_SECTOR_P_STATUS               --> 11")
    print("   BL_OTP_READ                           --> 12")
    print("   BL_DIS_R_W_PROTECT                    --> 13")
    print("   BL_MY_NEW_COMMAND                     --> 14")
    print("   MENU_EXIT                             --> 0")

    #command_code = int(input("\n   Type the command code here :") )

    command_code = input("\n   Type the command code here :")

    if(not command_code.isdigit()):
        print("\n   Please Input valid code shown above")
    else:
        decode_menu_command_code(int(command_code))

    input("\n   Press any key to continue  :")
    purge_serial_port()




